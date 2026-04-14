#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab11.3.B/Lab11.3.B.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTests
{
	TEST_CLASS(StudentLevelBTests)
	{
	public:

		TEST_METHOD(TestAverageWithUnion)
		{
			Student s;
			s.speciality = COMPUTER_SCIENCE;
			s.phys_grade = 5;
			s.math_grade = 4;
			s.extra.programming = 3;

			double expected = 4.0;
			double actual = GetAvg(s);
			Assert::AreEqual(expected, actual, 0.0001);
		}

		TEST_METHOD(TestBinSearchPosition)
		{
			const char* fname = "test_search.dat";
			ofstream f(fname, ios::binary);

			Student s1 = { "Popil", 2, INFORMATICS, 5, 5, 5 };
			s1.extra.numerical_methods = 5;

			Student s2 = { "Halyk", 1, COMPUTER_SCIENCE, 3, 3, 3 };
			s2.extra.programming = 3;

			f.write((char*)&s1, sizeof(Student));
			f.write((char*)&s2, sizeof(Student));
			f.close();

			int position = BinSearch(fname, "Halyk", 1, 3.0);

			Assert::AreEqual(2, position);

			remove(fname);
		}

		TEST_METHOD(TestBinSearchNotFound)
		{
			const char* fname = "test_empty.dat";
			int result = BinSearch(fname, "Unknown", 1, 4.0);
			Assert::AreEqual(-1, result);
		}
	};
}