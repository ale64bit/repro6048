#include <iostream>
#include <memory>

#include "tools/cpp/runfiles/runfiles.h"

using bazel::tools::cpp::runfiles::Runfiles;

int main(int argc, char **argv) {
  std::string error;
  std::unique_ptr<Runfiles> runfiles(Runfiles::Create(argv[0], &error));
  if (runfiles == nullptr) {
    std::cerr << "failed to create Runfiles: " << error << '\n';
    return -1;
  }
  std::string path = runfiles->Rlocation("repro6048/data/test.txt");
  std::cout << "path: " << path << '\n';

  std::unique_ptr<std::FILE, decltype(&std::fclose)> fp(
      std::fopen(path.c_str(), "r"), &std::fclose);
  if (!fp) {
    std::cerr << "file not found" << '\n';
    return -1;
  }
  return 0;
}
