//Preprocessing txts
#include <basics.h>

#ifndef MAXFILESZ
#define MAXFILESZ 8388608
#endif
#ifndef MAXTOKSZ
#define MAXTOKSZ 1048576
#endif

int tokarr1_len = 0, tokarr2_len = 0;
char tokarr1[MAXTOKSZ];
char tokarr2[MAXTOKSZ];
char filebuf[MAXFILESZ], fnbuf[1024];

inline bool isword(char ch) {
  return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch == '_');
}

inline bool iswhite(char ch) {
  return ch == ' ' || ch == '\n' || ch == '\t';
}

void
readtxt2tokarr(char txtfn[], char *tokarr, int *toklen) {
  FILE *txtfile = LOCALOPEN_D(txtfn);
#ifdef DB
  fprintf(stderr, "Opening File %s under workdir\n", txtfn);
#endif
  panic_on("Open File Failed", txtfile != NULL);
  int length = fread(filebuf, 1, MAXFILESZ, txtfile);
  for (int i = 0; i < length; i++) {
    if (iswhite(filebuf[i])) continue;
    if (isword(filebuf[i])) {
      //It is a word left boundary
      if (i && !isword(filebuf[i - 1]))
        tokarr[(*toklen)++] = 'W';
    }
    else tokarr[(*toklen)++] = filebuf[i];
  }
  fclose(txtfile);
}

//print token arrays
void
tokdb() {
  FILE *prepres = LOCALOPEN_W("tok1.txt");
  for (int i = 0; i < tokarr1_len; i++)
    fputc(tokarr1[i], prepres);
  fclose(prepres);
  prepres = LOCALOPEN_W("tok2.txt");
  for (int i = 0; i < tokarr2_len; i++)
    fputc(tokarr2[i], prepres);
  fclose(prepres);
}

void
preptxt() {
  FILE *flist1 = LOCALOPEN("list1.txt");
  FILE *flist2 = LOCALOPEN("list2.txt");
  assert(flist1 != NULL);
  assert(flist2 != NULL);
  char txtfn[1024];
  while (~fscanf(flist1, "%s", txtfn)) {
    readtxt2tokarr(txtfn, tokarr1, &tokarr1_len);
  }
  while (~fscanf(flist2, "%s", txtfn)) {
    readtxt2tokarr(txtfn, tokarr2, &tokarr2_len);
  }
  fclose(flist1);
  fclose(flist2);
#ifdef DB
  tokdb();
#endif
  // readtxt(list1);
}