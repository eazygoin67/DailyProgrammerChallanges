#include <stdio.h>
#include <stdlib.h>

#define CONSOLE_MAX 10

int main( int argc, char **argv )
{
	// Check Arguments
	if ( argc < 2 )
	{
		fprintf( stderr, "Error: Please enter multiplication number\n" );
		return 1;
	}

	// Get Multi Value from Command Line
	long multi = strtol( argv[1], NULL, 10 );
	if ( multi <= 1 )
	{
		fprintf( stderr, "Error: Please enter a value greater than 1\n" );
		return 1;
	}

	// Print Table to Console
	if ( multi <= CONSOLE_MAX )
	{
		for( long row = 1; row <= multi; ++row )
		{
			for( long col = 1; col <= multi; ++col )
			{
				fprintf( stdout, "%ld\t", col*row );
			}

			fprintf( stdout, "\n" );
		}
	}

	// Print to File if Big Table
	else
	{
		FILE *file = fopen( "Table.txt", "w" );
		if ( file == NULL )
		{
			fprintf( stderr, 
					 "Running Error: Tried to write to file, but could not open file for writing\n" );
			return 1;
		}

		fprintf( stdout, "Big Table\nWriting to File 'Table.txt'... " );
		for( long row = 1; row <= multi; ++row )
		{
			for( long col = 1; col <= multi; ++col )
			{
				fprintf( file, "%ld\t", col*row );
			}

			fprintf( file, "\n" );
		}
		fprintf( stdout, "Done!\n" );

		fclose( file );
	}

	// Return Success
	return 0;
}