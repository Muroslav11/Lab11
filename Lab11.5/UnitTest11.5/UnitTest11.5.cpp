#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab11.5/Lab11.5.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest115
{
	TEST_CLASS(UnitTest115)
	{
	public:

		TEST_METHOD(TestSort)
		{
			char fname[] = "test_sort.dat";
			ofstream f(fname, ios::binary);

			Institute inst1 = { "LNU", 100, {"AMI", "Math", 180.0} };
			Institute inst2 = { "KNU", 200, {"Cyber", "IT", 195.0} };

			f.write((char*)&inst1, sizeof(Institute));
			f.write((char*)&inst2, sizeof(Institute));
			f.close();

			Sort(fname);

			ifstream fin(fname, ios::binary);
			Institute res;
			fin.read((char*)&res, sizeof(Institute));

			Assert::AreEqual("KNU", res.name);
			Assert::AreEqual(195.0, res.fac.entrance_grade);

			fin.close();
			remove(fname);
		}

		TEST_METHOD(TestSearch)
		{
			char fname[] = "test_search.dat";
			ofstream f(fname, ios::binary);

			Institute inst = { "KPI", 150, {"FICT", "CS", 190.0} };
			f.write((char*)&inst, sizeof(Institute));
			f.close();

			ifstream fin(fname, ios::binary);
			Institute temp;
			bool found = false;
			double target = 190.0;

			while (fin.read((char*)&temp, sizeof(Institute))) {
				if (abs(temp.fac.entrance_grade - target) < 0.1) {
					found = true;
					break;
				}
			}
			fin.close();

			Assert::IsTrue(found);
			Assert::AreEqual("KPI", temp.name);

			remove(fname);
		}
	};
}