/*
 * time: testtimeCompareRev
 * Author: Richard Andrus
 * Userid: cs30foy
 * Description: Unit test program to test the function timeCompareRev()
 * Date: Nov 8 2018
 * Sources of Help: tutorialspoint.com
 */

#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "test.h"    /* For TEST() macro and stdio.h */
#include "pa4.h"

/*
 * Unit Test for timeCompareRev.s
 *
 * long timeCompareRev( char * src );
 *
 */
void testtimeCompareRev() {
  
  // Create two  fileInfo structs to compare
  struct fileInfo *file1 = malloc(sizeof(struct fileInfo));
  struct fileInfo *file2 = malloc(sizeof(struct fileInfo));
  
  /* Test equal times */
  file1->time = 10;
  file2->time = 10;
  TEST( timeCompareRev(&file1, &file2) == 0 );
  
  /* Test where p1 comes before p2 */
  file1->time--;
  TEST( timeCompareRev(&file1, &file2) == 1 );
  
  /* Test where p2 comes before p1 */
  file1->time++;
  file2->time--;
  TEST( timeCompareRev(&file1, &file2) == -1 );

  // Free allocated memory
  free(file1);
  free(file2);

}

int main() {
  fprintf( stderr, "Testing timeCompareRev...\n\n" );
  testtimeCompareRev();
  fprintf( stderr, "\nDone running tests.\n" );
  return 0;
}
