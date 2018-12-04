/*
 * Filename: freeFileTree.c
 * Author: Richard Andrus
 * Userid: cs30foy
 * Description: Frees all memory in filetree structure
 * Date: Nov 22 2018
 * Sources of Help: tutorialspoint.com
 */

/*
 * Function Name: freeFileTree()
 * Function Prototype: void freeFileTree(struct fileInfo *fi);
 * Description: Frees all memory in filetree structure
 * Parameters: fi - Preinitialized fileinfo structure
 * Side Effects: Frees memory from the heap
 * Error Conditions: None
 * Return Value: None
 *
 */

#include "pa4.h"
#include "pa4Strings.h"
#include <stdlib.h>

void freeFileTree(struct fileInfo *fi) {

  // Go through all the children is this file
  for (int i = 0; i < fi->childrenSize; i++) {

    // Free each child file
    freeFileTree(fi->children[i]);

  }

  // Free the current file
  free(fi);

}
