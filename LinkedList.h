#pragma once
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
using namespace std;

template <typename T>
struct Node {
	T data;
	Node<T>* next;
};

template <typename T>
void khoiTao(Node<T>*& head) {
	head = nullptr;
}

template <typename T>
void themDau(Node<T>*& head, const T& data) {
	Node<T>* newNode = new Node<T>{ data, head };
	head = newNode;
}

template <typename T>
void themCuoi(Node<T>*& head, const T& data) {
	Node<T>* newNode = new Node<T>{ data, nullptr };
	if (!head) {
		head = newNode;
		return;
	}
	Node<T>* temp = head;
	while (temp->next) temp = temp->next;
	temp->next = newNode;
}

template <typename T>
void themSauNodeQ(Node<T>* q, const T& data) {
	if (!q) return;
	Node<T>* newNode = new Node<T>{ data, q->next };
	q->next = newNode;
}

template <typename T>
Node<T>* timNodeTheoDieuKien(Node<T>* head, bool(*dieuKien)(const T&)) {
	Node<T>* temp = head;
	while (temp) {
		if (dieuKien(temp->data)) return temp;
		temp = temp->next;
	}
	return nullptr;
}

template <typename T>
void xoaDau(Node<T>*& head) {
	if (!head) return;
	Node<T>* temp = head;
	head = head->next;
	delete temp;
}

template <typename T>
void xoaCuoi(Node<T>*& head) {
	if (!head) return;
	if (!head->next) {
		delete head;
		head = nullptr;
		return;
	}
	Node<T>* prev = nullptr;
	Node<T>* temp = head;
	while (temp->next) {
		prev = temp;
		temp = temp->next;
	}
	prev->next = nullptr;
	delete temp;
}

template <typename T>
void xoaSauNodeQ(Node<T>* q) {
	if (!q || !q->next) return;
	Node<T>* temp = q->next;
	q->next = temp->next;
	delete temp;
}

template <typename T>
void xoaTheoDieuKien(Node<T>*& head, bool(*dieuKien)(const T&)) {
	while (head && dieuKien(head->data)) {
		Node<T>* temp = head;
		head = head->next;
		delete temp;
	}
	Node<T>* current = head;
	while (current && current->next) {
		if (dieuKien(current->next->data)) {
			Node<T>* temp = current->next;
			current->next = temp->next;
			delete temp;
		}
		else {
			current = current->next;
		}
	}
}

template <typename T>
void sapxep(Node<T>* head, bool(*cmp)(const T&, const T&)) {
	for (Node<T>* i = head; i && i->next; i = i->next) {
		for (Node<T>* j = i->next; j; j = j->next) {
			if (cmp(j->data, i->data)) {
				swap(i->data, j->data);
			}
		}
	}
}

template <typename T>
void themKhiDaSapxep(Node<T>*& head, const T& data, bool(*cmp)(const T&, const T&)) {
	Node<T>* newNode = new Node<T>{ data, nullptr };
	if (!head || cmp(data, head->data)) {
		newNode->next = head;
		head = newNode;
		return;
	}
	Node<T>* prev = head;
	while (prev->next && cmp(prev->next->data, data)) {
		prev = prev->next;
	}
	newNode->next = prev->next;
	prev->next = newNode;
}

template <typename T>
void xuatDanhSach(Node<T>* head) {
	if (!head) {
		cout << "Danh sach rong.\n";
		return;
	}
	Node<T>* temp = head;
	while (temp) {
		cout << temp->data << "\n";
		temp = temp->next;
	}
}


template <typename T>
void giaiPhong(Node<T>*& head) {
	while (head) {
		Node<T>* temp = head;
		head = head->next;
		delete temp;
	}
}

#endif
