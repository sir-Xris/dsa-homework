/**                                                                             
 * Just a declaration and defination of stu_info.
 * Requirement of our homework.
 * 2016220204004 信息与软件工程学院 软件工程（软件技术） 叶鉴赏                 
 * Email: sir@xris.co
 */
#ifndef _STU_INFO_H_
#define _STU_INFO_H_ 1

#include <string>    /* std::string */
#include <iostream>  /* std::ostream */

struct stu_info {
  std::string name;
  /* I bet there is no one older than 4294967295 */
  unsigned int age;
  bool operator==(const stu_info &) const;
  bool operator<(const stu_info &) const;
  bool operator<=(const stu_info &) const;
  friend std::ostream &operator<<(std::ostream &, const stu_info &);
  friend std::istream &operator>>(std::istream &, stu_info &);
};

bool stu_info::operator==(const stu_info &si) const {
  return this->name == si.name && this->age == si.age;
}

bool stu_info::operator<(const stu_info &si) const {
  return this->name < si.name || (this->name == si.name && this->age < si.age);
}

bool stu_info::operator<=(const stu_info &si) const {
  return *this == si || *this < si;
}

std::ostream &operator<<(std::ostream &os, const stu_info &si) {
  os << si.name << ' ' << si.age;
  return os;
}

std::istream &operator>>(std::istream &is, stu_info &si) {
  cin >> si.name >> si.age;
  return is;
}

#endif  /* _STU_INFO_H_ */

