#include "pch.h"
#include "CppUnitTest.h"
#include "../AISTD2.3/FB.h"
#include "../AISTD2.3/Queue.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace lab3test
{
	TEST_CLASS(lab3test)
	{
	public:

		TEST_METHOD(key_exist)
		{
			Queue<int, string> queue;
			queue.push("A");
			queue.push("B");
			queue.push("C");
			Assert::AreEqual(queue.search_key("A"), 0);
			Assert::AreEqual(queue.search_key("B"), 1);
			Assert::AreEqual(queue.search_key("C"), 2);
		}

		TEST_METHOD(key_doesnt_exist)
		{
			Queue<int, string> queue;
			queue.push("A");
			queue.push("B");
			queue.push("C");
			Assert::AreEqual(queue.search_key("D"), -1);
		}
	};
}