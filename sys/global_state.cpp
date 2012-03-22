
#include <runtime/base/hphp.h>
#include <sys/global_variables.h>
#include <sys/cpputil.h>

namespace hphp_impl_starter {}
using namespace std;

namespace HPHP {
///////////////////////////////////////////////////////////////////////////////

namespace global_state {
void get_static_global_variables(Array &res);
void get_dynamic_global_variables(Array &res) {
  DECLARE_GLOBAL_VARIABLES(g);
  Array dynamic_global_variables;
  dynamic_global_variables = *get_variable_table();
  res.set("dynamic_global_variables", dynamic_global_variables);
}

void get_method_static_variables(Array &res);
void get_method_static_inited(Array &res);
void get_class_static_variables(Array &res);
void get_dynamic_constants(Array &res);
void get_pseudomain_variables(Array &res);
void get_redeclared_functions(Array &res);
void get_redeclared_classes(Array &res);
}

using namespace global_state;

Array get_global_state() {
  Array res(Array::Create());
  get_static_global_variables(res);
  get_dynamic_global_variables(res);
  get_dynamic_constants(res);
  get_method_static_variables(res);
  get_method_static_inited(res);
  get_class_static_variables(res);
  get_pseudomain_variables(res);
  get_redeclared_functions(res);
  get_redeclared_classes(res);
  return res;
}


///////////////////////////////////////////////////////////////////////////////
}
