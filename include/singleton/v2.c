#include <string>
#include <map>
#include <functional>
#include <iostream>
#include <utility>
#include <mutex>
#include <tuple>

template <typename OBJ>
class message_bus
{
  public:
    static message_bus<OBJ> *instance()
    {
        static auto ins = new message_bus<OBJ>();
        return ins;
    }

    typedef std::function<void(void *, void *, std::string topic)> handler_f;
    void register_handler(std::string const &name, OBJ *t, handler_f f)
    {
        std::lock_guard<std::mutex> lck(mtx);

        for (auto it = invokers_.begin(); it != invokers_.end(); it++)
        {
            if (std::get<1>(it->second) == t)
            {
                invokers_.erase(it);
            }
        }

        (this->invokers_).emplace(name, std::make_tuple(f, t));
    }

    void call(const std::string &name, void *message)
    {
        std::lock_guard<std::mutex> lck(mtx);
        auto it = invokers_.equal_range(name);

        for (auto iter = it.first; iter != it.second; iter++)
        {
            handler_f cb;
            OBJ *obj;
            std::tie(cb, obj) = iter->second;
            cb((void *)obj, message, name);
        }
    }

    void remove_handler(std::string const &name, OBJ *t)
    {
        std::lock_guard<std::mutex> lck(mtx);
        for (auto it = invokers_.begin(); it != invokers_.end(); it++)
        {
            if (std::get<1>(it->second) == t)
            {
                invokers_.erase(it);
            }
        }
    }

  private:
    std::multimap<std::string, std::tuple<handler_f, OBJ *>> invokers_;
    std::mutex mtx;
};

int main()
{
    int a = 0;
#if 0
    message_bus<int> bus;
  

    bus.register_handler("test", &a, [](void *objp, void *msgp, std::string topic) { std::cout << "objp is : " << (void *)objp << " msgp is : " << (void *)msgp << " topic is : " << topic << std::endl; });
    bus.register_handler("test", &a, [](void *objp, void *msgp, std::string topic) { std::cout << "objp isxxxx : " << (void *)objp << " msgp is : " << (void *)msgp << " topic is : " << topic << std::endl; });
    bus.call("test", (void *)0);

    bus.remove_handler("test", &a);
    bus.call("test", (void *)0);
#endif
    auto bus = message_bus<int>::instance();
    bus->register_handler("test", &a, [](void *objp, void *msgp, std::string topic) { std::cout << "objp is : " << (void *)objp << " msgp is : " << (void *)msgp << " topic is : " << topic << std::endl; });
    bus->register_handler("test", &a, [](void *objp, void *msgp, std::string topic) { std::cout << "objp isxxxx : " << (void *)objp << " msgp is : " << (void *)msgp << " topic is : " << topic << std::endl; });
    bus->call("test", (void *)0);

    bus->remove_handler("test", &a);
    bus->call("test", (void *)0);
}
