#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab11.1/Lab11.1.cpp" 

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTest111
{
	TEST_CLASS(UnitTest111)
	{
	public:

		TEST_METHOD(TestProcessEvenOddDistribution)
		{
			char testIn[] = "test_in.dat";
			char testEven[] = "test_even.dat";
			char testOdd[] = "test_odd.dat";

			ofstream f(testIn, ios::binary);
			int n1 = 2, n2 = 3;
			f.write((char*)&n1, sizeof(int));
			f.write((char*)&n2, sizeof(int));
			f.close();

			Process(testIn, testEven, testOdd);

			ifstream fEven(testEven, ios::binary);
			int resEven;
			fEven.read((char*)&resEven, sizeof(int));
			Assert::AreEqual(2, resEven);
			fEven.close();

			ifstream fOdd(testOdd, ios::binary);
			int resOdd;
			fOdd.read((char*)&resOdd, sizeof(int));
			Assert::AreEqual(3, resOdd); 
			fOdd.close();

			remove(testIn);
			remove(testEven);
			remove(testOdd);
		}
	};
}