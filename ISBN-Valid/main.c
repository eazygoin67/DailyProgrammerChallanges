#include <stdio.h>
#include <stdlib.h>

static inline int is_number( char value )
{
	return ( value >= '0' && value <= '9' );
}

int main( int argc, char **argv )
{
	if ( argc < 2 )
	{
		fprintf( stderr, "ERROR: Please enter the ISBN code as a command argument\n" );
		return 1;
	}

	int isbn_values[10];
	int count = 0;
	char current[2] = { 0, 0 };
	char* at = argv[1];

	while( *at )
	{
		if ( !is_number(at[0]) && at[0] != 'x' && at[0] != 'X' )
		{
			fprintf( stderr, "ERROR: %s is not a proper ISBN value\n", argv[1] );
			return 1;
		}

		if ( count < 10 )
		{
			current[0] = at[0];
			isbn_values[count] = ( current[0] == 'x' || current[0] == 'X' ?
								   10 :
								   strtol( current, 0, 10 ) );
		}

		++count;
		++at;
	}

	if ( count != 10)
	{
		fprintf( stderr, "ERROR: %s is not a proper ISBN value\n", argv[1] );
		return 1;
	}

	unsigned short checksum;
	for( unsigned i = 0; i < 10; ++i )
	{
		checksum += (10-i) * isbn_values[i];
	}

	printf( "%s is a %s ISBN Number\n", 
			argv[1],
			(checksum % 11 == 0 ? "valid" : "invalid") );

	return 0;
}