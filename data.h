#include <iostream>
#include <string>
#include <string.h>
#include <fstream>
#include <stdexcept>

using namespace std;

// �������� � ��� ����� ������� ������� �� ������� ��������:
// �������� ������������ ����� ������ ����� � ������
// �������� ������������ ���� ������� � �������� ������


// ***********************************************************************************************************************************************************************************


struct Newspaper {

	int postcode;
	string name;
	string publisher;
	int circulation;
	int period;
	int price;


	/* 
	Newspaper() {
	��� ������� ����� ����������� ��� � ������� �����������(�� ���� ������ ����� ������ ����� �������������� ������ �������),
	��� � ���� �� ����������� ��� � ���������(�� ���� ������ ����� ������ ����� �� ������� �������)
	��� ����� ����� �������� ����� � ���������� ������������ ������� �������� ������������ ����� ����� ����� � �����, ������ �� ������� ��������
	}
	
	void editNewspaper() {
	��� ������� ����� ����������� ��� � ������� �����������(�� ���� ������ ����� ������ ����� �������������� ������ �������),
	��� � ���� �� ����������� ��� � ���������(�� ���� ������ ����� ������ ����� �� ������� �������)
	��� ����� ����� �������� ����� � ���������� ������������ ������� �������� ������������ ����� ����� ����� � �����, ������ �� ������� ��������
	}

	void showNewspaper() {
	}

	CRUD - Create, Read, Update, Delete ?
	*/

	/*
	int getPostcode() {
	return this->postcode;
	}

	int getName() {
	return this->name;
	}

	int getPublisher() {
	return this->publisher;
	}
	*/

	/*
	bool lessPostcode(Newspaper* data) {
	return (this->postcode < data->getPostcode()); 
	}

	bool lessName(Newspaper* data) {
	return (this->name < data->getName()); 
	}
	*/

	/*
	bool compareName(string name) {
	return (this->name == name);
	}

	bool comparePublisher(string publisher) {
	return (this->publisher < publisher);
	}
	*/
};


// ***********************************************************************************************************************************************************************************


size_t readIndex() {
	size_t index;
	cout << "Enter the index: ";
	cin >> index; // ������ ������� ���������� ������� ����� ����� ������������ ������� ������� ����� �� ������� �������� 
	return index;
}

class listNewspaper {

private:

	class Node
	{
	public:
		Node(Newspaper* data, Node* next = nullptr, Node* prev = nullptr) { // constructor
			this->data = data;
			this->next = next;
			this->prev = prev;
		}

		
		// ~Node delete data;
		// CRUD - Create, Read ?, Update ?, Delete

		Newspaper* data;
		Node* next;
		Node* prev;

	};

	Node* head; // creating head
	Node* tail; // creating tail
	size_t Size; // error! ������, �������� �� cur

public:
	// CRUD - Create +, Read +, Update +, Delete +
	// �� �������� Read ������������� ��� ������ �� ������ ������ ������ �� �����, � ��� �� ����� ����� ������ � ����

	listNewspaper() // intialize the first object
	{
		head = nullptr;
		tail = nullptr;
		Size = 0;
	}

	~listNewspaper() // destructor
	{
		clear();
	}

	void clear() { // deleting all list items
		size_t size = GetSize();
		while (size) { 
			pop_front();
		}
	}

	size_t GetSize() { // ���������� �������: ������� ������ ������� �� cur �� head �� tail, ����������� ����������� ���-�� ���������� �������� � ���������� size
		return Size;
	}

	void push_front(Newspaper* data) { // incerting a node at the top of the list 

		if (Size > 1) {
			Node* cur = head;
			head = new Node(data, head);
			cur->prev = head;
		}
		else if (Size == 1) {
			head = new Node(data, head); // creating a new head element
			tail->prev = this->head; // at the tail, we put the previous on the new element
		}
		else {
			head = tail = new Node(data); //  new Node(data, head, tail);
		}
		Size++; // ����� ��� ����� ������

	}

	void push_back(Newspaper* data) { // incerting a node at the end of the list

		if (Size > 1) {
			Node* cur = tail;
			tail = new Node(data, nullptr, tail);
			cur->next = tail;
		}
		else if (Size == 1) {
			tail = new Node(data, nullptr, tail);
			head->next = this->tail;
		}
		else {
			head = tail = new Node(data); // new Node(data, head, tail);
		}
		Size++; // ����� ��� ����� ������

	}

	void pop_front() { // removing a node from the top of the list

		if (!isEmpty() == 0) {
			if (Size > 1) {
				Node* cur = head;
				head = head->next;
				delete cur;
			}
			else if (Size == 1) {
				Node* cur = head;
				tail = head = head->next;
				delete cur;
			}
			Size--; // ����� ��� ����� ������

		}
		else throw std::invalid_argument("Index is out of range");

	}

	void pop_back() { // removing a node from the end of the list

		size_t size = this->GetSize();
		if (!isEmpty()) {
			if (size > 1) {
				Node* item = tail->prev;
				delete tail;
				tail = item;
				tail->next = nullptr;
			}
			else if (size == 1) {
				delete head;
				head = tail = nullptr;	
			}
			Size--; // ����� ��� ����� ������
		}
		else throw std::invalid_argument("Index is out of range");
	}

	void incert(Newspaper* data, size_t index) { // adding an item by* index*     *before *���������� ��� ������������ (� ��������� ������� �������� index-1) ����������� ���� ������� �� ������� �������
		size_t size = GetSize();
		if (index <= size && index >= 0) {
			if (index == 0) push_front(data);
			else if (index == size) push_back(data);
			else if (index <= size / 2) { // if the head is closer
				Node* previous = this->head; //creating a node with the adress of the head
				for (int i = 0; i < index - 1; i++) { // walk from the head to the node that point to the one we need
					previous = previous->next;
				}
				Node* newNode = new Node(data, previous->next, previous); // creating a new node
				previous->next = newNode;
				Node* pNext = newNode->next;
				pNext->prev = newNode;
				Size++; // ����� ��� ����� ������
			}
		}
		else if (index > size / 2) { // all the tail is closer
			Node* pNext = this->tail;
			for (int i = size - 1; i > index; i--) {
				pNext = pNext->prev;
			}
			Node* newNode = new Node(data, pNext, pNext->prev); // creating a new node
			pNext->prev = newNode;
			Node* previous = newNode->prev;
			previous->next = newNode;
			Size++; // ����� ��� ����� ������
		}
		else throw std::invalid_argument("Index is out of range");
	}

	void remove(size_t index) { // deleting an item by index*                 *��������� ��� ������������ ����������� ���� ������� �� ������� �������
		size_t size = GetSize();
		if (index < size && index >= 0) {
			if (index == 0) pop_front();
			else if (index == size - 1) pop_back();
			else if (index <= size / 2) { // if the head is closer
				Node* previous = this->head;
				for (int i = 0; i < index - 1; i++) {
					previous = previous->next;
				}

				Node* toDelete = previous->next;
				previous->next = toDelete->next;
				Node* pNext = toDelete->next;
				pNext->prev = previous;
				delete toDelete;
				Size--; // ����� ��� ����� ������
			}
			else if (index > size / 2) { // if the tail is closer
				Node* pNext = this->tail;
				for (int i = size - 1; i > index - 1; i--) {
					pNext = pNext->prev;
				}
				Node* toDelete = pNext->prev;
				pNext->prev = toDelete->prev;
				Node* previous = toDelete->prev;
				previous->next = pNext;
				delete toDelete;
				Size--; // ����� ��� ����� ������
			}
		}
		else throw std::invalid_argument("Index is out of range");
	}

	void set(Newspaper* data, size_t index) { // set �� edit                  *��������� ��� ������������ ����������� ���� ������� �� ������� �������
		size_t size = GetSize();
		if (index < size && index >= 0) { // ����� ���������� index ��� ������������
			if (index <= size) {
				Node* cur = this->head;
				for (int i = 0; i < index; i++)
				{
					cur = cur->next;
				}
				cur->data = data; // �������� �������� �������� ������� ������ ����� ������ Newspaper � ����������
				// cur->data->editNewspaper(...)
			} 
		}
		else throw std::invalid_argument("Index is out of range");
	}

	bool isEmpty() {
		return (GetSize() == 0);
	}

	Newspaper* at(size_t index) { // getting an item by index*                 *��������� ��� ������������            ����������� ���� ������� �� ������� �������
		size_t size = GetSize();
		if (index < size && index >= 0) {
			Node* cur = head;
			for (int i = 0; i < index; i++) {
				cur = cur->next;
			}
			return cur->data;
		}
		else throw std::invalid_argument("Index is out of range");
	}

	void showList() {
		size_t size = GetSize();
		if (size > 0) {
			Node* cur = head;
			for (int i = 0; i < size; i++) {
				cout << i + 1; // ����� �� ����� ��� ������������ ��������� ������ �������� ��� 0
				cur->data->showNewspaper();
				cout << endl; // �������� ����������� ����� ���������� ������
				cur = cur->next;
			}
		}
		else throw std::invalid_argument("The list is empty");
	}



	// ************************************************************************************************************************************************************************************



	/*
	void saveList() {
	� ��������� ������� ������������� ��� ����� ���� ����� ��������� ������,
	��� ��� ����� ������ ������ �������
	��� ����� ����� ����� ��������� ������������� ���� (����� ������� ������� �� ������� ��������)
	��� ������� ���������� showList - ������ � ���� �� ����� �������� ������ ��������
	}

	void readList() {
	� ��������� ������� ������������� ��� ����� ������ ����� ������� ������,
	��� ��� ����� ������ ������ �������
	��� ����� ����� ����� ��������� ������������� ���� (����� ������� ������� �� ������� ��������)
	��� ������� ������� ���������� showList - ������ �� ����� �� ����� ��������� ������ ��������
	����� ������ ��� ������������� ���������� ������, ��� ����� ����������� ����� ���������:
	��� �������������� ������� ��� ������� ����� �� ��� ����� - �, �� ��������� �����, �������� ������ ������ (����� ��������� ����� �� getline �� eof() ������ �� 7 - ��� ���-�� ��������� ������)
	��� ������� � ������ ������ ����� ������ ������, � ����� ����� ���� for � ������� getline ��������� �� ������� ��� �������� ������ (�� ��������� �����)
	��� ����� �� ������� ���� ���������� ����� ����� �� eof() - �, ��� ����, ����� �� ��������� ����� ������� � ����� ������ ����� ���������� ��������� 6 �����
	��� ���������� �������� ���������� �� �����, �������������� ��� �������� ������� ������ ����� ������� (�������� ������)
	}



	// ******************************************************************************************************************************************************************************************



	void findByName() {
	��� ������� ����� ����������� ��� � ������ ����������(�� ���� ������ ����� ����� �������������� ������ �������),
	��� � ����� ���������� (�� ���� ������ ����� ����� �� ������� �������)
	����� �� 2 �������� ������� �������� ������������ ����� ������
		size_t size = GetSize();
		if (size > 0) {
			Node* cur = head;
			for (int i = 0; i < size; i++) {
				if (cur->data->name == name) { // ����� �������� ��������� �� ������� ������ ��������� � string - �������, ��� ������� substring()
					cur->data->showNewspaper();
					cout << endl; // �������� ����������� ����� ���������� ������
					break; // �������� ��� ������� � ������ ���� ��������� ����� ������� (==)
				}
				cur = cur->next;
			}
		}
		else throw std::invalid_argument("The list is empty");
	}

	void findByPublisher() {
	��� ������� ����� ����������� ��� � ������ ����������(�� ���� ������ ������������ ����� �������������� ������ �������),
	��� � ����� ���������� (�� ���� ������ ������������ ����� �� ������� �������)
	����� �� 2 �������� ������� �������� ������������ ����� ������
	��� ������� ���������� ���������� �������
	}

	void sortByPostcode() {
	� �������� ��������� ���������� ����� ������������ ����������� ���������� (������� ���� �� ������ ������),
	��� ������� ���������� (��������� ������ ������� �� size, � ������ ��� ����� �� ������ � ������ ������ ���� � �����)
	��� ��������� ���� ��������� ������ (�������������� ����������� cur1 � cur2) ������� ��������� ������������ ���:
		if (cur1->data->postcode > cur2->data->postcode) {
			������ ������� ���� ������� ����� ����� data
			Newspaper* tmp = cur1->data;
			cur1->data = cur2->data;
			cur2->data = tmp;
		}
	}

	void sortByName() {
	��� ������� ����� �� ��� ���� - ������ ������ ������� ��������� ���������� ���� name
	}
	*/
};