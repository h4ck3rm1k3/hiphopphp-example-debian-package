
#include <runtime/base/hphp.h>
#include <sys/global_variables.h>
#include <sys/cpputil.h>

namespace hphp_impl_starter {}
using namespace std;

namespace HPHP {
///////////////////////////////////////////////////////////////////////////////

namespace global_state {
void get_dynamic_constants(Array &res) {
  DECLARE_GLOBAL_VARIABLES(g);
  Array dynamic_constants;
  dynamic_constants.set("k_SID", g->k_SID);
  res.set("dynamic_constants", dynamic_constants);
}

}

///////////////////////////////////////////////////////////////////////////////
}
