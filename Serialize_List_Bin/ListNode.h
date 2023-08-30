#pragma once
#include <string>

struct ListNode {
	ListNode* prev = nullptr; // указатель на предыдущий эл-т списка, либо 'nullptr' в случае начала списка
	ListNode* next = nullptr;
	ListNode* rand = nullptr; // указатель на произвольный эл-т данного списка, либо 'nullptr'
	std::string data; // произвольные пользовательские данные
};