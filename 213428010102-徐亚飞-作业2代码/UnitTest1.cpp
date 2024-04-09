#include "pch.h"
#include "CppUnitTest.h"
#include "../Project/code.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(TestMethod1)
		{
			int test[6] = { 0,0,0,0,0,0 };
			Assert::AreEqual(0, find_max_add(6, test));
		}

		TEST_METHOD(TestMethod2)
		{
			int test[6] = { 0,1,2,3,4,5 };
			Assert::AreEqual(15, find_max_add(6, test));
		}

		TEST_METHOD(TestMethod3)
		{
			int test[6] = { 0,-1,-2,-3,-4,-5 };
			Assert::AreEqual(0, find_max_add(6, test));
		}

		TEST_METHOD(TestMethod4)
		{
			int test[6] = { -2,11,-4,13,-5,-2 };
			Assert::AreEqual(20, find_max_add(6, test));
		}
	};
}
