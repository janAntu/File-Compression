/*
 * Filename: buildFileTree.c
 * Author: Richard Andrus
 * Userid: cs30foy
 * Description: Builds the file tree struct for a file
 * Date: Nov 22 2018
 * Sources of Help: tutorialspoint.com
 */

/*
 * Function Name: buildFileTree()
 * Function Prototype: struct fileInfo *buildFileTree(
 *                     const char *filename, SortBy sortby, int rev);
 * Description: Builds the file tree struct for a file
 * Parameters: filename - Name of the file
 *             sortby - Criteria to sort the files, either name or date
 *             rev - Tells whether to sort in reverse order
 * Side Effects: Allocates memory on the heap
 * Error Conditions: 
 * Return Value: Pointer to dynamically allocated struct fileInfo
 *
 */

#include "pa4.h"
#include "pa4Strings.h"
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>

struct fileInfo *buildFileTree(
    const char *filename, SortBy sortby, int rev) {

  /*
   * 1. Dynamically allocate space for one struct fileInfo
   */

  struct fileInfo *fInfo = calloc(1, sizeof(struct fileInfo));

  // Check if memory allocation failed; if so, print error
  if (fInfo == NULL) {

    perror(__func__);
    return NULL;

  }

  /*
   * 2. Call getFileInfo on this new struct to fill fields
   */

  getFileInfo(fInfo, filename);

  /*
   * 3. Determine if file is a directory and set corresponding flag
   */

  DIR *dir = opendir(filename);
  if (dir != NULL) {

    fInfo->isDir = TRUE;

    /*
     * 4. If file is directory, recursively allocate each of its
     *    children using buildDir, creating a tree data structure.
     */

    // Allocate memory for children array
    fInfo->children = calloc(
      fInfo->childrenCapacity, sizeof(struct fileInfo*));

    // Use readdir to read each subfile
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {

      // If subfile name is "." or "..", skip
      if (strcmp(entry->d_name, STR_THIS) != 0 &&
          strcmp(entry->d_name, STR_UP) != 0) {

        // Concatenate the directory name with the
        // subfile's name
        char catName[MAXLEN];
        sprintf(catName, FILE_CONCAT_FORMAT, 
          filename, entry->d_name);

        // If there are more children than there is
        // capacity, expand children array with realloc
        if (fInfo->childrenSize >= 
            fInfo->childrenCapacity) {

         struct fileInfo **temp  = realloc(fInfo->children, 
            sizeof(struct fileInfo*) *
            (fInfo->childrenSize + CHILDREN_INCREMENT));

          // If realloc fails, print
          // error, free everything
          // and return NULL.
          if (temp == NULL) {

            perror(__func__);
            if (fInfo->children != NULL) 
              free(fInfo->children);
            free(fInfo);
            return(NULL);

          // Otherwise, update childrenCapacity
          } else {

            fInfo->children = temp;
            fInfo->childrenCapacity += CHILDREN_INCREMENT;

          }

        }

        // Call buildFileTree with concatenated
        // string and store result to appropriate
        // location in the children array
        fInfo->children[fInfo->childrenSize] =
          buildFileTree(catName, sortby, rev);
        if (fInfo->children[fInfo->childrenSize] == NULL) {
          return NULL;
        }

        // Increment childrenSize
        fInfo->childrenSize++;

      }

    }

    // Close the directory
    closedir(dir);

    // Sort the files in order using qsort, using
    // sortBy and rev to determine the sorting method
    void *sort;
    if (sortby == NAME) {

      if (rev == TRUE) {

        sort = nameCompareRev;

      } else {

        sort = nameCompare;

      }

    } else if (rev == TRUE) {

      sort = timeCompareRev;

    } else {

      sort = timeCompare;

    }

    qsort(fInfo->children, fInfo->childrenSize, 
          sizeof(struct fileInfo*), sort);

  }

  return fInfo;

}
