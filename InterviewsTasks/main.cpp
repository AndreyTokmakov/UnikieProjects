/**============================================================================
Name        : main.cpp
Created on  : 02.02.2024
Author      : Andrei Tokmakov
Version     : 1.0
Copyright   : Your copyright notice
Description : InterviewsTasks main
============================================================================**/

#include <iostream>
#include <string_view>
#include <algorithm>
#include <array>
#include <vector>
#include <set>

#include "StringUtilities.h"

namespace
{
    using StrSizeTPair = std::pair<std::string, size_t>;
    using StringPair = std::pair<std::string, std::string>;

    template<typename _Ty>
    std::ostream& operator<<(std::ostream& stream, const std::vector<_Ty>& vec)
    {
        for (const auto & v: vec)
            stream << v << ' ';
        return stream;
    }

    template<typename _Ty>
    std::ostream& operator<<(std::ostream& stream, const std::set<_Ty>& vec)
    {
        for (const auto & v: vec)
            stream << v << ' ';
        return stream;
    }
}


namespace Numbers
{
    int __gcd(int a, int b)
    {
        return 0 == b ? a : __gcd(b, a % b);
    }

    int __gcd1(int a, int b)
    {
        while (b != 0) {
            a = a % b;
            std::swap(a, b);
        }
        return a;
    }

    void GreatestCommonDivisor()
    {
        for (const auto& [values, expected] : std::vector<std::pair<std::pair<int, int>,int>> {
                {{9, 3}, 3},
                {{3, 9}, 3},
                {{0, 0}, 0},
                {{8, 6}, 2},
                {{128, 40}, 8},
                {{48, 18}, 6},
        })
        {
            std::cout << __gcd(values.first, values.second) << "  " <<  __gcd1(values.first, values.second)
                      << " -->  " << expected << std::endl;
        }
    }
}

namespace Numbers
{
    int reverse_number(int number)
    {
        int16_t sign = number > 0 ? 1: -1;
        number = number * sign;
        int reverse_number = 0;
        while (0 != number) {
            reverse_number = reverse_number * 10 + number % 10;
            number = number / 10;
        }
        return reverse_number * sign;
    }

    void ReverseNumber()
    {
        for (const auto& [num, expected]: std::vector<std::pair<int, int>> {
                {123,321},
                {-123,-321}
        })
        {
            std::cout << reverse_number(num) << "  " << expected << std::endl;
        };
    }
}

namespace Numbers
{
    int midpoint(int a, int b) {
        return a / 2 + b / 2 + static_cast<int>((a & 1) && (b & 1));
    }

    void MidPoint()
    {
        for (const auto& [values, expected]: std::vector<std::pair<std::pair<int, int>, int>>{
                {{1,1}, 1}, {{2,2}, 2},
                {{3,5}, 4},
                {{8,5}, 6},

        })
        {
            const int actual = midpoint(values.first, values.second);
            if (expected != actual) {
                std::cerr << expected << " != " << actual << std::endl;
                return;
            }
        }
        std::cout << "OK: All tests passed\n";
    }
}

namespace Numeric
{
    int add_digits(int value)
    {
        int tmp = 0;
        while (value > 9) {
            tmp = value; value = 0;
            while (tmp > 9) {
                value += tmp % 10;
                tmp = tmp / 10;
            }
            value += tmp;
        }
        return value;
    }

    /**
    Given an integer num, repeatedly add all its digits until the result has only one digit, and return it.
    Example 1:  Input: num = 38     Explanation: The process is
                Output: 2           38 --> 3 + 8 --> 11
                                    11 --> 1 + 1 --> 2
                                    Since 2 has only one digit, return it.
    */
    void AddDigits()
    {
        for (const auto& [value, expected]: std::vector<std::pair<int, int>>{
                {10, 1}, {38, 2}, {123, 6}, {1234, 1},
                {8888, 5}, {99992, 2}
        })
        {
            const int actual = add_digits(value);
            if (expected != actual) {
                std::cerr << expected << " != " << actual << std::endl;
                return;
            }
        }
        std::cout << "OK: All tests passed\n";
    }
}


namespace Strings
{
    int find(const std::string& haystack, const std::string& needle)
    {
        const int textSize = std::ssize(haystack), searchBlockSize = std::ssize(needle);
        for (int idx = 0, m = 0, n = 0; idx <= textSize - searchBlockSize; ++idx)
        {
            for (m = 0, n = idx; m < searchBlockSize; ++m, ++n) {
                if (needle[m] != haystack[n])
                    break;
            }
            if (m == searchBlockSize)
                return idx;
        }
        return -1;
    }

    void FindSubString()
    {
        for (const auto& [values, expected] : std::vector<std::pair<std::pair<std::string, std::string>,int>> {
                {{"aaabbbccc", "bbb"}, 3},
                {{"aaabbbccc", "ddd"}, -1},
                {{"aaa", "aaaa"}, -1},
                {{"", ""}, 0},
                {{"baabaa", "aa"}, 1},
        })
        {
            int pos = find(values.first, values.second);
            if (pos != expected)
                std::cerr << "Error: (" << values.first << ", " << values.second << ") != " << expected << std::endl;
        }

        std::cout << "All passed\n";
    }
}

namespace Strings
{
    std::string longest_word(const std::string& input)
    {
        std::vector<std::string_view> words;
        StringUtilities::split_to(input, words, " ");

        size_t longestIdx = 0;
        for (size_t idx = 0, maxLen = 0; idx < words.size(); ++idx)
        {
            if (words[idx].size() > maxLen) {
                longestIdx = idx;
                maxLen = words[idx].size();
            }
        }

        return std::string{words[longestIdx]};
    }

    void Longest_Word()
    {
        for (const auto  &[value, expected]: std::vector<StringPair> {
                {"11 222 33", "222"},
                {"1", "1"},
                {"", ""},
                {"Hello world aaaaaa bbbbbb", "aaaaaa"},

        })
        {
            const std::string actual = longest_word(value);
            if (expected != actual) {
                std::cerr << expected << " != " << actual << std::endl;
                return;
            }
        }
        std::cout << "OK: All tests passed\n";
    }
}

namespace Strings
{
    std::string intersperse_strings(const std::string& str1,
                                    const std::string& str2)
    {
        std::string result {};
        result.reserve(str1.size() + str2.size());

        for (size_t idx1 = 0, idx2 = 0, size1 = str1.size(), size2 = str2.size(); idx1 < size1 || idx2 < size2;)
        {
            if (idx1 < size1 && idx2 < size2)
            {
                result.append(1, str1[idx1++]);
                result.append(1, str2[idx2++]);
            }
            else if (idx1 < size1)
                result.append(1, str1[idx1++]);
            else if (idx2 < size2)
                result.append(1, str2[idx2++]);
        }

        return result;
    }

    void Intersperse_String()
    {
        for (const auto  &[values, expected]: std::vector<std::pair<StringPair, std::string>> {
                {{"12345", "abcde"}, "1a2b3c4d5e"},
                {{"12345", "a"}, "1a2345"},
                {{"", "12345"}, "12345"},
                {{"abcd", ""}, "abcd"},
                {{"123456789", "z9y08regqa57"}, "1z293y40586r7e8g9qa57"},
        })
        {
            const std::string actual = intersperse_strings(values.first, values.second);
            if (expected != actual) {
                std::cerr << expected << " != " << actual << std::endl;
                return;
            }
        }
        std::cout << "OK: All tests passed\n";
    }
}

namespace Strings
{
    int hamming_distance(const std::string& first,
                         const std::string& second)
    {
        int count = std::abs(std::ssize(first) - std::ssize(second));
        for (size_t idx1 {0}, idx2 {0}; idx1 < first.size() && idx2 < second.size(); ++idx1, ++idx2) {
            if (first[idx1] != second[idx2])
                ++count;
        }

        return count;
    }

    /**
     * Have the function HammingDistance(strArr) take the array of strings stored in strArr,
     * which will only contain two strings of equal length and return the Hamming distance between them.
     * The Hamming distance is the number of positions where the corresponding characters are different.
     * For example: if strArr is ["coder", "codec"] then your program should return 1.
     * The string will always be of equal length and will only contain lowercase characters from the alphabet and numbers.
     */
    void HammingDistance()
    {
        for (const auto  &[values, expected]: std::vector<std::pair<StringPair, int>> {
                {{"coder", "codec"}, 1},
                {{"coder1", "codec234"}, 4},
        })
        {
            const int actual = hamming_distance(values.first, values.second);
            if (expected != actual) {
                std::cerr << expected << " != " << actual << std::endl;
                return;
            }
        }
        std::cout << "OK: All tests passed\n";
    }
}

namespace Strings
{
    std::string roman_numeral_reduction(const std::string& str)
    {
        constexpr std::array<std::pair<char, u_int16_t>, 7> numerals {{
            {'M', 1000}, {'D', 500}, {'C', 100}, {'L', 50}, {'X', 10}, {'V', 5}, {'I', 1}
        }};

        int value = 0;
        for (const char c: str)
        {
            const auto mapping = std::find_if(numerals.cbegin(), numerals.cend(),[&](const auto& entry) {
                return entry.first == c;
            });
            value += mapping->second;

        }

        std::string result;
        while (value) {
            for (const auto& [ch, val]: numerals) {
                if (value >= val) {
                    value -= val;
                    result.append(1, ch);
                    break;
                }
            }
        }

        return result;
    }

    std::string roman_numeral_reduction_2(const std::string& str)
    {
        constexpr std::array<u_int16_t, 26> map = [] { ;
            std::array<u_int16_t, 26> tmp {};
            tmp['M' - 'A'] = 1000; tmp['D' - 'A'] = 500; tmp['C' - 'A'] = 100;
            tmp['L' - 'A'] = 50; tmp['X' - 'A'] = 10; tmp['V' - 'A'] = 5; tmp['I' - 'A'] = 1;
            return tmp;
        }();

        constexpr std::array<std::pair<char, u_int16_t>, 7> numerals {{
            {'M', 1000}, {'D', 500}, {'C', 100}, {'L', 50}, {'X', 10}, {'V', 5}, {'I', 1}
        }};

        int value = 0;
        for (const char c: str) {
            value += map[c - 'A'];
        }

        std::string result;
        while (value) {
            for (const auto& [ch, val]: numerals) {
                if (value >= val) {
                    value -= val;
                    result.append(1, ch);
                    break;
                }
            }
        }

        return result;
    }


    /**
     * Have the function RomanNumeralReduction(str) read str which will be a string of roman numerals in decreasing order.
     * The numerals being used are: I for 1, V for 5, X for 10, L for 50, C for 100, D for 500 and M for 1000.
     * Your program should return the same number given by str using a smaller set of roman numerals.
     * For example: if str is "LLLXXXVVVV" this is 200, so your program should return CC because this is the shortest
     * way to write 200 using the roman numeral system given above. If a string is given in its shortest form,
     * just return that same string.
     */
    void RomanNumeralReduction()
    {
        for (const auto  &[roman_number, expected]: std::vector<StringPair> {
                {"LLLXXXVVVV", "CC"},
                {"LLLXXXVVVVI", "CCI"},
                {"DD", "M"},
                {"DDD", "MD"},
                {"IIIII", "V"},
                {"XXXX", "XXXX"},
                {"XXXXX", "L"}
        })
        {
            std::string actual = roman_numeral_reduction(roman_number);
            if (expected != actual) {
                std::cerr << expected << " != " << actual << std::endl;
                return;
            }

            std::string actual2 = roman_numeral_reduction_2(roman_number);
            if (expected != actual2) {
                std::cerr << expected << " != " << actual << std::endl;
                return;
            }
        }
        std::cout << "OK: All tests passed\n";
    }
}



int main([[maybe_unused]] int argc,
         [[maybe_unused]] char** argv)
{
    const std::vector<std::string_view> args(argv + 1, argv + argc);

    // Numbers::GreatestCommonDivisor();
    // Numbers::ReverseNumber();
    // Numbers::Numbers();
    // Numbers::AddDigits();

    // Strings::FindSubString();
    // Strings::Longest_Word();
    // Strings::Intersperse_String();
    // Strings::HammingDistance();
    Strings::RomanNumeralReduction();

    return EXIT_SUCCESS;
}
