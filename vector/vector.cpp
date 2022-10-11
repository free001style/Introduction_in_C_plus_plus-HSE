#include "vector.h"
Vector::Vector() {
    size_ = 0;
    capacity_ = 0;
    vector_ = nullptr;
}
Vector::Vector(size_t size) {
    assert(size > 0);
    vector_ = new int[size];
    size_ = size;
    capacity_ = size_;
    for (size_t i = 0; i < size; ++i) {
        vector_[i] = 0;
    }
}
Vector::Vector(std::initializer_list<ValueType> list) {
    size_ = list.size();
    capacity_ = list.size();
    vector_ = new int[capacity_];
    size_t i = 0;
    for (auto now : list) {
        vector_[i] = now;
        ++i;
    }
}
Vector::Vector(const Vector& other) {
    size_ = other.size_;
    vector_ = new int[other.capacity_];
    capacity_ = other.capacity_;
    for (size_t i = 0; i < other.size_; ++i) {
        vector_[i] = other[i];
    }
}
Vector::~Vector() {
    delete[] vector_;
}
Vector& Vector::operator=(const Vector& other) {
    size_ = other.size_;
    vector_ = new int[other.capacity_];
    capacity_ = other.capacity_;
    for (size_t i = 0; i < other.size_; ++i) {
        vector_[i] = other[i];
    }
    return *this;
}
Vector::SizeType Vector::Size() const {
    return size_;
}
Vector::SizeType Vector::Capacity() const {
    return capacity_;
}
Vector::ValueType Vector::operator[](size_t position) const {
    return vector_[position];
}
Vector::ValueType& Vector::operator[](size_t position) {
    return vector_[position];
}
void Vector::PopBack() {
    vector_[--size_] = 0;
}
void Vector::PushBack(const ValueType& new_element) {
    if (size_ == capacity_) {
        Memory();
    }
    vector_[size_++] = new_element;
}
void Vector::Clear() {
    size_ = 0;
}
const Vector::ValueType* Vector::Data() const {
    return this->vector_;
}
void Vector::Swap(Vector& other) {
    std::swap(other.capacity_, this->capacity_);
    std::swap(other.size_, this->size_);
    std::swap(other.vector_, this->vector_);
}
bool Vector::operator!=(const Vector& other) const {
    if (size_ != other.size_) {
        return true;
    } else {
        for (size_t i = 0; i < size_; ++i) {
            if (vector_[i] != other.vector_[i]) {
                return true;
            }
        }
    }
    return false;
}
bool Vector::operator==(const Vector& other) const {
    if (size_ != other.size_) {
        return false;
    } else {
        for (size_t i = 0; i < size_; ++i) {
            if (vector_[i] != other.vector_[i]) {
                return false;
            }
        }
    }
    return true;
}
std::strong_ordering Vector::operator<=>(const Vector& other) const {
    for (size_t i = 0; i < std::min(size_, other.size_); ++i) {
        if (vector_[i] < other.vector_[i]) {
            return std::strong_ordering::less;
        } else if (vector_[i] > other.vector_[i]) {
            return std::strong_ordering::greater;
        }
    }
    if (size_ < other.size_) {
        return std::strong_ordering::less;
    } else {
        return std::strong_ordering::greater;
    }
}
Vector::Iterator::Iterator(){};
Vector::Iterator::Iterator(ValueType* pointer) {
    it_ = pointer;
}
Vector::ValueType& Vector::Iterator::operator*() const {
    return *it_;
}
Vector::ValueType* Vector::Iterator::operator->() const {
    return this->it_;
}
Vector::Iterator& Vector::Iterator::operator=(Iterator other) {
    it_ = other.it_;
    return *this;
}
Vector::Iterator& Vector::Iterator::operator++() {
    ++it_;
    return *this;
}
Vector::Iterator Vector::Iterator::operator++(int) {
    Iterator temp = *this;
    ++it_;
    return temp;
}
Vector::Iterator& Vector::Iterator::operator--() {
    --it_;
    return *this;
}
Vector::Iterator Vector::Iterator::operator--(int) {
    Iterator temp = *this;
    --it_;
    return temp;
}
Vector::Iterator Vector::Iterator::operator+(DifferenceType shift) {
    Vector::Iterator copy_it;
    copy_it.it_ = it_;
    copy_it.it_ += shift;
    return copy_it;
}
Vector::DifferenceType Vector::Iterator::operator-(Iterator other) {
    Vector::Iterator copy_it;
    copy_it.it_ = it_;
    return copy_it.it_ - other.it_;
}
Vector::Iterator& Vector::Iterator::operator+=(DifferenceType shift) {
    it_ += shift;
    return *this;
}
Vector::Iterator& Vector::Iterator::operator-=(DifferenceType shift) {
    it_ -= shift;
    return *this;
}
bool Vector::Iterator::operator!=(const Iterator& other) const {
    return it_ != other.it_;
}
bool Vector::Iterator::operator==(const Iterator& other) const {
    return it_ == other.it_;
}
std::strong_ordering Vector::Iterator::operator<=>(const Iterator& other) const {
    if (it_ < other.it_) {
        return std::strong_ordering::less;
    } else {
        return std::strong_ordering::greater;
    }
}
Vector::Iterator Vector::begin() {
    return Iterator(&vector_[0]);
}
Vector::Iterator Vector::end() {
    return Iterator(&vector_[size_]);
}
Vector::Iterator Vector::Begin() {
    return Iterator(&vector_[0]);
}
Vector::Iterator Vector::End() {
    return Iterator(&vector_[size_]);
}
void Vector::Reserve(SizeType new_capacity) {
    if (new_capacity > capacity_) {
        capacity_ = new_capacity - capacity_;
        int* vec = vector_;
        vector_ = new int[capacity_];
        for (size_t i = 0; i < size_; ++i) {
            vector_[i] = vec[i];
        }
        delete[] vec;
    }
}
