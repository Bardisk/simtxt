#include <basics.h>
#include <getopt.h>
#include <preptxt.h>
#include <hash.h>
#include <winnow.h>

int work_dir_len;
bool is_single_file = false;
bool use_stdin = false;
bool use_stdout = false;
char work_dir[1024];

int
main(int argc, char *argv[]){
  fprintf(stderr, "Simtxt (0.0.x) (Incomplished), Iskunion\n");
  int opt;
  while (~(opt = getopt(argc, argv, "sD:io"))) {
    switch (opt) {
      case 's':
        is_single_file = true;
        break;
      case 'D':
        work_dir_len = sprintf(work_dir, "%s", optarg);
        break;
      case 'i':
        use_stdin = true;
        break;
      case 'o':
        use_stdout = true;
        break;
      default:
        printf("Usage: simtxt -D Work_Directory\n");
        exit(1);
        break;
    }
  }
  if (use_stdout || use_stdin) {
    assert(is_single_file);
  }
  if (!work_dir[0])
    work_dir_len = sprintf(work_dir, ".");
  preptxt();
  get_shingles();
  getBM();
  return 0;
}