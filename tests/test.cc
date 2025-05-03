#include <iostream>
#include "DebugLog.h"

int main() {

    float a = 0.123456789;
    DBG_LOGI("This is a test log: %f", a);
    std::cout << a << std::endl;
    return 0;
}