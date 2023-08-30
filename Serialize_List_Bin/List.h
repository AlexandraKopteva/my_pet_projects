#pragma once
#include "ListNode.h"


/*
* Implementation of the function to serialize and deserialize
* a doubly linked list. The data is written in binary format.
* The expected algorithmic complexity is less than the quadratic one.
*/

class List {
public:

	List() : head(nullptr), tail(nullptr), size_(0) {}
	
	List(const List& obj);
	
	List(List& obj);

	List(List&& obj);

	~List();

	[[nodiscard]] bool IsEmpty() const noexcept;

	// ���������� ���������� ��������� � ������ �� ����� O(1)
	[[nodiscard]] size_t GetSize() const noexcept;

	// ������� ������ �� ����� O(N)
	void Clear() noexcept;

	void Copy(List& obj);

	// �������� ������� ������ �� �������
	std::string GetElement(int index);

	// �������� �������� �������� � ��������� �������
	void SetElement(std::string data_, int index);

	// ���������� ������� data � ������ ������ �� ����� O(1)
	void AddBegin(const std::string& data);

	// �������� ������� � ����� ������
	void AddEnd(const std::string& data);
	
	// �������� ������� � ��������� �������
	void Insert(const std::string& data, int index);
	
	//������� ������� �� �������
	void Delete(int index);
	
	//�������� ������� �� ������������
	bool CorrectIndex(int index);

	//������ ������ ������
	void PrintEnd();

	void printRandomElement();

	void PrintBegin();

	//������������ � ��������������

	void Serialize(std::ofstream& out);
	
	void Deserialize(std::ifstream& in);
	
private:

	ListNode* Move(int index);

	void write(std::ostream& os, int8_t distance, const std::string& data);

	int8_t distance(ListNode* tmp);

	//
	ListNode* head;
	ListNode* tail;
	int size_;
};


