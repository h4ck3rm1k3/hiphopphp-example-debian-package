
#include <runtime/base/complex_types.h>
#include <sys/literal_strings_remap.h>


namespace HPHP {
///////////////////////////////////////////////////////////////////////////////

StaticString s_ss8fa3fe70("hello world!");

void init_literal_varstrings() {
  extern void sys_init_literal_varstrings();
  sys_init_literal_varstrings();
}

///////////////////////////////////////////////////////////////////////////////
}
