#include <iostream>
#include "Log/DebugLog.h"
#include "Wheels/RBTree/RBTree.hpp"
int main()
{
    my_wheel::RBNode<int> *root = new my_wheel::RBNode<int>(10, my_wheel::RBNode<int>::RED, nullptr, nullptr, nullptr);
    return 0;
}