#include <stdio.h>
#include <stdlib.h>

int main( int argc, char **argv )
{
  if ( argc < 3 )
  {
    fprintf( stderr, "Error: Invalid Command Arguments\n" );
    return 1;
  }

  long person_count = strtol( argv[1], 0, 10 );
  long plant_start_count = strtol( argv[2], 0, 10 );

  if ( person_count <= 0 || plant_start_count <=0 )
  {
    fprintf( stderr, "Error: Invalid number of people or plants\n" );
    return 1;
  }

  long plants = plant_start_count;
  long fruits = 0;
  unsigned week = 1;

  while( fruits < person_count )
  {
    fruits += plants;
    plants += fruits;
    ++week;
  }

  fprintf( stdout, "It would take %u week(s) to feed %ld people with %ld starting plants.\n",
           week, person_count, plant_start_count );

  return 0;
}
