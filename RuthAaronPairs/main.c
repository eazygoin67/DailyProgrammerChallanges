#include <stdio.h>

unsigned long sum_prime_factors( int value )
{
	unsigned long result = 0;
	
	for ( unsigned i = 2; i <= value; ++i )
	{
		if ( value % i == 0 )
		{
			result += i;
			while( value % i == 0 )
				value /= i;
		}
	}
	
	return result;
}

int main( int argc, char** argv )
{
	// TODO(troy): Fix type safety when reading input
	
	// Parse From Text File
	if ( argc > 1 )
	{
		FILE *file;
		file = fopen( argv[1], "r" );
		int c;
		
		if ( file == NULL )
		{
			printf( "File '%s' not found!\n", argv[1] );
			return 1;
		}
		
		while( 1 )
		{
			if ( feof( file ) )
				break;
			
			unsigned a, b;
			if ( fscanf( file, "%u, %u%c", &a, &b, &c ) == 2 )
			{
				int valid = ( b == a+1) &&
							( sum_prime_factors(a) == sum_prime_factors(b) );
				
				printf( "(%u, %u) %s VALID\n", a, b, ( valid ? "" : "NOT" ) );
			}
			else
			{
				printf( "File Syntax Error!\n" );
				if ( c == '\n' )
					fscanf( file, "%c", &c );
				else
				{
					while( c != '\n' )
						fscanf( file, "%c", &c );
				}

			}
		}
	}
	else
	
	// Parse from command
	{
		unsigned pairs_number;
		int c;
		
		printf( "How many pairs to check? " );
		scanf( "%u", &pairs_number );
		
		for ( unsigned i = 1; i <= pairs_number; ++i )
		{
			unsigned a, b;
			
			printf( "\nPair: " );
			if ( scanf( "%u, %u", &a, &b ) == 2 )
			{
				int valid = ( b == a+1) &&
							( sum_prime_factors(a) == sum_prime_factors(b) );
				
				printf( "(%u, %u) %s VALID\n", a, b, ( valid ? "" : "NOT" ) );
			}
			else
			{
				printf( "Syntax Error: please enter pairs in format 'num1, num2'\n" );
				scanf( "%c", &c );
				--i;
			}
		}
	}
	
	return 0;
}