#include "word2vec.h"

#include <vector>
int ScalProd(const std::vector<int>& a, const std::vector<int>& b) {
    int sum = 0;
    for (int i = 0; i < a.size(); ++i) {
        sum += a[i] * b[i];
    }
    return sum;
}

std::vector<std::string> FindClosestWords(const std::vector<std::string>& words,
                                          const std::vector<std::vector<int>>& vectors) {
    std::vector<std::string> ans;
    std::vector<int> vec;
    for (size_t i = 1; i < vectors.size(); ++i) {  //поиск скалярного произведения
        vec.push_back(ScalProd(vectors[0], vectors[i]));
    }
    int max = -10000;
    for (size_t i = 0; i < vec.size(); ++i) {  //поиск максимума из всех произведений
        if (vec[i] > max) {
            max = vec[i];
        }
    }
    for (size_t i = 0; i < vec.size(); ++i) {  //проверка на повторения максимума и сопоставление вектора со словом
        if (vec[i] == max) {
            ans.push_back(words[i + 1]);
        }
    }
    return ans;
}
