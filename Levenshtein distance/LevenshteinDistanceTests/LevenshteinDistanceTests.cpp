#pragma once
#include "pch.h"
#include "CppUnitTest.h"
#include "..\Levenshtein distance.cpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LevenshteinDistanceTests
{
	TEST_CLASS(LevenshteinDistanceTests)
	{
	public:
		
		TEST_METHOD(TestAppendSymbols)
		{
			int dist = editDistance("app", "apple", 3, 5);
			Assert::IsTrue(dist == 2);
		}
		TEST_METHOD(TestRemoveSymbols)
		{
			int dist = editDistance("apple", "app", 5, 3);
			Assert::IsTrue(dist == 2);
		}
		TEST_METHOD(TestSubstituteSymbols)
		{
			int dist = editDistance("apple", "zpplx", 5, 5);
			Assert::IsTrue(dist == 2);
		}
		TEST_METHOD(TestEmptyStrings)
		{
			int dist = editDistance("", "", 0, 0);
			Assert::IsTrue(dist == 0);
		}
		TEST_METHOD(TestEqualStrings)
		{
			int dist = editDistance("bananas", "bananas", 7, 7);
			Assert::IsTrue(dist == 0);
		}
		TEST_METHOD(TestComplexStrings)
		{
			int dist = editDistance("kitten", "sitting", 6, 7);
			Assert::IsTrue(dist == 3);

			dist = editDistance("aaaaaaaa", "bbbbbbbb", 8, 8);
			Assert::IsTrue(dist == 8);
		}
	};
}
