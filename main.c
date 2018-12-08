/*
 * Filename: main.c
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
#include "pa4Strings.h"

/*
 * Function Name: main
 * Function Prototype: int main( int argc, char *argv[] )
 * Description: Main driver for the main portion of pa4 
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
  char directory[MAXLEN];

  // Set default path to "."
  strcpy(directory, STR_THIS);

  // Cycle through each get_opt flag
  int opt;
  while ((opt = getopt(argc, argv, FLAGS)) != -1) {
  
    switch (opt) {

      // For help flag, print usage and exit
      case FLAG_HELP:
        fprintf(stderr, STR_USAGE, argv[0]);
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

      // For filename flag, replace default path to arg
      case FLAG_FILENAME:
        strcpy(directory, optarg);
        break;

      // If user sets an incorrect flag, print error and exit
      case FLAG_UNKNOWN:
        fprintf(stderr, STR_USAGE, argv[0]);
        return EXIT_FAILURE;
        break;

      default:
        fprintf(stderr, STR_USAGE, argv[0]);
        return EXIT_FAILURE;

    }

  }

  /*
   * 2. Check for any extra arguments
   */

  if (optind != argc) {

    fprintf(stderr, STR_EXTRA_ARG, argv[optind]);
    fprintf(stderr, STR_USAGE, argv[0]);
    return EXIT_FAILURE;

  }

  /*
   * 3. Check if the file exists using access
   */
  
  if (access(directory, F_OK) != 0) {

    // If file doesn't exists, print error and return
    fprintf(stderr, ERR_DNE, directory);
    return EXIT_FAILURE;

  }
  
  /*
   * 4. Construct the filetree by using buildFileTree
   */

  struct fileInfo *root = buildFileTree(directory, sortby, rev);

  // Check if buildFileTree failed
  if (root == NULL) {

    return EXIT_FAILURE;

  }

  /*
   * 5. If specified, print the filecount
   */
  
  if (countFlag == TRUE) {

    fprintf(stdout, STR_COUNT, directory, getFileCount(root));

  }

  /*
   * 6. Call printFiles to display the data structure
   */

  printFiles(root, allFlag, longFlag, 0);

  /*
   * 7. Free the entire data structure using freeFileTree
   */

  freeFileTree(root);

  return EXIT_SUCCESS;

}
