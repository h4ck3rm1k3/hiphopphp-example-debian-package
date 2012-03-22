
#include <runtime/base/hphp.h>
#include <sys/global_variables.h>

namespace hphp_impl_starter {}

using namespace std;

namespace HPHP {
///////////////////////////////////////////////////////////////////////////////


// Function Invoke Table
bool get_call_info(const CallInfo *&ci, void *&extra, const char *s, int64 hash) {
  DECLARE_GLOBAL_VARIABLES(g);
  extra = NULL;
  return get_call_info_builtin(ci, extra, s, hash);
}
bool get_call_info_no_eval(const CallInfo *&ci, void *&extra, const char *s, int64 hash) {
  DECLARE_GLOBAL_VARIABLES(g);
  extra = NULL;
  return get_call_info_builtin(ci, extra, s, hash);
}

///////////////////////////////////////////////////////////////////////////////
}
