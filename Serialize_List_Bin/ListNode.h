#pragma once
#include <string>

struct ListNode {
	ListNode* prev = nullptr; // ��������� �� ���������� ��-� ������, ���� 'nullptr' � ������ ������ ������
	ListNode* next = nullptr;
	ListNode* rand = nullptr; // ��������� �� ������������ ��-� ������� ������, ���� 'nullptr'
	std::string data; // ������������ ���������������� ������
};