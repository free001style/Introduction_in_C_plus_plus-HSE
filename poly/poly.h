#pragma once
#include <vector>
#include <map>
#include <iostream>

int64_t Power(const int&, const int&);
class Poly {
private:
    std::map<int, int> polinom_;

public:
    Poly();
    Poly(const std::vector<int>&);
    Poly(const std::map<int, int>&);
    Poly(const Poly&);
    int64_t operator()(const int&) const;
    friend bool operator!=(const Poly&, const Poly&);
    friend bool operator==(const Poly&, const Poly&);
    friend Poly operator-(const Poly&, const Poly&);
    friend Poly operator+(const Poly&, const Poly&);
    friend Poly operator+=(Poly&, const Poly&);
    friend Poly operator-=(Poly&, const Poly&);
    friend Poly operator*(const Poly&, const Poly&);
    Poly operator-() const;
    Poly operator=(const Poly&);
    friend std::ostream& operator<<(std::ostream&, const Poly&);
};
