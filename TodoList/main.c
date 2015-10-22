#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef enum
{
	token_type_unknown,
	token_type_null,

	token_type_identifier,
	token_type_string,
	token_type_open_paren,
	token_type_close_paren,
	token_type_semicolon

} token_type_t;

typedef struct Token
{
	char 			*start;
	size_t 			length;
	token_type_t 	type;
} token_t;

static inline void eat_whitespace( char **at )
{
	while( 	*at[0] == ' '  || 
			*at[0] == '\t' ||
			*at[0] == '\r' || 
			*at[0] == '\n' )
	{
		++(*at);
	}
}

static inline bool is_identifier_character( char c )
{

	return ( 
		(c >= 'a' && c <='z') ||
		(c >= 'A' && c <='Z') ||
		(c >= '0' && c <='9') ||
		(c == '_')
	);
}

static token_t get_token( char **at )
{
	token_t result = {};
	result.start = *at;
	result.length = 0;

	// Null Terminator
	if ( *at[0] == '\0' ) { result.type = token_type_null; result.length = 0; }
	else
	// Open Paren
	if ( *at[0] == '(' ) { result.type = token_type_open_paren; result.length = 1; ++(*at); }
	else
	// Close Paren
	if ( *at[0] == ')' ) { result.type = token_type_close_paren; result.length = 1; ++(*at); }
	else
	// Semicolon
	if ( *at[0] == ';' ) { result.type = token_type_semicolon; result.length = 1; ++(*at); }
	else
	// String
	if ( *at[0] == '\'')
	{
		result.type = token_type_string;
		++(*at);
		++(result.start);
		while( **at != '\'' )
		{
			if ( *at == NULL )
			{
				result.type = token_type_unknown;
				result.length = 0;
				break;
			}

			++(*at);
			++result.length;
		}

		if ( **at == '\'' )
			++(*at);
	}
	// Identifier
	else
	if ( is_identifier_character(*at[0]) )
	{
		result.type = token_type_identifier;
		do
		{
			++(*at);
			++result.length;
		}
		while( is_identifier_character(*at[0]) );
	}
	else
	{
		result.type = token_type_unknown;
	}

	return result;
}

static inline bool require_token( char **at, token_type_t type )
{
	return ( get_token( at ).type == type );
}

static inline bool identifier_equals( token_t token, const char *value )
{
	const size_t value_length = strlen( value );
	if ( value_length != token.length )
		return false;

	for( unsigned i = 0; i < value_length; ++i )
	{
		if ( token.start[i] != value[i] )
			return false;
	}

	return true;
}

static void function_add_item( char **at )
{
	eat_whitespace( at );
	if ( !require_token( at, token_type_open_paren ) )
	{
		fprintf( stderr, "SYNTAX ERROR: Expected character (\n" );
		return;
	}

	eat_whitespace( at );
	char message[128];
	token_t mes_token = get_token( at );
	if ( mes_token.type != token_type_string )
	{
		fprintf( stderr, "SYNTAX ERROR: Expected string: message\n" );
		return;
	}
	// NOTE(troy): This currently only supports todo messages with 
	// 			   a maximum length of 128
	size_t len = ( mes_token.length >= 128 ? 127 : mes_token.length );
	memcpy( message, mes_token.start, len );
	message[len] = 0;

	eat_whitespace( at );
	if ( !require_token( at, token_type_close_paren ) )
	{
		fprintf( stderr, "SYNTAX ERROR: Expected character )\n" );
		return;
	}

	eat_whitespace( at );
	if ( !require_token( at, token_type_semicolon ) )
	{
		fprintf( stderr, "SYNTAX ERROR: Expected character ;\n" );
		return;
	}

	const char *todo_file_name = "todo.txt";
	FILE *todo = fopen( todo_file_name, "a" );
	if ( todo == NULL )
	{
		fprintf( stderr, "RUN TIME ERROR: Could not open file '%s' to add TODO item\n",
				 todo_file_name );
		return;
	}

	fprintf( todo, "%s\n", message );

	fclose( todo );
}

static void function_delete_item( char **at )
{
	eat_whitespace( at );
	if ( !require_token( at, token_type_open_paren ) )
	{
		fprintf( stderr, "SYNTAX ERROR: Expected character (\n" );
		return;
	}

	eat_whitespace( at );
	char message[128];
	token_t mes_token = get_token( at );
	if ( mes_token.type != token_type_string )
	{
		fprintf( stderr, "SYNTAX ERROR: Expected string: message\n" );
		return;
	}
	// NOTE(troy): This currently only supports todo messages with 
	// 			   a maximum length of 128
	size_t len = ( mes_token.length >= 128 ? 127 : mes_token.length );
	memcpy( message, mes_token.start, len );
	message[len] = 0;

	eat_whitespace( at );
	if ( !require_token( at, token_type_close_paren ) )
	{
		fprintf( stderr, "SYNTAX ERROR: Expected character )\n" );
		return;
	}

	eat_whitespace( at );
	if ( !require_token( at, token_type_semicolon ) )
	{
		fprintf( stderr, "SYNTAX ERROR: Expected character ;\n" );
		return;
	}

	const char *todo_file_name = "todo.txt";
	FILE *todo = fopen( todo_file_name, "rb" );
	if ( todo == NULL )
	{
		fprintf( stderr, "RUN TIME ERROR: Could not open file '%s' to view TODO items\n",
				 todo_file_name );
		return;
	}

	// Get File Size
	fseek( todo, 0, SEEK_END );
	size_t todo_size = ftell( todo );
	fseek( todo, 0, SEEK_SET );

	char *read = (char *)malloc( todo_size + 1 ); 
	if ( read == 0 )
	{
		fprintf( stderr, "RUN TIME ERROR: Could not allocate memory to read TODO items\n" );
		fclose( todo );
		return;
	}

	fread( read, todo_size, 1, todo );
	read[todo_size] = 0;
	fclose( todo );

	// Find SubString
	char *sub = strstr( read, message );

	if ( sub )
	{
		// Check that sub points to a complete todo item, not just part of it
		char *sub_end = sub + len;
		if ( *sub_end == '\n' ||
			 *sub_end == '\r' ||
			 *sub_end == '\0'  )
		{
			eat_whitespace( &sub_end );
			while( *sub_end )
			{
				*sub = *sub_end;
				++sub;
				++sub_end;
			}

			*sub = '\0';

			todo = fopen( todo_file_name, "w" );
			if ( todo == NULL )
			{
				fprintf( stderr, "RUN TIME ERROR: Could not open file '%s' to view TODO items\n",
						 todo_file_name );
			}
			else
			{
				fprintf( todo, "%s", read );
				fclose( todo );
			}
		}	
	}

	free( read );
}

static void function_view_list( char **at )
{
	// Check Syntax
	eat_whitespace( at );
	if ( !require_token( at, token_type_open_paren ) )
	{
		fprintf( stderr, "SYNTAX ERROR: Expected character (\n" );
		return;
	}
	eat_whitespace( at );
	if ( !require_token( at, token_type_close_paren ) )
	{
		fprintf( stderr, "SYNTAX ERROR: Expected character )\n" );
		return;
	}
	eat_whitespace( at );
	if ( !require_token( at, token_type_semicolon ) )
	{
		fprintf( stderr, "SYNTAX ERROR: Expected character ;\n" );
		return;
	}

	const char *todo_file_name = "todo.txt";
	FILE *todo = fopen( todo_file_name, "rb" );
	if ( todo == NULL )
	{
		fprintf( stderr, "RUN TIME ERROR: Could not open file '%s' to view TODO items\n",
				 todo_file_name );
		return;
	}

	// Get File Size
	fseek( todo, 0, SEEK_END );
	size_t todo_size = ftell( todo );
	fseek( todo, 0, SEEK_SET );

	char *read = (char *)malloc( todo_size + 1 ); 
	if ( read == 0 )
	{
		fprintf( stderr, "RUN TIME ERROR: Could not allocate memory to read TODO items\n" );
		fclose( todo );
		return;
	}

	fread( read, todo_size, 1, todo );
	read[todo_size] = 0;

	printf( "%s\n", read );
	
	free( read );
	fclose( todo );
}

static void function_clear_list( char **at )
{
	// Check Syntax
	eat_whitespace( at );
	if ( !require_token( at, token_type_open_paren ) )
	{
		fprintf( stderr, "SYNTAX ERROR: Expected character (\n" );
		return;
	}
	eat_whitespace( at );
	if ( !require_token( at, token_type_close_paren ) )
	{
		fprintf( stderr, "SYNTAX ERROR: Expected character )\n" );
		return;
	}
	eat_whitespace( at );
	if ( !require_token( at, token_type_semicolon ) )
	{
		fprintf( stderr, "SYNTAX ERROR: Expected character ;\n" );
		return;
	}

	const char *todo_file_name = "todo.txt";
	FILE *todo = fopen( todo_file_name, "w" );
	if ( todo )
		fclose( todo );
}

static bool parse_command( char *command )
{
	char *at = command;

	while( *at )
	{
		eat_whitespace( &at );
		token_t token = get_token( &at );

		switch( token.type )
		{
			case token_type_identifier: {
				if ( identifier_equals( token, "addItem" ) )
					function_add_item( &at );
				else
				if ( identifier_equals( token, "deleteItem" ) )
					function_delete_item( &at );
				else
				if ( identifier_equals( token, "viewList" ) )
					function_view_list( &at );
				else
				if ( identifier_equals( token, "clearList" ) )
					function_clear_list( &at );
				else
				{
					char token_name[128];
					memset( token_name, 0, 128 );
					memcpy( token_name, token.start, (token.length < 128 ? token.length : 127) );
					fprintf( stderr, 
							 "ERROR: Unknown identifier: %s\nSkipping...\n",
							 token_name );
				}
			} break;

			case token_type_unknown: {
				fprintf( stderr, 
						 "\nSYNTAX ERROR: Unknown token on line:\n\t%sAborting...",
						 command );
				return false;
			} break;

			default: {
			} break;
		}
	}

	// Return Success
	return true;
}

int main( int argc, char **argv )
{
	if ( argc < 2 )
	{
		fprintf( stderr,  "ERROR: No Input File Found!\n");
		return 1;
	}

	FILE *file = fopen( argv[1], "r" );

	if ( file == NULL )
	{
		fprintf( stderr, "ERROR: Could not load input file '%s'\n", argv[1] );
		return 1;
	}

	char line[1024];
	bool result = true;
	while( fgets( line, sizeof(line), file ) != NULL )
	{
		result = parse_command( line );
		if ( !result )
			break;
	}

	fclose(file);

	return !result;
}