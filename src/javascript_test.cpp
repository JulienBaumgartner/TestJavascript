#include <fstream>
#include "javascript_test.h"

namespace test {

	TEST_F(JavascriptTest, DuktapeCreateTest)
	{
		ASSERT_TRUE(js_);
	}

    TEST_F(JavascriptTest, DuktapeCallFunctionFromFile)
    {
        ASSERT_TRUE(js_);

        std::ifstream is("test.js", std::ios::in);
        ASSERT_TRUE(is.is_open());
        js_->AddFromStream(is);

        std::any value = js_->CallFunction("addition", { 2, 3 });
        ASSERT_EQ(5, std::any_cast<double>(value));
    }

    TEST_F(JavascriptTest, DuktapeCallMethodFromFile)
    {
        ASSERT_TRUE(js_);

        std::ifstream is("test.js", std::ios::in);
        ASSERT_TRUE(is.is_open());
        js_->AddFromStream(is);

        std::any value = js_->CallMethod("MyClass", "multiply", { 2, 3 });
        ASSERT_EQ(5, std::any_cast<double>(value));
    }
}