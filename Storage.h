#pragma once
#include "myVector.h"
#include "String.h"
#include <fstream>

template<typename T>
class Storage {
private:
	myVector<T> items;
public:
	Storage() : items(T(), 0) {}
	void add(const T& item) {
		items.push_back(item);
	}
	int get_count() {
		return items.size();
	}
	T& get_at(int pos) {
		return items.get_live_reference_at(pos);
	}
	T* find_ptr(const String& id) {
		int size = items.size();
		for (int i = 0; i < size; i++) {
			if (items.get_live_reference_at(i).get_user_id() == id) {
				return &items.get_live_reference_at(i);
			}
		}
		return nullptr;
	}
	void save_to_file(const char* filename) {
		std::ofstream fout(filename);
		if (!fout) {
			cout << "File not found.\n";
			return;
		}
		int ct = items.size();
		for (int i = 0; i < ct; i++) {
			fout << items.get_live_reference_at(i).serialize() << std::endl;
		}
		fout.close();
	}
	void clear_storage() {
		items.clear();
	}
};