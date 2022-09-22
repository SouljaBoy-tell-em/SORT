#ifndef _FUNC_H__
#define _FUNC_H__


#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <cstdint>


#define SWAP(type, a, b) type tmp = a; a = b; b = tmp;
#define MAINEND(status) status >=1 return 1;
#define CHECK_ERROR(condition, message_error, error_code) \
            do {                                          \
               if (condition) {                           \
                   printf ("%s", message_error);          \
                   return error_code;                     \
               }                                          \
            } while(false)


enum error_code {

    NO_ERROR,
    FILE_AREN_T_OPENING,
    MEMORY_NOT_FOUND,
    EMPTY_FILE
};


unsigned int amountOfString (char * mem);
void close (FILE * file, FILE * rec, char * mem_start, char * copy_mem_start, char ** getAdress);
int comp (const void * aptr, const void * bptr);
unsigned long FileSize (FILE * file, struct stat * buf);
void fileRecord (char ** getAdress, unsigned long amount_of_string, FILE * rec);
int comp (const void * aptr, const void * bptr);
void my_sort (void * base, size_t num, size_t size, int (*compare) (const void * obj1, const void * obj2));
bool openFiles (FILE ** file, FILE ** rec);
void pointerGetStr (char * buffer, char ** getAdress, unsigned long filesize);
void recordInBuffer (const char * mem_start, char * buffer);
unsigned int turnOnPointers (char ** mem_start, char ** copy_mem_start, char *** getAdress, unsigned long filesize,\
                             unsigned long * amount_of_string, FILE * file);

#endif
