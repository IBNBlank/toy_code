/****************************************************************
 * Copyright 2021 HUST Control Science Innovation Base.
 * All rights reserved.
 * Author: Dong Zhaorui 847235539@qq.com
 * Date  : 2021-10-30
 ****************************************************************/

#include <iostream>
#include <string>

class CStud {
 public:
  CStud();
  ~CStud() = default;
  static float avg();
  void setdata(std::string no, std::string name, float score);
  void disp();

 private:
  static float sum_;
  static float num_;
  std::string no_;
  std::string name_;
  float score_;
};

float CStud::sum_ = 0;
float CStud::num_ = 0;

CStud::CStud() {
  no_ = "";
  name_ = "";
  score_ = 0.0;
  num_++;
}

float CStud::avg() { return sum_ / num_; }

void CStud::setdata(std::string no, std::string name, float score) {
  no_ = no;
  name_ = name;
  score_ = score;
  sum_ += score;
}

void CStud::disp() {
  std::cout << "no:" << no_ << std::endl
            << "name:" << name_ << std::endl
            << "score:" << score_ << std::endl;
}

int main(int argc, char const *argv[]) {
  CStud cstud[3];
  cstud[0].setdata("M202173200", "张三", 89.0);
  cstud[0].disp();
  cstud[1].setdata("M202173201", "李四", 90.0);
  cstud[1].disp();
  cstud[2].setdata("M202173202", "王五", 91.0);
  cstud[2].disp();

  std::cout << "avg():" << CStud::avg() << std::endl;

  return 0;
}
