#include <iostream>
#include <string>
#include "LinkedList.h"
using namespace std;

struct SinhVien {
	long maSo;
	string hoTen;
	string ngaySinh;
	string queQuan;
	double diem;
};

// Hàm xuất 1 SV
void xuatSV(const SinhVien& sv) {
	cout << "MSSV: " << sv.maSo << "\n";
	cout << "Ho ten: " << sv.hoTen << "\n";
	cout << "Ngay sinh: " << sv.ngaySinh << "\n";
	cout << "Que quan: " << sv.queQuan << "\n";
	cout << "Diem: " << sv.diem << "\n\n";
}

// So sánh tăng dần theo MSSV
bool sosanhTang(const SinhVien& a, const SinhVien& b) {
	return a.maSo < b.maSo;
}

// Điều kiện xóa SV theo MSSV cụ thể
bool xoaTheoMa(const SinhVien& sv) {
	return sv.maSo == 2018002;
}

int main() {
	Node<SinhVien>* danhSach;
	khoiTao(danhSach);

	SinhVien sv1 = { 1001, "Nguyen Van A", "01/01/2000", "Ha Noi", 7.5 };
	SinhVien sv2 = { 1003, "Tran Thi B", "02/02/2001", "Hai Phong", 8.2 };
	SinhVien sv3 = { 1002, "Le Van C", "03/03/2002", "Da Nang", 9.0 };

	themDau(danhSach, sv1);
	themCuoi(danhSach, sv2);
	themKhiDaSapxep(danhSach, sv3, sosanhTang);

	cout << "=== DANH SACH ===\n";
	xuatDanhSach(danhSach, xuatSV);

	cout << "\nSau khi sap xep:\n";
	sapxep(danhSach, sosanhTang);
	xuatDanhSach(danhSach, xuatSV);

	giaiPhong(danhSach);
	return 0;
}
