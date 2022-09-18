#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>


#define LEN 50


void openStatus (FILE * file);
unsigned long fileSize (FILE * file, struct stat buf);
void statusMemory (char * mem);
unsigned long amountOfString (char * mem);


typedef struct list {

    char str [LEN];
    struct list * next;

} List;



int main (void) {

    struct stat buf;
    FILE * file = fopen ("sort.txt", "rb");
    char * mem_start = NULL;
    openStatus (file);
    unsigned long filesize = fileSize (file, buf);
    mem_start = (char * ) calloc (sizeof (char), filesize);
    statusMemory (mem_start);

    fread (mem_start, sizeof (char), filesize, file);
    unsigned long amount_of_string = amountOfString (mem_start);

    char * str [amount_of_string];

    int j = 1;
    str[0] = mem_start;
    while (*mem_start != EOF) {

        if (*(mem_start - 1) == '\n') {

            * (mem_start - 1) = '\0';
            str[j] = mem_start;
            j++;
        }

        mem_start++;
    }

    for (int i = 0; i < amount_of_string; i++) {

        puts (str[i]);
        putchar ('\n');

    }

    return 0;
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


unsigned long amountOfString (char * mem) {

    int i = 0, amount = 0;

    for (i = 0; i < strlen (mem); i++)
        if (*(mem + i) == '\n')
            amount++;

    return amount;
}
