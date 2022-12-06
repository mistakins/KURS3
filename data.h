#include <iostream>
#include <string>
#include <string.h>
#include <fstream>
#include <stdexcept>

using namespace std;

// вставить в это место готовые функции из второго семестра:
// проверка правильности ввода целого числа и строки
// проверка правильности пути входных и выходных файлов


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
	эту функцию можно реализовать или с пустыми параметрами(то есть запрос новых данных будет осуществляться внутри функции),
	или в теми же параметрами что в структуре(то есть запрос новых данных будет во внешней функции)
	при вводе новых значений полей с клавиатуры использовать функции проверки правильности ввода целых чисел и строк, взятых со второго семестра
	}
	
	void editNewspaper() {
	эту функцию можно реализовать или с пустыми параметрами(то есть запрос новых данных будет осуществляться внутри функции),
	или в теми же параметрами что в структуре(то есть запрос новых данных будет во внешней функции)
	при вводе новых значений полей с клавиатуры использовать функции проверки правильности ввода целых чисел и строк, взятых со второго семестра
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
	cin >> index; // вместо прямого считывания индекса здесь можно использовать готовую функцию ввода из второго семестра 
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
	size_t Size; // error! убрать, заменить на cur

public:
	// CRUD - Create +, Read +, Update +, Delete +
	// по операции Read предусмотреть доп фунции по чтению данных списка из файла, а так же вывод всего списка в файл

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

	size_t GetSize() { // переписать функцию: считать список вручную по cur от head до tail, параллельно подсчитывая кол-во пройденных элемнтов в переменной size
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
		Size++; // позже это можно убрать

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
		Size++; // позже это можно убрать

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
			Size--; // позже это можно убрать

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
			Size--; // позже это можно убрать
		}
		else throw std::invalid_argument("Index is out of range");
	}

	void incert(Newspaper* data, size_t index) { // adding an item by* index*     *before *подправить для пользователя (в аргументе функции записать index-1) просмотреть ввод индекса во внешней функции
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
				Size++; // позже это можно убрать
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
			Size++; // позже это можно убрать
		}
		else throw std::invalid_argument("Index is out of range");
	}

	void remove(size_t index) { // deleting an item by index*                 *исправить для пользователя просмотреть ввод индекса во внешней функции
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
				Size--; // позже это можно убрать
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
				Size--; // позже это можно убрать
			}
		}
		else throw std::invalid_argument("Index is out of range");
	}

	void set(Newspaper* data, size_t index) { // set на edit                  *исправить для пользователя просмотреть ввод индекса во внешней функции
		size_t size = GetSize();
		if (index < size && index >= 0) { // опять подправить index для пользователя
			if (index <= size) {
				Node* cur = this->head;
				for (int i = 0; i < index; i++)
				{
					cur = cur->next;
				}
				cur->data = data; // возможно придется дописать функцию чтения новых данных Newspaper с клавиатуры
				// cur->data->editNewspaper(...)
			} 
		}
		else throw std::invalid_argument("Index is out of range");
	}

	bool isEmpty() {
		return (GetSize() == 0);
	}

	Newspaper* at(size_t index) { // getting an item by index*                 *исправить для пользователя            просмотреть ввод индекса во внешней функции
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
				cout << i + 1; // вывод на экран для пользователя порядкого номера элемента без 0
				cur->data->showNewspaper();
				cout << endl; // красивый разделитель между элементами списка
				cur = cur->next;
			}
		}
		else throw std::invalid_argument("The list is empty");
	}



	// ************************************************************************************************************************************************************************************



	/*
	void saveList() {
	в аргументе функции предусмотреть имя файла куда нужно сохранить список,
	или его можно ввести внутри функции
	при вводе имени файла проверять существования пути (взять готовую функцию из второго семестра)
	код функции аналогичен showList - только в файл не нужно выводить индекс элемента
	}

	void readList() {
	в аргументе функции предусмотреть имя файла откуда нужно считать список,
	или его можно ввести внутри функции
	при вводе имени файла проверять существования пути (взять готовую функцию из второго семестра)
	код функции немного аналогичен showList - только из файла не нужно считывать индекс элемента
	чтобы понять где заканчивается считывание списка, это можно реализовать тремя способами:
	или предварительно считать все строчки файла до его конца - и, на основании этого, опредить размер списка (число считанных строк по getline до eof() делить на 7 - это кол-во элементов списка)
	или считать с первой строки файла размер списка, а затем через цикл for с помощью getline считывать по очереди все элементы списка (по отдельным полям)
	или сразу же ставить цикл считывания строк файла до eof() - и, при этом, сразу же добавлять новый элемент в конец списка после считывания очередных 6 строк
	при выполнении операции считывания из файла, предварительно все элементы старого списка нужно удалить (очистить список)
	}



	// ******************************************************************************************************************************************************************************************



	void findByName() {
	эту функцию можно реализовать или с пустым параметрам(то есть запрос имени будет осуществляться внутри функции),
	или с одним параметром (то есть запрос имени будет во внешней функции)
	взять из 2 семестра функцию проверки правильности ввода строки
		size_t size = GetSize();
		if (size > 0) {
			Node* cur = head;
			for (int i = 0; i < size; i++) {
				if (cur->data->name == name) { // можно заменить равенство на функцию поиска подстроки в string - кажется, это функция substring()
					cur->data->showNewspaper();
					cout << endl; // красивый разделитель между элементами списка
					break; // оставить эту команду в случае если равенство будет строгое (==)
				}
				cur = cur->next;
			}
		}
		else throw std::invalid_argument("The list is empty");
	}

	void findByPublisher() {
	эту функцию можно реализовать или с пустым параметрам(то есть запрос издательства будет осуществляться внутри функции),
	или с одним параметром (то есть запрос издательства будет во внешней функции)
	взять из 2 семестра функцию проверки правильности ввода строки
	код функции аналогичен предыдущей функции
	}

	void sortByPostcode() {
	в качестве алгоритма сортировки можно использовать пузырьковую сортировку (двойной цикл от головы списка),
	или быструю сортировку (разбиение списка пополам по size, а дальше два цикла от головы и хвоста списка друг к другу)
	при сравнении двух элементов списка (представленных указателями cur1 и cur2) условия сравнения записываются так:
		if (cur1->data->postcode > cur2->data->postcode) {
			внутри условия идет простой обмен ячеек data
			Newspaper* tmp = cur1->data;
			cur1->data = cur2->data;
			cur2->data = tmp;
		}
	}

	void sortByName() {
	код функции такой же как выше - только внутри условия сравнения выбирается поле name
	}
	*/
};