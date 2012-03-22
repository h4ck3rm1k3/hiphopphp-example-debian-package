
#include <runtime/base/hphp.h>
#include <runtime/base/fiber_reference_map.h>
#include <sys/global_variables.h>
#include <sys/cpputil.h>

namespace hphp_impl_starter {}
using namespace std;

namespace HPHP {
///////////////////////////////////////////////////////////////////////////////

static hphp_const_char_map<int> s_gsmap;
class GlobalSymbolMapInitializer {
  public: GlobalSymbolMapInitializer() {
    static const char *names[] = {
      "gv_HTTP_RAW_POST_DATA",
      "gv__COOKIE",
      "gv__ENV",
      "gv__FILES",
      "gv__GET",
      "gv__POST",
      "gv__REQUEST",
      "gv__SERVER",
      "gv__SESSION",
      "gv_argc",
      "gv_argv",
      "gv_http_response_header",
      "k_SID",
      "run_pm_php$test2_php",
      0
    };
    int index = 0;
    for (const char **p = names; *p; p++) {
      s_gsmap[*p] = index++;
    }
  }
};
static GlobalSymbolMapInitializer s_gsmap_initializer;

void fiber_marshal_global_state(GlobalVariables *g1, GlobalVariables *g2,
 FiberReferenceMap &refMap) {
  g1->fiberMarshal(g2, refMap);
  if (g2->run_pm_php$test2_php) g1->run_pm_php$test2_php = true;
  refMap.marshal(g1->GV(HTTP_RAW_POST_DATA), g2->GV(HTTP_RAW_POST_DATA));
  refMap.marshal(g1->GV(_COOKIE), g2->GV(_COOKIE));
  refMap.marshal(g1->GV(_ENV), g2->GV(_ENV));
  refMap.marshal(g1->GV(_FILES), g2->GV(_FILES));
  refMap.marshal(g1->GV(_GET), g2->GV(_GET));
  refMap.marshal(g1->GV(_POST), g2->GV(_POST));
  refMap.marshal(g1->GV(_REQUEST), g2->GV(_REQUEST));
  refMap.marshal(g1->GV(_SERVER), g2->GV(_SERVER));
  refMap.marshal(g1->GV(_SESSION), g2->GV(_SESSION));
  refMap.marshal(g1->GV(argc), g2->GV(argc));
  refMap.marshal(g1->GV(argv), g2->GV(argv));
  refMap.marshal(g1->GV(http_response_header), g2->GV(http_response_header));
  refMap.marshal(g1->k_SID, g2->k_SID);
  refMap.marshal((Array&)(*g1), (Array&)(*g2));
}
void fiber_unmarshal_global_state(GlobalVariables *g1, GlobalVariables *g2,
 FiberReferenceMap &refMap, char default_strategy,
 const vector<pair<string, char> > &resolver) {
  g1->fiberUnmarshal(g2, refMap);
  hphp_string_map<char> strategies;
  char r[14]; memset(r, default_strategy, sizeof(r));
  for (unsigned int i = 0; i < resolver.size(); i++) {
    hphp_const_char_map<int>::const_iterator it =
      s_gsmap.find(resolver[i].first.c_str());
    if (it != s_gsmap.end()) r[it->second] = resolver[i].second;
    else strategies[resolver[i].first] = resolver[i].second;
  }

  if (g2->run_pm_php$test2_php) g1->run_pm_php$test2_php = true;
  refMap.unmarshal(g1->GV(HTTP_RAW_POST_DATA), g2->GV(HTTP_RAW_POST_DATA), r[0]);
  refMap.unmarshal(g1->GV(_COOKIE), g2->GV(_COOKIE), r[1]);
  refMap.unmarshal(g1->GV(_ENV), g2->GV(_ENV), r[2]);
  refMap.unmarshal(g1->GV(_FILES), g2->GV(_FILES), r[3]);
  refMap.unmarshal(g1->GV(_GET), g2->GV(_GET), r[4]);
  refMap.unmarshal(g1->GV(_POST), g2->GV(_POST), r[5]);
  refMap.unmarshal(g1->GV(_REQUEST), g2->GV(_REQUEST), r[6]);
  refMap.unmarshal(g1->GV(_SERVER), g2->GV(_SERVER), r[7]);
  refMap.unmarshal(g1->GV(_SESSION), g2->GV(_SESSION), r[8]);
  refMap.unmarshal(g1->GV(argc), g2->GV(argc), r[9]);
  refMap.unmarshal(g1->GV(argv), g2->GV(argv), r[10]);
  refMap.unmarshal(g1->GV(http_response_header), g2->GV(http_response_header), r[11]);
  refMap.unmarshal(g1->k_SID, g2->k_SID, r[12]);
  refMap.unmarshalDynamicGlobals((Array&)(*g1), (Array&)(*g2), default_strategy, strategies);
}

///////////////////////////////////////////////////////////////////////////////
}
