# SORT
This program can sort a huge text. If you want to sort something text:
1) you should choose the name of file, where the text recorded;
2) you should choose the name of file, where the text'll record after sort.

I used built-in QSORT function for the 1st option of sort.

Else I wrote my function, that can sort text, but not so fast, how QSORT.
I realised the algorithm that void-pointer casts to type uint8_t that casts to type uint64_t and back. 
