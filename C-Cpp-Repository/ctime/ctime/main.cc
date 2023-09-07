/****************************************************************
 * Copyright 2021 HUST Control Science Innovation Base.
 * All rights reserved.
 * Author : Dong Zhaorui 847235539@qq.com
 * Date   : 2021-12-20
 ****************************************************************/

#include <iostream>

#include "ctime/ctime.h"

using my_ctime::CTime;

int main(int argc, char const *argv[]) {
  CTime time_1(1, 1, 1, 1, 1, 1);
  CTime time_2(10000);
  std::cout << "time_1 : " << time_1 << std::endl;
  std::cout << "time_1.GetWholeSecond() : " << time_1.GetWholeSecond()
            << std::endl;
  std::cout << "time_2 : " << time_2 << std::endl;
  std::cout << "time_2.GetWholeSecond() : " << time_2.GetWholeSecond()
            << std::endl;

  CTime time_3(time_1);
  std::cout << "time_3(time_1) : " << time_3 << std::endl;
  time_3 = time_2;
  std::cout << "time_3 = time_2 : " << time_3 << std::endl;
  time_3 += time_1;
  std::cout << "time_3 += time_1 : " << time_3 << std::endl;
  time_3 -= time_2;
  std::cout << "time_3 -= time_2 : " << time_3 << std::endl;
  time_3 *= 2;
  std::cout << "time_3 *= 2 : " << time_3 << std::endl;
  time_3 /= 2;
  std::cout << "time_3 /= 2 : " << time_3 << std::endl;
  std::cout << "time_1 + time_2 : " << (time_1 + time_2) << std::endl;
  std::cout << "time_1 - time_2 : " << (time_1 - time_2) << std::endl;
  std::cout << "time_1 * 2 : " << (time_1 * 2) << std::endl;
  std::cout << "time_1 / 2 : " << (time_1 / 2) << std::endl;
  std::cout << "time_3 == time_1 : " << (time_3 == time_1) << std::endl;
  std::cout << "time_3 != time_2 : " << (time_3 != time_2) << std::endl;
  std::cout << "time_3 > time_2 : " << (time_3 > time_2) << std::endl;
  std::cout << "time_3 >= time_2 : " << (time_3 > time_2) << std::endl;
  std::cout << "time_2 < time_1 : " << (time_2 < time_1) << std::endl;
  std::cout << "time_2 <= time_1 : " << (time_2 <= time_1) << std::endl;

  return 0;
}
