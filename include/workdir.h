#ifndef _WORKDIR_
#define _WORKDIR_
extern char work_dir[], fnbuf[]; 

#define LOCALOPEN(name) \
  ({sprintf(fnbuf, "%s/" name, work_dir); fopen(fnbuf, "r");})
#define LOCALOPEN_D(name) \
  ({sprintf(fnbuf, "%s/%s", work_dir, name); fopen(fnbuf, "r");})
#define LOCALOPEN_W(name) \
  ({sprintf(fnbuf, "%s/" name, work_dir); fopen(fnbuf, "w");})
#define LOCALOPEN_WD(name) \
  ({sprintf(fnbuf, "%s/%s", work_dir, name); fopen(fnbuf, "w");})

#define LOCALOPEN_C(name, custom) \
  ({sprintf(fnbuf, "%s/" name, work_dir); fopen(fnbuf, custom);})
#define LOCALOPEN_CD(name, custom) \
  ({sprintf(fnbuf, "%s/%s", work_dir, name); fopen(fnbuf, custom);})

#endif