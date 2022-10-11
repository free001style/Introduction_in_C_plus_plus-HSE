#include "palindrome.h"

bool IsPalindrome(const std::string &str) {
    size_t left = 0;
    if (str.size() < 2) {
        return true;
    }
    size_t right = str.size() - 1;
    while (left < right) {
        while (left < right && str[left] == ' ') {
            ++left;
        }
        while (left < right && str[right] == ' ') {
            --right;
        }
        if (str[left] != str[right]) {
            return false;
        } else {
            ++left;
            --right;
        }
    }
    return true;
}
