//#include <iostream>
//#include "myVector.h"
//using namespace std;
//
//void myVector::display() {
//	cout << "Size : " << this->s << "\t" << "Capacity : " << this->c << endl;
//	cout << "Vector : [";
//	for (int i = 0; i < this->c - 1; i++) {
//		cout << this->ptr[i] << ", ";
//	}
//	if (this->c > 0) cout << this->ptr[this->c - 1];
//	cout << "]\n";
//}
//
//t* myVector<t>::regrow(t* old_ptr) {
//	t* new_ptr = new t[this->c * 2];
//	for (int i = 0; i < this->c; i++) {
//		new_ptr[i] = old_ptr[i];
//	}
//	for (int i = this->c; i < this->c * 2; i++) {
//		new_ptr[i] = this->v;
//	}
//	delete[] old_ptr;
//	this->c *= 2;
//	return new_ptr;
//}
//
//myVector::myVector(int cap, int val) : s{ 0 }, c{ cap }, v{ val } {
//	this->ptr = new int[cap];
//	for (int i = 0; i < this->c; i++) {
//		this->ptr[i] = val;
//	}
//}
//
//myVector::~myVector() {
//	delete[] this->ptr;
//}
//
//myVector& myVector::operator=(const myVector& other) {
//	if (this->ptr != other.ptr) {
//		delete[] this->ptr;
//		this->s = other.s;
//		this->c = other.c;
//		this->ptr = new int[this->c];
//		for (int i = 0; i < this->c; i++) {
//			this->ptr[i] = other.ptr[i];
//		}
//	}
//	return *(this);
//}
//
//myVector& myVector::assign(int cap, int value) {
//	this->c = cap;
//	delete[] this->ptr;
//	this->ptr = new int[this->c];
//	for (int i = 0; i < this->c; i++) {
//		this->ptr[i] = value;
//	}
//	return *(this);
//}
//
//int myVector::at(int pos) {
//	if (pos < 0 || pos > this->s - 1) exit(1);
//	return this->ptr[pos];
//}
//
//int myVector::operator[](int pos) {
//	if (pos < 0 || pos > this->s - 1) exit(1);
//	return this->ptr[pos];
//}
//
//int myVector::front() {
//	if(this->c > 0) return this->ptr[0];
//	exit(1);
//}
//
//int myVector::back() {
//	if (this->c > 0) return this->ptr[this->s - 1];
//	exit(1);
//}
//
//bool myVector::empty() {
//	if (this->s == 0) return true;
//	else return false;
//}
//
//int myVector::size() {
//	return this->s;
//}
//
//int myVector::size() const{
//	return this->s;
//}
//
//int myVector::capacity() {
//	return this->c;
//}
//
//int myVector::capacity() const{
//	return this->c;
//}
//
//void myVector::reserve(int new_cap) {
//	if (new_cap > this->c) {
//		this->c = new_cap;
//		int* temp = new int[this->c];
//		for (int i = 0; i < this->s; i++) {
//			temp[i] = this->ptr[i];
//		}
//		delete[] this->ptr;
//		this->ptr = temp;
//	}
//}
//
//void myVector::shrink_to_fit() {
//	this->c = this->s;
//	int* t = new int[this->c];
//	for (int i = 0; i < this->c; i++) {
//		t[i] = this->ptr[i];
//	}
//	delete[] this->ptr;
//	this->ptr = t;
//}
//
//void myVector::clear() {
//	this->s = 0;
//}
//
//void myVector::push_back(int val) {
//	if (this->s == this->c) this->ptr = regrow(this->ptr);
//	this->ptr[this->s++] = val;
//}
//
//void myVector::pop_back() {
//	if(!empty()) this->s--;
//	this->ptr[this->s] = this->v;
//}
//
//void myVector::resize(int count) {
//	if (count < this->s) {
//		for (int i = count; i < this->s; i++) {
//			this->ptr[i] = this->v;
//		}
//		this->s = count;
//	}
//	else if (count > this->s) {
//		for (int i = this->s; i < count; i++) {
//			if (this->s == this->c) this->ptr = regrow(this->ptr);
//			this->ptr[this->s++] = this->v;
//		}
//	}
//}
//
//void myVector::resize(int count, int val) {
//	if (count < this->s) {
//		for (int i = count; i < this->s; i++) {
//			this->ptr[i] = this->v;
//		}
//		this->s = count;
//	}
//	else if (count > this->s) {
//		for (int i = this->s; i < count; i++) {
//			if (this->s == this->c) this->ptr = regrow(this->ptr);
//			this->ptr[this->s++] = val;
//		}
//	}
//}
//
//void myVector::swap(myVector& other) {
//	int* temp = this->ptr;
//	int tempVar = this->s;
//	this->ptr = other.ptr;
//	other.ptr = temp;
//	this->s = other.s;
//	other.s = tempVar;
//	tempVar = this->c;
//	this->c = other.c;
//	other.c = tempVar;
//}
//
//bool myVector::operator==(const myVector& other) {
//	if (size() == other.size()) {
//		for (int i = 0; i < this->s; i++) {
//			if (this->ptr[i] != other.ptr[i]) return false;
//		}
//		return true;
//	}
//	return false;
//}
//
//bool myVector::operator!=(const myVector& other) {
//	if (!operator==(other)) return true;
//	return false;
//}
//
//bool myVector::operator>(const myVector & other) {
//	if (size() > other.size()) return true;
//	return false;
//}
//
//bool myVector::operator>=(const myVector & other) {
//	if (size() >= other.size()) return true;
//	return false;
//}
//
//bool myVector::operator<(const myVector & other) {
//	if (size() < other.size()) return true;
//	return false;
//}
//
//bool myVector::operator<=(const myVector & other) {
//	if (size() <= other.size()) return true;
//	return false;
//}
