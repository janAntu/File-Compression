/*
 * time: testtimeCompare
 * Author: Richard Andrus
 * Userid: cs30foy
 * Description: Unit test program to test the function timeCompare()
 * Date: Nov 8 2018
 * Sources of Help: tutorialspoint.com
 */

#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "test.h"    /* For TEST() macro and stdio.h */
#include "pa4.h"

/*
 * Unit Test for timeCompare.s
 *
 * long timeCompare( char * src );
 *
 */
void testtimeCompare() {
  
  // Create two  fileInfo structs to compare
  struct fileInfo *file1 = malloc(sizeof(struct fileInfo));
  struct fileInfo *file2 = malloc(sizeof(struct fileInfo));
  struct time_t *time1 = malloc(sizeof(struct time_t));
  struct time_t *time2 = malloc(sizeof(struct time_t));
  
  /* Test equal times */
  file1->time = time(NULL);
  file2->time = time(NULL);
  TEST( timeCompare(&file1, &file2) == 0 );
  
  /* Test where p1 comes before p2 */
  file1->time++;
  TEST( timeCompare(&file1, &file2) == -1 );
  
  /* Test where p2 comes before p1 */
  file1->time--;
  file2->time++;
  TEST( timeCompare(&file1, &file2) == 1 );

  // Free allocated memory
  free(file1);
  free(file2);

}

int main() {
  fprintf( stderr, "Testing timeCompare...\n\n" );
  testtimeCompare();
  fprintf( stderr, "\nDone running tests.\n" );
  return 0;
}
