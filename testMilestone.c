/*
 * Filename: testMilestone
 * Author: Richard Andrus
 * Userid: cs30foy
 * Description: Unit test program to test milestone functions
 * Date: Nov 8 2018
 * Sources of Help: tutorialspoint.com
 */

#include <string.h>
#include <stdlib.h>

#include "test.h"    /* For TEST() macro and stdio.h */
#include "pa4.h"

/*
 * Unit Test for Milestone.s
 *
 * long Milestone( char * src );
 *
 */
void testMilestone() {
  
  // Create file tree using buildFileTree
  struct fileInfo *fInfo = buildFileTree(".", NAME, TRUE);

  // Print the file's name and permissions
  printPermissions(fInfo->mode);
  printf(" %-8s\n", fInfo->filename);


  // Print name and permission for all children
  int i;
  for(i = 0; i < fInfo->childrenSize; i++) {

    printPermissions(fInfo->children[i]->mode);
    printf(" %-8s\n", fInfo->children[i]->filename);
    
  }    

}

int main() {
  fprintf( stderr, "Testing Milestone...\n\n" );
  testMilestone();
  fprintf( stderr, "\nDone running tests.\n" );
  return 0;
}
