/*
 * Filename: mainEC.c
 * Author: Richard Andrus
 * Userid: cs30foy
 * Description: Main driver program for pa4
 * Date: Nov 28, 2018
 * Sources of Help: tutorialspoint.com
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <getopt.h>
#include <unistd.h>

#include "pa4.h"
#include "pa4EC.h"
#include "pa4Strings.h"

/*
 * Function Name: mainEC
 * Function Prototype: int mainEC( int argc, char *argv[] )
 * Description: Main driver for the mainEC portion of pa4 
 * Parameters: argc - number of arguments from terminal
 *             argv - array of terminal arguments
 * Side Effects: Prints to stdout and stderr, calls other subroutines
 * Error Conditions: Error calling fopen - print error and return
 *              No input file specified - print MISSING_INFILE and return
 *              Extra arguments detected - print STR_ERR_EXTRA_ARGS
 * Return Value: Returns EXIT_SUCCESS if no errors, EXIT_FAILURE if errors.
 *
 */

int main( int argc, char *argv[] ) {

  /*
   * 1. Parse Command Line Arguments using getopt
   */

  // Keep track of which flags are set
  char allFlag = FALSE;
  char countFlag = FALSE;
  char longFlag = FALSE;
  char rev = FALSE;
  SortBy sortby = NAME;
  char directory[MAXLEN][MAXLEN];
  int numFiles = 1;

  // Set default path to "."
  strcpy(directory[0], STR_THIS);

  // Cycle through each get_opt flag
  int opt;
  while ((opt = getopt(argc, argv, EC_FLAGS)) != -1) {
  
    switch (opt) {

      // For help flag, print usage and exit
      case FLAG_HELP:
        fprintf(stderr, EC_STR_USAGE, argv[0]);
        return EXIT_SUCCESS;

      // For hidden flag, set allFlag to true
      case FLAG_SHOWHIDDEN:
        allFlag = TRUE;
        break;

      // For count flag, set countFlag to true
      case FLAG_COUNT:
        countFlag = TRUE;
        break;

      // For long flag, set longFlag to true
      case FLAG_LONGFMT:
        longFlag = TRUE;
        break;

      // For reverse flag, set rev to true
      case FLAG_REVERSE:
        rev = TRUE;
        break;

      // For time flag, set sortby to TIME
      case FLAG_TIME:
        sortby = TIME;
        break;

      // If user sets an incorrect flag, print error and exit
      case FLAG_UNKNOWN:
        fprintf(stderr, EC_STR_USAGE, argv[0]);
        return EXIT_FAILURE;
        break;

      default:
        fprintf(stderr, EC_STR_USAGE, argv[0]);
        return EXIT_FAILURE;

    }

  }

  /*
   * 2. Parse each extra argument as a new filename
   */

  for (int i = optind; i < argc; i++) {
    
    strcpy(directory[i - optind], argv[i]);
    numFiles++; 

  }

  /*
   * 3. Check if the file exists using access
   */
  
  for (int i = 0; i < numFiles; i++) {

    if (access(directory[i], F_OK) != 0) {

      // If file doesn't exists, print error and return
      fprintf(stderr, ERR_DNE, directory[i]);
      return EXIT_FAILURE;

    }

  }
  
  /*
   * 4. Construct the filetree by using buildFileTree
   */

  struct fileInfo *root[MAXLEN];
  for (int i = 0; i < numFiles; i++) {

    root[i] = buildFileTree(directory[i], sortby, rev);

    // Check if buildFileTree failed
    if (root[i] == NULL) {

      return EXIT_FAILURE;

    }

  }

  /*
   * 4b. Sort files using qsort()
   */

  void *sort;
  if (sortby == NAME) {

    if (rev == TRUE) {

      sort = nameCompareRev;

    } else {

      sort = nameCompare;

    }

  // If sorting by time, use timeCompare or timeCompareRev
  } else if (rev == TRUE) {

    sort = timeCompareRev;

  } else {

    sort = timeCompare;

  }

  qsort(root, numFiles, sizeof(struct fileInfo*), sort);

  /*
   * 5. If specified, print the filecount
   */
  
  int count = 0;
  for (int i = 0; i < numFiles; i++) {

    count += getFileCount(root[i]);

  }

  if (countFlag == TRUE) {

    fprintf(stdout, EC_STR_COUNT, count);

  }

  /*
   * 6. Call printFiles to display the data structure
   */

  for (int i = 0; i < numFiles; i++) {

    printFiles(root[i], allFlag, longFlag, 0);

  }  
  
  /*
   * 7. Free the entire data structure using freeFileTree
   */
  
  for (int i = 0; i < numFiles; i++) {

    freeFileTree(root[i]);

  }

  return EXIT_SUCCESS;

}
