
#ifndef __GENERATED_sys_global_variables_h3635be65__
#define __GENERATED_sys_global_variables_h3635be65__

#include <runtime/base/hphp.h>
namespace hphp_impl_starter {}

namespace HPHP {
///////////////////////////////////////////////////////////////////////////////


// Class Forward Declarations

class GlobalVariables : public SystemGlobals {
DECLARE_SMART_ALLOCATION_NOCALLBACKS(GlobalVariables);
public:
  GlobalVariables();
  ~GlobalVariables();

  virtual bool class_exists(CStrRef name);
  CallInfo* tgv_CallInfoPtr[1];
  RedeclaredObjectStaticCallbacksConst* tgv_RedeclaredObjectStaticCallbacksConstPtr[1];
  Variant tgv_Variant[1];
  bool tgv_bool[1];
  #define run_pm_php$test2_php tgv_bool[0]
  double tgv_double[1];
  int tgv_int[1];
  int64 tgv_int64[1];

  // Global Array Wrapper Methods
  virtual ssize_t staticSize() const {
    return 12;
  }

  // LVariableTable Methods
  virtual CVarRef getRefByIdx(ssize_t idx, Variant &k);
  virtual ssize_t getIndex(const char *s, int64 prehash) const;
  virtual Variant &getImpl(CStrRef s);
  virtual bool exists(CStrRef s) const;
};

// Scalar Arrays
class ScalarArrays : public SystemScalarArrays {
public:
  static void initialize();
  static void initializeNamed();

};


LVariableTable *get_variable_table();

///////////////////////////////////////////////////////////////////////////////
}

#endif // __GENERATED_sys_global_variables_h3635be65__
