///\file
///\brief This file can show a program (main);


#include "head_sort.h"
#include "sort.h"


int main (void) {

    // OPENING FILES:
    FILE * file = fopen ("sort.txt", "r");
    CHECK_ERROR (file == NULL, "Problem with opening sort.txt", FILE_AREN_T_OPENING);
    FILE * rec = fopen ("aftersort.txt", "w");
    CHECK_ERROR (rec == NULL, "Problem with opening aftersort.txt", FILE_AREN_T_OPENING);
    // --------------
    unsigned long filesize = FileSize (file), amount_of_string = 0;
    CHECK_ERROR (filesize == 0, "File is empty.", EMPTY_FILE);
    char * mem_start = NULL, ** getAdress = NULL;
    turnOnPointers (&mem_start, &getAdress, filesize, &amount_of_string, file);
    
    // first sort:
    pointerGetStr (mem_start, getAdress, filesize);
    qsort (getAdress, amount_of_string, sizeof (char *), comp);
    fileRecord (getAdress, amount_of_string, rec);
    // --------------

    // second (my) sort:
    /* pointerGetStr (mem_start, getAdress, filesize); 
    my_sort (getAdress, amount_of_string, sizeof (char *), comp);
    fileRecord (getAdress, amount_of_string, rec); */
    // --------------

    // original text:
    for (int i = 0; i < filesize; i++)
        fputc ((mem_start [i] ? mem_start [i] : '\n'), rec);
    // --------------
    
    close (file, rec, mem_start, getAdress);
    
    return 0;
}
