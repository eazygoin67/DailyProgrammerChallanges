#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static long rotation_difference( long current, long target, long size, bool counter_clockwise )
{
	// If the next is the same as the current, it will require one full rotation
	if ( current == target )
		return size;

	// Counter Clockwise
	if ( counter_clockwise )
	{
		return ( current > target ? 
					current - target : 
					size - ( target - current ) );
	}

	// Clockwise
	else
	{
		return ( target > current ?
					target - current :
					size - ( current - target ) );
	}
}

int main( int argc, char **argv )
{
	// Check Arguments
	if ( argc < 5 )
	{
		fprintf( stderr, "Error: Incorrect Number of Arguments\n" );
		return 1;
	}

	// Declare Variables
	long dial_count;
	long code[3];
	long rotation_count = 0;

	// Convert Command Line Arguments
	dial_count = strtol( argv[1], NULL, 10 );
	for( long i = 0; i < 3; ++i )
		code[i] = strtol( argv[i+2], NULL, 10 );

	// Check Valid Values
	bool valid = true;
	if ( dial_count < 2 )
		valid = false;
	else
	for( long i = 0; i < 3; ++i )
	{
		if ( code[i] < 0 || code[i] > dial_count )
		{
			valid = false;
			break;
		}
	}

	// Print Error Message if Invalid Arguments
	if ( !valid )
	{
		fprintf( stderr, "Error: Invalid Command line Arguments: %ld, %ld, %ld, %ld\n",
				 dial_count, code[0], code[1], code[2] );
		return 1;
	}

	// Find Rotation Count
	rotation_count += dial_count * 2;
	rotation_count += rotation_difference( 0, code[0], dial_count, false );
	rotation_count += dial_count;
	rotation_count += rotation_difference( code[0], code[1], dial_count, true );
	rotation_count += rotation_difference( code[1], code[2], dial_count, false );

	// Print Rotation Count
	fprintf( stdout, "It will take %ld rotations to open the lock\n", rotation_count );

	// Return Success
	return 0;
}