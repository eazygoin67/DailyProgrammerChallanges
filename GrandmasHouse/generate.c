#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static inline double random_double( double min_value, double max_value )
{
	return (double)(min_value + ( rand() / (RAND_MAX / (max_value-min_value)) )); 
}

int main( int argc, char **argv )
{
	srand( (unsigned)time(0) );

	int point_count;

	if ( argc < 2 )
	{
		fprintf( stderr, "ERROR: Please pass number of points to generate" );
		return 1;
	}
	else
	{
		char* end;
		point_count = strtol( argv[1], &end, 10 );
		point_count *= ( (point_count < 0) ? -1 : 1 );
		point_count += 40 * ( point_count == 0 );
	}

	char* filename = "test.txt";
	FILE *file;
	if ( argc > 2 )
		file = fopen( argv[2], "w" );
	else
		file = fopen( filename, "w" );

	if ( file == NULL )
	{
		fprintf( stderr, "ERROR: Could not open the file named: '%s' for writing\n",
				(argc > 2 ? argv[2] : filename) );
		return 1;
	}

	fprintf( file, "%i\n", point_count );
	fprintf( stdout, "Printing %i values to '%s'\n", 
			 point_count,
			 (argc > 2 ? argv[2] : filename) );

	double x, y;
	const double min_value = 0.00000001;
	const double max_value = 9.99999999;
	for( unsigned i = 0; i < point_count; ++i )
	{
		x = random_double( min_value, max_value );
		y = random_double( min_value, max_value );
		fprintf( file, "(%lf, %lf)\n", x, y );
	}

	fclose( file );
}