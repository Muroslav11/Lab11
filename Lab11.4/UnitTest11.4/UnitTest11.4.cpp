#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab11.4/Lab11.4.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTest114
{
	TEST_CLASS(UnitTest114)
	{
	public:

		TEST_METHOD(TestSortLogic)
		{
			const char* fname = "test_sort.dat";
			ofstream f(fname, ios::binary);

			Route r1 = { "Kyiv", "Lviv", 50 };
			Route r2 = { "Odesa", "Kyiv", 10 };

			f.write((char*)&r1, sizeof(Route));
			f.write((char*)&r2, sizeof(Route));
			f.close();

			Sort((char*)fname);

			ifstream fin(fname, ios::binary);
			Route res;
			fin.read((char*)&res, sizeof(Route));

			Assert::AreEqual(10, res.routeNumber);
			Assert::AreEqual("Odesa", res.startPoint);

			fin.close();
			remove(fname);
		}

		TEST_METHOD(TestSearchFound)
		{
			const char* fname = "test_search.dat";
			ofstream f(fname, ios::binary);

			Route r1 = { "Warsaw", "Berlin", 101 };
			f.write((char*)&r1, sizeof(Route));
			f.close();

			ifstream fin(fname, ios::binary);
			Route r;
			bool found = false;
			int target = 101;

			while (fin.read((char*)&r, sizeof(Route))) {
				if (r.routeNumber == target) {
					found = true;
					break;
				}
			}
			fin.close();

			Assert::IsTrue(found);
			Assert::AreEqual("Warsaw", r.startPoint);

			remove(fname);
		}

		TEST_METHOD(TestSearchNotFound)
		{
			const char* fname = "test_empty.dat";
			ifstream f(fname, ios::binary);

			Route r;
			bool found = false;
			int target = 999;

			if (f) {
				while (f.read((char*)&r, sizeof(Route))) {
					if (r.routeNumber == target) {
						found = true;
						break;
					}
				}
				f.close();
			}

			Assert::IsFalse(found);
		}
	};
}