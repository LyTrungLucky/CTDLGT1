#include <iostream>
#include <string>
using namespace std;

struct Temp {
	float coef; // hệ số
	float exp;  // bậc
};

void nhap1Temp(Temp& t) {
	cout << "Nhap he so: ";
	cin >> t.coef;
	cout << "Nhap bac: ";
	cin >> t.exp;
}

void xuat1Temp(Temp t) {
	cout << t.coef << "x^" << t.exp;
	if (t.coef >= 0) cout << " + ";
}

struct Node {
	Temp info;
	Node* next;
};

// === HÀM XỬ LÝ DANH SÁCH ===

void init(Node*& head) {
	head = NULL;
}

Node* createNode(Temp t) {
	Node* p = new Node;
	p->info = t;
	p->next = NULL;
	return p;
}

Node* findKey(Node* head, float exp) {
	Node* p = head;
	while (p != NULL) {
		if (p->info.exp == exp)
			return p;
		p = p->next;
	}
	return NULL;
}

// Thêm vào cuối
void insertLast(Node*& head, Temp t) {
	Node* p = createNode(t);
	if (!head) {
		head = p;
	}
	else {
		Node* tmp = head;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = p;
	}
}

// Thêm vào đầu
void insertFirst(Node*& head, Temp t) {
	Node* p = createNode(t);
	p->next = head;
	head = p;
}

// Thêm sau node có exp = key
void insertAfterKey(Node*& head, float key, Temp t) {
	Node* q = findKey(head, key);
	if (q) {
		Node* p = createNode(t);
		p->next = q->next;
		q->next = p;
	}
	else {
		cout << "Khong tim thay bac " << key << " de chen sau.\n";
	}
}

// Xóa đầu
void delFirst(Node*& head) {
	if (!head) return;
	Node* p = head;
	head = head->next;
	delete p;
}

// Xóa cuối
void delLast(Node*& head) {
	if (!head) return;
	if (!head->next) {
		delete head;
		head = nullptr;
		return;
	}
	Node* prev = NULL;
	Node* curr = head;
	while (curr->next) {
		prev = curr;
		curr = curr->next;
	}
	prev->next = NULL;
	delete curr;
}

// Xóa sau node có exp = key
void delAfterKey(Node*& head, float key) {
	Node* q = findKey(head, key);
	if (q && q->next) {
		Node* temp = q->next;
		q->next = temp->next;
		delete temp;
	}
	else {
		cout << "Khong the xoa sau bac " << key << " (khong ton tai hoac la cuoi).\n";
	}
}

// Truy xuất phần tử tại vị trí x (index 0)
void truyxuat(Node* head, int x) {
	int count = 0;
	Node* tmp = head;
	while (tmp && count < x) {
		tmp = tmp->next;
		count++;
	}
	if (tmp) {
		xuat1Temp(tmp->info);
		cout << endl;
	}
	else {
		cout << "Vi tri khong hop le.\n";
	}
}

// In danh sách
void printList(Node* head) {
	if (!head) {
		cout << "Danh sach rong!\n";
		return;
	}
	cout << "f(x) = ";
	Node* tmp = head;
	while (tmp) {
		xuat1Temp(tmp->info);
		tmp = tmp->next;
	}
	cout << "\b\b  \n"; // xóa dấu + cuối cùng
}

// Sắp xếp tăng theo bậc
void sort(Node*& head) {
	for (Node* i = head; i && i->next; i = i->next) {
		for (Node* j = i->next; j; j = j->next) {
			if (i->info.exp < j->info.exp) {
				swap(i->info, j->info);
			}
		}
	}
}

// Thêm có thứ tự giảm dần theo bậc
void insertOrdered(Node*& head, Temp x) {
	Node* p = createNode(x);
	if (!head || head->info.exp < x.exp) {
		p->next = head;
		head = p;
		return;
	}
	Node* current = head;
	while (current->next && current->next->info.exp >= x.exp)
		current = current->next;

	p->next = current->next;
	current->next = p;
}

// Giải phóng bộ nhớ
void destroyList(Node*& head) {
	while (head) {
		delFirst(head);
	}
}

float tinhGiaTriDaThuc(Node* head, float x) {
	float ketQua = 0;
	Node* p = head;

	while (p) {
		ketQua += p->info.coef * pow(x, p->info.exp); // coef * x^exp
		p = p->next;
	}

	return ketQua;
}


int main() {
	Node* head;
	init(head);

	// Nhập 3 đa thức thêm cuối
	cout << "Nhap 3 da thuc them cuoi:\n";
	for (int i = 0; i < 3; ++i) {
		Temp t;
		nhap1Temp(t);
		insertLast(head, t);
	}

	cout << "\nDanh sach sau khi them cuoi:\n";
	printList(head);

	// Sắp xếp
	cout << "\nSap xep tang dan theo bac:\n";
	sort(head);
	printList(head);

	cout<<"KQ: " << tinhGiaTriDaThuc(head, 3)<<endl ;

	// Thêm đầu
	Temp td;
	cout << "\nNhap da thuc them dau:\n";
	nhap1Temp(td);
	insertFirst(head, td);

	cout << "\nDanh sach sau khi them dau:\n";
	printList(head);

	// Thêm sau bậc cụ thể
	float bac;
	cout << "\nNhap bac muon chen sau: ";
	cin >> bac;
	Temp ts;
	nhap1Temp(ts);
	insertAfterKey(head, bac, ts);

	cout << "\nDanh sach sau khi chen sau bac " << bac << ":\n";
	printList(head);

	// Xóa đầu
	cout << "\nXoa dau danh sach:\n";
	delFirst(head);
	printList(head);

	// Xóa cuối
	cout << "\nXoa cuoi danh sach:\n";
	delLast(head);
	printList(head);

	// Xóa sau node
	cout << "\nNhap bac muon xoa sau: ";
	cin >> bac;
	delAfterKey(head, bac);
	printList(head);

	// Truy xuất
	int pos;
	cout << "\nNhap vi tri muon truy xuat: ";
	cin >> pos;
	cout << "Phan tu tai vi tri " << pos << ": ";
	truyxuat(head, pos);

	// Thêm theo thứ tự giảm dần
	cout << "\nThem da thuc vao dung vi tri (giam dan theo bac):\n";
	Temp tg;
	nhap1Temp(tg);
	insertOrdered(head, tg);
	cout << "\nDanh sach sau khi chen theo thu tu:\n";
	printList(head);

	// Giải phóng
	cout << "\nGiai phong danh sach.\n";
	destroyList(head);

	system("pause");
	return 0;
}
