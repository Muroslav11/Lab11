#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab11.3.A/Lab11.3.A.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTest113A
{
	TEST_CLASS(UnitTest113A)
	{
	public:

		TEST_METHOD(TestGetAvg)
		{
			Student s;
			s.phys_grade = 5;
			s.math_grade = 5;
			s.inf_grade = 2;
			double expected = 4.0;
			double actual = GetAvg(s);
			Assert::AreEqual(expected, actual, 0.0001);
		}

		TEST_METHOD(TestBinSearchNotFound)
		{
			const char* fname = "test_none.dat";
			int result = BinSearch(fname, "NoName", 1, 3.0);
			Assert::AreEqual(-1, result);
		}

		TEST_METHOD(TestBinSearchFound)
		{
			const char* fname = "test_search.dat";
			ofstream f(fname, ios::binary);

			Student s1 = { "Popil", 2, INFORMATICS, 5, 5, 5 };
			Student s2 = { "Halyk", 1, COMPUTER_SCIENCE, 3, 3, 3 };

			f.write((char*)&s1, sizeof(Student));
			f.write((char*)&s2, sizeof(Student));
			f.close();

			int index = BinSearch(fname, "Halyk", 1, 3.0);
			Assert::AreEqual(1, index);

			remove(fname);
		}
	};
}