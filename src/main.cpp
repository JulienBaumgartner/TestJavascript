#include <stdio.h>
#include "duktape.h"
#include "../javascript/js_duktape.h"
#include <fstream>
#include <gtest/gtest.h>
#include "javascript_test.h"

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
