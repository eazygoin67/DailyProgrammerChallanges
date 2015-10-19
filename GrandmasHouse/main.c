#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <SDL.h>

#define SCREEN_WIDTH 	640
#define SCREEN_HEIGHT 	480
#define MAX_PRINT		40

/**
	TODO_NEXT:
	 - Draw Points
**/

typedef struct Point 
{
	double x;
	double y;
} point_t;

static inline double point_distance_sqaure( const point_t p1, 
											const point_t p2 )
{
	const double xx = p2.x - p1.x;
	const double yy = p2.y - p1.y;

	return ( xx*xx + yy*yy );
}

int show_SDL_output();
void print_points( const point_t const *points, const unsigned point_count );
void find_closest_points( const point_t const *points, 
						  const unsigned point_count,
						  point_t *p1, point_t *p2 );

int main( int argc, char *argv[] )
{
	// Start SDL
	if ( SDL_Init(SDL_INIT_EVERYTHING) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		return 1;
	}

	int result = 1;

	point_t *points = NULL;
	unsigned point_count;
	size_t array_size;

	// Parse From Text File
	if ( argc > 1 )
	{
		FILE *file;
		file = fopen( argv[1], "r" );
		char buffer[256];
		
		if ( file == NULL )
		{
			printf( "Unable to open file '%s'\n", argv[1] );
			return 1;
		}
		
		if ( feof( file ) )
		{
			printf( "Empty File!" );
			fclose( file );
			return 1;
		}

		// SDL to time
		clock_t end_time;
		clock_t start_time = clock();

		// Get Size Info and Allocate Memory
		fgets( buffer, 256, file );
		sscanf( buffer, "%u", &point_count );
		array_size = point_count * sizeof( point_t );
		printf( "Allocating %u bytes for point array (%u per point)\n", 
				array_size,
				sizeof( point_t ) );
		points = malloc( array_size );

		// Read Points
		for( unsigned i = 0; i < point_count; ++i )
		{
			//if ( feof( file ) )
			if ( !fgets( buffer, 256, file ) )
			{
				point_count = i;
				break;
			}

			//printf( "%s", buffer );
			int read = sscanf( buffer, "(%lf, %lf)", &(points[i].x), &(points[i].y) );
			//printf( "%i doubles read\n", read );
		}

		// Print file load time
		end_time = clock();
		printf( "\n%f seconds taken to load file\n", ((float)(end_time-start_time))/CLOCKS_PER_SEC );
		start_time = end_time;

		// Close File 
		fclose( file );

		// Debug - Print out Points
		if ( point_count <= MAX_PRINT )
			print_points( points, point_count );
		else
			printf( "%u Points\nWay to many values to print!\n", point_count );

		// Find and Print Closest Points
		point_t close1, close2;
		find_closest_points( points, point_count, &close1, &close2 );
		printf( "Closest Points: (%lf,%lf) and (%lf,%lf)\n",
				close1.x, close1.y, close2.x, close2.y );

		end_time = clock();
		printf( "\n%f seconds finding closest\n", ((float)(end_time-start_time))/CLOCKS_PER_SEC );

		// Show GUI Solution
		result = show_SDL_output();
	}
	else
	{
		printf( "Please pass a text file argument when running program!\n" );
		return 1;
	}

	// Free Memory
	if ( points != NULL )
		free( points );

	// Free SDL
	SDL_Quit();

	// Return Success
	return result;
}

int show_SDL_output()
{
	// NOTE(troy): Assumes SDL is already initialise

	// Create Window and Renderer
	SDL_Window 		*window = SDL_CreateWindow( "Where Does Grandmas House Go?", 
												SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
												SCREEN_WIDTH, SCREEN_HEIGHT, 0 );
	SDL_Renderer 	*renderer = SDL_CreateRenderer( window, -1, 
												  	SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );

	// Main Execution Loop
	bool running = true;
	while( running )
	{
		// Handle Events
		SDL_Event event;
		while( SDL_PollEvent( &event ) )
		{
			if (event.type == SDL_QUIT)
				running = false;
		}

		// Draw Program
		SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
		SDL_RenderClear( renderer );

		// TODO(troy): Draw Points Here!

		SDL_RenderPresent( renderer );
	}

	// Return Success
	return 0;
}

void print_points( const point_t const *points, const unsigned point_count )
{
	printf( "Point List (%u points):\n", point_count );

	for( unsigned i = 0; i < point_count; ++i )
		printf( "(%lf, %lf)\n", points[i].x, points[i].y );

	printf( "\n" );
}

void find_closest_points( const point_t const *points, 
						  const unsigned point_count,
						  point_t *p1, point_t *p2 )
{
	if ( point_count <= 1 )
		return;

	point_t res1 = points[0];
	point_t res2 = points[1];
	double 	dist;
	double 	best_dist = point_distance_sqaure( res1, res2 );

	unsigned jstart = 1;

	for( unsigned i = 0; i < point_count-1; ++i )
	{
		for( unsigned j = jstart; j < point_count; ++j )
		{
			dist = point_distance_sqaure( points[i], points[j] );

			// For Debugging Purposes
			/*printf( "(%lf,%lf) & (%lf,%lf)\nDist: %lf\nBest Dist: %lf\n", 
					points[i].x, points[i].y, points[j].x, points[j].y,
					dist, best_dist ); */

			if ( dist < best_dist )
			{
				res1 = points[i];
				res2 = points[j];
				best_dist = dist;
			}
		}
		++jstart;
	}

	*p1 = res1;
	*p2 = res2;
}