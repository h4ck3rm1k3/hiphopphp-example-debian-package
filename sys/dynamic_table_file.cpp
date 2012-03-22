
#include <runtime/base/hphp.h>

namespace hphp_impl_starter {}

using namespace std;

namespace HPHP {
///////////////////////////////////////////////////////////////////////////////

typedef Variant (*pm_t)(bool incOnce, LVariableTable* variables, Globals *globals);

// File Invoke Table
Variant pm_php$test2_php(bool incOnce, LVariableTable* variables, Globals *globals);

static Variant dummy_pm(bool oncOnce, LVariableTable* variables,   Globals *globals) { return true; }
class hashNodeFile {
public:
  hashNodeFile() {}
  hashNodeFile(int64 h, const char *n, const void *p) :
    hash(h), name(n), ptr(p), next(NULL) {}
  int64 hash;
  const char *name;
  const void *ptr;
  hashNodeFile *next;
};
static hashNodeFile *fileMapTable[2];
static hashNodeFile fileBuckets[1];

static class FileTableInitializer {
  public: FileTableInitializer() {
    const char *fileMapData[] = {
      (const char *)"test2.php", (const char *)&pm_php$test2_php,
      NULL, NULL, (const char *)&dummy_pm,
    };
    hashNodeFile *b = fileBuckets;
    for (const char **s = fileMapData; *s; s++, b++) {
      const char *name = *s++;
      const void *ptr = *s;
      int64 hash = hash_string(name, strlen(name));
      hashNodeFile *node = new(b) hashNodeFile(hash, name, ptr);
      int h = hash & 1;
      if (fileMapTable[h]) node->next = fileMapTable[h];
      fileMapTable[h] = node;
    }
  }
} file_table_initializer;

static inline pm_t findFile(const char *name, int64 hash) {
  for (const hashNodeFile *p = fileMapTable[hash & 1 ]; p; p = p->next) {
    if (p->hash == hash && !strcmp(p->name, name)) return (pm_t)p->ptr;
  }
  return NULL;
}

Variant invoke_file(CStrRef s, bool once /* = false */, LVariableTable* variables /* = NULL */,const char *currentDir /* = NULL */) {
  pm_t ptr = findFile(s.c_str(), s->hash());
  if (ptr) return ptr(once, variables, get_globals());
  if (s.empty()) return pm_php$test2_php(once, variables, get_globals());
  return throw_missing_file(s.c_str());
}

///////////////////////////////////////////////////////////////////////////////
}
