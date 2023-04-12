#include <basics.h>
#include <preptxt.h>

static const unsigned long long base = 233;
unsigned long long hashed_shingles1[MAXTOKSZ], hashed_shingles2[MAXTOKSZ];

static unsigned long long
krsm_hash(const char *from, const char *to) {
  unsigned long long ans = 0;
  for (const char *pos = from; pos != to; pos++) {
    ans += *pos; ans *= base;
  }
  return ans;
}

void
get_shingles() {
  for (int i = 0; i < SHINGLE_LEN(tokarr1_len); i++) {
    hashed_shingles1[i] = krsm_hash(tokarr1 + i, tokarr1 + i + MINGRAM);
  }
  
  if (!is_single_file)
  for (int i = 0; i < SHINGLE_LEN(tokarr2_len); i++) {
    hashed_shingles2[i] = krsm_hash(tokarr2 + i, tokarr2 + i + MINGRAM);
  }

#ifdef DB
  FILE *hs1 = LOCALOPEN_W("g1.hsdb");
  for (int i = 0; i < SHINGLE_LEN(tokarr1_len); i++) {
    fprintf(hs1, "%07d: %16llx\n", i, hashed_shingles1[i]);
  }
  fclose(hs1);

  if (is_single_file) return ;

  FILE *hs2 = LOCALOPEN_W("g2.hsdb");
  for (int i = 0; i < SHINGLE_LEN(tokarr2_len); i++) {
    fprintf(hs2, "%07d: %16llx\n", i, hashed_shingles2[i]);
  }
  fclose(hs2);
#else
//   FILE *bm1 = LOCALOPEN_C("g1.bm", "wb");
//     fwrite(hashed_shingles1 + i, sizeof (unsigned long long), bm1);
//   if (is_single_file) return ;
//   LOCALOPEN_C("g2.bm", "wb");
#endif
}

