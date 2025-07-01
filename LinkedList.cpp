#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct SinhVien {
	long maSo;
	string hoTen;
	string ngaySinh;
	string queQuan;
	double diem;
};

struct Node {
	SinhVien data;
	Node* next;
};


void khoiTao(Node*& head) {
	head = nullptr;
}

void xuatDanhSach(Node* head) {
	if (!head) {
		cout << "Danh sach rong.\n";
		return;
	}
	Node* temp = head;
	while (temp) {
		cout << "MSSV: " << temp->data.maSo << endl;
		cout << "Ho ten: " << temp->data.hoTen << endl;
		cout << "Ngay sinh: " << temp->data.ngaySinh << endl;
		cout << "Que quan: " << temp->data.queQuan << endl;
		cout << "Diem: " << temp->data.diem << endl << endl;
		temp = temp->next;
	}
}

Node* timNodeTheoMSSV(Node* head, int mssv) {
	Node* temp = head;
	while (temp) {
		if (temp->data.maSo == mssv)
			return temp;
		temp = temp->next;
	}
	return nullptr;
}


void themDau(Node*& head, const SinhVien& sv) {
	Node* newNode = new Node{ sv, head };
	head = newNode;
}

void themCuoi(Node*& head, const SinhVien& sv) {
	Node* newNode = new Node{ sv, nullptr };
	if (!head) {
		head = newNode;
		return;
	}
	Node* temp = head;
	while (temp->next)
		temp = temp->next;
	temp->next = newNode;
}

void themSauNodeQ(Node* q, const SinhVien& sv) {
	if (!q) {
		cout << "Node q khong ton tai!\n";
		return;
	}
	Node* newNode = new Node{ sv, q->next };
	q->next = newNode;
}

void xoaDau(Node*& head) {
	if (!head) {
		cout << "Danh sach rong.\n";
		return;
	}
	Node* temp = head;
	head = head->next;
	delete temp;
}

void xoaCuoi(Node*& head) {
	if (!head) {
		cout << "Danh sach rong.\n";
		return;
	}
	if (!head->next) {
		delete head;
		head = nullptr;
		return;
	}
	Node* prev = nullptr;
	Node* temp = head;
	while (temp->next) {
		prev = temp;
		temp = temp->next;
	}
	prev->next = nullptr;
	delete temp;
}

void xoaSauNodeQ(Node* q) {
	if (!q || !q->next) {
		cout << "Khong the xoa sau node q (q null hoac q la cuoi).\n";
		return;
	}
	Node* temp = q->next;
	q->next = temp->next;
	delete temp;
}

void xoaTheoMSSV(Node*& head, const int mssv) {
	if (!head) return;

	// Trường hợp đặc biệt: xóa đầu
	while (head && head->data.maSo == mssv) {
		Node* temp = head;
		head = head->next;
		delete temp;
	}

	// Xử lý phần còn lại
	Node* current = head;
	while (current && current->next) {
		if (current->next->data.maSo == mssv) {
			Node* temp = current->next;
			current->next = temp->next;
			delete temp;
		}
		else {
			current = current->next;
		}
	}
}


void docTuFile(Node*& head, const string& tenTep) {
	ifstream fin(tenTep);
	if (!fin) {
		cout << "Khong mo duoc file.\n";
		return;
	}

	while (true) {
		SinhVien sv;
		fin >> sv.maSo;
		if (fin.fail()) break;

		fin.ignore();
		getline(fin, sv.hoTen, '#');
		getline(fin, sv.ngaySinh, '#');
		getline(fin, sv.queQuan, '#');
		fin >> sv.diem;
		fin.ignore();

		themCuoi(head, sv);
	}


	fin.close();
}

void sapxep(Node* head) {
	if (!head || !head->next) return; // Không cần sắp nếu danh sách có 0 hoặc 1 phần tử

	for (Node* i = head; i && i->next; i = i->next) {
		for (Node* j = i->next; j; j = j->next) {
			if (j->data.maSo < i->data.maSo) {
				swap(i->data, j->data);
			}
		}
	}
}

void themKhiDaSapxep(Node*& head, SinhVien sv) {
	Node* newNode = new Node{ sv, nullptr };

	// Trường hợp danh sách rỗng hoặc thêm vào đầu
	if (!head || sv.maSo < head->data.maSo) {
		newNode->next = head;
		head = newNode;
		return;
	}

	// Tìm vị trí để chèn
	Node* prev = head;
	while (prev->next && prev->next->data.maSo < sv.maSo) {
		prev = prev->next;
	}

	// Chèn sau node prev
	newNode->next = prev->next;
	prev->next = newNode;
}


void giaiPhong(Node*& head) {
	while (head) {
		Node* temp = head;
		head = head->next;
		delete temp;
	}
}



/*int main() {
	Node* danhSach;
	khoiTao(danhSach);

	// Đọc từ file
	docTuFile(danhSach, "SinhVien.txt");

	// Thêm thủ công
	SinhVien sv1 = { 9997, "Hoang Thi D", "04/04/2004", "Vinh Long", 8.9 };
	themDau(danhSach, sv1);

	SinhVien sv2 = { 9998, "Hoang Thi F", "04/04/2004", "Vinh Long", 9 };
	themCuoi(danhSach, sv2);

	SinhVien sv3 = { 9999, "Hoang Thi E", "04/04/2004", "Vinh Long", 10 };
	Node * qthemsau = timNodeTheoMSSV(danhSach, 9998);
	themSauNodeQ(qthemsau,sv3);

	SinhVien sv4 = { 10000, "Hoang Thi E", "04/04/2004", "Vinh Long", 10 };

	sapxep(danhSach);

	themKhiDaSapxep(danhSach, sv4);

	cout << "\n=== SAU KHI THEM===\n";
	xuatDanhSach(danhSach);

	// Xóa 
	xoaDau(danhSach);

	Node* qXoaSau = timNodeTheoMSSV(danhSach, 9998);
	xoaSauNodeQ(qXoaSau);

	xoaCuoi(danhSach);

	xoaTheoMSSV(danhSach, 2018002);

	cout << "\n=== SAU KHI XOA ===\n";
	xuatDanhSach(danhSach);

	// Giải phóng bộ nhớ
	giaiPhong(danhSach);

	system("pause");
	return 0;
}*/
