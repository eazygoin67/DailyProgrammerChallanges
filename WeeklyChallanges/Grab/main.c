#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 2048

int main( int argc, char **argv )
{
	// Check for Command Line Arguments
	if ( argc < 3 )
	{
		fprintf( stderr, "Error: Incorrect number of arguments\n" );
		return 1;
	}

	// Declare Variables
	FILE 		*file;
	char 		*line;
	unsigned 	line_number = 1;

	// Open File
	file = fopen( argv[2], "rb" );
	if ( file == NULL )
	{
		fprintf( stderr, "Error: Could not open file '%s'\n", argv[2] );
		return 1;
	}

	// Allocate Line Memory
	line = (char *)malloc( MAX_LINE_LENGTH );
	if ( line == NULL )
	{
		fprintf( stderr, "Error: Could not allocate memory for line reading\n" );
		fclose( file );
		return 1;
	}

	// Read Per Line
	while( fgets( line, MAX_LINE_LENGTH, file ) != NULL )
	{
		if ( strstr( line, argv[1] ) != NULL )
			fprintf( stdout, " %u. %s\n", line_number, line );

		++line_number;
	}

	// Free Memory
	fclose( file );
	free( line );

	// Return Success
	return 0;
}