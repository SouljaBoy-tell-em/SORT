///\file
///\brief This file contains function for sorting string in file;


unsigned int amountOfString (char * mem, unsigned long filesize) {

    unsigned long indexFile = 0, amount = 0;
    for (indexFile = 0; indexFile < filesize; indexFile++)
        if (*(mem + indexFile) == '\0')
            amount++;

    return amount;
}


void close (FILE * file, FILE * rec, char * mem_start, char ** getAdress) {

    free (mem_start);
    free (getAdress);
    fclose (file);
    fclose (rec);
}


int comp (const void * aptr, const void * bptr) {

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


unsigned long FileSize (FILE * file) {

    struct stat buf = {};
    if (fstat (fileno (file), &buf) == 0)
        return buf.st_size;

    return 0;
}


void fileRecord (char ** getAdress, unsigned long amount_of_string, FILE * rec) {

    int i = 0;
    for (i = 0; i < amount_of_string; i++) {
        if (getAdress [i][0] != '\0')
            fprintf (rec, "%s\n", getAdress [i]);
    }
}


unsigned int getBuffer (char ** mem_start, unsigned long filesize,\
                            unsigned long * amount_of_string, FILE * file) {

    * mem_start = (char * ) calloc (filesize, sizeof (char));
    CHECK_ERROR (* mem_start == NULL, "Memory not allocated for mem_start.", MEMORY_NOT_FOUND);
    fread (* mem_start, sizeof (char), filesize, file);
    recordInBuffer (* mem_start);
    * amount_of_string = amountOfString (* mem_start, filesize);

    return NO_ERROR;
}


unsigned int InitializePointersArray (char *** getAdress, char * mem_start, unsigned long filesize,\
                              unsigned long amount_of_string) {

    * getAdress = (char ** )calloc (amount_of_string, sizeof (char * ));
    CHECK_ERROR (* getAdress == NULL, "Memory not allocated for getAdress.", MEMORY_NOT_FOUND);
    pointerGetStr (mem_start, * getAdress, filesize);

    return NO_ERROR;
}


void my_sort (void * base, size_t num, size_t size, int (*compare) (const void * obj1, const void * obj2)) {

    int i = 0, j = 0;
    uint8_t * temp = (uint8_t * ) base;

    for (i = 0; i < num; i++) {

        for (j = num - 1; j > i; j--) {

            uint8_t * cur =        (uint8_t * ) (temp + j * size);
            uint8_t * prev = (uint8_t * ) (temp + (j - 1) * size);  
            if ((*compare) (prev, cur) > 0)
                swap (size, prev, cur);
        }
    }

}


void originalText (unsigned long filesize, char * mem_start, FILE * rec) {

    for (int i = 0; i < filesize; i++)
        fputc ((mem_start [i] ? mem_start [i] : '\n'), rec);
}


void pointerGetStr (char * buffer, char ** getAdress, unsigned long filesize) {

    getAdress [0] = &buffer [0];
    
    unsigned long i = 1, j = 1;
    for (i = 0; i < filesize; i++) {
        if (buffer[i] == '\0') {

            getAdress [j] = &buffer [i+1];
            j++;
        }
    }
}


void recordInBuffer (char * mem_start) {

    int amount_of_symbols = strlen (mem_start);
    for (int i = 0; i < amount_of_symbols; i++) {

        if (mem_start[i] == EOF)
            mem_start[i] = '\0';

        if (mem_start [i] == '\n') {

            mem_start[i] = '\0';
            continue;
        }
    }

}


void swap (size_t size, uint8_t * cur, uint8_t * prev) {

    int i = 0;
    for (i = 0; i < size; i += 8) {
        
        uint64_t temp = * (uint64_t * )(cur + i);
        * (uint64_t * )(cur + i) =  * (uint64_t * )(prev + i);
        * (uint64_t * )(prev + i) = temp;
    }
    
    for (i; i < size; i++) {
        
        uint8_t temp = * (cur + i);
        * (cur + i) =  * (prev + i);
        * (prev + i) = temp;
    }
}


void timer (char ** getAdress, unsigned long amount_of_string, int (* comp) (const void * , const void *)) {

    int i = 0;
    double start = clock ();
    for (i = 0; i < 20; i++)
        my_sort (getAdress, amount_of_string, sizeof (char *), comp);
    double finish = clock ();

    printf ("Time of 20 sortings: %lf\n", (finish - start) / (20 * CLOCKS_PER_SEC));
}
