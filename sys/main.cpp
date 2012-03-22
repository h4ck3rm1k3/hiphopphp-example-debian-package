
#include <runtime/base/hphp.h>
#include <sys/global_variables.h>
#include <sys/cpputil.h>

namespace hphp_impl_starter {}
using namespace std;

namespace HPHP {
///////////////////////////////////////////////////////////////////////////////

IMPLEMENT_SMART_ALLOCATION_NOCALLBACKS(GlobalVariables)
GlobalVariables::GlobalVariables() {
  memset(&tgv_bool, 0, sizeof(tgv_bool));
  memset(&tgv_int, 0, sizeof(tgv_int));
  memset(&tgv_int64, 0, sizeof(tgv_int64));
  memset(&tgv_double, 0, sizeof(tgv_double));
  memset(&tgv_CallInfoPtr, 0, sizeof(tgv_CallInfoPtr));

  // Redeclared Classes
}


void init_static_variables() {
  ScalarArrays::initialize();
  init_constant_table();
}
static IMPLEMENT_THREAD_LOCAL(GlobalArrayWrapper, g_array_wrapper);
#if defined(USE_GCC_FAST_TLS)
static __thread GlobalVariables *g_variables;
GlobalVariables *get_global_variables() {
  ASSERT(g_variables);
  return g_variables;
}
GlobalVariables *get_global_variables_check() {
  if (!g_variables) g_variables = NEW(GlobalVariables)();
  return g_variables;
}
void free_global_variables() {
  if (g_variables) DELETE(GlobalVariables)(g_variables);
  g_variables = NULL;
  g_array_wrapper.destroy();
}

#else /* USE_GCC_FAST_TLS */
static ThreadLocal<GlobalVariables *> g_variables;
GlobalVariables *get_global_variables() {
  GlobalVariables *g = *(g_variables.getNoCheck());
  ASSERT(g);
  return g;
}
GlobalVariables *get_global_variables_check() {
  if (!*g_variables) *g_variables = NEW(GlobalVariables)();
  return *g_variables;
}
void free_global_variables() {
  GlobalVariables *g = *(g_variables.getNoCheck());
  if (g) DELETE(GlobalVariables)(g);
  g_variables.destroy();
  g_array_wrapper.destroy();
}
#endif /* USE_GCC_FAST_TLS */
void init_global_variables() {
  GlobalVariables *g = get_global_variables_check();
  ThreadInfo::s_threadInfo->m_globals = g;
  g->initialize();
}
LVariableTable *get_variable_table() { return (LVariableTable*)get_global_variables();}
Globals *get_globals() { return (Globals*)get_global_variables();}
SystemGlobals *get_system_globals() { return (SystemGlobals*)get_global_variables();}
Array get_global_array_wrapper(){ return g_array_wrapper.get();}

///////////////////////////////////////////////////////////////////////////////
}

#ifndef HPHP_BUILD_LIBRARY
int main(int argc, char** argv) {
  return HPHP::execute_program(argc, argv);
}
#endif
