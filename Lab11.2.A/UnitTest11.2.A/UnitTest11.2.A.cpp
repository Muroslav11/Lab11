#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab11.2.A/Lab11.2.A.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest112
{
	TEST_CLASS(UnitTest112)
	{
	public:
		TEST_METHOD(TestCountGoodGrades)
		{
			char fname[] = "test_grades.dat";
			ofstream f(fname, ios::binary);

			Student s1 = { "Ivanov", 1, COMPUTER_SCIENCE, 4, 5, 3 };
			Student s2 = { "Petrov", 2, INFORMATICS, 3, 4, 5 };
			Student s3 = { "Sidorov", 3, MATH_ECON, 2, 3, 4 };

			f.write((char*)&s1, sizeof(Student));
			f.write((char*)&s2, sizeof(Student));
			f.write((char*)&s3, sizeof(Student));
			f.close();

			int ph, mt, inf;
			CountGoodGrades(fname, ph, mt, inf);

			Assert::AreEqual(1, ph);
			Assert::AreEqual(1, mt);
			Assert::AreEqual(1, inf);

			remove(fname);
		}

		TEST_METHOD(TestPercentExcellentPhysMath)
		{
			char fname[] = "test_percent.dat";
			ofstream f(fname, ios::binary);

			Student s1 = { "Ivanov", 1, COMPUTER_SCIENCE, 5, 5, 4 };
			Student s2 = { "Petrov", 2, INFORMATICS, 5, 4, 5 };
			Student s3 = { "Sidorov", 3, MATH_ECON, 4, 5, 5 };

			f.write((char*)&s1, sizeof(Student));
			f.write((char*)&s2, sizeof(Student));
			f.write((char*)&s3, sizeof(Student));
			f.close();

			double expectedPercent = 100.0 / 3.0;
			double actualPercent = PercentExcellentPhysMath(fname);

			Assert::AreEqual(expectedPercent, actualPercent, 0.01);

			remove(fname);
		}
	};
}