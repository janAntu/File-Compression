/*
 * Filename: getFileInfo.c
 * Author: Sungyeol Oh
 * Userid: cs30ycb
 * Description: Defines the getFileInfo function for the PA4 program.
 * Date: 09/01/2017
 * Sources of help: Given file
 */

#include "pa4.h"
#include <string.h>
#include <stdlib.h>
#define NULL_ARG "Null argument in getFileInfo.\n"

/* fill in the following in the struct fileInfo fi
  filename, time, size, mode, uid, gid. Given*/
void getFileInfo(struct fileInfo * fi, const char * filename){

  /* invalid args, should not happen. */  
  if (!fi || !filename) {
    fprintf(stderr, NULL_ARG);
    return;
  }

  /*call the stats function*/
  struct stat stats;
  stat(filename, &stats);

  /*fill in fields in fi*/
  strcpy(fi->filename, filename);
  fi->time = stats.st_mtime;
  fi->size = stats.st_size;
  fi->mode = stats.st_mode;
  fi->uid = stats.st_uid;
  fi->gid = stats.st_gid;

}
