#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

bool read_date( const char *input )
{
	const char *at = input;
	char *next;
	long date_value[3];
	short i = 0;

	while( *at != '\0' &&
		   *at != '\n' &&
		   *at != '\r' && 
		   i < 3 )
	{
		if ( isdigit(*at) )
		{
			date_value[i++] = strtol( at, &next, 10 );
			at = next;
		}
		else
		{
			++(at);
		}
	}

	if ( i >= 3 )
	{
		// M D Y (Shorthand Year)
		if ( date_value[0] < 100 && date_value[1] < 100 && date_value[2] < 100 )
		{
			fprintf( stdout, "%s%ld-%s%ld-%s%ld\n", 
				 ( date_value[2] > 20 ? "19" : "20" ), date_value[2], 
				 ( date_value[0] < 10 ? "0" : "" ), date_value[0], 
				 ( date_value[1] < 10 ? "0" : "" ), date_value[1] );
			return true;
		}
		else

		// Y M D
		if ( date_value[0] >= 1000 )
		{
			fprintf( stdout, "%ld-%s%ld-%s%ld\n", 
				 date_value[0], 
				 ( date_value[1] < 10 ? "0" : "" ), date_value[1], 
				 ( date_value[2] < 10 ? "0" : "" ), date_value[2] );
			return true;
		}

		// M D Y
		else
		{
			fprintf( stdout, "%ld-%s%ld-%s%ld\n", 
				 date_value[2], 
				 ( date_value[0] < 10 ? "0" : "" ), date_value[0], 
				 ( date_value[1] < 10 ? "0" : "" ), date_value[1] );
			return true;
		}
	}
	else
	{
		return false;
	}
}

int main( int argc, char **argv )
{
	// Return Result
	int result = 0;

	// Check for Command Argument
	if ( argc < 2 )
	{
		fprintf( stderr, "Error: No Input File!\n" );
		return 1;
	}

	// Open Input File
	FILE *file = fopen( argv[1], "r" );
	if ( file == NULL )
	{
		fprintf( stderr, "Error: Cannot open file %s\n", argv[1] );
		return 1;
	}

	// Declare Buffer for Line
	char line[128];
	while( fgets( line, 128, file ) )
	{
		if ( !read_date( line ) )
		{
			result = 1;
			fprintf( stderr, "Error: Could not parse line:\n%s", line );
			break;
		}
	}

	// Close Input File
	fclose( file );

	// Return Success
	return result;
}