#pragma once
#include "List.h"

#include <iostream>
#include <cassert>
#include <fstream>

template <typename T>
std::string toString(T val)
{
	std::ostringstream oss;
	oss << val;
	return oss.str();
}

void TestList() {
	{
		const List list;
		assert(list.GetSize() == 0u);
		assert(list.IsEmpty() == true);
	}
	{
		auto count = 10;
		List list;
		for (auto i = 0; i < count; ++i)
			list.AddBegin(toString(i));

		assert(list.GetSize() == 10);
		assert(!list.IsEmpty());

		assert(list.CorrectIndex(3) == true);

		list.PrintBegin();
		list.printRandomElement();

		list.Delete(1);
		list.PrintBegin();
		list.printRandomElement();
		//
		list.Clear();
		assert(list.GetSize() == 0u);
		assert(list.IsEmpty() == true);
	}
	std::string fname = "D:\\serialize.bin";
	{
		std::cout << "Serialize" << std::endl;
		auto examples = { "one", "two","three","four","five" };
		List list;
		for (auto& el : examples)
			list.AddBegin(el);

		list.PrintBegin();
		list.printRandomElement();
		//
		std::ofstream out(fname, std::ios::out | std::ios::binary);
		list.Serialize(out);
	}
	{
		std::cout << "Deserialize" << std::endl;
		List list;
		std::ifstream in(fname, std::ios::in | std::ios::binary);
		list.Deserialize(in);
		list.PrintBegin();
		list.printRandomElement();
	}
}