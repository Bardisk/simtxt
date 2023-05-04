//Preprocessing txts
#include <basics.h>

int tokarr1_len = 0, tokarr2_len = 0;
char tokarr1[MAXTOKSZ];
char tokarr2[MAXTOKSZ];
char filebuf[MAXFILESZ], fnbuf[1024];

inline bool isword(char ch) {
  return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch == '_') || (ch & (0x80));
}

inline bool iswhite(char ch) {
  return ch == ' ' || ch == '\n' || ch == '\t';
}

void
readtxt2tokarr(char txtfn[], char *tokarr, int *toklen) {
  FILE *txtfile = use_stdin ? stdin : LOCALOPEN_D(txtfn);
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
        if (!(*toklen) || tokarr[*toklen - 1] != 'W')
          tokarr[(*toklen)++] = 'W';
    }
    else tokarr[(*toklen)++] = filebuf[i];
  }
  fprintf(stderr, "%s: %d token(s)\n", txtfn ? txtfn : "stdin", *toklen);
  fclose(txtfile);
}

//print token arrays
void
tokdb() {
  // if (use_stdout) return ;
  FILE *prepres = LOCALOPEN_W("tok1.txt");
  for (int i = 0; i < tokarr1_len; i++)
    fputc(tokarr1[i], prepres);
  fclose(prepres);
  if (is_single_file) return ;
  prepres = LOCALOPEN_W("tok2.txt");
  for (int i = 0; i < tokarr2_len; i++)
    fputc(tokarr2[i], prepres);
  fclose(prepres);
}

void
preptxt() {
  char txtfn[1024];
  if (use_stdin)
    readtxt2tokarr(NULL, tokarr1, &tokarr1_len);
  else {
    FILE *flist1 = LOCALOPEN("list1.txt");
    assert(flist1 != NULL);
    while (~fscanf(flist1, "%s", txtfn)) {
      readtxt2tokarr(txtfn, tokarr1, &tokarr1_len);
    }
    fclose(flist1);
  }
  
  if (is_single_file) goto prep_end;
  
  FILE *flist2 = LOCALOPEN("list2.txt");
  assert(flist2 != NULL);
  while (~fscanf(flist2, "%s", txtfn)) {
    readtxt2tokarr(txtfn, tokarr2, &tokarr2_len);
  }
  fclose(flist2);

  prep_end:
#ifdef DB
  tokdb();
#endif
  // readtxt(list1);
}