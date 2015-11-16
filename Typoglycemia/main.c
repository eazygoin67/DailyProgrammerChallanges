#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

int main( int argc, char **argv )
{
	// Check File
	if ( argc < 2 )
	{
		fprintf( stderr, "Error: Please pass input file name\n" );
		return 1;
	}

	FILE *file = fopen( argv[1], "rb" );
	if ( file == NULL )
	{
		fprintf( stderr, "Error: Could not open input file: '%s'\n", argv[1] );
		return 1;
	}

	// Set Random Seed
	srand( time(NULL) );

	// Get Memory Size of File
	fseek( file, 0, SEEK_END );
	size_t mem_size = ftell( file );
	fseek( file, 0, SEEK_SET );

	// Allocate Memory and Read Entire File
	char *input = (char *)malloc( mem_size+1 );
	if ( input == NULL )
	{
		fprintf( stderr, 
				 "Error: Unable to allocate memory for input. Memory amount %u bytes\n", 
				 mem_size+1 );
		fclose( file );
		return 1;
	}
	fread( input, mem_size, 1, file );
	input[mem_size] = 0; // Null-Terminate
	printf( "File Read: %u bytes used\n", mem_size+1 );
	fclose( file );

	// Reopen File as Output File
	file = fopen( "output.txt", "w" );
	if ( file == NULL )
	{
		fprintf( stderr, "Error: Could not open/create output file: 'output.txt'\n" );
		free( input );
		return 1;
	}

	// Read through Input File Scanning for words (alpha characters only)
	char *at = input;
	char word[256];
	while( *at )
	{
		// Read through non-alpha characters, writing to file
		if ( !isalpha(*at) )
		{
			fprintf( file, "%c", *at );
			++at;
			continue;
		}

		// Read Current Word
		unsigned len = 0;
		while( isalpha(*at) )
		{
			word[len] = *at;

			++len;
			++at;
		}
		word[len] = '\0'; // Add Null-Terminator

		// Jumble Words
		if ( len > 3 )
		{
			const unsigned chance = 2;
			char temp;
			for( unsigned i = 1; i < len-2; ++i )
			{
				if ( rand() % chance == 0 ||
					 i == 1 )					// Always make a swap on the first letter
				{
					temp = word[i];
					word[i] = word[i+1];
					word[i+1] = temp;
				}
			}
		}

		// Write word to file
		fprintf( file, "%s", word );
	}

	// Free Memory and Return Success
	fclose( file );
	free( input );
	return 0;
}