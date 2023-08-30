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

	// Возвращает количество элементов в списке за время O(1)
	[[nodiscard]] size_t GetSize() const noexcept;

	// Очищает список за время O(N)
	void Clear() noexcept;

	void Copy(List& obj);

	// Получить элемент списка по индексу
	std::string GetElement(int index);

	// Изменить значение элемента в указанной позиции
	void SetElement(std::string data_, int index);

	// Добавиляет элемент data в начало списка за время O(1)
	void AddBegin(const std::string& data);

	// Добавить элемент в конец списка
	void AddEnd(const std::string& data);
	
	// Добавить элемент в выбранную позицию
	void Insert(const std::string& data, int index);
	
	//Удаляет элемент по индексу
	void Delete(int index);
	
	//Проверка индекса на корректность
	bool CorrectIndex(int index);

	//Методы печати списка
	void PrintEnd();

	void printRandomElement();

	void PrintBegin();

	//сериализация и десериализация

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


