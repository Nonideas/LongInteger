#include "test.h"

class MemoryLeakDetector {
public:
	MemoryLeakDetector() {
		_CrtMemCheckpoint(&memState_);
	}

	~MemoryLeakDetector() {
		_CrtMemState stateNow, stateDiff;
		_CrtMemCheckpoint(&stateNow);
		int diffResult = _CrtMemDifference(&stateDiff, &memState_, &stateNow);
		if (diffResult)
			reportFailure(stateDiff.lSizes[1]);
	}
private:
	void reportFailure(unsigned int unfreedBytes) {
		FAIL() << "Memory leak of " << unfreedBytes << " byte(s) detected.";
	}
	_CrtMemState memState_;
};

TEST(Ctor, Default) {
	LongInteger n;
	ASSERT_EQ(n.number_get(0), 0);
	ASSERT_FALSE(n.is_negative_get());
}

TEST(Ctor, Int1) {
	LongInteger n(0);
	ASSERT_EQ(n.number_get(0), 0);
	ASSERT_FALSE(n.is_negative_get());
}

TEST(Ctor, Int2) {
	LongInteger n(-1);
	ASSERT_EQ(n.number_get(0), 1);
	ASSERT_TRUE(n.is_negative_get());
}

TEST(Ctor, String1) {
	MemoryLeakDetector leakDetector;
	LongInteger n("0");
	ASSERT_EQ(n.number_get(0), 0);
	ASSERT_FALSE(n.is_negative_get());
}

TEST(Ctor, String2) {
	MemoryLeakDetector leakDetector;
	LongInteger n("-1");
	ASSERT_EQ(n.number_get(0), 1);
	ASSERT_TRUE(n.is_negative_get());
}

TEST(Ctor, String3) {
	MemoryLeakDetector leakDetector;
	LongInteger n("");
	ASSERT_EQ(n.number_get(0), 0);
	ASSERT_FALSE(n.is_negative_get());
}

TEST(Ctor, LInt1) {
	MemoryLeakDetector leakDetector;
	LongInteger n;
	LongInteger m(n);
	ASSERT_EQ(m.number_get(0), 0);
	ASSERT_FALSE(m.is_negative_get());
}

TEST(Ctor, LInt2) {
	MemoryLeakDetector leakDetector;
	LongInteger n(-1);
	LongInteger m(n);
	ASSERT_EQ(m.number_get(0), 1);
	ASSERT_TRUE(m.is_negative_get());
}

TEST(ToString, Assepted1) {
	MemoryLeakDetector leakDetector;
	LongInteger n(0);
	char buf[] = "  ";
	EXPECT_EQ(2, n.ToString(buf, 3));
	ASSERT_STREQ("0", buf);
}

TEST(ToString, Assepted2) {
	MemoryLeakDetector leakDetector;
	LongInteger n(-123);
	char buf[] = "    ";
	EXPECT_EQ(5, n.ToString(buf, 5));
	ASSERT_EQ(strlen("-123"), strlen(buf));
	ASSERT_STREQ("-123", buf);
}

TEST(ToString, Overflow) {
	MemoryLeakDetector leakDetector;
	LongInteger n(123);
	char* buf = nullptr;
	EXPECT_EQ(4, n.ToString(buf, 2));
	ASSERT_STRNE("123", buf);
	ASSERT_STREQ(nullptr, buf);
}

TEST(Logic, Equality) {
	MemoryLeakDetector leakDetector;
	LongInteger n(2);
	LongInteger m(2);
	ASSERT_TRUE(n == m);
}

TEST(Logic, NotEquality) {
	MemoryLeakDetector leakDetector;
	LongInteger n(2);
	LongInteger m(3);
	ASSERT_TRUE(n != m);
}

TEST(Logic, More1) {
	MemoryLeakDetector leakDetector;
	LongInteger n(3);
	LongInteger m(2);
	ASSERT_TRUE(n > m);
}

TEST(Logic, More2) {
	MemoryLeakDetector leakDetector;
	LongInteger n(3);
	LongInteger m(-3);
	ASSERT_TRUE(n > m);
}

TEST(Logic, MoreEquality1) {
	MemoryLeakDetector leakDetector;
	LongInteger n(3);
	LongInteger m(2);
	ASSERT_TRUE(n >= m);
}

TEST(Logic, MoreEquality2) {
	MemoryLeakDetector leakDetector;
	LongInteger n(3);
	LongInteger m(3);
	ASSERT_TRUE(n >= m);
}

TEST(Logic, Less1) {
	MemoryLeakDetector leakDetector;
	LongInteger n(2);
	LongInteger m(3);
	ASSERT_TRUE(n < m);
}

TEST(Logic, Less2) {
	MemoryLeakDetector leakDetector;
	LongInteger n(-5);
	LongInteger m(3);
	ASSERT_TRUE(n < m);
}

TEST(Logic, LessEquality1) {
	MemoryLeakDetector leakDetector;
	LongInteger n(2);
	LongInteger m(3);
	ASSERT_TRUE(n <= m);
}

TEST(Logic, LessEquality2) {
	MemoryLeakDetector leakDetector;
	LongInteger n(323);
	LongInteger m(323);
	ASSERT_TRUE(n <= m);
}

TEST(Algebra, Assignment) {
	MemoryLeakDetector leakDetector;
	LongInteger n(-21341);
	LongInteger m("3");
	n = m;
	EXPECT_EQ(n.number_get(0), 3);
	ASSERT_FALSE(n.is_negative_get());
}

TEST(Algebra, Plus1) {
	MemoryLeakDetector leakDetector;
	LongInteger n(2);
	LongInteger m(3);
	LongInteger k(0);
	k = m + n;
	EXPECT_EQ(k.number_get(0), 5);
	ASSERT_FALSE(k.is_negative_get());
}

TEST(Algebra, Plus2) {
	MemoryLeakDetector leakDetector;
	LongInteger n(3);
	LongInteger m(-2);
	LongInteger k(0);
	k = m + n;
	EXPECT_EQ(k.number_get(0), 1);
	ASSERT_FALSE(k.is_negative_get());
}

TEST(Algebra, Plus3) {
	MemoryLeakDetector leakDetector;
	LongInteger n(-3);
	LongInteger m(-2);
	LongInteger k(0);
	k = m + n;
	EXPECT_EQ(k.number_get(0), 5);
	ASSERT_TRUE(k.is_negative_get());
}

TEST(Algebra, Plus4) {
	MemoryLeakDetector leakDetector;
	LongInteger n(-3);
	LongInteger m(2);
	LongInteger k(0);
	k = m + n;
	EXPECT_EQ(k.number_get(0), 1);
	ASSERT_TRUE(k.is_negative_get());
}

TEST(Algebra, Minus1) {
	MemoryLeakDetector leakDetector;
	LongInteger n(3);
	LongInteger m(2);
	LongInteger k(0);
	k = n - m;
	EXPECT_EQ(k.number_get(0), 1);
	ASSERT_FALSE(k.is_negative_get());
}

TEST(Algebra, Minus2) {
	MemoryLeakDetector leakDetector;
	LongInteger n(3);
	LongInteger m(-2);
	LongInteger k(0);
	k = n - m;
	EXPECT_EQ(k.number_get(0), 5);
	ASSERT_FALSE(k.is_negative_get());
}

TEST(Algebra, Minus3) {
	MemoryLeakDetector leakDetector;
	LongInteger n(-3);
	LongInteger m(2);
	LongInteger k(0);
	k = n - m;
	EXPECT_EQ(k.number_get(0), 5);
	ASSERT_TRUE(k.is_negative_get());
}

TEST(Algebra, Minus4) {
	MemoryLeakDetector leakDetector;
	LongInteger n(2);
	LongInteger m(3);
	LongInteger k(0);
	k = n - m;
	EXPECT_EQ(k.number_get(0), 1);
	ASSERT_TRUE(k.is_negative_get());
}

TEST(Algebra, PlasAssignment) {
	MemoryLeakDetector leakDetector;
	LongInteger n(2);
	LongInteger m(3);
	n += m;
	EXPECT_EQ(n.number_get(0), 5);
	ASSERT_FALSE(n.is_negative_get());
}

TEST(Algebra, PlasAssignmentInt) {
	MemoryLeakDetector leakDetector;
	LongInteger n(2);
	n += 3;
	EXPECT_EQ(n.number_get(0), 5);
	ASSERT_FALSE(n.is_negative_get());
}

TEST(Algebra, MinusAssignmentInt) {
	MemoryLeakDetector leakDetector;
	LongInteger n(2);
	LongInteger m(3);
	n -= m;
	EXPECT_EQ(n.number_get(0), 1);
	ASSERT_TRUE(n.is_negative_get());
}

TEST(Algebra, MinusAssignment) {
	MemoryLeakDetector leakDetector;
	LongInteger n(2);
	n -= 3;
	EXPECT_EQ(n.number_get(0), 1);
	ASSERT_TRUE(n.is_negative_get());
}

TEST(Algebra, Multiplication1) {
	MemoryLeakDetector leakDetector;
	LongInteger n(2);
	LongInteger m(3);
	LongInteger k(0);
	k = n * m;
	EXPECT_EQ(k.number_get(0), 6);
	ASSERT_FALSE(k.is_negative_get());
}

TEST(Algebra, Multiplication2) {
	MemoryLeakDetector leakDetector;
	LongInteger n(-2);
	LongInteger m(3);
	LongInteger k(0);
	k = n * m;
	EXPECT_EQ(k.number_get(0), 6);
	ASSERT_TRUE(k.is_negative_get());
}

TEST(Algebra, Multiplication3) {
	MemoryLeakDetector leakDetector;
	LongInteger n(123);
	LongInteger m(304);
	LongInteger k(0);
	k = n * m;
	EXPECT_EQ(k.number_get(0), 2);
	EXPECT_EQ(k.number_get(1), 9);
	EXPECT_EQ(k.number_get(2), 3);
	EXPECT_EQ(k.number_get(3), 7);
	EXPECT_EQ(k.number_get(4), 3);
	ASSERT_FALSE(k.is_negative_get());
}

TEST(Algebra, MultiplicationAssignment) {
	MemoryLeakDetector leakDetector;
	LongInteger n(2);
	LongInteger m(3);
	n *= m;
	EXPECT_EQ(n.number_get(0), 6);
	ASSERT_FALSE(n.is_negative_get());
}

TEST(Algebra, Div1) {
	MemoryLeakDetector leakDetector;
	LongInteger n(0);
	LongInteger m(2);
	LongInteger k(0);
	k = n / m;
	EXPECT_EQ(k.number_get(0), 0);
	ASSERT_FALSE(k.is_negative_get());
}

TEST(Algebra, Div2) {
	MemoryLeakDetector leakDetector;
	LongInteger n(7854);
	LongInteger m(625);
	LongInteger k(0);
	k = n / m;
	EXPECT_EQ(k.number_get(0), 2);
	EXPECT_EQ(k.number_get(1), 1);
	ASSERT_FALSE(k.is_negative_get());
}

TEST(Algebra, Div3) {
	MemoryLeakDetector leakDetector;
	LongInteger n(-7854);
	LongInteger m(625);
	LongInteger k(0);
	k = n / m;
	EXPECT_EQ(k.number_get(0), 2);
	EXPECT_EQ(k.number_get(1), 1);
	ASSERT_TRUE(k.is_negative_get());
}

TEST(Algebra, Div4) {
	MemoryLeakDetector leakDetector;
	LongInteger n(7854);
	LongInteger m(-625);
	LongInteger k(0);
	k = n / m;
	EXPECT_EQ(k.number_get(0), 2);
	EXPECT_EQ(k.number_get(1), 1);
	ASSERT_TRUE(k.is_negative_get());
}

TEST(Algebra, Mod1) {
	MemoryLeakDetector leakDetector;
	LongInteger n(7);
	LongInteger m(2);
	LongInteger k(0);
	k = n % m;
	EXPECT_EQ(k.number_get(0), 1);
	ASSERT_FALSE(k.is_negative_get());
}

TEST(Algebra, Mod2) {
	MemoryLeakDetector leakDetector;
	LongInteger n(7854);
	LongInteger m(625);
	LongInteger k(0);
	k = n % m;
	EXPECT_EQ(k.number_get(0), 4);
	EXPECT_EQ(k.number_get(1), 5);
	EXPECT_EQ(k.number_get(2), 3);
	ASSERT_FALSE(k.is_negative_get());
}

TEST(Algebra, Mod3) {
	MemoryLeakDetector leakDetector;
	LongInteger n(-7854);
	LongInteger m(-625);
	LongInteger k(0);
	k = n % m;
	EXPECT_EQ(k.number_get(0), 4);
	EXPECT_EQ(k.number_get(1), 5);
	EXPECT_EQ(k.number_get(2), 3);
	ASSERT_FALSE(k.is_negative_get());
}
