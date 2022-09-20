#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


// функция swap в bubble_sort; static swap ();


#define CHECK_ERROR (condition, message_error, error_code) \
            do { \
               if (condition) { \
                   printf ("%s", message_error); \
                   return error_code; \
               } \
            } while(false)


enum error_code {

    NO_ERROR,
    FILE_AREN_T_OPENING,
    MEMORY_NOT_FOUND,
    EMPTY_FILE
};


void openStatus (FILE * file);
unsigned long FileSize (FILE * file, struct stat * buf);
void statusMemory (char * mem);
unsigned int amountOfString (char * mem);
int mycomp (const void * aptr, const void * bptr);
void recordInBuffer (const char * mem_start, char * buffer);
void pointerGetStr (char * buffer, char ** getAdress, unsigned long filesize);
void fileRecord (char ** getAdress, unsigned long amount_of_string, FILE * rec);
int comp (const void * aptr, const void * bptr);
void my_sort (void * base, size_t num, size_t size, int (*compare) (const void * obj1, const void * obj2));
int test_comp (const void * obj1, const void * obj2);
void close (FILE * file, FILE * rec, char * mem_start, char * copy_mem_start, char ** getAdress);


int main (void) {

    struct stat buf = {};

    // OPENING FILES:
    FILE * file = fopen ("sort.txt", "rb");
    CHECK_ERROR (file == NULL, "Problem with opening file.", FILE_AREN_T_OPENING);
    FILE * rec = fopen ("aftersort.txt", "a");
    CHECK_ERROR (rec == NULL, "Problem with opening file.", FILE_AREN_T_OPENING);
    // --------------

    // memory allocation: start memory;
    unsigned long filesize = FileSize (file, &buf);
    CHECK_ERROR (filesize == 0, "File is empty.", EMPTY_FILE);
    char * mem_start = (char * ) calloc (filesize, sizeof (char));
    CHECK_ERROR (mem_start == NULL, "Memory not allocated.", MEMORY_NOT_FOUND);
    // --------------

    // memory allocation: copy start memory;
    char * copy_mem_start = (char * ) calloc (filesize, sizeof (char));
    CHECK_ERROR (copy_mem_start == NULL, "Memory not allocated.", MEMORY_NOT_FOUND);
    // --------------

    fread (mem_start, sizeof (char), filesize, file);
    unsigned long amount_of_string = amountOfString (mem_start);

    // memory allocation: pointers for copy start memory;
    char ** getAdress = (char ** )calloc (amount_of_string, sizeof (char * ));
    CHECK_ERROR (getAdress == NULL, "Memory not allocated.", MEMORY_NOT_FOUND);
    copyBuf (mem_start, copy_mem_start); // !TODO: переместить указатели в отдельные функции
    // --------------

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


void close (FILE * file, FILE * rec, char * mem_start, char * copy_mem_start, char ** getAdress) {

    free (mem_start);
    free (copy_mem_start);
    free (getAdress);
    fclose (file);
    fclose (rec);
}


void my_sort (void * base, size_t num, size_t size, int (*compare) (const void * obj1, const void * obj2)) {

    int i = 0, j = 0;
    void * save = (void * ) calloc (1, size);
    // !TODO: привести void * к char *
    for (i = 0; i < num; i++) {

        for (j = num - 1; j > i; j--) {

            //printf ("A: %p B: %p\n", base + (j - 1) * size, base + j * size);

            if ((*compare) (base + (j - 1) * size, base + j * size) > 0) {

                memcpy (save                 , base + (j - 1) * size,       size);
                memcpy (base + (j - 1) * size, base + j * size      ,       size);
                memcpy (base + j * size      , save                 ,       size);
            }



        }
    }

    free (save);
}


int test_comp (const void * i, const void * j)
{

  const int  a = *(const int *) i;
  const int  b = *(const int *) j;

  //printf ("A: %d; B: %d\n", a, b);

  if (a < b)
        return 1;

  if (a > b)
        return -1;

  return 0;

}

void fileRecord (char ** getAdress, unsigned long amount_of_string, FILE * rec) {

    int i = 0;
    for (i = 0; i < amount_of_string; i++) {
        if (getAdress [i][0] != '\0')
            fprintf (rec, "%s\n", getAdress [i]);
    }
}


void pointerGetStr (char * buffer, char ** getAdress, unsigned long filesize) {

    unsigned long i = 0, j = 0;
    bool flag = false;

    for (i = 0; i < filesize; i++) {

        if (flag == false) {

            getAdress [j] = &buffer [i];
            flag = true;
            j++;
            continue;
        }

        if (buffer[i] == '\0') {

            getAdress [j] = &buffer [i+1];
            j++;
        }
    }
}


void recordInBuffer (const char * mem_start, char * buffer) {

    int amount_of_symbols = strlen (mem_start);
    for (int i = 0; i < amount_of_symbols; i++) {

        if (mem_start[i] == EOF)
            buffer[i] = '\0';

        if (mem_start [i] == '\n') {

            buffer[i] = '\0';
            continue;
        }

        buffer [i] = mem_start [i];
    }

}


int comp (const void * aptr, const void * bptr)
{

	const char * str1 = * (const char ** ) aptr;
	const char * str2 = * (const char ** ) bptr;
    int indexStr1 = 0;
    int indexStr2 = 0;

    while (true) {

        while(!isalpha(str1[indexStr1]) && (str1[indexStr1] != '\0'))
            indexStr1++;

        while(!isalpha(str2[indexStr2]) && (str2[indexStr2] != '\0'))
            indexStr2++;

        if(str1[indexStr1] != str2[indexStr2])
            break;

        if(str1[indexStr1] == '\0' || str2[indexStr2] == '\0')
            break;

        indexStr1++;
        indexStr2++;
    }

    return (str1[indexStr1] - str2[indexStr2]);
}


void statusMemory (char * mem) {

    if (mem == NULL) {

        puts ("You have problem with getting memory");
        exit (EXIT_FAILURE);
    }
}


unsigned long FileSize (FILE * file, struct stat * buf) {

    if (fstat (fileno (file), buf) == 0)
        return buf->st_size;

    return 0;
}


unsigned int amountOfString (char * mem) {

    unsigned long indexFile = 0, amount = 0, length = strlen (mem);
    for (indexFile = 0; indexFile < length; indexFile++)
        if (*(mem + indexFile) == '\n')
            amount++;

    return amount;
}
