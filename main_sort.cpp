#include "head_sort.h"
#include "sort.h"


int main (void) {

    struct stat buf = {};

    // OPENING FILEpS:
    FILE * file = fopen ("sort.txt", "rb");
    CHECK_ERROR (file == NULL, "Problem with opening file.", FILE_AREN_T_OPENING);
    FILE * rec = fopen ("aftersort.txt", "a");
    CHECK_ERROR (rec == NULL, "Problem with opening file.", FILE_AREN_T_OPENING);
    // --------------

    unsigned long filesize = FileSize (file, &buf), amount_of_string = 0;
    CHECK_ERROR (filesize == 0, "File is empty.", EMPTY_FILE);
    char * mem_start = NULL, * copy_mem_start = NULL, ** getAdress = NULL;
    turnOnPointers (&mem_start, &copy_mem_start, &getAdress, filesize, &amount_of_string, file);

    // first sort:
    pointerGetStr (copy_mem_start, getAdress, filesize);
    qsort (getAdress, amount_of_string, sizeof (char *), comp);
    fileRecord (getAdress, amount_of_string, rec);
    // --------------

    // second (my) sort:
    pointerGetStr (copy_mem_start, getAdress, filesize);
    my_sort (getAdress, amount_of_string, sizeof (char *), comp);
    fileRecord (getAdress, amount_of_string, rec);
    // --------------

    // original text:
    fputs (mem_start, rec);
    // --------------

    close (file, rec, mem_start, copy_mem_start, getAdress);
    return 0;
}
