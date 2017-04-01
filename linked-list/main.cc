#include <map>
#include <iostream>
#include <string>
#include "singly_linked_list.h"
using namespace std;

#include "stu_info.h"

const char usage[] = "\
--*-- --*-- --*-- --*-- --*-- --*-- --*-- --*-- --*-- --*-- --*-- --*--\n\
Show all lists: all\n\
Create list: create <list-name>\n\
Delete list: delete <list-name>\n\
Show list:   show   <list-name>\n\
Insert node: insert <list-name> <student-name> <student-age>\n\
Remove node: remove <list-name> <student-name> <student-age>\n\
Sort list:   sort   <list-name>\n\
Merge lists: merge  <list-name> <list-name>\n\
--*-- --*-- --*-- --*-- --*-- --*-- --*-- --*-- --*-- --*-- --*-- --*--\n\
Please input command: ";

map<string, singly_linked_list<stu_info>> db;

void all() {
  for (auto it = db.begin(); it != db.end(); ++it) {
    cout << it->first << ' ';
  }
  cout << endl;
}

void create(const string &list_name) {
  if (db.find(list_name) != db.end()) {
    cout << "List exists." << endl;
  } else {
    db[list_name] = singly_linked_list<stu_info>();
    cout << "Create successfully." << endl;
  }
}

void deletes(const string &list_name) {
  auto it = db.find(list_name);
  if (it == db.end()) {
    cout << "List not exists." << endl;
  } else {
    db.erase(it);
    cout << "Delete successfully." << endl;
  }
}

void show(const string &list_name) {
  auto it = db.find(list_name);
  if (it == db.end()) {
    cout << "List not exists." << endl;
  } else cout << it->second << endl;
}

void insert(const string &list_name, const stu_info &student) {
  auto it = db.find(list_name);
  if (it == db.end()) {
    cout << "List not exists." << endl;
  } else {
    it->second.push_back(student);
    cout << "Insert successfully." << endl;
  }
}

void remove(const string &list_name, const stu_info &student) {
  auto it = db.find(list_name);
  if (it == db.end()) {
    cout << "List not exists." << endl;
  } else {
    it->second.remove(student);
    cout << "Remove successfully." << endl;
  }
}

void sort(const string &list_name) {
  auto it = db.find(list_name);
  if (it == db.end()) {
    cout << "List not exists." << endl;
  } else {
    it->second.sort(increase);
    cout << "Sort successfully." << endl;
  }
}

/**
 * This operation will `not' delete the second list, but will sort it.
 * Tired of elinimating side effects,
 * though copy to a new list should make different.
 */
void merge(const string &list0, const string &list1) {
  auto it0 = db.find(list0), it1 = db.find(list1);
  if (it0 == db.end() || it1 == db.end()) {
    cout << "List not exists." << endl;
  } else {
    /**
     * When use function merge, we have to ensure two lists are both sorted.
     * As for the enum `increase', see singly_linked_list.h.
     */
    it0->second.sort(increase); it1->second.sort(increase);
    it0->second.sorted_uniqued_reverse_merge(it1->second);
    cout << "Merge successfully." << endl;
  }
}

int main() {
  string command, list_name, another_list;
  stu_info student;

  while (true) {
    cout << usage;
    cin >> command;
    if (cin.eof()) {
      cout << "Bye!" << endl;
      return 0;
    } else if (command == "all") {
      all();
    } else if (command == "create") {
      cin >> list_name; create(list_name);
    } else if (command == "delete") {
      cin >> list_name; deletes(list_name);
    } else if (command == "show") {
      cin >> list_name; show(list_name);
    } else if (command == "insert") {
      cin >> list_name >> student;
      insert(list_name, student);
    } else if (command == "remove") {
      cin >> list_name >> student;
      remove(list_name, student);
    } else if (command == "sort") {
      cin >> list_name; sort(list_name);
    } else if (command == "merge") {
      cin >> list_name >> another_list;
      merge(list_name, another_list);
    } else {
      cout << "Command not found, try again." << endl;
      cout << "Press Ctrl+C or EOF to exit the program." << endl;
      cout << "i.e. Ctrl+D in Unix-like system and Ctrl+Z in Windows." << endl;
    }
    while (cin.get() != '\n');
    cout << endl;
  }
  return 0;
}
