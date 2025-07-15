#include <iostream>
#include <string>
using namespace std;

struct Node {
	int info;
	Node* next, *prev;
};

struct DoublyLinkedList {
	Node* head, *tail;
};

// Khởi tạo danh sách rỗng
void khoiTao(DoublyLinkedList& list) {
	list.head = list.tail = nullptr;
}

// Tạo node mới
Node* createNode(int x) {
	Node* p = new Node;
	p->info = x;
	p->next = p->prev = nullptr;
	return p;
}

// Thêm đầu
void themDau(DoublyLinkedList& list, int x) {
	Node* p = createNode(x);
	if (!list.head) {
		list.head = list.tail = p;
	}
	else {
		p->next = list.head;
		list.head->prev = p;
		list.head = p;
	}
}

// Thêm cuối
void themCuoi(DoublyLinkedList& list, int x) {
	Node* p = createNode(x);
	if (!list.tail) {
		list.head = list.tail = p;
	}
	else {
		p->prev = list.tail;
		list.tail->next = p;
		list.tail = p;
	}
}

// Thêm sau node q
void themSauNodeQ(DoublyLinkedList& list, Node* q, int x) {
	if (!q) return;
	Node* p = createNode(x);
	p->next = q->next;
	p->prev = q;
	if (q->next)
		q->next->prev = p;
	else
		list.tail = p;
	q->next = p;
}

// Tìm node theo giá trị
Node* timNodeTheoGiaTri(DoublyLinkedList list, int x) {
	for (Node* p = list.head; p != nullptr; p = p->next) {
		if (p->info == x)
			return p;
	}
	return nullptr;
}

// Tìm node lớn nhất
Node* timMax(DoublyLinkedList list) {
	if (!list.head) return nullptr;
	Node* maxNode = list.head;
	for (Node* p = list.head->next; p != nullptr; p = p->next) {
		if (p->info > maxNode->info)
			maxNode = p;
	}
	return maxNode;
}

// Tìm node nhỏ nhất
Node* timMin(DoublyLinkedList list) {
	if (!list.head) return nullptr;
	Node* minNode = list.head;
	for (Node* p = list.head->next; p != nullptr; p = p->next) {
		if (p->info < minNode->info)
			minNode = p;
	}
	return minNode;
}

// Xoá đầu
void xoaDau(DoublyLinkedList& list) {
	if (!list.head) return;
	Node* p = list.head;
	list.head = list.head->next;
	if (list.head)
		list.head->prev = nullptr;
	else
		list.tail = nullptr;
	delete p;
}

// Xoá cuối
void xoaCuoi(DoublyLinkedList& list) {
	if (!list.tail) return;
	Node* p = list.tail;
	list.tail = list.tail->prev;
	if (list.tail)
		list.tail->next = nullptr;
	else
		list.head = nullptr;
	delete p;
}

// Xoá node q
void xoaNodeQ(DoublyLinkedList& list, Node* q) {
	if (!q) return;
	if (q == list.head)
		xoaDau(list);
	else if (q == list.tail)
		xoaCuoi(list);
	else {
		q->prev->next = q->next;
		q->next->prev = q->prev;
		delete q;
	}
}

// Xuất danh sách
void xuat(DoublyLinkedList list) {
	for (Node* p = list.head; p != nullptr; p = p->next) {
		cout << p->info << " ";
	}
	cout << endl;
}

// Giải phóng vùng nhớ
void giaiPhong(DoublyLinkedList& list) {
	while (list.head) {
		Node* temp = list.head;
		list.head = list.head->next;
		delete temp;
	}
	list.tail = nullptr;
}

// MAIN DEMO
int main() {
	DoublyLinkedList list;
	khoiTao(list);

	themDau(list, 10);
	themDau(list, 20);
	themCuoi(list, 5);
	themCuoi(list, 15);

	cout << "Danh sach ban dau: ";
	xuat(list);

	Node* q = timNodeTheoGiaTri(list, 10);
	if (q) {
		cout << "Them 99 sau node co gia tri 10\n";
		themSauNodeQ(list, q, 99);
	}

	cout << "Danh sach sau khi them: ";
	xuat(list);

	cout << "Node lon nhat: " << timMax(list)->info << endl;
	cout << "Node nho nhat: " << timMin(list)->info << endl;

	cout << "Xoa dau, cuoi, node co gia tri 99\n";
	xoaDau(list);
	xoaCuoi(list);
	xoaNodeQ(list, timNodeTheoGiaTri(list, 99));

	cout << "Danh sach sau khi xoa: ";
	xuat(list);

	giaiPhong(list);

	system("pause");
	return 0;
}
