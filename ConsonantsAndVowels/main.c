#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

int main( int argc, char **argv )
{
	// Check for Command Line Argument
	if ( argc < 2 )
	{
		fprintf( stderr, "ERROR: Please pass word structure as command line argument.\n" );
		return 1;
	}

	// Seed Pseudo-Random Number
	srand( time(0) );

	// Allocate New Word Memory
	const size_t input_size = strlen( argv[1] );
	char *output = (char *)malloc( input_size + 1 );
	output[input_size] = 0; // Null-Terminator

	// Define vowel and consonant (with sizes)
	const char *consonants = "bcdfghjklmnpqrstvwxyz";
	const size_t consonant_size = 21;
	const char *vowels = "aeiou";
	const size_t vowel_size = 5;

	// Construct New Word
	for( size_t i = 0; i < input_size; ++i )
	{
		// Current Input Character
		char character = argv[1][i];

		// Consonant
		if ( character == 'c' || character == 'C' )
		{
			size_t index = rand() % consonant_size;
			output[i] = ( isupper(character) ? toupper(consonants[index]) : consonants[index] );
		}
		else

		// Vowel
		if ( character == 'v' || character == 'V' )
		{
			size_t index = rand() % vowel_size;
			output[i] = ( isupper(character) ? toupper(vowels[index]) : vowels[index] );
		}

		// Error
		else
		{
			fprintf( stderr, "ERROR: Please enter input consisting of only 'c' and 'v' characters.\n" );
			free( output );
			return 1;
		}
	}

	// Print New Word
	fprintf( stdout, "New Word: %s\n", output );

	// Free Memory 
	free( output );

	// Return Success
	return 0;
}
