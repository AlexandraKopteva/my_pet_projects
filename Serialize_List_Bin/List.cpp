#include "List.h"
#include <exception>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>

List::List(const List& obj)
{
	Copy(obj);
}

List::List(List& obj)
{
}


List::~List() {
	Clear();
}

[[nodiscard]] bool List::IsEmpty() const noexcept {
	if (size_ == 0)
		return true;
	else
		return false;
}

[[nodiscard]] size_t List::GetSize() const noexcept {
	return static_cast<size_t>(size_);
}

void List::Clear() noexcept {
	if (IsEmpty()) return;

	for (int i = 0; i < size_; i++)
		Delete(0);
}

void List::Copy(const List& obj)
{
	Clear();
	ListNode* tmp = obj.head;
	while (tmp != nullptr)
	{
		AddEnd(tmp->data);
		tmp = tmp->next;
	}
}

std::string List::GetElement(int index)
{
	if (!CorrectIndex(index))
		throw std::out_of_range("Incorrect index.");

	ListNode* tmp = Move(index);
	return tmp->data;
}

void List::SetElement(std::string data_, int index)
{
	if (!CorrectIndex(index))
		return;
	ListNode* tmp = Move(index);
	tmp->data = data_;
}

// Добавиляет элемент data в начало списка за время O(1)
void List::AddBegin(const std::string& data) {
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
	catch (std::bad_alloc e)
	{
		// Если память не выделена, то вывести системное сообщение
		std::cout << e.what() << std::endl;
	}
}
// Добавить элемент в конец списка
void List::AddEnd(const std::string& data)
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
		std::cout << e.what() << std::endl;
	}
}
// Добавить элемент в выбранную позицию
void List::Insert(const std::string& data, int index)
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
	catch (std::bad_alloc e)
	{
		std::cout << e.what() << std::endl;
	}
}

void List::Delete(int index)
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

	//rand el
	for (auto it = head; it; it = it->next) {
		if (item == it->rand)
		{
			int rand_number = rand() % size_;
			it->rand = Move(rand_number);
		}
	}

	delete item;
}

bool List::CorrectIndex(int index)
{
	return (index >= 0) && (index < size_);
}

void List::PrintEnd()
{
	ListNode* temp = tail;
	while (temp != nullptr) {
		std::cout << temp->data << ' ';
		temp = temp->prev;
	}
	std::cout << std::endl;
}

void List::printRandomElement()
{
	std::cout << "printRandomElement" << std::endl;
	ListNode* temp = head;
	while (temp != nullptr) {
		std::cout << temp->rand->data << ' ';
		temp = temp->next;
	}
	std::cout << std::endl;
}
void List::PrintBegin()
{
	ListNode* temp = head;
	while (temp != nullptr) {
		std::cout << temp->data << ' ';
		temp = temp->next;
	}
	std::cout << std::endl;
}

void List::Serialize(std::ofstream& out)
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

void List::Deserialize(std::ifstream& in)
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

ListNode* List::Move(int index)
{
	ListNode* tmp = head;
	for (int i = 0; i < index; i++)
		tmp = tmp->next;
	return tmp;
}

void List::write(std::ostream& os, int8_t distance, const std::string& data)
{
	const auto len = static_cast<uint8_t>(data.size());
	os.write(reinterpret_cast<const char*>(&distance), sizeof(distance));
	os.write(reinterpret_cast<const char*>(&len), sizeof(len));
	if (len > 0)
		os.write(data.data(), len);
}

int8_t List::distance(ListNode* tmp)
{
	int8_t dis = 0;
	for (auto it = head; it; it = it->next)
	{
		if (it == tmp) break;
		++dis;
	}
	return dis;
}
