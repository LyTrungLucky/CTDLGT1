#include <iostream>
#include <string>
using namespace std;

struct Node {
	int info;
	Node* next;
};

struct CircleLinkedList {
	Node* head, *tail;
};

// Khởi tạo danh sách rỗng
void khoiTao(CircleLinkedList& list) {
	list.head = list.tail = nullptr;
}

// Tạo node mới
Node* createNode(int x) {
	Node* p = new Node;
	p->info = x;
	p->next = nullptr;
	return p;
}

// Thêm đầu
void themDau(CircleLinkedList& list, int x) {
	Node* p = createNode(x);
	if (!list.head) {
		list.head = list.tail = p;
		p->next = p; // vòng
	}
	else {
		p->next = list.head;
		list.tail->next = p;
		list.head = p;
	}
}

// Thêm cuối
void themCuoi(CircleLinkedList& list, int x) {
	Node* p = createNode(x);
	if (!list.head) {
		list.head = list.tail = p;
		p->next = p;
	}
	else {
		list.tail->next = p;
		p->next = list.head;
		list.tail = p;
	}
}

// Duyệt danh sách
void duyet(CircleLinkedList list) {
	if (!list.head) {
		cout << "Danh sach rong.\n";
		return;
	}
	Node* p = list.head;
	do {
		cout << p->info << " ";
		p = p->next;
	} while (p != list.head);
	cout << endl;
}

// Xoá đầu
void xoaDau(CircleLinkedList& list) {
	if (!list.head) return;
	if (list.head == list.tail) {
		delete list.head;
		list.head = list.tail = nullptr;
		return;
	}
	Node* temp = list.head;
	list.head = list.head->next;
	list.tail->next = list.head;
	delete temp;
}

// Xoá cuối
void xoaCuoi(CircleLinkedList& list) {
	if (!list.head) return;
	if (list.head == list.tail) {
		delete list.head;
		list.head = list.tail = nullptr;
		return;
	}
	Node* p = list.head;
	while (p->next != list.tail) {
		p = p->next;
	}
	delete list.tail;
	list.tail = p;
	list.tail->next = list.head;
}

// Xoá theo giá trị
void xoaTheoGiaTri(CircleLinkedList& list, int x) {
	if (!list.head) return;

	// Xoá node đầu nếu trùng
	while (list.head && list.head->info == x) {
		xoaDau(list);
		if (!list.head) return;
	}

	Node* prev = list.head;
	Node* curr = list.head->next;

	while (curr != list.head) {
		if (curr->info == x) {
			if (curr == list.tail) {
				xoaCuoi(list);
				return;
			}
			prev->next = curr->next;
			delete curr;
			curr = prev->next;
		}
		else {
			prev = curr;
			curr = curr->next;
		}
	}
}

// Giải phóng vùng nhớ
void giaiPhong(CircleLinkedList& list) {
	if (!list.head) return;

	Node* p = list.head;
	do {
		Node* temp = p;
		p = p->next;
		delete temp;
	} while (p != list.head);

	list.head = list.tail = nullptr;
}

// MAIN DEMO
int main() {
	CircleLinkedList list;
	khoiTao(list);

	themCuoi(list, 10);
	themCuoi(list, 20);
	themCuoi(list, 30);
	themDau(list, 5);

	cout << "Danh sach hien tai: ";
	duyet(list);

	cout << "Xoa dau\n";
	xoaDau(list);
	duyet(list);

	cout << "Xoa cuoi\n";
	xoaCuoi(list);
	duyet(list);

	cout << "Xoa theo gia tri 20\n";
	xoaTheoGiaTri(list, 20);
	duyet(list);

	cout << "Giai phong danh sach\n";
	giaiPhong(list);
	duyet(list);

	system("pause");
	return 0;
}
