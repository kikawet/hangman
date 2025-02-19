
#include "ctest.h"
#include <string>

#ifndef TEST_COMMON_H
#define TEST_COMMON_H

#define C_STR(char) std::string(1, (char)).c_str()

#define ASSERT_CHAR(exp, real) ASSERT_STR(C_STR(exp), C_STR(real))
#define ASSERT_NOT_CHAR(exp, real) ASSERT_NOT_STR(C_STR(exp), C_STR(real))


#endif // TEST_COMMON_H