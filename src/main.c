#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <string.h>
#include <preptxt.h>

int work_dir_len;
char work_dir[1024];

int
main(int argc, char *argv[]){
  printf("Hello World from simtxt!\n");
  int opt;
  while (~(opt = getopt(argc, argv, "D:"))) {
    switch (opt) {
      case 'D':
        work_dir_len = sprintf(work_dir, "%s", optarg);
        break;
      default:
        printf("Usage: simtxt -D Work_Directory\n");
        exit(1);
        break;
    }
  }
  if (!work_dir[0])
    work_dir_len = sprintf(work_dir, ".");
  preptxt();
  return 0;
}