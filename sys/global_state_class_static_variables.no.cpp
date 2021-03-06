
#include <runtime/base/hphp.h>
#include <sys/global_variables.h>
#include <sys/cpputil.h>

namespace hphp_impl_starter {}
using namespace std;

namespace HPHP {
///////////////////////////////////////////////////////////////////////////////

namespace global_state {
void get_class_static_variables(Array &res) {
  DECLARE_GLOBAL_VARIABLES(g);
  Array class_static_variables;
  res.set("class_static_variables", class_static_variables);
}

}

///////////////////////////////////////////////////////////////////////////////
}
