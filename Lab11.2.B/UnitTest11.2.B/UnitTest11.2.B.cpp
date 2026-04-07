#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab11.2.B/Lab11.2.B.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest112B
{
	TEST_CLASS(UnitTest112B)
	{
	public:
		TEST_METHOD(TestCountGoodGrades)
		{
			char fname[] = "test_grades.dat";
			ofstream f(fname, ios::binary);

			Student s1 = { "Ivanov", 1, COMPUTER_SCIENCE, 4, 5 };
			s1.programming_grade = 4;
			Student s2 = { "Petrov", 2, INFORMATICS, 5, 4 };
			s2.numerical_methods_grade = 4;
			Student s3 = { "Sidorov", 3, MATH_ECON, 3, 3 };
			s3.pedagogy_grade = 4;

			f.write((char*)&s1, sizeof(Student));
			f.write((char*)&s2, sizeof(Student));
			f.write((char*)&s3, sizeof(Student));
			f.close();

			int ph, mt, prg, num, ped;
			CountGoodGrades(fname, ph, mt, prg, num, ped);

			Assert::AreEqual(1, ph);
			Assert::AreEqual(1, mt);
			Assert::AreEqual(1, prg);
			Assert::AreEqual(1, num);
			Assert::AreEqual(1, ped);

			remove(fname);
		}

		TEST_METHOD(TestPercentExcellentPhysMath)
		{
			char fname[] = "test_percent.dat";
			ofstream f(fname, ios::binary);

			Student s1 = { "Ivanov", 1, COMPUTER_SCIENCE, 5, 5 };
			s1.programming_grade = 5;
			Student s2 = { "Petrov", 2, INFORMATICS, 5, 4 };
			s2.numerical_methods_grade = 5;

			f.write((char*)&s1, sizeof(Student));
			f.write((char*)&s2, sizeof(Student));
			f.close();

			double expected = 50.0;
			double actual = PercentExcellentPhysMath(fname);

			Assert::AreEqual(expected, actual, 0.01);

			remove(fname);
		}
	};
}