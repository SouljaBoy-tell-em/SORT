#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

void traid12 (char *, char *);
void space_to_end (char * str, int pos);

int i, j;
const long LEN = 50;

int main () {

  SetConsoleCP(1251);
  SetConsoleOutputCP(1251);

  FILE * fp;
  fp = fopen ("sort.txt", "r");

  char ch;
  int amount = 1;

  while ((ch = getc(fp)) != EOF) {
    if (ch == '\n')
      amount++;
  }

  int j = 0;
  unsigned long lim = 0;
  char str[amount][LEN];

  for (i = 0; i < amount; i++) {
    j = 0;
    fseek (fp, lim, SEEK_SET);

    while ((ch = getc (fp)) != EOF) {

      str[i][j] = ch;
      if (ch == '\n') {
        str[i][j] = '\0';
        break;
      }
      j++;
      lim++;

    }

    lim += 2;

  }

  for (i = 0; i < amount; i++) {

    for (j = 0; j < amount; j++) {

      if (str[i][0] == '\0' || str[j][0] == '\0')
        continue;

      if (strcmp(str[i], str[j]) == -1)
        traid12 (str[i], str[j]);

    }
  }

  for (i = 0; i < amount; i++) {
      puts (str[i]);
  }

  fclose (fp);
  FILE * rec;
  rec = fopen ("recordSort.txt", "a");

  for (i = 0; i < amount; i++) {
    fwrite (str[i], sizeof (char), strlen (str[i]), rec);
    putc ('\n', fp);

  }

  fclose (rec);

  return 0;

}

void traid12 (char * str1, char * str2) {

  char str3[LEN];
  strcpy (str3, str1);
  strcpy (str1, str2);
  strcpy (str2, str3);

}

void space_to_end (char * str, int pos) {

  char pr[LEN - pos];
  for (int i = 0; i < LEN - pos; i++)
    pr[i] = ' ';
  strcat (str, pr);

}
