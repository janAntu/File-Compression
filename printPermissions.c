/*
 * Filename: printPermissions.c
 * Author: Richard Andrus
 * Userid: cs30foy
 * Description: Print file permissions for a file
 * Date: Nov 22 2018
 * Sources of Help: tutorialspoint.com
 */

/*
 * Function Name: printPermissions()
 * Function Prototype: void printPermissions(const mode_t mode);
 * Description: Print file permissions for a file
 * Parameters: mode - A bitfield representing access permissions
 * Side Effects: Prints to stdout
 * Error Conditions: None
 * Return Value: None
 *
 */

#include "pa4.h"
#include "pa4Strings.h"
#include <stdio.h>
#include <sys/stat.h>

void printPermissions(const mode_t mode) {

  // Check whether this file is a directory
  if (S_ISDIR(mode) != 0) {

    fprintf(stdout, D_PERMISSION);

  } else {

    fprintf(stdout, NO_PERMISSION);

  }

  // These bit flags help determine whether each bit of
  // mode is full or empty and whether each bit is
  // a read, write or execute bit
  unsigned short flag = S_IRUSR;
  unsigned short readBits = S_IRUSR | S_IRGRP | S_IROTH;
  unsigned short writeBits = S_IWUSR | S_IWGRP | S_IWOTH;
  unsigned short exeBits = S_IXUSR | S_IXGRP | S_IXOTH;

  // Loop through each bit of the bitfield
  for (; flag > 0; flag = flag >> 1) {

    // Check if the specified bit is zero
    if ((mode & flag) == 0) {

      // Print out a '-' for no permission
      fprintf(stdout, NO_PERMISSION);

    } else if ((flag & readBits) > 0) {

      // Print out a 'r' for read permission
      fprintf(stdout, R_PERMISSION);

    } else if (flag &  writeBits) {

      // Print out a 'w' for write permission
      fprintf(stdout, W_PERMISSION);

    } else if (flag & exeBits) {

      // Print out a 'x' for execute permission
      fprintf(stdout, X_PERMISSION);

    }

  }

}
