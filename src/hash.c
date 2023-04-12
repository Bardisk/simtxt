#include <basics.h>

static const unsigned long long base = 233;

unsigned long long
krsm_hash(const char *from, const char *to) {
  unsigned long long ans = 0;
  for (const char *pos = from; pos != to; pos++) {
    ans += *pos; ans *= base;
  }
  return ans;
}