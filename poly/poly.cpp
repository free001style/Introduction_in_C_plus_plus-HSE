#include "poly.h"

int64_t Power(const int& a, const int& b) {
    int64_t res = 1;
    for (size_t i = 0; i < b; ++i) {
        res *= a;
    }
    return res;
}

Poly::Poly() {
    polinom_ = {{0, 0}};
}

Poly::Poly(const std::vector<int>& value) {
    for (size_t i = 0; i < value.size(); ++i) {
        if (value[i] != 0) {
            polinom_.insert({i, value[i]});
        }
    }
}

Poly::Poly(const std::map<int, int>& value) {
    polinom_ = value;
}

Poly::Poly(const Poly& pol) {
    polinom_ = pol.polinom_;
}

int64_t Poly::operator()(const int& val) const {
    int64_t ans = 0;
    for (auto pair : polinom_) {
        ans += pair.second * Power(val, pair.first);
    }
    return ans;
}

bool operator!=(const Poly& pol1, const Poly& pol2) {
    return !(pol1.polinom_ == pol2.polinom_);
}

bool operator==(const Poly& pol1, const Poly& pol2) {
    return (pol1.polinom_ == pol2.polinom_);
}

Poly operator-(const Poly& pol1, const Poly& pol2) {
    Poly res;
    res.polinom_ = pol1.polinom_;
    for (auto now : pol2.polinom_) {
        if (res.polinom_.find(now.first) != res.polinom_.end()) {
            res.polinom_[now.first] -= now.second;
            if (res.polinom_[now.first] == 0 && res.polinom_.size() != 1) {
                res.polinom_.erase(now.first);
            }
        } else {
            res.polinom_.insert({now.first, -1 * now.second});
        }
    }
    if (res.polinom_.size() == 1) {
        for (auto now : res.polinom_) {
            if (now.second == 0) {
                res.polinom_ = {{0, 0}};
                return res;
            }
        }
    }
    return res;
}

Poly operator+(const Poly& pol1, const Poly& pol2) {
    Poly res;
    res.polinom_ = pol1.polinom_;
    for (auto now : pol2.polinom_) {
        if (res.polinom_.find(now.first) != res.polinom_.end()) {
            res.polinom_[now.first] += now.second;
            if (res.polinom_[now.first] == 0 && res.polinom_.size() != 1) {
                res.polinom_.erase(now.first);
            }
        } else {
            res.polinom_.insert({now.first, now.second});
        }
    }
    return res;
}

Poly operator+=(Poly& pol1, const Poly& pol2) {
    for (auto now : pol2.polinom_) {
        if (pol1.polinom_.find(now.first) != pol1.polinom_.end()) {
            pol1.polinom_[now.first] += now.second;
            if (pol1.polinom_[now.first] == 0 && pol1.polinom_.size() != 1) {
                pol1.polinom_.erase(now.first);
            }
        } else {
            pol1.polinom_.insert({now.first, now.second});
        }
    }
    return pol1;
}

Poly operator-=(Poly& pol1, const Poly& pol2) {
    for (auto now : pol2.polinom_) {
        if (pol1.polinom_.find(now.first) != pol1.polinom_.end()) {
            pol1.polinom_[now.first] -= now.second;
            if (pol1.polinom_[now.first] == 0 && pol1.polinom_.size() != 1) {
                pol1.polinom_.erase(now.first);
            }
        } else {
            pol1.polinom_.insert({now.first, -1 * now.second});
        }
    }
    return pol1;
}

Poly operator*(const Poly& pol1, const Poly& pol2) {
    Poly ret;
    std::map<int, int> comp_sum;
    for (auto now1 : pol1.polinom_) {
        for (auto now2 : pol2.polinom_) {
            comp_sum.insert({now1.first + now2.first, now1.second * now2.second});
        }
        ret += comp_sum;
        comp_sum.clear();
    }
    return ret;
}

Poly Poly::operator-() const {
    Poly ret;
    ret.polinom_ = polinom_;
    for (auto& now : ret.polinom_) {
        now.second *= -1;
    }
    return ret;
}

Poly Poly::operator=(const Poly& pol) {
    polinom_ = pol.polinom_;
    return *this;
}
std::ostream& operator<<(std::ostream& out, const Poly& pol) {
    if (pol.polinom_.rbegin()->first != 0) {
        out << "y = " << pol.polinom_.rbegin()->second << "x^" << pol.polinom_.rbegin()->first;
    } else {
        out << "y = " << pol.polinom_.rbegin()->second;
    }
    for (int i = pol.polinom_.rbegin()->first - 1; i >= 0; --i) {
        if (pol.polinom_.find(i) != pol.polinom_.end()) {
            if (i != 0) {
                if (pol.polinom_.find(i)->second > 0) {
                    out << " + " << pol.polinom_.find(i)->second << "x^" << i;
                } else if (pol.polinom_.find(i)->second < 0) {
                    out << " - " << -1 * pol.polinom_.find(i)->second << "x^" << i;
                }
            } else {
                if (pol.polinom_.find(i)->second > 0) {
                    out << " + " << pol.polinom_.find(i)->second;
                } else if (pol.polinom_.find(i)->second < 0) {
                    out << " - " << -1 * pol.polinom_.find(i)->second;
                }
            }
        }
    }
    return out;
}