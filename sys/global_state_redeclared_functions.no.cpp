
#include <runtime/base/hphp.h>
#include <sys/global_variables.h>
#include <sys/cpputil.h>

namespace hphp_impl_starter {}
using namespace std;

namespace HPHP {
///////////////////////////////////////////////////////////////////////////////

namespace global_state {
void get_redeclared_functions(Array &res) {
  DECLARE_GLOBAL_VARIABLES(g);
  Array redeclared_functions;
  res.set("redeclared_functions", redeclared_functions);
}

}

///////////////////////////////////////////////////////////////////////////////
}
