///\file
///\brief This file contains function for sorting string in file;


unsigned int amountOfString (char * mem) {

    unsigned long indexFile = 0, amount = 0, length = strlen (mem);
    for (indexFile = 0; indexFile < length; indexFile++)
        if (*(mem + indexFile) == '\n')
            amount++;

    return amount;
}


void close (FILE * file, FILE * rec, char * mem_start, char * copy_mem_start, char ** getAdress) {

    free (mem_start);
    free (copy_mem_start);
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


unsigned long FileSize (FILE * file, struct stat * buf) {

    if (fstat (fileno (file), buf) == 0)
        return buf->st_size;

    return 0;
}


void fileRecord (char ** getAdress, unsigned long amount_of_string, FILE * rec) {

    int i = 0;
    for (i = 0; i < amount_of_string; i++) {
        if (getAdress [i][0] != '\0')
            fprintf (rec, "%s\n", getAdress [i]);
    }
}


void my_sort (void * base, size_t num, size_t size, int (*compare) (const void * obj1, const void * obj2)) {

    int i = 0, j = 0;
    
    // uint8_t * save = (uint8_t * ) calloc (1, size);
    uint8_t * temp = (uint8_t * ) base, * cur = NULL, * prev = NULL;

    for (i = 0; i < num; i++) {

        for (j = num - 1; j > i; j--) {

            cur = (uint8_t * ) (temp + j * size);
            prev = (uint8_t * ) (temp + (j - 1) * size);  
            if ((*compare) (prev, cur) > 0) {

                SWAP (uint8_t *, prev, cur);
                
                /*
                memcpy (save, prev, size);
                memcpy (prev,  cur, size);
                memcpy (cur,  save, size);
                */
            }



        }
    }

    // free (save);
}


bool openFiles (FILE ** file, FILE ** rec) {



    * file = fopen ("sort.txt", "rb");
    CHECK_ERROR (file == NULL, "Problem with opening file.", FILE_AREN_T_OPENING);
    * rec = fopen ("aftersort.txt", "a");
    CHECK_ERROR (rec == NULL, "Problem with opening file.", FILE_AREN_T_OPENING);

    return NO_ERROR;
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


unsigned int turnOnPointers (char ** mem_start, char ** copy_mem_start, char *** getAdress, unsigned long filesize,\
                            unsigned long * amount_of_string, FILE * file) {

    * mem_start = (char * ) calloc (filesize, sizeof (char));
    CHECK_ERROR (* mem_start == NULL, "Memory not allocated.", MEMORY_NOT_FOUND);
    * copy_mem_start = (char * ) calloc (filesize, sizeof (char));
    CHECK_ERROR (* copy_mem_start == NULL, "Memory not allocated.", MEMORY_NOT_FOUND);
    fread (* mem_start, sizeof (char), filesize, file);
    recordInBuffer (* mem_start, * copy_mem_start);
    * amount_of_string = amountOfString (* mem_start);
    * getAdress = (char ** )calloc (* amount_of_string, sizeof (char * ));
    CHECK_ERROR (getAdress == NULL, "Memory not allocated.", MEMORY_NOT_FOUND);

    return NO_ERROR;
}
