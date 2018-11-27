/*
 * Filename: testnameCompare
 * Author: Richard Andrus
 * Userid: cs30foy
 * Description: Unit test program to test the function nameCompare()
 * Date: Nov 8 2018
 * Sources of Help: tutorialspoint.com
 */

#include <string.h>
#include <stdlib.h>

#include "test.h"    /* For TEST() macro and stdio.h */
#include "pa4.h"

/*
 * Unit Test for nameCompare.s
 *
 * long nameCompare( char * src );
 *
 */
void testnameCompare() {
  
  // Create two  fileInfo structs to compare
  struct fileInfo *file1 = malloc(sizeof(struct fileInfo));
  struct fileInfo *file2 = malloc(sizeof(struct fileInfo));
  
  /* Test equal filenames */
  strcpy(file1->filename, "FILE");
  strcpy(file2->filename, "FILE");
  TEST( nameCompare(&file1, &file2) == 0 );
  
  /* Test where p1 comes before p2 */
  strcpy(file1->filename, "name");
  strcpy(file2->filename, "nome");
  TEST( nameCompare(&file1, &file2) == -1 );
  
  /* Test where p2 comes before p1 */
  strcpy(file1->filename, "FILE");
  strcpy(file2->filename, "FAIL");
  TEST( nameCompare(&file1, &file2) == 1 );

  // Free allocated memory
  free(file1);
  free(file2);

}

int main() {
  fprintf( stderr, "Testing nameCompare...\n\n" );
  testnameCompare();
  fprintf( stderr, "\nDone running tests.\n" );
  return 0;
}
