#include <stdio.h>
#include <stdlib.h>

int main( int argc, char** argv )
{
	char bag[7] = { 'O', 'I', 'S', 'Z', 'L', 'J', 'T' }; //"OISZLJT";
	unsigned short bag_size = 7;
	unsigned short bag_remaining = 7;

	unsigned loop_max = 140;
	if ( argc > 1 )
	{
		char* end;
		loop_max = strtol( argv[1], &end, 10 );
		loop_max *= ( (loop_max < 0) ? -1 : 1 );
		loop_max += 140 * ( loop_max == 0 );
	}

	for( unsigned i = 0; i < loop_max; ++i )
	{
		unsigned short index = rand() % bag_remaining;
		char letter = bag[index];
		printf( "%c", letter );

		--bag_remaining;
		bag[index] = bag[bag_remaining];
		bag[bag_remaining] = letter;

		if ( bag_remaining == 0 )
		{
			printf( " " );
			bag_remaining = bag_size;
		}
	}

	printf( "\n" );

	return 0;
}