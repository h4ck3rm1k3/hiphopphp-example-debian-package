
#include <runtime/base/hphp.h>
#include <sys/global_variables.h>

namespace hphp_impl_starter {}

using namespace std;

namespace HPHP {
///////////////////////////////////////////////////////////////////////////////


// Class Invoke Tables
Variant get_class_var_init(CStrRef s, const char *var) {
  DECLARE_GLOBAL_VARIABLES(g);
  return get_builtin_class_var_init(s, var);
}
ObjectData *create_object_only_no_init(CStrRef s, ObjectData* root /* = NULL*/) {
  DECLARE_GLOBAL_VARIABLES(g);
  return create_builtin_object_only_no_init(s, root);
}
Object create_object_only(CStrRef s, ObjectData* root /* = NULL*/) {
  Object r(create_object_only_no_init(s, root));
  r->init();
  return r;
}
bool get_call_info_static_method(MethodCallPackage &mcp) {
  StringData *s ATTRIBUTE_UNUSED (mcp.rootCls);
  return get_call_info_static_method_builtin(mcp);
}
const ObjectStaticCallbacks * get_object_static_callbacks(CStrRef s) {
  DECLARE_GLOBAL_VARIABLES(g);
  return get_builtin_object_static_callbacks(s);
}
Variant get_static_property(CStrRef s, const char *prop) {
  {
    const ObjectStaticCallbacks * cwo = get_object_static_callbacks(s);
    if (cwo) return cwo->os_get(prop);
  }
  return get_builtin_static_property(s, prop);
}
Variant *get_static_property_lv(CStrRef s, const char *prop) {
  {
    const ObjectStaticCallbacks * cwo = get_object_static_callbacks(s);
    if (cwo) return &cwo->os_lval(prop);
  }
  return get_builtin_static_property_lv(s, prop);
}
Variant get_class_constant(CStrRef s, const char *constant, bool fatal /* = true */) {
  {
    const ObjectStaticCallbacks * cwo = get_object_static_callbacks(s);
    if (cwo) return cwo->os_constant(constant);
  }
  return get_builtin_class_constant(s, constant, fatal);
}

///////////////////////////////////////////////////////////////////////////////
}
