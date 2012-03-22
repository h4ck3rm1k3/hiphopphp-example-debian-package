
#include <runtime/base/hphp.h>
#include <sys/global_variables.h>
#include <sys/cpputil.h>

namespace hphp_impl_starter {}
using namespace std;

namespace HPHP {
///////////////////////////////////////////////////////////////////////////////

namespace global_state {
void get_pseudomain_variables(Array &res) {
  DECLARE_GLOBAL_VARIABLES(g);
  Array pseudomain_variables;
  pseudomain_variables.set("run_pm_php$test2_php", g->run_pm_php$test2_php);
  res.set("pseudomain_variables", pseudomain_variables);
}

}

///////////////////////////////////////////////////////////////////////////////
}
