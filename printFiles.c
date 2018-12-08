/*
 * Filename: printFiles.c
 * Author: Richard Andrus
 * Userid: cs30foy
 * Description: Print information for each file in tree
 * Date: Nov 22 2018
 * Sources of Help: tutorialspoint.com
 */

/*
 * Function Name: printFiles()
 * Function Prototype: void printFiles(const struct fileInfo *fi,
 *                     int showLongFmt, int indent);
 * Description: Print information for each file in tree
 * Parameters: mode - A bitfield representing access Files
 * Side Effects: Prints out to stdout
 * Error Conditions: exe
 * Return Value: exe
 *
 */

#include "pa4.h"
#include "pa4Strings.h"
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <grp.h>
#include <pwd.h>
#include <time.h>

#define WKDAY_OFF 4
#define TIME_LEN 12

void printFiles (const struct fileInfo * fi, 
                 int showHidden, int longFormat, int indent) { 

  // Check if file is hidden, and if so return early
  if (showHidden == FALSE && isHidden(fi->filename) == TRUE) {

    return;

  }

  // If long format is specified, print extra details
  if (longFormat == TRUE) {

    // Print file permissions
    printPermissions(fi->mode);

    // Print space after file permissions
    printf(" ");

    // Print User ID
    printf(STR_PWNAME, getpwuid(fi->uid)->pw_name);
    
    // Print Group ID
    printf(STR_GNAME, getgrgid(fi->gid)->gr_name);
    
    // Print file size
    printf(STR_SIZE, fi->size);
    
    // Print month, date and time ALL AT ONCE
    char *timeStr = ctime(&fi->time);
    timeStr += WKDAY_OFF;
    timeStr[TIME_LEN] = '\0';
    printf("%s ", timeStr);
    
  } 

  // Print spaces before file
  for (int i = 0; i < indent; i++) {

    printf(" ");

  }


  // Print file name
  printf("%s\n", fi->filename);

  // Go through all the children is this file
  for (int i = 0; i < fi->childrenSize; i++) {

    // Print each child file
    printFiles(fi->children[i], showHidden, longFormat, indent + 1);

  }

}
