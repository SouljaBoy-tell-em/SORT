#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>


void openStatus (FILE * file);
unsigned long fileSize (FILE * file, struct stat buf);
void statusMemory (char * mem);
unsigned int amountOfString (char * mem);
int comp (const void * aptr, const void * bptr);
void copyBuf (const char * mem_start, char * buffer);

int main (void) {

    struct stat buf;

    FILE * file = fopen ("sort.txt", "r");
    openStatus (file);

    unsigned long filesize = fileSize (file, buf);
    char * mem_start = (char * ) calloc (filesize, sizeof (char));
    statusMemory (mem_start);
    char * copy_mem_start = (char * ) calloc (filesize, sizeof (char));
    statusMemory (copy_mem_start);
    char ** getAdress = (char ** ) calloc (filesize, sizeof (char * ));

    fread (mem_start, sizeof (char), filesize, file);
    unsigned long amount_of_string = amountOfString (mem_start);
    copyBuf (mem_start, copy_mem_start);


    return 0;
}


void copyBuf (const char * mem_start, char * buffer) {

    for (int i = 0; i < strlen (mem_start); i++)
        buffer [i] = mem_start [i];

}


int comp (const void * aptr, const void * bptr)
{

	const char * str1 = * (const char ** ) aptr;
	const char * str2 = * (const char ** ) bptr;

    assert(str1);
    assert(str2);

    int i = 0;
    int j = 0;

    while(true) {

        while(!isalpha(str1[i]) && (str1[i] != '\0'))
            i++;
        while(!isalpha(str2[j]) && (str2[j] != '\0'))
            j++;

        if(str1[i] != str2[j])
            break;

        if(str1[i] == '\0')
            break;

        i++;
        j++;
    }

    return(str1[i] - str2[j]);
}



void openStatus (FILE * file) {

    if (file == NULL) {

        puts ("File isn't opening. Program the end.");
        exit (EXIT_FAILURE);
    }
}


void statusMemory (char * mem) {

    if (mem == NULL) {

        puts ("You have problem with getting memory");
        exit (EXIT_FAILURE);
    }
}


unsigned long fileSize (FILE * file, struct stat buf) {

    fstat (fileno (file), &buf);

    return buf.st_size;
}


unsigned int amountOfString (char * mem) {

    unsigned long i = 0, amount = 0;

    for (i = 0; i < strlen (mem); i++)
        if (*(mem + i) == '\n')
            amount++;

    return amount;
}


