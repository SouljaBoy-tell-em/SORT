#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

//fseek () & ftell()
// функция swap в bubble_sort; static swap ();

void openStatus (FILE * file);
unsigned long FileSize (FILE * file, struct stat * buf);
void statusMemory (char * mem);
unsigned int amountOfString (char * mem);
int mycomp (const void * aptr, const void * bptr);
void copyBuf (const char * mem_start, char * buffer);
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
    //openStatus (file); // !TODO: переместить в define
    FILE * rec = fopen ("aftersort.txt", "w");
    //openStatus (rec);
    // --------------

    // memory allocation: start memory;
    unsigned long filesize = FileSize (file, &buf);
    char * mem_start = (char * ) calloc (filesize, sizeof (char));
    statusMemory (mem_start); //!TODO: переместить в define
    // --------------

    // memory allocation: copy start memory;
    char * copy_mem_start = (char * ) calloc (filesize, sizeof (char));
    statusMemory (copy_mem_start);
    // --------------

    fread (mem_start, sizeof (char), filesize, file);
    unsigned long amount_of_string = amountOfString (mem_start);

    // memory allocation: pointers for copy start memory;
    char ** getAdress = (char ** )calloc (amount_of_string, sizeof (char * ) + 1); //!TODO: +1 ?
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

            if ((*compare) (base + (j - 1) * size, base + j * size) < 0) {

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
    for (i = 0; i < amount_of_string; i++)
       if (getAdress[i][0] != '\r')
            fputs (getAdress[i], rec);
}


void pointerGetStr (char * buffer, char ** getAdress, unsigned long filesize) {

    assert (getAdress); // !TODO: заменить на define

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


void copyBuf (const char * mem_start, char * buffer) { // !TODO: переименовать функцию

    int amo = strlen (mem_start);
    for (int i = 0; i < amo; i++) {

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


unsigned long FileSize (FILE * file, struct stat * buf) { // const char * st;
                                                         // char const*
                                                         //const char const* st

    fstat (fileno (file), buf); // !TODO: обработать fstat

    return buf->st_size;
}


unsigned int amountOfString (char * mem) {

    unsigned long i = 0, amount = 0;

    for (i = 0; i < strlen (mem); i++)
        if (*(mem + i) == '\n')
            amount++;

    return amount;
}
