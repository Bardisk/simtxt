#include <basics.h>
#include <getopt.h>
#include <preptxt.h>
#include <hash.h>

int work_dir_len;
bool is_single_file = false;
char work_dir[1024];

int
main(int argc, char *argv[]){
  printf("Hello World from simtxt!\n");
  int opt;
  while (~(opt = getopt(argc, argv, "sD:"))) {
    switch (opt) {
      case 's':
        is_single_file = true;
        break;
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
  get_shingles();
  return 0;
}