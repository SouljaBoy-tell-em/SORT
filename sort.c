#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define LEN 50

int i = 0, j = 0;

int Amount (FILE *);
void brain_sort (void (*pr) (char *, char *), char * [], int);
void traid12 (char *, char *);
void record (FILE *, char * [], int);

int main () {

  SetConsoleCP(1251);
  SetConsoleOutputCP(1251);

  FILE * fp;

  if ((fp = fopen ("sort.txt", "r")) == NULL) {

    puts ("Problem opening file");
    exit (EXIT_FAILURE);

  }

  puts ("File opened!");

  int amount = Amount (fp);
  char ch;

  char str [amount][LEN];
  int str_len [amount];
  char * pt [amount];
  
  void ( * pr) (char *, char *);
  pr = traid12;

  fseek (fp, 0, SEEK_SET);

  while ((ch = getc (fp)) != EOF) {

    if (ch == '\n') {

      str[i][j] = '\0';
      pt[i] = str[i];
      str_len[i] = j;
      i++;
      j = 0;
      continue;

    }

    str[i][j] = ch;
    j++;

  }

  fclose (fp);

  brain_sort (pr, pt, amount);


  FILE * rec;
  if ((rec = fopen ("recordSort.txt", "a")) == NULL) {

    puts ("File for record not found!");
    exit (EXIT_FAILURE);

  }

  record (rec, pt, amount);
  fclose (rec);

  puts ("Input SORT in console: ");
  putchar ('\n');

  for (i = 0; i < amount; i++)
    puts (pt[i]);

  return 0;

}

void traid12 (char * str1, char * str2) {

  char str3[LEN];
  strcpy (str3, str1);
  strcpy (str1, str2);
  strcpy (str2, str3);

}

int Amount (FILE * fp) {

  char ch;
  int amount = 0;

  while ((ch = getc (fp)) != EOF) {

    if (ch == '\n')
      amount++;

  }

  return amount;

}

void brain_sort (void (*fp)(char *, char *), char * str[], int amount) {

  int i = 0, j = 0;

  for (i = 0; i < amount; i++) {

    for (j = 0; j < amount; j++) {

      if (str[i] == "\0" || str[j] == "\0")
        continue;

      if (strcmp(str[i], str[j]) == -1)
        (* fp) (str[i], str[j]);

    }

  }

}

void record (FILE * fp, char * str[], int amount) {

  for (i = 0; i < amount; i++) {

    fwrite (str[i], sizeof (char), strlen (str[i]), fp);
    putc ('\n', fp);

  }

}
