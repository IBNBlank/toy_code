/****************************************************************
 * Copyright 2021 HUST Control Science Innovation Base.
 * All rights reserved.
 * Author : Dong Zhaorui 847235539@qq.com
 * Date   : 2021-12-20
 ****************************************************************/

#ifndef CTIME_CTIME_H_
#define CTIME_CTIME_H_

#include <iostream>

namespace my_ctime {

class CTime {
 public:
  // constructor
  explicit CTime(uint32_t second = 0, uint32_t minute = 0, uint32_t hour = 0,
                 uint32_t day = 0, uint32_t month = 0, uint32_t year = 0);

  // big three
  CTime(const CTime&);
  CTime& operator=(const CTime&);

  // set element
  inline void SetYear(uint32_t year) { year_ = year; }
  inline void SetMonth(uint32_t month) { month_ = month; }
  inline void SetDay(uint32_t day) { day_ = day; }
  inline void SetHour(uint32_t hour) { hour_ = hour; }
  inline void SetMinute(uint32_t minute) { minute_ = minute; }
  inline void SetSecond(uint32_t second) { second_ = second; }
  inline void SetWholeSecond(uint32_t);

  // get element
  inline uint32_t GetYear() const { return year_; }
  inline uint32_t GetMonth() const { return month_; }
  inline uint32_t GetDay() const { return day_; }
  inline uint32_t GetHour() const { return hour_; }
  inline uint32_t GetMinute() const { return minute_; }
  inline uint32_t GetSecond() const { return second_; }
  inline uint32_t GetWholeSecond() const {
    return (
        ((((year_ * 12 + month_) * 30 + day_) * 24 + hour_) * 60 + minute_) *
            60 +
        second_);
  }

  CTime& operator+=(const CTime&);
  CTime& operator-=(const CTime&);
  CTime& operator*=(uint32_t);
  CTime& operator/=(uint32_t);

 private:
  uint32_t year_;
  uint32_t month_;
  uint32_t day_;
  uint32_t hour_;
  uint32_t minute_;
  uint32_t second_;
};

// add
CTime operator+(const CTime&, const CTime&);

// subtract
CTime operator-(const CTime&, const CTime&);

// multiply
CTime operator*(const CTime&, uint32_t);
CTime operator*(uint32_t, const CTime&);

// divide
CTime operator/(const CTime&, uint32_t);

// less
bool operator<(const CTime&, const CTime&);

// greater
bool operator>(const CTime&, const CTime&);

// equal
bool operator==(const CTime&, const CTime&);

// not equal
bool operator!=(const CTime&, const CTime&);

// less or equal
bool operator<=(const CTime&, const CTime&);

// greater or equal
bool operator>=(const CTime&, const CTime&);

// output
std::ostream& operator<<(std::ostream&, const CTime&);

}  // namespace my_ctime

#endif  // CTIME_CTIME_H_
