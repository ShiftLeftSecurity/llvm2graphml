#pragma once

namespace llvm {
class raw_ostream;
}

namespace llvm2graphml {

const char *llvm2graphmlVersionString();
const char *llvm2graphmlCommitString();
const char *llvm2graphmlBuildDateString();

const char *llvmVersionString();
void printVersionInformationStream(llvm::raw_ostream &out);

} // namespace llvm2graphml
