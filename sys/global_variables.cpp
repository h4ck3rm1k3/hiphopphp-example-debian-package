
#include <runtime/base/hphp.h>
#include <sys/global_variables.h>
#include <sys/cpputil.h>
#include <sys/literal_strings.h>

namespace hphp_impl_starter {}
using namespace std;

namespace HPHP {
///////////////////////////////////////////////////////////////////////////////

bool has_eval_support = false;
GlobalVariables::~GlobalVariables() {}
#ifndef OMIT_JUMP_TABLE_GLOBAL_GETIMPL
class hashNodeGV {
public:
  hashNodeGV() {}
  hashNodeGV(int64 h, const char *n, int64 l, int64 o, int64 i) :
    hash(h), name(n), len(l), off(o), index(i), next(NULL) {}
  int64 hash;
  const char *name;
  int64 len;
  int64 off;
  int64 index;
  hashNodeGV *next;
};
static hashNodeGV *gvMapTable[32];
static hashNodeGV gvBuckets[12];

#define GET_GV_OFFSET(n) (offsetof(GlobalVariables, n))
const char *gvMapData[] = {
  (const char *)"HTTP_RAW_POST_DATA",
  (const char *)18,
  (const char *)GET_GV_OFFSET(gvm_HTTP_RAW_POST_DATA),
  (const char *)0,
  (const char *)"_COOKIE",
  (const char *)7,
  (const char *)GET_GV_OFFSET(gvm__COOKIE),
  (const char *)1,
  (const char *)"_ENV",
  (const char *)4,
  (const char *)GET_GV_OFFSET(gvm__ENV),
  (const char *)2,
  (const char *)"_FILES",
  (const char *)6,
  (const char *)GET_GV_OFFSET(gvm__FILES),
  (const char *)3,
  (const char *)"_GET",
  (const char *)4,
  (const char *)GET_GV_OFFSET(gvm__GET),
  (const char *)4,
  (const char *)"_POST",
  (const char *)5,
  (const char *)GET_GV_OFFSET(gvm__POST),
  (const char *)5,
  (const char *)"_REQUEST",
  (const char *)8,
  (const char *)GET_GV_OFFSET(gvm__REQUEST),
  (const char *)6,
  (const char *)"_SERVER",
  (const char *)7,
  (const char *)GET_GV_OFFSET(gvm__SERVER),
  (const char *)7,
  (const char *)"_SESSION",
  (const char *)8,
  (const char *)GET_GV_OFFSET(gvm__SESSION),
  (const char *)8,
  (const char *)"argc",
  (const char *)4,
  (const char *)GET_GV_OFFSET(gvm_argc),
  (const char *)9,
  (const char *)"argv",
  (const char *)4,
  (const char *)GET_GV_OFFSET(gvm_argv),
  (const char *)10,
  (const char *)"http_response_header",
  (const char *)20,
  (const char *)GET_GV_OFFSET(gvm_http_response_header),
  (const char *)11,
  NULL, NULL, NULL, NULL,
};

static class GVTableInitializer {
  public: GVTableInitializer() {
    hashNodeGV *b = gvBuckets;
    for (const char **s = gvMapData; *s; s++, b++) {
      const char *name = *s++;
      int64 len = (int64)(*s++);
      int64 off = (int64)(*s++);
      int64 index = (int64)(*s);
      int64 hash = hash_string(name, len);
      hashNodeGV *node = new(b) hashNodeGV
        (hash, name, len, off, index);
      int h = hash & 31;
      if (gvMapTable[h]) node->next = gvMapTable[h];
      gvMapTable[h] = node;
    }
  }
} gv_table_initializer;

static inline const hashNodeGV *
findGV(const char *name, int64 hash) {
  for (const hashNodeGV *p = gvMapTable[hash & 31];
       p; p = p->next) {
    if (p->hash == hash && strcmp(p->name, name) == 0) return p;
  }
  return NULL;
}
static inline const hashNodeGV *
findGV(const char *name, int64 len, int64 hash) {
  for (const hashNodeGV *p = gvMapTable[hash & 31];
       p; p = p->next) {
    if (p->hash == hash && p->len == len &&
        memcmp(p->name, name, len) == 0) {
      return p;
    }
  }
  return NULL;
}

Variant &GlobalVariables::getImpl(CStrRef s) {
  const hashNodeGV *p = findGV(s.data(), s.size(), s->hash());
  if (p) return *(Variant *)((char *)this + p->off);
  return LVariableTable::getImpl(s);
}
#endif // OMIT_JUMP_TABLE_GLOBAL_GETIMPL
bool GlobalVariables::class_exists(CStrRef s) {
  return false;
}
#ifndef OMIT_JUMP_TABLE_GLOBAL_EXISTS
bool GlobalVariables::exists(CStrRef s) const {
  const hashNodeGV *p = findGV(s.data(), s.size(), s->hash());
  if (p) return isInitialized(*(Variant *)((char *)this + p->off));
  if (!LVariableTable::exists(s)) return false;
  return isInitialized(const_cast<GlobalVariables*>(this)->get(s));
}
#endif // OMIT_JUMP_TABLE_GLOBAL_EXISTS
#ifndef OMIT_JUMP_TABLE_GLOBAL_GETINDEX
ssize_t GlobalVariables::getIndex(const char* s, int64 hash) const {
  const GlobalVariables *g ATTRIBUTE_UNUSED = this;
  if (hash < 0) hash = hash_string(s);
  const hashNodeGV *p = findGV(s, hash);
  if (p) return p->index;
  return m_px ? (m_px->getIndex(s) + 12) : -1;
}
#endif // OMIT_JUMP_TABLE_GLOBAL_GETINDEX

CVarRef GlobalVariables::getRefByIdx(ssize_t idx, Variant &k) {
  GlobalVariables *g ATTRIBUTE_UNUSED = this;
  if (idx >= 0 && idx < 12) {
    k = gvMapData[idx << 2]; // idx * 4
    if (idx < 12) {
      return g->stgv_Variant[idx];
    } else {
      return g->tgv_Variant[idx - 12];
    }
  }
  return Globals::getRefByIdx(idx, k);
}

///////////////////////////////////////////////////////////////////////////////
}
