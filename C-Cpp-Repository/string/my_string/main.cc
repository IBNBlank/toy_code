/****************************************************************
 * Copyright 2021 HUST Control Science Innovation Base.
 * All rights reserved.
 * Author : Dong Zhaorui 847235539@qq.com
 * Date   : 2021-12-07
 ****************************************************************/

#include <iostream>

#include "my_string/my_string.h"

using my_string::MyString;

int main(int argc, char const *argv[]) {
  MyString s1("hello");
  MyString s2("world");

  MyString s3(s2);
  std::cout << s3 << std::endl;

  s3 = s1;
  std::cout << s3 << std::endl;
  std::cout << s2 << std::endl;
  std::cout << s1 << std::endl;

  MyString s4 = "000000";
  std::cout << s4 << std::endl;

  return 0;
}
