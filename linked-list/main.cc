/**
 * main function here.
 * 2016220204004 信息与软件工程学院 软件工程（软件技术） 叶鉴赏
 * Email: sir@xris.co
 */

#include <map>
#include <iostream>
#include <string>
#include "singly_linked_list.h"
using namespace std;

#include "stu_info.h"

const char usage[] = R"(
--*-- --*-- --*-- --*-- --*-- --*-- --*-- --*-- --*-- --*-- --*-- --*--
Show all lists: all
Create list: create <list-name>
Delete list: delete <list-name>
Show list:   show   <list-name>
Insert node: insert <list-name> <student-name> <student-age>
Remove node: remove <list-name> <student-name> <student-age>
Sort list:   sort   <list-name>
Merge lists: merge  <list-name> <list-name>
--*-- --*-- --*-- --*-- --*-- --*-- --*-- --*-- --*-- --*-- --*-- --*--
Please input command: )";

map<string, singly_linked_list<stu_info>> db;

void all() {
  cout << "\033[1m";
  for (auto it = db.begin(); it != db.end(); ++it) {
    cout << it->first << ' ';
  }
  cout << "\033[0m" << endl;
}

void create(const string &list_name) {
  if (db.find(list_name) != db.end()) {
    cerr << "\033[1;31mList exists.\033[0m" << endl;
  } else {
    db[list_name] = singly_linked_list<stu_info>();
    cerr << "\033[1;32mCreate successfully.\033[0m" << endl;
  }
}

void deletes(const string &list_name) {
  auto it = db.find(list_name);
  if (it == db.end()) {
    cerr << "\033[1;31mList not exists.\033[0m" << endl;
  } else {
    db.erase(it);
    cerr << "\033[1;32mDelete successfully.\033[0m" << endl;
  }
}

void show(const string &list_name) {
  auto it = db.find(list_name);
  if (it == db.end()) {
    cerr << "\033[1;31mList not exists.\033[0m" << endl;
  } else cout << "\033[1m" << it->second << "\033[0m" << endl;
}

void insert(const string &list_name, const stu_info &student) {
  auto it = db.find(list_name);
  if (it == db.end()) {
    cerr << "\033[1;31mList not exists.\033[0m" << endl;
  } else {
    it->second.push_back(student);
    cerr << "\033[1;32mInsert successfully.\033[0m" << endl;
  }
}

void remove(const string &list_name, const stu_info &student) {
  auto it = db.find(list_name);
  if (it == db.end()) {
    cerr << "\033[1;31mList not exists.\033[0m" << endl;
  } else {
    it->second.remove(student);
    cerr << "\033[1;32mRemove successfully.\033[0m" << endl;
  }
}

void sort(const string &list_name) {
  auto it = db.find(list_name);
  if (it == db.end()) {
    cerr << "\033[1;31mList not exists.\033[0m" << endl;
  } else {
    it->second.sort(increase);
    cerr << "\033[1;32mSort successfully.\033[0m" << endl;
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
    cerr << "\033[1;31mList not exists.\033[0m" << endl;
  } else {
    /**
     * When use function merge, we have to ensure two lists are both sorted.
     * As for the enum `increase', see singly_linked_list.h.
     */
    it0->second.sort(increase); it1->second.sort(increase);
    it0->second.sorted_uniqued_reverse_merge(it1->second);
    cerr << "\033[1;32mMerge successfully.\033[0m" << endl;
  }
}

int main() {
  string command, list_name, another_list;
  stu_info student;

  while (true) {
    cout << usage;
    cin >> command;
    if (cin.eof()) {
      cerr << "\033[1mBye!\033[0m" << endl;
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
      cerr << "\033[1;31mCommand not found, try again.\033[0m" << endl;
      cerr << "Press Ctrl+C or EOF to exit the program." << endl;
      cerr << "i.e. Ctrl+D in Unix-like system and Ctrl+Z in Windows." << endl;
    }
    while (cin.get() != '\n');
    cout << endl;
  }
  return 0;
}
