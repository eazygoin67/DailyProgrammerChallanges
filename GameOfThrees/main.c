#include <stdio.h>
#include <stdlib.h>

int main( int argc, char **argv )
{
	if ( argc < 2 )
	{
		fprintf( stderr, "Error: Please pass starting number as command argument\n" );
		return 1;
	}

	long value, mod, action;
	value = strtol( argv[1], NULL, 10 );

	if ( value <= 1 )
	{
		fprintf( stderr, "Error: Start value must be integer larger than 1\n" );
		return 1;
	}

	do
	{
		mod = value % 3;
		action = 0 + 
				 (-1) * ( mod == 1 ) + 
				 (1) * ( mod == 2 );

		printf( "%ld %ld \n", value, action );

		value += action;
		value /= 3;
	}
	while( value > 1 );

	printf( "\n%ld\n", value );

	return 0;
}