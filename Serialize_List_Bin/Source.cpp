/*
* Implementation of the function to serialize and deserialize
* a doubly linked list. The data is written in binary format.
* The expected algorithmic complexity is less than the quadratic one.
*/

#include <iostream>
#include <string>
#include <cstring>
#include <map>
#include <sstream>
#include <cassert>
#include <exception>
#include <cstdio>
#include <stdio.h>
#include <iterator>
#include <fstream>
#include <vector>

using namespace std;

//структуру ListNode модифицировать нельзя
struct ListNode {
	ListNode* prev = nullptr; // указатель на предыдущий элемент
	//списка, либо `nullptr` в случае начала списка
	ListNode* next = nullptr;
	ListNode* rand = nullptr; // указатель на произвольный элемент
	//данного списка, либо `nullptr`
	std::string data; // произвольные пользовательские данные
};

class List {
public:
	void Serialize(std::ofstream& out)
	{
		if (out.is_open())
		{
			for (auto it = head; it; it = it->next) {
				int8_t distance_ = distance(it->rand);
				write(out, distance_, it->data);
			}
			out.close();
		}
		else {
			std::cerr << "Error open file." << std::endl;
		}
	}

	void Deserialize(std::ifstream& in)
	{
		if (in.is_open())
		{
			std::vector<int8_t> rand_el;
			char rand, count;

			//считываем позицию рандомного элемента
			//количество позиций занимаемых data
			while (in >> rand >> count) {
				rand_el.push_back(static_cast<int8_t>(rand));
				const int quantity = static_cast<int>(count);
				std::string symbols;
				symbols.resize(quantity);
				// data
				for (auto& el : symbols) {
					in >> el;
				}
				AddBegin(symbols);
			}
			in.close();

			//restore random element
			size_t j = 0;
			for (auto it = head; it; it = it->next) {
				it->rand = Move(rand_el[j]);
				++j;
			}
		}
		else {
			std::cerr << "Error open file." << std::endl;
		}
	}

	//
	List() :head(nullptr), tail(nullptr), size_(0) {}
	List(const List& obj)
	{
		Copy(obj);
	}
	~List() {
		Clear();
	}

	[[nodiscard]] bool IsEmpty() const noexcept {
		if (size_ == 0)
			return true;
		else
			return false;
	}
	// Возвращает количество элементов в списке за время O(1)
	[[nodiscard]] size_t GetSize() const noexcept {
		return static_cast<size_t>(size_);
	}
	// Очищает список за время O(N)
	void Clear() noexcept {
		if (IsEmpty()) return;

		int n = size_;
		for (int i = 0; i < n; i++)
			Delete(0);
	}

	void Copy(const List& obj)
	{
		Clear();
		ListNode* tmp = obj.head;
		while (tmp != nullptr)
		{
			AddEnd(tmp->data);
			tmp = tmp->next;
		}
	}

	// Получить элемент списка по индексу
	std::string GetElement(int index)
	{
		if (!CorrectIndex(index))
			throw out_of_range("Incorrect index.");

		ListNode* tmp = Move(index);
		return tmp->data;
	}

	// Изменить значение элемента в указанной позиции
	void SetElement(std::string data_, int index)
	{
		if (!CorrectIndex(index))
			return;
		ListNode* tmp = Move(index);
		tmp->data = data_;
	}

	// Добавиляет элемент data в начало списка за время O(1)
	void AddBegin(const std::string& data) {
		try {
			ListNode* new_node = new ListNode;
			new_node->next = nullptr;
			new_node->data = data;
			//Если список не пуст
			if (head != nullptr) {
				new_node->prev = tail;
				tail->next = new_node;
				tail = new_node;
			}
			//Если список пустой
			else {
				new_node->prev = nullptr;
				head = tail = new_node;
			}
			++size_;
			//Добавить рандомный элемент
			int rand_number = rand() % size_;
			new_node->rand = Move(rand_number);
		}
		catch (bad_alloc e)
		{
			// Если память не выделена, то вывести системное сообщение
			cout << e.what() << endl;
		}
	}
	// Добавить элемент в конец списка
	void AddEnd(const std::string& data)
	{
		try
		{
			ListNode* new_node = new ListNode;
			new_node->next = nullptr;
			new_node->prev = tail;
			new_node->data = data;

			if (tail != nullptr)
				tail->next = new_node;

			if (size_ == 0) {
				head = tail = new_node;
			}
			else {
				tail = new_node;
			}
			++size_;
			//Добавить рандомный элемент
			int rand_number = rand() % size_;
			new_node->rand = Move(rand_number);
		}
		catch (std::bad_alloc e)
		{
			cout << e.what() << endl;
		}
	}
	// Добавить элемент в выбранную позицию
	void Insert(const std::string& data, int index)
	{
		if (!CorrectIndex(index))
			return;

		if (index == size_)
		{
			AddEnd(data);
			return;
		}
		if (index == 0)
		{
			AddBegin(data);
			return;
		}
		try
		{
			ListNode* itemPrev = Move(index - 1);
			ListNode* item = Move(index);
			ListNode* new_node = new ListNode;
			new_node->data = data;
			new_node->next = item;
			new_node->prev = itemPrev;
			itemPrev->next = new_node;
			item->prev = new_node;
			++size_;
			//Добавить рандомный элемент
			int rand_number = rand() % size_;
			new_node->rand = Move(rand_number);
		}
		catch (bad_alloc e)
		{
			cout << e.what() << endl;
		}
	}
	void Delete(int index)
	{
		if (size_ == 0) return;

		if (!CorrectIndex(index))
			return;

		ListNode* item = Move(index);
		ListNode* itemPrev = item->prev;
		ListNode* itemNext = item->next;

		if ((size_ > 1) && (itemPrev != nullptr))
			itemPrev->next = itemNext;

		if ((itemNext != nullptr) && (size_ > 1))
			itemNext->prev = itemPrev;

		if (index == 0)
			head = itemNext;

		if (index == size_ - 1)
			tail = itemPrev;
		--size_;

		//rand
		for (auto it = head; it; it = it->next) {
			if (item == it->rand)
			{
				int rand_number = rand() % size_;
				it->rand = Move(rand_number);
			}
		}

		delete item;
	}
	// Печатает список
	void PrintEnd()
	{
		ListNode* temp = tail;
		while (temp != nullptr) {
			std::cout << temp->data << " ";
			temp = temp->prev;
		}
		std::cout << std::endl;
	}

	void printRandomElement()
	{
		std::cout << "printRandomElement" << std::endl;
		ListNode* temp = head;
		while (temp != nullptr) {
			std::cout << temp->rand->data << " ";
			temp = temp->next;
		}
		std::cout << std::endl;
	}
	void PrintBegin()
	{
		ListNode* temp = head;
		while (temp != nullptr) {
			cout << temp->data << " ";
			temp = temp->next;
		}
		std::cout << std::endl;
	}

	bool CorrectIndex(int index)
	{
		return (index >= 0) && (index < size_);
	}

private:

	ListNode* Move(int index)
	{
		ListNode* tmp = head;
		for (int i = 0; i < index; i++)
			tmp = tmp->next;
		return tmp;
	}

	void write(std::ostream& os, int8_t distance, const std::string& data)
	{
		const auto len = static_cast<uint8_t>(data.size());
		os.write(reinterpret_cast<const char*>(&distance), sizeof(distance));
		os.write(reinterpret_cast<const char*>(&len), sizeof(len));
		if (len > 0)
			os.write(data.data(), len);
	}

	int8_t distance(ListNode* tmp)
	{
		int8_t dis = 0;
		for (auto it = head; it; it = it->next)
		{
			if (it == tmp) break;
			++dis;
		}
		return dis;
	}
	//
	ListNode* head;
	ListNode* tail;
	int size_;
};

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

int main()
{
	TestList();
	return 0;
}