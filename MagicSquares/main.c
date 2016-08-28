#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static bool validate_square( const unsigned int *square,
							 const unsigned int dimensions )
{
	// Make Sure Input is Valid
	if ( square == NULL ||
		 dimensions < 3 )
	{
		return false;
	}

	// Get Magic Sum Constant
	const unsigned int MAGIC_CONSTANT = ( dimensions * (dimensions*dimensions + 1) ) / 2;

	// Validate
	unsigned int sum_row, sum_col;
	unsigned int sum_diag1 = 0, sum_diag2 = 0;
	for( unsigned int i = 0; i < dimensions; ++i )
	{
		// Reset Sum
		sum_row  = 0;
		sum_col  = 0;

		// Check Rows and Columns
		for( unsigned int j = 0; j < dimensions; ++j )
		{
			sum_row += square[ dimensions*i + j ];
			sum_col += square[ i + dimensions*j ];
		}
		if ( sum_row != MAGIC_CONSTANT ||
			 sum_col != MAGIC_CONSTANT )
		{
			return false;
		}

		// Collect Diagonal Data
		sum_diag1 += square[ dimensions*i + i ];
		sum_diag2 += square[ dimensions*i + (dimensions-1) - i ];
	}

	// Return Success Based on Diagonal Result
	return ( sum_diag1 == MAGIC_CONSTANT &&
		 	 sum_diag2 == MAGIC_CONSTANT );

}

static const unsigned int squares[4][9] = { {8, 1, 6, 3, 5, 7, 4, 9, 2},    //==> True
										 	{2, 7, 6, 9, 5, 1, 4, 3, 8},    //==> True
										 	{3, 5, 7, 8, 1, 6, 4, 9, 2},    //==> False
										 	{8, 1, 6, 7, 5, 3, 4, 9, 2} };  //==> False

int main( void )
{
	for( unsigned int i = 0; i < 4; ++i )
	{
		printf( "%s\n", 
				( validate_square(squares[i], 3) ? "True" : "False" )
			);
	}
	return 0;
}