#pragma once
#include <iostream>
#include <fstream>
#include <cstdlib>

class String {
	char* s;
	int l;

	int length(const char*);
	int length(char*);
	int length(char* temp) const;
	int length();
	char* regrow(char*, int, int);
	char* regrow(char*, int, int) const;
	char* regrow(char*, int);
	String* regrow(String*, int&);
	int* regrow(int*, int&);
	char* shrink(char*, int);
	bool search(const char*, char);
	bool search_substr(const char*, char*, int, int);
	bool is_lower(char);
	bool is_upper(char);

public:
	String();
	String(const char*);
	String(const String&);
	explicit String(double);
	explicit String(long long int);
	explicit String(long int);
	explicit String(int);
	~String();
	String& operator=(const String&);
	void Print();
	char& at(int);
	char& operator[](int);
	const char& operator[](int) const;
	char& front();
	char& back();
	bool empty() const;
	int Length() const;
	void ReplaceFirst(char);
	String& insert(int, const char);
	String& insert(int, const char*);
	String& operator+=(const String&);
	String& operator+=(char);
	int compare(const String&);
	double stod();
	String dtos(double);
	long long int stoi();
	String itos(long long int);
	String trim();
	String trim() const;
	static String trim(const String);
	String* split(char, int&);
	String* tokenize(const char*, int&);
	int* all_sub_strings(const char*, int&);
	int find_first(char);
	int find_first(const String&);
	int find_last(char);
	int find_last(const String&);
	int* find_all(char, int&);
	int* find_all(const String&, int&);
	void remove_at(int);
	void remove_first(char);
	void remove_last(char ch);
	void remove_all(char);
	void clear();
	String to_upper();
	String to_lower();
	friend std::ostream& operator<<(std::ostream&, const String&);
	friend std::istream& operator>>(std::istream&, String&);
	friend String operator+(const String&, const String&);
	friend bool operator==(const String&, const String&);
	friend bool operator!=(const String&, const String&);
	friend bool operator<(const String&, const String&);
	friend bool operator>(const String&, const String&);
	friend bool operator<= (const String&, const String&);
	friend bool operator>=(const String&, const String&);
};