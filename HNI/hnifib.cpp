#include "hphp/runtime/base/base-includes.h"

namespace HPHP {

static int64_t HHVM_FUNCTION(hni_fib, int64_t n) {
  if (n <= 2) return 1;
  return HPHP::f_hni_fib(n - 2) + HPHP::f_hni_fib(n - 1);
}

static class HnifibExtension : public Extension {
 public:
  HnifibExtension() : Extension("hnifib") {}
  virtual void moduleInit() {
    HHVM_FE(hni_fib);
    loadSystemlib();
  }
} s_hnifib_extension;

HHVM_GET_MODULE(hnifib)
}
