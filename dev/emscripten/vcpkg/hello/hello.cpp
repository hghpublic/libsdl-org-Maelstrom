// hello.cpp

#include <fmt/core.h>

int main()
{
    fmt::print("fmt version: {}\n", FMT_VERSION);
    fmt::print("Hello, {}!\n", "world");
}
