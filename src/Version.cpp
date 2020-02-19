#include "Version.h"
#include <llvm/Support/raw_ostream.h>

namespace llvm2graphml {

const char *llvm2graphmlVersionString() {
  return "@PROJECT_VERSION@";
}

const char *llvm2graphmlCommitString() {
  return "@GIT_COMMIT@";
}

const char *llvm2graphmlBuildDateString() {
  return "@BUILD_DATE@";
}

const char *llvmVersionString() {
  return "@LLVM_VERSION@";
}

void printVersionInformationStream(llvm::raw_ostream &out) {
  out << "Version: " << llvm2graphmlVersionString() << "\n";
  out << "Commit: " << llvm2graphmlCommitString() << "\n";
  out << "Date: " << llvm2graphmlBuildDateString() << "\n";
  out << "LLVM: " << llvmVersionString() << "\n";
}
} // namespace llvm2graphml