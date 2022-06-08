# LongInteger

LongInteger() -- Конструктор по умолчанию

LongInteger(int i) -- Конструктор определяющий LongInteger из знакового целого.

LongInteger(const char* iStr) -- Конструктор из строкового представления целого числи по основанию 10.

LongInteger(const LongInteger& val) -- Копирующий конструктор.

~LongInteger() -- деструктор.

size_t ToString(char* buff, size_t buff_lenght) -- Преобразует LongInteger в строковое представление целого числа по основанию 10.
   char* buff - Буфер для строки, size_t buff_lenght - длина буфера. Возвращает количество записанных в буфер байт (включая заключительный ноль). 
   Если в буфере не достаточно места, в буфер ничего не записывается и возвращается количество байт, необходимое для правильного вывода (включая заключительный ноль).


Стандартные операторы, принимающие в качестве аргументов int:

LongInteger& operator= (int val) -- Оператор присваивания, аналог конструктора из целого числа.

LongInteger& operator+=(int val) -- Оператор +=, прибавить...

LongInteger& operator-=(int val) -- Оператор -=, отнять...

LongInteger& operator*=(int val) -- Оператор *=, умножить на...

LongInteger& operator/=(int val) -- Оператор /=, поделить на...


Стандартные операторы, принимающие в качестве аргументов LongInteger

LongInteger& operator= (const LongInteger& val) -- Оператор присваивания, аналог конструктора копирующего конструктора.

LongInteger& operator+=(const LongInteger& val) -- Оператор +=, прибавить...

LongInteger& operator-=(const LongInteger& val) -- Оператор -=, отнять...

LongInteger& operator*=(const LongInteger& val) -- Оператор *=, умножить на...

LongInteger& operator/=(const LongInteger& val) -- Оператор /=, поделить на...
bool operator==(const LongInteger& right) -- Оператор ==, возвращает true если аргумент равен исходному числу
bool operator!=(const LongInteger& right) -- Оператор !=, возвращает true если аргумент не равен исходному числу
bool operator>=(const LongInteger &right) -- Оператор больше либо равно
bool operator<=(const LongInteger &right) -- Оператор меньше либо равно
bool operator>(const LongInteger &right) -- Оператор больше
bool operator<(const LongInteger &right) -- Оператор меньше
LongInteger operator+(const LongInteger& right) -- Оператор сложения длинных целых чисел
LongInteger operator-(const LongInteger& right) -- Оператор вычитания длинных целых чисел
LongInteger operator*(const LongInteger& right) -- Оператор умножения длинных целых чисел
LongInteger operator/(const LongInteger& right) -- Оператор деления длинных целых чисел
LongInteger operator%(const LongInteger &right) -- Оператор остаток от деления длинных целых чисел
