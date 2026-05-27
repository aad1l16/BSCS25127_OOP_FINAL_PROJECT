#include <iostream>
#include "String.h"
#include <cstdlib>

int String::length(const char* temp) {
	int l = 0;
	for (; temp[l] != '\0'; l++);
	return l;
}

int String::length(char* temp) {
	int l = 0;
	for (; temp[l] != '\0'; l++);
	return l;
}

int String::length(char* temp) const {
	int l = 0;
	for (; temp[l] != '\0'; l++);
	return l;
}

int String::length() {
	int l = 0;
	for (; this->s[l] != '\0'; l++);
	return l;
}

char* String::regrow(char* old_ptr, int len, int pos) {
	int leng = length(old_ptr);
	char* new_ptr = new char[leng + len + 1];
	for (int i = 0; i < pos; i++) {
		new_ptr[i] = old_ptr[i];
	}
	for (int i = pos + 1; i < leng + len; i++) {
		new_ptr[i] = old_ptr[i - len];
	}
	new_ptr[leng + len] = '\0';
	delete[] old_ptr;
	return new_ptr;
}

char* String::regrow(char* old_ptr, int len, int pos) const {
	int leng = length(old_ptr);
	char* new_ptr = new char[leng + len + 1];
	for (int i = 0; i < pos; i++) {
		new_ptr[i] = old_ptr[i];
	}
	for (int i = pos + 1; i < leng + len; i++) {
		new_ptr[i] = old_ptr[i - len];
	}
	new_ptr[leng + len] = '\0';
	delete[] old_ptr;
	return new_ptr;
}

char* String::regrow(char* old_ptr, int len) {
	int leng = length(old_ptr);
	char* new_ptr = new char[leng + len + 1];
	for (int i = 0; i < leng; i++) {
		new_ptr[i] = old_ptr[i];
	}
	new_ptr[leng + len] = '\0';
	delete[] old_ptr;
	return new_ptr;
}

String* String::regrow(String* old_ptr, int& count) {
	String* new_ptr = new String[count + 1];
	for (int i = 0; i < count; i++) {
		new_ptr[i] = old_ptr[i];
	}
	count++;
	delete[] old_ptr;
	return new_ptr;
}

int* String::regrow(int* old_ptr, int& count) {
	int* new_ptr = new int[count + 1];
	for (int i = 0; i < count; i++) {
		new_ptr[i] = old_ptr[i];
	}
	count++;
	delete[] old_ptr;
	return new_ptr;
}

char* String::shrink(char* old_ptr, int idx) {
	int len = length(old_ptr);
	char* new_ptr = new char[len];
	for (int i = 0; i < idx; i++) {
		new_ptr[i] = old_ptr[i];
	}
	for (int i = idx + 1; i < len + 1; i++) {
		new_ptr[i - 1] = old_ptr[i];
	}
	delete[] old_ptr;
	return new_ptr;
}

bool String::search(const char* delim, char find) {
	for (int i = 0; delim[i] != '\0'; i++) {
		if (find == delim[i]) return true;
	}
	return false;
}

bool String::search_substr(const char* substr, char* str, int len, int start) {
	for (int i = 0; i < len; i++) {
		if (str[start + i] != substr[i]) return false;
	}
	return true;
}

bool String::is_lower(char ch) {
	if (ch > 96 && ch < 123) return true;
	return false;
}

bool String::is_upper(char ch) {
	if (ch > 64 && ch < 91) return true;
	return false;
}

String::String() :l{ 0 } {
	this->s = new char[1];
	this->s[0] = '\0';
}

String::String(const char* str) {
	this->l = length(str);
	this->s = new char[this->l + 1];
	for (int i = 0; i < this->l; i++) {
		this->s[i] = str[i];
	}
	this->s[this->l] = '\0';
}

String::String(const String& str) {
	this->l = str.l;
	this->s = new char[this->l + 1];
	for (int i = 0; i < this->l + 1; i++) {
		this->s[i] = str.s[i];
	}
}

String::String(long long int num) {
	this->l = 1;
	s = new char[this->l + 1];
	s[0] = (num % 10) + '0';
	num /= 10;
	s[1] = '\0';
	for (int i = 0; num != 0; i++) {
		s = regrow(s, 1, 0);
		s[0] = (num % 10) + '0';
		num /= 10;
		this->l++;
	}
}

String::~String() {
	delete[] this->s;
}

String& String::operator=(const String& str) {
	if (this->s != str.s) {
		this->l = str.l;
		//if (this->s != nullptr) 
		delete[] this->s;
		this->s = new char[this->l + 1];
		for (int i = 0; i < this->l; i++) {
			this->s[i] = str.s[i];
		}
		this->s[this->l] = '\0';
	}
	return *(this);
}

const char* String::c_str() const {
	return this->s;
}

void String::Print() {
	std::cout << this->s;
}

char& String::at(int pos) {
	if (pos < 0 || pos > this->l - 1) {
		std::cout << "Invalid position. Returning Null\n";
		return this->s[this->l];
	}
	return this->s[pos];
}

char& String::operator[](int pos) {
	if (pos < 0 || pos > this->l - 1) {
		std::cout << "Invalid position. Returning Null\n";
		return this->s[this->l];
	}
	return this->s[pos];
}

const char& String::operator[](int pos) const {
	if (pos < 0 || pos > this->l - 1) {
		std::cout << "Invalid position. Returning Null\n";
		return this->s[this->l];
	}
	return this->s[pos];
}

char& String::front() {
	return this->s[0];
}

char& String::back() {
	return this->s[this->l - 1];
}

bool String::empty() const {
	if (this->l == 0) return 1;
	return 0;
}

int String::Length() const {
	return this->l;
}

void String::ReplaceFirst(char c) {
	if (this->l > 0) this->s[0] = c;
}

String& String::insert(int pos, const char str) {
	if (pos < 0 || pos > this->l - 1) {
		std::cout << "Invalid position.\n";
		exit(1);
	}
	this->s = regrow(this->s, 1, pos);
	this->s[pos] = str;
	this->l = length();
	return *(this);
}

String& String::insert(int pos, const char* first) {
	if (pos < 0 || pos > this->l - 1) {
		std::cout << "Invalid position.\n";
		exit(1);
	}
	int tempL = length(first);
	this->s = regrow(this->s, tempL, pos);
	for (int i = 0; i < tempL; i++) {
		this->s[pos + i] = first[i];
	}
	this->l = length();
	return *(this);
}

String& String::operator+=(const String& str) {
	this->s = regrow(this->s, str.l);
	for (int i = 0; i < str.l; i++) {
		this->s[this->l + i] = str.s[i];
	}
	this->l = length(this->s);
	return *(this);
}

String& String::operator+=(char c) {
	this->s = regrow(this->s, 1);
	this->s[this->l] = c;
	this->l = length(this->s);
	return *(this);
}

int String::compare(const String& temp) {
	if (this->l > temp.l) return 1;
	else if (this->l < temp.l) return -1;
	else {
		for (int i = 0; i < this->l; i++) {
			if (this->s[i] > temp.s[i]) return 1;
			else if (this->s[i] < temp.s[i]) return -1;
		}
		return 0;
	}

}

long long int String::stoi() {
	long long int temp = this->s[0] - '0';
	for (int i = 1; i < this->l; i++) {
		temp = (temp * 10) + (this->s[i] - '0');
	}
	return temp;
}

String String::itos(long long int num) {
	String temp(num);
	return temp;
}

String String::trim() {
	String temp;
	int k = 0, i = 0, m = this->l - 1;
	for (; ; i++) {
		if (this->s[i] != ' ' && this->s[i] != '\n' && this->s[i] != '\t') {
			break;
		}
	}
	for (; ; m--) {
		if (this->s[m] != ' ' && this->s[m] != '\n' && this->s[m] != '\t') {
			break;
		}
	}
	for (int j = i; j <= m; j++) {
		temp.s = regrow(temp.s, 1, k);
		temp.l++;
		temp.s[k++] = this->s[j];
	}
	return temp;
}

String String::trim() const {
	String temp;
	int k = 0, i = 0, m = this->l - 1;
	for (; ; i++) {
		if (this->s[i] != ' ' && this->s[i] != '\n' && this->s[i] != '\t') {
			break;
		}
	}
	for (; ; m--) {
		if (this->s[m] != ' ' && this->s[m] != '\n' && this->s[m] != '\t') {
			break;
		}
	}
	for (int j = i; j <= m; j++) {
		temp.s = regrow(temp.s, 1, k);
		temp.l++;
		temp.s[k++] = this->s[j];
	}
	return temp;
}

String String::trim(const String t) {
	String temp = t.trim();
	return temp;
}

String* String::split(char delim, int& count) {
	count = 0;
	String* ret = nullptr;
	int temp = 0;
	for (int i = 0; i < this->l; i++) {
		if (this->s[i] == delim) {
			ret = regrow(ret, count);
			for (int j = temp; j < i; j++) {
				ret[count - 1].s = regrow(ret[count - 1].s, 1);
				ret[count - 1].s[j - temp] = this->s[j];
				ret[count - 1].l++;
			}
			temp = i + 1;
		}
	}
	ret = regrow(ret, count);
	for (int i = temp; i < this->l; i++) {
		ret[count - 1].s = regrow(ret[count - 1].s, 1);
		ret[count - 1].s[i - temp] = this->s[i];
		ret[count - 1].l++;
	}
	return ret;
}

String* String::tokenize(const char* delim, int& count) {
	count = 0;
	String* ret = nullptr;
	int temp = 0;
	for (int i = 0; i < this->l; i++) {
		if (search(delim, this->s[i])) {
			ret = regrow(ret, count);
			for (int j = temp; j < i; j++) {
				ret[count - 1].s = regrow(ret[count - 1].s, 1);
				ret[count - 1].s[j - temp] = this->s[j];
				ret[count - 1].l++;
			}
			temp = i + 1;
		}
	}
	ret = regrow(ret, count);
	for (int i = temp; i < this->l; i++) {
		ret[count - 1].s = regrow(ret[count - 1].s, 1);
		ret[count - 1].s[i - temp] = this->s[i];
		ret[count - 1].l++;
	}
	return ret;
}

int* String::all_sub_strings(const char* substr, int& count) {
	count = 0;
	int len = length(substr);
	int* ret = nullptr;
	for (int i = 0; i < this->l - len; i++) {
		if (search_substr(substr, this->s, len, i)) {
			ret = regrow(ret, count);
			ret[count - 1] = i;
		}
	}
	return ret;
}

int String::find_first(char ch) {
	for (int i = 0; i < this->l; i++) {
		if (this->s[i] == ch) return i;
	}
	return -1;
}

int String::find_first(const String& t) {
	int len = length(t.s);
	for (int i = 0; i < this->l - len; i++) {
		if (search_substr(t.s, this->s, len, i)) return i;
	}
	return -1;
}

int String::find_last(char ch) {
	for (int i = this->l - 1; i > -1; i--) {
		if (this->s[i] == ch) return i;
	}
	return -1;
}

int String::find_last(const String& t) {
	int len = length(t.s);
	for (int i = this->l - len; i > -1; i--) {
		if (search_substr(t.s, this->s, len, i)) return i;
	}
	return -1;
}

int* String::find_all(char ch, int& c) {
	c = 0;
	int* ret = nullptr;
	for (int i = 0; i < this->l; i++) {
		if (this->s[i] == ch) {
			ret = regrow(ret, c);
			ret[c - 1] = i;
		}
	}
	return ret;
}

int* String::find_all(const String& t, int& c) {
	c = 0;
	int* ret = nullptr;
	int len = length(t.s);
	for (int i = 0; i < this->l - len; i++) {
		if (search_substr(t.s, this->s, len, i)) {
			ret = regrow(ret, c);
			ret[c - 1] = i;
		}
	}
	return ret;
}

void String::remove_at(int idx) {
	if (idx < 0 || idx > this->l - 1) return;
	this->s = shrink(this->s, idx);
	this->l--;
}

void String::remove_first(char ch) {
	int idx = find_first(ch);
	this->s = shrink(this->s, idx);
	this->l--;
}

void String::remove_last(char ch) {
	int idx = find_last(ch);
	this->s = shrink(this->s, idx);
	this->l--;
}

void String::remove_all(char ch) {
	int idx = find_first(ch);
	while (idx != -1) {
		this->s = shrink(this->s, idx);
		this->l--;
		idx = find_first(ch);
	}
}

void String::clear() {
	delete[] this->s;
	this->s = new char[1];
	this->s[0] = '\0';
	this->l = 0;
}

String String::to_upper() {
	String temp(*this);
	for (int i = 0; i < temp.l; i++) {
		if (is_lower(temp.s[i])) temp.s[i] -= 32;
	}
	return temp;
}

String String::to_lower() {
	String temp(*this);
	for (int i = 0; i < temp.l; i++) {
		if (is_upper(temp.s[i])) temp.s[i] += 32;
	}
	return temp;
}

String operator+(const String& lhs, const String& rhs) {
	String temp(lhs);
	temp += rhs;
	return temp;
}

bool operator==(const String& lhs, const String& rhs) {
	String temp(lhs);
	if (temp.compare(rhs) == 0) return 1;
	else return 0;
}

bool operator!=(const String& lhs, const String& rhs) {
	String temp(lhs);
	if (temp.compare(rhs) != 0) return 1;
	else return 0;
}

bool operator<(const String& lhs, const String& rhs) {
	String temp(lhs);
	if (temp.compare(rhs) == -1) return 1;
	else return 0;
}

bool operator>(const String& lhs, const String& rhs) {
	String temp(lhs);
	if (temp.compare(rhs) == 1) return 1;
	else return 0;
}

bool operator<=(const String& lhs, const String& rhs) {
	String temp(lhs);
	if (temp.compare(rhs) == -1 || temp.compare(rhs) == 0) return 1;
	else return 0;
}

bool operator>=(const String& lhs, const String& rhs) {
	String temp(lhs);
	if (temp.compare(rhs) == 1 || temp.compare(rhs) == 0) return 1;
	else return 0;
}

std::ostream& operator<<(std::ostream& out, const String& str) {
	out << str.s;
	return out;
}

std::istream& operator>>(std::istream& in, String& str) {
	String temp;
	str.s = new char[1];
	str.s[0] = '\0';
	str.l = 0;
	char ch;
	in.get(ch);
	while (ch != '\n') {
		str.s = temp.regrow(str.s, 1, str.l);
		str.s[str.l] = ch;
		str.l++;
		in.get(ch);
	}
	return in;
}
