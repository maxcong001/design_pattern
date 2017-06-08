#include "singleton/singleton.hpp"
#include "util/logger.hpp"
class test {
 public:
  void hello_word() { __LOG(debug, "hello world!"); }
};

void singleton_example() {
  auto project_instance = Singleton<test>::Instance();
  project_instance->hello_word();
  project_instance->DestroyInstance();
}

int main() {
  // this is example for singleton
  singleton_example();
}
