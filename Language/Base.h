#pragma once
#include <iostream>

class Base
{
public:
    virtual void do_something()
    {
        std::cout << "i am Base\n";
    }
};

class Child_class : Base
{
public:
    void do_something() override
    {
        std::cout << "i am child\n";
    }
};
