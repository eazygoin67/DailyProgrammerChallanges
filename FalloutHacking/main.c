#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX_WORD_LENGTH 15
#define MAX_WORD_COUNT 15

int main( int argc, char ** argv )
{
	// Set Random Seed
	srand( time(NULL) );

	// Allocate Word Memory
	char current_word[128];
	char *word_list[MAX_WORD_COUNT];
	size_t mem_size = MAX_WORD_COUNT * (MAX_WORD_LENGTH+1);
	char* word_block = malloc( mem_size );
	memset( word_block, 0, mem_size );
	if ( word_block == NULL )
	{
		fprintf( stderr, "ERROR: Could not allocate word memory\n" );
		return 1;
	}
	for( unsigned i = 0; i < MAX_WORD_COUNT; ++i )
		word_list[i] = word_block + ( i * (MAX_WORD_LENGTH+1) );

	// Get Difficulty
	long difficulty = 0;
	while( difficulty < 1 || difficulty > 5 )
	{
		printf( "Please Enter Difficulty (1-5): " );
		scanf( "%s", current_word );
		difficulty = strtol( current_word, (char **)NULL, 10 );
	}

	// Set Word Lengths
	unsigned pass_length = ( (difficulty == 1) ? 4 + rand()%1 : 
							 (difficulty == 2) ? 6 + rand()%2 : 
							 (difficulty == 3) ? 9  + rand()%1: 
							 (difficulty == 4) ? 11 + rand()%1: 
							 /* else */			 13 + rand()%2 );

	// Print Newline
	printf( "\n" );

	// Read Words from Dictionary file
	FILE *file = fopen( "enable1.txt", "r" );
	if ( file == NULL )
	{
		fprintf( stderr, "ERROR: Could not open dictionary file\n" );
		return 1;
	}
	unsigned retrieve_count = 0;
	while( retrieve_count < MAX_WORD_COUNT )
	{
		char c = fscanf( file, "%s", current_word );
		if ( c == EOF )
		{
			// Return to Start of File
			fseek( file, 0, SEEK_SET );
		}
		else
		{
			// NOTE(troy): The chance value can be lowered to make more similar 
			//			   words more likely, or raised to make words more varied

			const unsigned length = strlen( current_word );
			const unsigned chance = 100;
			if ( length == pass_length && rand() % chance == 0 )
			{
				strcpy( word_list[retrieve_count], current_word );
				++retrieve_count;
			}
		}
	}
	fclose( file );

	// Choose Which Word (index) is Correct
	const unsigned winner = rand() % MAX_WORD_COUNT;

	// Debugging - Show Winner
	//printf( "Winner: %u (%s)\n\n", winner, word_list[winner] );

	// Print Word Selection
	for( unsigned i = 0; i < MAX_WORD_COUNT; ++i )
		printf( "%u. %s\n", (i+1), word_list[i] );

	// Print Newline
	printf( "\n" );

	// Loop through, letting user make word selections
	unsigned try_number = 1;
	const unsigned max_tries = 5;
	while( try_number <= max_tries )
	{
		// Get selection
		printf( "Tries Left: %u\n", max_tries+1-try_number );
		printf( "Please choose a word to try (1-15): " );
		scanf( "%s", current_word );
		long selection = strtol( current_word, (char **)NULL, 10 );

		// Check in bounds
		if ( selection < 1 || selection > MAX_WORD_COUNT )
			continue;

		// Check for Winner
		if ( selection-1 == winner )
		{
			printf( "Correct! You Win!\n" );
			break;
		}

		// Loop Through Words Checking 
		char *word = word_list[selection-1];
		char *win_word = word_list[winner];
		unsigned correct_count = 0;
		for( unsigned i = 0; i < pass_length; ++i )
		{
			correct_count += ( word[i] == win_word[i] );
		}
		printf( "Incorrect Selection - Correct Letters: %u\n\n", correct_count );

		++try_number;
	}

	// Losing Message
	if ( try_number > max_tries )
	{
		printf( "You have been locked out\nPlease connect your system administrator\n\n" );
	}

	// Free and Return Success
	free( word_block );
	return 0;
}
