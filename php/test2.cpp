
#include <php/test2.h>
#include <php/test2.fws.h>

// Dependencies
#include <runtime/ext/ext.h>
namespace hphp_impl_starter {}

namespace HPHP {
///////////////////////////////////////////////////////////////////////////////

/* preface starts */
extern CallInfo ci_;
/* preface finishes */
Variant pm_php$test2_php(bool incOnce, LVariableTable* variables, Globals *globals) {
  PSEUDOMAIN_INJECTION(run_init::test2.php, pm_php$test2_php);
  LVariableTable *gVariables ATTRIBUTE_UNUSED = (LVariableTable *)g;
  echo(NAMSTR(s_ss8fa3fe70, "hello world!"));
  return true;
}
namespace hphp_impl_splitter {}

///////////////////////////////////////////////////////////////////////////////
}
