
#include <stdio.h>
#include <array>
#include <memory>

class A
{

};

constexpr int V = 4;
int main()
{
    std::array<std::unique_ptr<A>, V> x = { std::make_unique<A>(), std::make_unique<A>() };

    return 0;
}
