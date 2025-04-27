#include <iostream>
#include "base/include/add.h"
#include "XTool/tool1/sub.h"
#include "Log/include/DebugLog.h"
#include "Wheels/RBTree/RBTree.hpp"

int main()
{
     std::cout << add(1, 2) << std:: endl;
     std::cout << sub(1, 2) << std:: endl;
     my_wheel::RBTNode<int> node;
     return 0;
}