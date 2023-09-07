/****************************************************************
 * Copyright 2021 HUST Control Science Innovation Base.
 * All rights reserved.
 * Author : Dong Zhaorui 847235539@qq.com
 * Date   : 2021-12-20
 ****************************************************************/

#include "ctime/ctime.h"

#include <iostream>

namespace my_ctime {
// constructor
CTime::CTime(uint32_t second, uint32_t minute, uint32_t hour, uint32_t day,
             uint32_t month, uint32_t year)
    : year_(year),
      month_(month),
      day_(day),
      hour_(hour),
      minute_(minute),
      second_(second) {
  if (second_ >= 60) {
    minute_ += second_ / 60;
    second_ %= 60;
  }
  if (minute_ >= 60) {
    hour_ += minute_ / 60;
    minute_ %= 60;
  }
  if (hour_ >= 24) {
    day_ += hour_ / 24;
    hour_ %= 24;
  }
  if (day_ >= 30) {
    month_ += day_ / 30;
    day_ %= 30;
  }
  if (month_ >= 12) {
    year_ += month_ / 12;
    month_ %= 12;
  }
}

CTime::CTime(const CTime& ctime) {
  year_ = ctime.GetYear();
  month_ = ctime.GetMonth();
  day_ = ctime.GetDay();
  hour_ = ctime.GetHour();
  minute_ = ctime.GetMinute();
  second_ = ctime.GetSecond();
}

CTime& CTime::operator=(const CTime& ctime) {
  if (this == &ctime) {
    return *this;
  }

  year_ = ctime.GetYear();
  month_ = ctime.GetMonth();
  day_ = ctime.GetDay();
  hour_ = ctime.GetHour();
  minute_ = ctime.GetMinute();
  second_ = ctime.GetSecond();

  return *this;
}

// public method
inline void CTime::SetWholeSecond(uint32_t whole_second) {
  second_ = whole_second % 60;
  uint32_t left_minute = whole_second / 60;
  minute_ = left_minute % 60;
  uint32_t left_hour = left_minute / 60;
  hour_ = left_hour % 24;
  uint32_t left_day = left_hour / 24;
  day_ = left_day % 30;
  uint32_t left_month_ = left_day / 30;
  month_ = left_month_ % 12;
  year_ = left_month_ / 12;
}

// class operator overloading
CTime& CTime::operator+=(const CTime& right) {
  this->SetWholeSecond(this->GetWholeSecond() + right.GetWholeSecond());
  return *this;
}

CTime& CTime::operator-=(const CTime& right) {
  if (this->GetWholeSecond() > right.GetWholeSecond()) {
    this->SetWholeSecond(this->GetWholeSecond() - right.GetWholeSecond());
  }
  return *this;
}

CTime& CTime::operator*=(uint32_t right) {
  this->SetWholeSecond(this->GetWholeSecond() * right);
  return *this;
}

CTime& CTime::operator/=(uint32_t right) {
  this->SetWholeSecond(this->GetWholeSecond() / right);
  return *this;
}

// add
CTime operator+(const CTime& left, const CTime& right) {
  CTime result;
  result.SetWholeSecond(left.GetWholeSecond() + right.GetWholeSecond());
  return result;
}

// subtract
CTime operator-(const CTime& left, const CTime& right) {
  CTime result;
  result.SetWholeSecond(left.GetWholeSecond() - right.GetWholeSecond());
  return result;
}

// multiply
CTime operator*(const CTime& left, uint32_t right) {
  CTime result;
  result.SetWholeSecond(left.GetWholeSecond() * right);
  return result;
}

CTime operator*(uint32_t left, const CTime& right) {
  CTime result;
  result.SetWholeSecond(left * right.GetWholeSecond());
  return result;
}

// divide
CTime operator/(const CTime& left, uint32_t right) {
  CTime result;
  result.SetWholeSecond(left.GetWholeSecond() / right);
  return result;
}

// less
bool operator<(const CTime& left, const CTime& right) {
  return (left.GetWholeSecond() < right.GetWholeSecond());
}

// greater
bool operator>(const CTime& left, const CTime& right) {
  return (left.GetWholeSecond() > right.GetWholeSecond());
}

// equal
bool operator==(const CTime& left, const CTime& right) {
  return (left.GetWholeSecond() == right.GetWholeSecond());
}

// not equal
bool operator!=(const CTime& left, const CTime& right) {
  return (left.GetWholeSecond() != right.GetWholeSecond());
}

// less or equal
bool operator<=(const CTime& left, const CTime& right) {
  return (left.GetWholeSecond() <= right.GetWholeSecond());
}

// greater or equal
bool operator>=(const CTime& left, const CTime& right) {
  return (left.GetWholeSecond() >= right.GetWholeSecond());
}

// output
std::ostream& operator<<(std::ostream& os, const CTime& time) {
  return os << time.GetYear() << "-" << time.GetMonth() << "-" << time.GetDay()
            << " " << time.GetHour() << ":" << time.GetMinute() << ":"
            << time.GetSecond();
}

}  // namespace my_ctime
