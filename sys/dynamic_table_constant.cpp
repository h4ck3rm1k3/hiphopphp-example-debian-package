
#include <runtime/base/hphp.h>
#include <sys/global_variables.h>

namespace hphp_impl_starter {}

using namespace std;

namespace HPHP {
///////////////////////////////////////////////////////////////////////////////


// Get Constant Table
void init_constant_table() { init_builtin_constant_table(); }
Variant get_constant(CStrRef name, bool error) {
  DECLARE_GLOBAL_VARIABLES(g);
  return get_builtin_constant(name, error);
}

///////////////////////////////////////////////////////////////////////////////
}
