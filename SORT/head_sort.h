///\file
///\brief Program, which can sort strings alphabetically (header);

#ifndef _FUNC_H__
#define _FUNC_H__


#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <cstdint>


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


//! This function can count amount of string; 
//! @param [in] mem - pointer of the buffer;
//! @return amount of strings.
unsigned int amountOfString (char * mem, unsigned long filesize);


//! This function closes files and free a memory for gotted pointers; 
//! @param [in] file - pointer of the openable file;
//! @param [in] rec - pointer of the recordable file;
//! @param [in] mem_start - pointer of the elementary memory;
//! @param [in] getAdress - pointer of the array of strings.
void close (FILE * file, FILE * rec, char * mem_start, char ** getAdress);


//! This function arranges the lines in the correct order;
//! @param [in] aptr - pointer of the cycle string;
//! @param [in] aptr - other pointer of the cycle string.
//! @return difference of row elements.
int comp (const void * aptr, const void * bptr);


//! This function determines the file size;
//! @param [in] file - pointer of the openable file;
//! @param [in] buf - pointer of the struct stat;
//! @return size of the file.
unsigned long FileSize (FILE * file);


//! This function determines the file size;
//! @param [in] getAdress - pointer of the array of the strings.
//! @param [in] amount_of_string - amount of strings;
//! @param [in] rec - pointer of the recordable file.
void fileRecord (char ** getAdress, unsigned long amount_of_string, FILE * rec);


//! This function sorting some array (my function qsort ());
//! @param [in] base - pointer of the buffer/array.
//! @param [in] num - amount of the elements;
//! @param [in] size - size of every element;
//! @param [in] compare - function-comparator (previously: my_comp ()).
void my_sort (void * base, size_t num, size_t size, int (*compare) (const void * obj1, const void * obj2));


//! This function opens files;
//! @param [in] base - pointer of the buffer/array.
//! @param [in] file - pointer of the pointer openable file;
//! @param [in] rec - pointer of the pointer recordable file;
//! @return "true", if there is a problem opening the file and "false", if everything is allrigth.
bool openFiles (FILE ** file, FILE ** rec);


//! This function prints original text;
//! @param [in] filesize - size of the file;
//! @param [in] mem_start - pointer of the elementary memory;
//! @param [in] rec - pointer of the pointer recordable file.
void originalText (unsigned long filesize, char * mem_start, FILE * rec);


//! This function initializes buffer;
//! @param [in] buffer - pointer of the buffer;
//! @param [in] getAdress - pointer of the array strings;
//! @param [in] filesize - size of the file.
void pointerGetStr (char * buffer, char ** getAdress, unsigned long filesize);


//! This function traids symbols '\n' on '\0' and records gotted result in buffer;
//! @param [in] mem_start - pointer of the elementary memory;
//! @param [in] buffer - pointer of the buffer.
void recordInBuffer (char * mem_start);


//! This function swaps elements;
//! @param [in] size - size of array elements;
//! @param [in] cur - pointer of current element;
//! @param [in] prev - pointer of previous element.
void swap (size_t size, uint8_t * cur, uint8_t * prev);


//! This function allocates memory for pointers;
//! @param [in] mem_start - pointer of the pointer elementary memory;
//! @param [in] getAdress - pointer of the pointer array strings;
//! @param [in] filesize - size of the file;
//! @param [in] amount_of_string - pointer of the value, which saves amount of strings;
//! @param [in] file - pointer of the openable file;
//! @return 0, if no errors weren't found and >=1, if errors were found.
unsigned int turnOnPointers (char ** mem_start, char *** getAdress, unsigned long filesize,\
                             unsigned long * amount_of_string, FILE * file);

#endif
