
#include <runtime/base/hphp.h>
#include <sys/global_variables.h>
#include <sys/cpputil.h>

namespace hphp_impl_starter {}
using namespace std;

namespace HPHP {
///////////////////////////////////////////////////////////////////////////////

namespace global_state {
void get_static_global_variables(Array &res) {
  DECLARE_GLOBAL_VARIABLES(g);
  Array static_global_variables;
  static_global_variables.set("gv_HTTP_RAW_POST_DATA", g->GV(HTTP_RAW_POST_DATA));
  static_global_variables.set("gv__COOKIE", g->GV(_COOKIE));
  static_global_variables.set("gv__ENV", g->GV(_ENV));
  static_global_variables.set("gv__FILES", g->GV(_FILES));
  static_global_variables.set("gv__GET", g->GV(_GET));
  static_global_variables.set("gv__POST", g->GV(_POST));
  static_global_variables.set("gv__REQUEST", g->GV(_REQUEST));
  static_global_variables.set("gv__SERVER", g->GV(_SERVER));
  static_global_variables.set("gv__SESSION", g->GV(_SESSION));
  static_global_variables.set("gv_argc", g->GV(argc));
  static_global_variables.set("gv_argv", g->GV(argv));
  static_global_variables.set("gv_http_response_header", g->GV(http_response_header));
  res.set("static_global_variables", static_global_variables);
}

}

///////////////////////////////////////////////////////////////////////////////
}
