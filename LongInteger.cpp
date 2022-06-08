#include "LongInteger.hpp"
#include <cstring>

bool LongInteger::isZero() {
    return number.size() == 1 && number[0] == 0;
}

bool LongInteger::isMore(const LongInteger& left, const LongInteger& right) {
    if (!left.is_negative && right.is_negative) {
        return true;
    }
    else if (left.is_negative && !right.is_negative) {
        return false;
    }
    if (left.number.size() > right.number.size()) {
        return true;
    }
    else if (left.number.size() < right.number.size()) {
        return false;
    }
    for (int i = (int)left.number.size() - 1; i >= 0; --i) {
        if (left.number[i] > right.number[i]) {
            return true;
        }
        else if (left.number[i] < right.number[i]) {
            return false;
        }
    }
    return false;
}

LongInteger LongInteger::abs(const LongInteger& val) {
    LongInteger new_val(val);
    new_val.is_negative = false;
    return new_val;
}

LongInteger LongInteger::to_negative(const LongInteger& val)
{
    LongInteger new_val(val);
    new_val.is_negative = true;
    return new_val;
}

LongInteger LongInteger::Plus(const LongInteger& min, const LongInteger& max) {
    LongInteger answer;
    answer.number.pop_back();
    int remainder = 0;
    for (unsigned int i = 0; i < min.number.size(); ++i) {
        answer.number.push_back((min.number[i] + max.number[i] + remainder) % 10);
        remainder = (min.number[i] + max.number[i] + remainder) / 10;
    }
    for (size_t i = min.number.size(); i < max.number.size(); ++i) {
        answer.number.push_back((max.number[i] + remainder) % 10);
        remainder = (max.number[i] + remainder) / 10;
    }
    if (remainder != 0) {
        answer.number.push_back(remainder);
    }
    answer.is_negative = min.is_negative && max.is_negative;
    return answer;
}

LongInteger LongInteger::Minus(const LongInteger& min, const LongInteger& max) {
    LongInteger answer;
    answer.number.pop_back();
    bool duty = false;
    for (unsigned int i = 0; i < min.number.size(); ++i) {
        if (max.number[i] < min.number[i] + duty) {
            answer.number.push_back(10 + max.number[i] - min.number[i] - duty);
            duty = true;
        }
        else {
            answer.number.push_back(max.number[i] - min.number[i] - duty);
            duty = false;
        }
    }
    for (size_t i = min.number.size(); i < max.number.size(); ++i) {
        if (max.number[i] < duty) {
            answer.number.push_back(10 + max.number[i] - duty);
            duty = true;
        }
        else {
            answer.number.push_back(max.number[i] - duty);
            duty = false;
        }
    }
    answer.is_negative = !min.is_negative && max.is_negative && duty;

    while (answer.number.size() > 1 && answer.number.back() == 0) {
        answer.number.pop_back();
    }
    return answer;
}

int LongInteger::number_get(const size_t i) {
    return number[i];
}

bool LongInteger::is_negative_get() {
    return is_negative;
}

LongInteger::LongInteger() {
    number.push_back(0);
    is_negative = false;
}

LongInteger::LongInteger(int i) {
    if (i < 0) {
        is_negative = true;
        i = -i;
    }
    else {
        is_negative = false;
    }
    do {
        number.push_back(i % 10);
        i /= 10;
    } while (i);
}

LongInteger::LongInteger(const char* iStr) {
    if (iStr[0] == '\0') {
        is_negative = false;
        number.push_back(0);
    }
    else {
        int pointer;
        if (iStr[0] == '-') {
            is_negative = true;
            pointer = 1;
        }
        else {
            is_negative = false;
            pointer = 0;
        }
        for (int k = (int)strlen(iStr) - 1; k >= pointer; --k) {
            number.push_back((int)iStr[k] - '0');
        }
    }
}

LongInteger::LongInteger(const LongInteger& val) {
    number = val.number;
    is_negative = val.is_negative;
}

size_t LongInteger::ToString(char* buff, size_t buff_lenght) {
    size_t pointer = 0;
    if (buff_lenght < number.size() + (int)is_negative + 1) {
        return number.size() + (int)is_negative + 1;
    }
    if (is_negative && !isZero() && buff_lenght > 0) {
        buff[pointer] = '-';
        pointer++;
    }
    for (int i = (int)number.size() - 1; i >= 0; i--) {
            buff[pointer] = (char)(number[i] + (int)'0');
            pointer++;
    }
    buff[pointer] = '\0';
    return pointer + 1;
}

LongInteger& LongInteger::operator= (int val) {
    *this = LongInteger(val);
    return *this;
}

LongInteger& LongInteger::operator+=(int val) {
    *this += LongInteger(val);
    return *this;
}

LongInteger& LongInteger::operator-=(int val) {
    *this -= LongInteger(val);
    return *this;
}

LongInteger& LongInteger::operator*=(int val) {
    *this *= LongInteger(val);
    return *this;
}

LongInteger& LongInteger::operator/=(int val) {
    *this /= LongInteger(val);
    return *this;
}

LongInteger& LongInteger::operator=(const LongInteger& val) {
    this->number = val.number;
    this->is_negative = val.is_negative;
    return *this;
}

LongInteger& LongInteger::operator+=(const LongInteger& val) {
    *this = *this + val;
    return *this;
}

LongInteger& LongInteger::operator-=(const LongInteger& val) {
    *this = *this - val;
    return *this;
}

LongInteger& LongInteger::operator*=(const LongInteger& val) {
    *this = *this * val;
    return *this;
}

LongInteger& LongInteger::operator/=(const LongInteger& val) {
    *this = *this / val;
    return *this;
}

bool LongInteger::operator==(const LongInteger& right) const {
    if ((is_negative && !right.is_negative) || (!is_negative && right.is_negative)) {
        return false;
    }
    if (number.size() != right.number.size()) {
        return false;
    }
    for (unsigned int i = 0; i < number.size(); ++i) {
        if (number[i] != right.number[i]) {
            return false;
        }
    }
    return true;
}

bool LongInteger::operator!=(const LongInteger& right) const {
    return !operator==(right);
}

bool LongInteger::operator>=(const LongInteger& right) const {
    return !operator<(right);
}

bool LongInteger::operator<=(const LongInteger& right) const {
    return !operator>(right);
}

bool LongInteger::operator>(const LongInteger& right) const {
    return isMore(*this, right);
}

bool LongInteger::operator<(const LongInteger& right) const {
    return isMore(right, *this);
}

LongInteger LongInteger::operator+(const LongInteger& val) const {
    if (!is_negative && val.is_negative) {
        return *this - abs(val);
    }
    else if (is_negative && !val.is_negative) {
        return val - abs(*this);
    }
    else {
        if (*this < val) {
            return Plus(*this, val);
        }
        else {
            return Plus(val, *this);
        }
    }
}

LongInteger LongInteger::operator-(const LongInteger& val) const {
    if (is_negative && !val.is_negative) {
        return *this + to_negative(val);
    }
    else if (!is_negative && val.is_negative)
    {
        return *this + abs(val);
    }
    else {
        if (*this < val) {
            return to_negative(Minus(*this, val));
        }
        else {
            return Minus(val, *this);
        }
    }
}

LongInteger LongInteger::operator*(const LongInteger& val) const {
    LongInteger answer;
    if ((is_negative && !val.is_negative) || (!is_negative && val.is_negative)) {
        answer.is_negative = true;
    }
    answer.number.resize(number.size() + val.number.size() - 1, 0);
    for (int i = 0; i < val.number.size(); ++i) {
        for (unsigned int j = 0; j < number.size(); ++j) {
            answer.number[i + j] += val.number[i] * number[j];
        }
    }
    for (int i = 0; i < answer.number.size() - 1; ++i) {
        answer.number[i + 1] += answer.number[i] / 10;
        answer.number[i] = answer.number[i] % 10;
    }
    if (answer.number[answer.number.size() - 1] >= 10) {
        answer.number.push_back(answer.number[answer.number.size() - 1] / 10);
        answer.number[answer.number.size() - 2] %= 10;
    }
    while (answer.number.size() > 1 && answer.number.back() == 0) {
        answer.number.pop_back();
    }
    return answer;
}

LongInteger LongInteger::operator/(const LongInteger& val) const {
    if (abs(val) == LongInteger(0))
    {
        exit(1);
    }
    LongInteger answer;
    while (abs(answer * val) <= abs(*this))
    {
        answer += 1;
    }
    answer -= 1;
    if ((!is_negative && val.is_negative) || (is_negative && !val.is_negative)) {
        answer.is_negative = true;
    }
    return answer;
}

LongInteger LongInteger::operator%(const LongInteger& val) const {
    LongInteger div;
    div = *this / val;
    return *this - div * val;
}
