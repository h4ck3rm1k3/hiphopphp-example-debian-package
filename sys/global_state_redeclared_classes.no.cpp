
#include <runtime/base/hphp.h>
#include <sys/global_variables.h>
#include <sys/cpputil.h>

namespace hphp_impl_starter {}
using namespace std;

namespace HPHP {
///////////////////////////////////////////////////////////////////////////////

namespace global_state {
void get_redeclared_classes(Array &res) {
  DECLARE_GLOBAL_VARIABLES(g);
  Array redeclared_classes;
  res.set("redeclared_classes", redeclared_classes);
}

}

///////////////////////////////////////////////////////////////////////////////
}
