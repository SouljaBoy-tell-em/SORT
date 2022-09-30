#include <stdio.h>
#include <cstdint>


void swap (size_t size, char * cur, char * prev) {

    int i = 0;
    for (i = 0; i < size - (size % 8); i += 8) {
        
        printf ("i = %d\n", i);
        uint64_t temp = * (uint64_t * )(cur + i);
        * (uint64_t * )(cur + i) =  * (uint64_t * )(prev + i);
        * (uint64_t * )(prev + i) = temp;
    }
    
    for (i; i < size; i++) {
        
        printf ("i = %d\n", i);
        uint8_t temp = * (cur + i);
        * (cur + i) =  * (prev + i);
        * (prev + i) = temp;
    }
}


int main (void) {

    /*               012345678901234567890123456789 */
    char str1[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char str2[27] = "abcdefghijklmnopqrstuvwxyz";
    
    swap (23, str1, str2);
    printf ("'%s'\n", str1);
    printf ("'%s'\n", str2);

return 0;
}
