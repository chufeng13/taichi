#pragma once

#include "taichi/lang_util.h"
#include <vector>
#include <memory>

TI_NAMESPACE_BEGIN
class DynamicLoader;
TI_NAMESPACE_END

TLANG_NAMESPACE_BEGIN

class SNode;

namespace cccp {

class CCKernel;
class CCLayout;
class CCRuntime;
struct CCContext;

using CCFuncEntryType = void(CCContext *);

class CCProgram {
  // Launch C compiler to compile generated source code, and run them
 public:
  CCProgram();
  ~CCProgram();

  void add_kernel(std::unique_ptr<CCKernel> kernel);
  CCFuncEntryType *load_kernel(std::string const &name);
  void compile_layout(SNode *root);
  void init_runtime();
  void relink();

  CCLayout *get_layout() {
    return layout.get();
  }

  CCRuntime *get_runtime() {
    return runtime.get();
  }

  void *get_root_buffer() {
    return root_buf.data();
  }

  void *get_gtmp_buffer() {
    return gtmp_buf.data();
  }

 private:
  std::vector<char> root_buf;
  std::vector<char> gtmp_buf;
  std::vector<std::unique_ptr<CCKernel>> kernels;
  std::unique_ptr<CCRuntime> runtime;
  std::unique_ptr<CCLayout> layout;
  std::unique_ptr<DynamicLoader> dll;
  std::string dll_path;
  bool need_relink{true};
};

}  // namespace cccp
TLANG_NAMESPACE_END
