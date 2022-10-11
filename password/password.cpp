#include "password.h"
#include <cctype>

bool ValidatePassword(const std::string &password) {
    if (password.size() >= 8 && password.size() <= 14) {  //проверка длины
        int count_up = 0, count_low = 0, count_num = 0, count_other = 0;  //счётчики для провекри типов символов
        for (auto now: password) {
            if (char(now) >= 33 && char(now) <= 126) {  //провека на содержание символов с нужным кодом
                if (islower(now)) {  //проверка на нижний регистр
                    ++count_low;
                }
                if (isupper(now)) {  //проверка на верхний регистр
                    ++count_up;
                }
                if (isdigit(now)) {  //проверка на цифры
                    ++count_num;
                }
                if ((char(now) >= 33 && char(now) <= 47) || (char(now) >= 58 && char(now) <= 64) ||
                    (char(now) >= 91 && char(now) <= 96) || (char(now) >= 123 && char(now) <= 126)) {
                    ++count_other;
                }
            } else {
                return false;
            }
        }
        if ((count_up >= 1 && count_low >= 1 && count_num >= 1) ||
            (count_up >= 1 && count_low >= 1 && count_other >= 1) ||
            (count_up >= 1 && count_num >= 1 && count_other >= 1) ||
            (count_low >= 1 && count_num >= 1 && count_other >= 1)) {  //символов трёх классов должно быть как
            // минимум по одному
            return true;
        }
    }
    return false;
}
