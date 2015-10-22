#include <stdio.h>
#include <stdlib.h>

int main( int argc, char** argv )
{
	char bag[7] = { 'O', 'I', 'S', 'Z', 'L', 'J', 'T' }; //"OISZLJT";
	const unsigned short bag_size = 7;
	unsigned short bag_remaining = 7;

	// How many times are we outputting a bag value
	// Get command line argument, if it exists
	unsigned loop_max = 140;
	if ( argc > 1 )
	{
		char* end;
		loop_max = strtol( argv[1], &end, 10 );
		loop_max *= ( (loop_max < 0) ? -1 : 1 );
		loop_max += 140 * ( loop_max == 0 );
	}

	// Loop specified number of times
	for( unsigned i = 0; i < loop_max; ++i )
	{
		// Get and print value from remaing bag
		unsigned short index = rand() % bag_remaining;
		char letter = bag[index];
		printf( "%c", letter );

		// Decrement remaining size, and switch letter to back of array
		--bag_remaining;
		bag[index] = bag[bag_remaining];
		bag[bag_remaining] = letter;

		// Reset the bag if it's remaining size hits 0
		if ( bag_remaining == 0 )
		{
			printf( " " );
			bag_remaining = bag_size;
		}
	}

	// Newline
	printf( "\n" );

	// Return Success
	return 0;
}