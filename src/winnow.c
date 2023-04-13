#include <winnow.h>
#include <basics.h>
#include <hash.h>
#include <preptxt.h>

//mono queue, try to make the process linear
typedef struct {
  unsigned long long val;
  int num;
}mono_queue_t;
static mono_queue_t mono_queue[2 * WINDOW_SIZE];
static int head = 0, tail = 0;

#define pre(i) ((i) ? ((i) - 1) : (2 * WINDOW_SIZE - 1))
#define nxt(i) (((i) == 2 * WINDOW_SIZE - 1) ? 0 : ((i) + 1))

unsigned long long birthmark1[MAXTOKSZ], birthmark2[MAXTOKSZ];
int birthmark1_len = 0, birthmark2_len = 0;

static inline void queuein(unsigned long long val, int num) {
  while (head != tail && val <= mono_queue[pre(tail)].val) tail = pre(tail);
  mono_queue[tail] = (mono_queue_t) {.val = val, .num = num};
  tail = nxt(tail);
}
static inline void queueout(int lbound) {
  if (mono_queue[head].num <= lbound) head = nxt(head);
}
static inline unsigned long long queueque() {
  return mono_queue[head].val;
}
static inline void queuereset() {
  head = tail = 0;
}

void
getBM(){
  for (int i = 0; i < MIN(WINDOW_SIZE, SHINGLE_LEN(tokarr1_len)); i++)
    queuein(hashed_shingles1[i], i);
  unsigned long long lastmin = queueque();
  birthmark1[birthmark1_len++] = lastmin;
  for (int i = 0; i < SHINGLE_LEN(tokarr1_len) - WINDOW_SIZE; i++) {
    queueout(i);
    queuein(hashed_shingles1[i + WINDOW_SIZE], i + WINDOW_SIZE);
    if (queueque() != lastmin) {
      lastmin = queueque();
      birthmark1[birthmark1_len++] = lastmin;
    }
  }

  queuereset();
  for (int i = 0; i < MIN(WINDOW_SIZE, SHINGLE_LEN(tokarr2_len)); i++)
    queuein(hashed_shingles2[i], i);
  lastmin = queueque();
  birthmark2[birthmark2_len++] = lastmin;
  for (int i = 0; i < SHINGLE_LEN(tokarr2_len) - WINDOW_SIZE; i++) {
    queueout(i);
    queuein(hashed_shingles2[i + WINDOW_SIZE], i + WINDOW_SIZE);
    if (queueque() != lastmin) {
      lastmin = queueque();
      birthmark2[birthmark2_len++] = lastmin;
    }
  }

#ifdef DB
  FILE *bm1 = LOCALOPEN_W("g1.bmdb");
  for (int i = 0; i < birthmark1_len; i++) {
    fprintf(bm1, "%07d: %16llx\n", i, birthmark1[i]);
  }
  fclose(bm1);

  if (is_single_file) return ;

  FILE *bm2 = LOCALOPEN_W("g2.bmdb");
  for (int i = 0; i < birthmark2_len; i++) {
    fprintf(bm2, "%07d: %16llx\n", i, birthmark2[i]);
  }
  fclose(bm2);
#else
  FILE *bm1 = LOCALOPEN_C("g1.bm", "wb");
  fwrite(birthmark1, sizeof(unsigned long long), birthmark1_len, bm1);
  fclose(bm1);

  if (is_single_file) return ;

  FILE *bm2 = LOCALOPEN_C("g2.bm", "wb");
  fwrite(birthmark2, sizeof(unsigned long long), birthmark2_len, bm2);
  fclose(bm2);

#endif
  return ; 
}