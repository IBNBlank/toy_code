/****************************************************************
 * Copyright 2021 HUST Control Science Innovation Base.
 * All rights reserved.
 * Author : Dong Zhaorui 847235539@qq.com
 * Date   : 2021-12-07
 ****************************************************************/

#ifndef MY_STRING_MY_STRING_H_
#define MY_STRING_MY_STRING_H_

#include <iostream>

namespace my_string {

class MyString {
 public:
  // constructor
  MyString(const char* char_list = 0);

  // big three
  MyString(const MyString&);
  inline ~MyString() { delete[] pointer_; }
  MyString& operator=(const MyString&);

  // get element
  inline char* GetPointer() const { return pointer_; }

  // assignment
  MyString& operator=(const char*);

 private:
  char* pointer_;
};

// output
std::ostream& operator<<(std::ostream&, const MyString&);

}  // namespace my_string

#endif  // MY_STRING_MY_STRING_H_
