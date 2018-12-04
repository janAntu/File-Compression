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
#include "pa4.h"
#include "pa4Strings.h"
#include <getopt.h>

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

  int opt;
  FILE *infile;

  while ((opt = getopt(
    argc, argv, FLAGS)) != -1) {
  
    switch (opt) {

      case HELP_FLAG:
        fprintf(stderr, STR_USAGE);
        return EXIT_SUCCESS;

      case INFILE_FLAG:
        errno = 0;
        infile = fopen(optarg, "r");
        if (errno > 0 || infile == NULL) {

          // Print error message
          perror(RTABLE_FILE_ERR);
          fprintf(stderr, STR_USAGE);
          return EXIT_FAILURE;

        }
        break;

      default:
        fprintf(stderr, STR_USAGE);
        return EXIT_FAILURE;

    }

  }

  // If infile isn't initiated, print error and return
  if (infile == NULL) {

    fprintf(stderr, MISSING_INFILE);
    fprintf(stderr, STR_USAGE);
    return EXIT_FAILURE;

  }
  
  // If there are extra arguments, print an error and return
  if (optind < argc) {

    fprintf(stderr, EXTRA_ARGS, argv[0]);
    fprintf(stderr, STR_USAGE);
    fclose(infile);
    return EXIT_FAILURE;

  }

  /*
   * 2. Build the hashtables of email data using populateTables
   */

  table_t *htbl = (void*) malloc(sizeof(htbl));
  table_t *rtbl = (void*) malloc(sizeof(htbl));
  table_t *eotbl = (void*) malloc(sizeof(eotbl));

  // Check if dynamic memory allocation failed
  if (htbl == NULL || rtbl == NULL || eotbl == NULL) {
    free(htbl);
    free(rtbl);
    free(eotbl);
    perror(MEM_ERR);
    fprintf(stderr, STR_USAGE);
    return EXIT_FAILURE;
  }

  // Read data from infile to each table
  readTables(infile, htbl, rtbl, eotbl);

  /*
   * 3. Serialize hashtables to file using writeTables
   */

  launchUserQuery(htbl, rtbl, eotbl); 

  /*
   * 4. Free all dynamically allocated memory
   */

  fclose(infile);

  free(htbl->bitArray);
  free(rtbl->bitArray);

  for (int i = 0; i < eotbl->size; i++) {
    freeLinkedList(eotbl->llArray[i]);
  }

  free(htbl);
  free(rtbl);
  free(eotbl);
  return EXIT_SUCCESS;
  
}
