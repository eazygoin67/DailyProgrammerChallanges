#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

int main( int argc, char **argv )
{
	// Check Command Arguments
	if ( argc < 2 )
	{
		fprintf( stderr, "Error: No Command Line Argument\n" );
		return 1;
	}

	// Open File (and Error Check)
	FILE *file = fopen( argv[1], "rb" );
	if ( file == NULL )
	{
		fprintf( stderr, "Unable to open file '%s' for reading\n", argv[1] );
		return 1;
	}

	// Declare Checking Variables
	char buffer[256];
	char *at;
	char current, last;

	// Read File Word by Word
	while( fscanf( file, "%s", buffer ) != EOF )
	{
		// Check for Alphabetic Order
		bool in_order = true;
		at = buffer;
		while( isalpha( *at ) )
		{
			last = tolower( *at );
			current = tolower( *(++at) );

			if ( !isalpha( current ) ) break;

			if ( current < last )
			{
				in_order = false;
				break;
			}
		}

		// Print Result
		fprintf( stdout, "%s %s\n",
					 buffer,
					 ( in_order ? "IN ORDER" : "NOT IN ORDER" ) );
	}

	// Close File
	fclose( file );

	// Return Success
	return 0;
}