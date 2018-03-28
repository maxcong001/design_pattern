#include "singleton/singleton.hpp"
#include "logger/logger.hpp"


void singleton_example() {
  class test {
   public:
    void hello_word() { __LOG(debug, "hello world!"); }
  };
  auto project_instance = Singleton<test>::Instance();
  project_instance->hello_word();
  Singleton<test>::DestroyInstance();
}

int main() {
  // this is example for singleton
  singleton_example();
}
