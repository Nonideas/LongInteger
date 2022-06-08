#pragma once
#include <vector>

class LongInteger final {
    std::vector<int> number;
    bool is_negative;
public:
    LongInteger();
    LongInteger(int i);
    LongInteger(const char* iStr);
    LongInteger(const LongInteger& val);
    ~LongInteger() = default;
    size_t ToString(char* buff, size_t buff_lenght);

    LongInteger& operator= (int val);
    LongInteger& operator+=(int val);
    LongInteger& operator-=(int val);
    LongInteger& operator*=(int val);
    LongInteger& operator/=(int val);

    LongInteger& operator= (const LongInteger& val);
    LongInteger& operator+=(const LongInteger& val);
    LongInteger& operator-=(const LongInteger& val);
    LongInteger& operator*=(const LongInteger& val);
    LongInteger& operator/=(const LongInteger& val);

    bool operator==(const LongInteger& right) const;
    bool operator!=(const LongInteger& right) const;
    bool operator>=(const LongInteger& right) const;
    bool operator<=(const LongInteger& right) const;
    bool operator>(const LongInteger& right) const;
    bool operator<(const LongInteger& right) const;

    LongInteger operator+(const LongInteger& right) const;
    LongInteger operator-(const LongInteger& right) const;
    LongInteger operator*(const LongInteger& right) const;
    LongInteger operator/(const LongInteger& right) const;
    LongInteger operator%(const LongInteger& right) const;

    int number_get(const size_t i);
    bool is_negative_get();

protected:
private:
    bool isZero();
    static bool isMore(const LongInteger& left, const LongInteger& right);
    static LongInteger Plus(const LongInteger& min, const LongInteger& max);
    static LongInteger Minus(const LongInteger& min, const LongInteger& max);
    static LongInteger abs(const LongInteger& val);
    static LongInteger to_negative(const LongInteger& val);
};