#pragma once
#include <iostream>
using namespace std;

template<typename t>

class myVector {
	t* ptr;
	int s;
	int c;
	t v;
	t* regrow(t* old_ptr) {
		int temp;
		if (this->c == 0) temp = 1;
		else temp = this->c * 2;
		t* new_ptr = new t[temp];
		for (int i = 0; i < this->c; i++) {
			new_ptr[i] = old_ptr[i];
		}
		for (int i = this->c; i < temp; i++) {
			new_ptr[i] = this->v;
		}
		delete[] old_ptr;
		this->c = temp;
		return new_ptr;
	}
public:
	myVector(t val, int cap = 0) : s{ 0 }, c{ cap }, v{ val } {
		this->ptr = new t[cap];
		for (int i = 0; i < this->c; i++) {
			this->ptr[i] = val;
		}
	}
	~myVector() {
		delete[] this->ptr;
	}
	void display() {
		cout << "Size : " << this->s << "\t" << "Capacity : " << this->c << endl;
		cout << "Vector : [";
		for (int i = 0; i < this->c - 1; i++) {
			cout << this->ptr[i] << ", ";
		}
		if (this->c > 0) cout << this->ptr[this->c - 1];
		cout << "]\n";
	}
	myVector& operator=(const myVector& other) {
		if (this->ptr != other.ptr) {
			delete[] this->ptr;
			this->s = other.s;
			this->c = other.c;
			this->ptr = new t[this->c];
			for (int i = 0; i < this->c; i++) {
				this->ptr[i] = other.ptr[i];
			}
		}
		return *(this);
	}
	myVector& assign(int cap, t value) {
		this->c = cap;
		delete[] this->ptr;
		this->ptr = new int[this->c];
		for (int i = 0; i < this->c; i++) {
			this->ptr[i] = value;
		}
		return *(this);
	}
	t at(int pos) {
		try {
			if (pos < 0 || pos > this->s - 1) throw(1);
			return this->ptr[pos];
		}
		catch (...) {
			cout << "Invalid position.\n";
			return this->v;
		}
	}
	t& get_live_reference_at(int pos) {
		try {
			if (pos < 0 || pos > this->s - 1) throw(1);
			return this->ptr[pos];
		}
		catch (...) {
			cout << "Invalid Position.\n";
			return this->v;
		}
	}
	t operator[](int pos) {
		try {
			if (pos < 0 || pos > this->s - 1) throw(1);
			return this->ptr[pos];
		}
		catch (...) {
			cout << "Invalid position.\n";
			return this->v;
		}
	}
	t front() {
		try {
			if (this->c <= 0) throw (1);
			return this->ptr[0];
		}
		catch (...){
			cout << "No items in vectors.\n";
			return this->v;
		}
	}
	t back() {
		try {
			if (this->c <= 0) throw (1);
			return this->ptr[this->s - 1];
		}
		catch (...){
			cout << "No items in vectors.\n";
			return this->v;
		}
	}
	bool empty() {
		if (this->s == 0) return true;
		else return false;
	}
	int size() {
		return this->s;
	}
	int size() const {
		return this->s;
	}
	int capacity() {
		return this->c;
	}
	int capacity() const {
		return this->c;
	}
	void reserve(int new_cap) {
		if (new_cap > this->c) {
			this->c = new_cap;
			t* temp = new t[this->c];
			for (int i = 0; i < this->s; i++) {
				temp[i] = this->ptr[i];
			}
			delete[] this->ptr;
			this->ptr = temp;
		}
	}
	void shrink_to_fit() {
		this->c = this->s;
		t* temp = new t[this->c];
		for (int i = 0; i < this->c; i++) {
			temp[i] = this->ptr[i];
		}
		delete[] this->ptr;
		this->ptr = temp;
	}
	void clear() {
		for (int i = 0; i < this->s; i++) {
			this->s[i] = this->v;
		}
		this->s = 0;
	}
	void push_back(t val) {
		if (this->s == this->c) this->ptr = regrow(this->ptr);
		this->ptr[this->s++] = val;
	}
	void pop_back() {
		if (!empty()) this->s--;
		this->ptr[this->s] = this->v;
	}
	void resize(int count) {
		if (count < this->s) {
			for (int i = count; i < this->s; i++) {
				this->ptr[i] = this->v;
			}
			this->s = count;
		}
		else if (count > this->s) {
			for (int i = this->s; i < count; i++) {
				if (this->s == this->c) this->ptr = regrow(this->ptr);
				this->ptr[this->s++] = this->v;
			}
		}
	}
	void resize(int count, t val) {
		if (count < this->s) {
			for (int i = count; i < this->s; i++) {
				this->ptr[i] = this->v;
			}
			this->s = count;
		}
		else if (count > this->s) {
			for (int i = this->s; i < count; i++) {
				if (this->s == this->c) this->ptr = regrow(this->ptr);
				this->ptr[this->s++] = val;
			}
		}
	}
	void swap(myVector& other) {
		t* temp = this->ptr;
		int tempVar = this->s;
		this->ptr = other.ptr;
		other.ptr = temp;
		this->s = other.s;
		other.s = tempVar;
		tempVar = this->c;
		this->c = other.c;
		other.c = tempVar;
	}

	bool operator==(const myVector& other) {
		if (size() == other.size()) {
			for (int i = 0; i < this->s; i++) {
				if (this->ptr[i] != other.ptr[i]) return false;
			}
			return true;
		}
		return false;
	}
	bool operator!=(const myVector& other) {
		if (!operator==(other)) return true;
		return false;
	}
	bool operator<(const myVector& other) {
		if (size() > other.size()) return true;
		return false;
	}
	bool operator<=(const myVector& other) {
		if (size() >= other.size()) return true;
		return false;
	}
	bool operator>(const myVector& other) {
		if (size() < other.size()) return true;
		return false;
	}
	bool operator>=(const myVector& other) {
		if (size() <= other.size()) return true;
		return false;

	}
};
