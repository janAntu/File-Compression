/*
 * Filename: pa4EC.h
 * Author: CSE30 tutor
 * Userid: N/A
 * Description: Defines constants for PA4 extra credit
 * Date: 08/28/2018
 */

#ifndef PA4EC_H
#define PA4_H

#define STR_USAGE_LONG \
"Usage: %s [-aclrth] [-f file]\n"\
"  -a --all \t show all files, including hidden files\n"\
"  -c --count \t print file count, including hidden files\n"\
"  -f --file \t [file] specify directory to list\n"\
"  -l --long \t list files in long format\n"\
"  -r --reverse \t sort files in reversed order\n"\
"  -t --time \t sort files by time, instead of by name\n"\
"  -h --help \t show the help message\n"

#define FLAG_LONG_SHOWHIDDEN "all"
#define FLAG_LONG_COUNT "count"
#define FLAG_LONG_FILENAME "file"
#define FLAG_LONG_LONGFMT "long"
#define FLAG_LONG_REVERSE "reverse"
#define FLAG_LONG_TIME "time"
#define FLAG_LONG_HELP "help"

#endif
