
#include "ctest.h"
#include <string>
#include <codecvt>
#include <locale>

#ifndef TEST_COMMON_H
#define TEST_COMMON_H

#define C_STR(char32) TO_STR(std::u32string(1, (char32))).c_str()

#define ASSERT_CHAR(exp, real) ASSERT_STR(C_STR(exp), C_STR(real))
#define ASSERT_NOT_CHAR(exp, real) ASSERT_NOT_STR(C_STR(exp), C_STR(real))

static std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;

#define ASSERT_U32STR(exp, real) ASSERT_STR(TO_STR((exp)).c_str(), TO_STR((real)).c_str())

#define TO_STR(u32str) converter.to_bytes((u32str))

#endif // TEST_COMMON_H