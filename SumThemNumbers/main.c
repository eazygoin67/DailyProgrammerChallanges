#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main( int argc, char **argv )
{
	// Check for Argument
	if ( argc < 2 )
	{
		fprintf( stderr, "Error: Please pass number as number to root as command argument\n" );
		return 1;
	}

	// Find command length
	size_t start_length = strlen(argv[1]);

	// Check all values are positive integers
	for( unsigned i = 0; i < start_length; ++i )
	{
		if ( !isdigit( argv[1][i] ) )
		{
			fprintf( stderr, "Please make sure command line argument is a positive integer\n" );
			return 1;
		}
	}

	// Allocate String Memory
	char *test_string = (char *) malloc( start_length+1 );
	if ( test_string == NULL )
	{
		fprintf( stderr, "Error: Could not allocate string memory\n" );
		return 1;
	}

	// Declare Test Value(s)
	unsigned test_value;
	char temp_string[2]; temp_string[1] = '\0';

	// Start with passed in argument
	strcpy( test_string, argv[1] );

	// Loop until we have a root value
	do
	{
		// Reset Test Value and get test string's length
		size_t test_length = strlen( test_string );
		test_value = 0;

		// Add each individual digit to the test digit
		for( unsigned i = 0; i < test_length; ++i )
		{
			temp_string[0] = test_string[i];
			test_value += (long) strtol( temp_string, 0, 10 );

			// Extra output
			printf( "%s%c%s", ( i > 0 ? " + " : "" ),
							  ( test_string[i] ),
							  ( i == test_length-1 ? " = " : "" ) 
				  );
		}

		// Finish Extra Output
		printf( "%u\n", test_value );

		// Set String to new test value
		sprintf( test_string, "%u", test_value );
	}
	while( test_value > 9 );

	// Print Root Value
	printf( "\nRoot value of %s: %u\n", argv[1], test_value );

	// Free Memory and Return Success
	free( test_string );
	return 0;
}