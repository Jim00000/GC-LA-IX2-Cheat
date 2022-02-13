#include <iostream>
#include <Windows.h>
#include <spdlog/spdlog.h>
#include "VTableManager.hpp"

using namespace GCLAX2;

struct StructTest
{
    StructTest() = default;

    ~StructTest() noexcept {}

    void foo1() 
    {
        spdlog::info("Invoke foo1");
    }

    virtual void foo2()
    {
        spdlog::info("Invoke foo2");
    }

    virtual void foo3()
    {
        spdlog::info("Invoke foo3");
    }

    virtual void foo4()
    {
        spdlog::info("Invoke foo4");
    }

    virtual void foo5()
    {
        spdlog::info("Invoke foo5");
    }

    virtual void foo6()
    {
        spdlog::info("Invoke foo6");
    }

    virtual void foo7(const char* const msg)
    {
        spdlog::info("Invoke foo7: {}", msg);
    }
};

void __stdcall hookPrintOutHelloWorld(StructTest* const obj, const char * const msg)
{
    // Run original function
    //const std::intptr_t* const vtable = VTableManager::searchOriginalVTable(obj);
    //auto mfp = &StructTest::foo7;
    //mfp = *(decltype(mfp)*)&vtable[5];
    //(obj->*(mfp))("YoYoYo");

    //const auto mfp = VTableManager::getOriginalMemberFunctionPointer<void (StructTest::*)(const char* const)>(obj, 5);
    const auto mfp = VTableManager::getOriginalMemberFunctionPointer<decltype(&StructTest::foo7)>(obj, 5);
    (obj->*(mfp))(msg);

    // Run hook function
    spdlog::info("Invoke hookPrintOutHelloWorld: {}", msg);
}

int main()
{
    spdlog::set_level(spdlog::level::trace);
    struct StructTest *container = new StructTest {};
    container->foo7("Hello Victim");
    std::cout << std::endl;

    VTableManager container_vtman {container};
    container_vtman.hijack();
    container_vtman.hook(5, hookPrintOutHelloWorld);
    std::cout << std::endl;
    container->foo7("Hello Victim");
    std::cout << std::endl;

    container_vtman.unhook(5);
    container->foo7("Hello Victim");
    std::cout << std::endl;

    container_vtman.restore();
    container->foo7("Hello Victim");
    std::cout << std::endl;

    delete container;
    return 0;
}