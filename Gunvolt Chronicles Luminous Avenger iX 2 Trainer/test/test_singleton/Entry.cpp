#include <iostream>
#include <Helper/Singleton.hpp>

using namespace GCLAX2;

class Coo : Singleton<Coo>
{
    int value_1;
    int value_2;
public:
    virtual ~Coo() noexcept = default;

    const int getValue1() const noexcept
    {
        return this->value_1;
    }

    const int getValue2() const noexcept
    {
        return this->value_2;
    }

protected:
    Coo(int value_1, int value_2) noexcept : value_1{ value_1 }, value_2{ value_2 } {}
    
    friend static std::shared_ptr<Coo> Singleton<Coo>::get(int, int) noexcept;
};

std::shared_ptr<Coo> Singleton<Coo>::obj = nullptr;

int main()
{
    std::shared_ptr<Coo> coo = Singleton<Coo>::get(1, 2);
    std::cout << coo->getValue1() << std::endl;
    std::cout << coo->getValue2() << std::endl;
    return 0;
}