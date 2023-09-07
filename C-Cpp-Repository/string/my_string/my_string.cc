/****************************************************************
 * Copyright 2021 HUST Control Science Innovation Base.
 * All rights reserved.
 * Author : Dong Zhaorui 847235539@qq.com
 * Date   : 2021-12-07
 ****************************************************************/

#include "my_string/my_string.h"

#include <cstring>

namespace my_string {
// constructor
MyString::MyString(const char* char_list) {
  if (char_list) {
    uint64_t length = strlen(char_list) + 1;
    pointer_ = new char[length];
    snprintf(pointer_, length, "%s", char_list);
  } else {
    pointer_ = new char[1];
    *pointer_ = '\0';
  }
}

// big three
MyString::MyString(const MyString& my_string) {
  uint64_t length = strlen(my_string.GetPointer()) + 1;
  pointer_ = new char[length];
  snprintf(pointer_, length, "%s", my_string.GetPointer());
}

MyString& MyString::operator=(const MyString& my_string) {
  if (this == &my_string) {
    return *this;
  }

  delete[] pointer_;

  uint64_t length = strlen(my_string.GetPointer()) + 1;
  pointer_ = new char[length];
  snprintf(pointer_, length, "%s", my_string.GetPointer());

  return *this;
}

// operator
MyString& MyString::operator=(const char* char_list) {
  if (char_list) {
    delete[] pointer_;
    uint64_t length = strlen(char_list) + 1;
    pointer_ = new char[length];
    snprintf(pointer_, length, "%s", char_list);
  }

  return *this;
}

// output
std::ostream& operator<<(std::ostream& os, const MyString& my_string) {
  os << my_string.GetPointer();
  return os;
}

}  // namespace my_string
