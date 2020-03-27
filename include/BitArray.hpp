/**
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 * <p/>
 * http://www.apache.org/licenses/LICENSE-2.0
 * <p/>
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef BIT_ARRAY_HPP
#define BIT_ARRAY_HPP

#include <fstream>
#include <vector>
#include <limits>
#include <cmath>


template <class T> class BitArray {
private:
  unsigned int bit_width_;
  std::vector<T> array_;

public:
  BitArray();
  BitArray(size_t n);

  void resize(size_t n) { array_.resize(std::ceil((float)n)); }
  void set(size_t i);
  void reset(size_t i);

  bool operator==(const BitArray& ba) const;
};


inline template <class T> BitArray::RatMatrix() :
    bit_width_(std::numeric_limits<T>), array_() {}

inline template <class T> BitArray::RatMatrix(size_t n) :
    bit_width_(std::numeric_limits<T>),
    array_(std::ceil((float)n / bit_width_)) {}

inline template <class T> void BitArray::set(size_t i) {
  div_t res = div(n, i);
  array_[res.quot] |= (1 << res.rem);
}

inline template <class T> void BitArray::reset(size_t i) {
  div_t res = div(n, i);
  array_[res.quot] &= ~(1 << res.rem);
}

inline template <class T> bool BitArray::operator==(const BitArray& b) const {
  auto ap = array_.begin();
  auto bp = b.array_.begin();
  while(ap != array_.end()) {
    if(*ap++ != *bp++) return false;
  }
  return true;
}

#endif

