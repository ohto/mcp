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
#ifndef EX_POLY_HPP
#define EX_POLY_HPP

#include "Rat.hpp"
#include <boost/math/tools/polynomial.hpp>
using Polynomial = boost::math::tools::polynomial<Rat>;


class ExPoly : public Polynomial {
public:
  using Polynomial::Polynomial;
  void differential();
  Rat operator()(const Rat&) const;
};


inline ExPoly operator+(const ExPoly& a, const ExPoly& b) {
  ExPoly ret = a;
  ret += b;
  return ret;
}

inline ExPoly operator-(const ExPoly& a, const ExPoly& b) {
  ExPoly ret = a;
  ret -= b;
  return ret;
}

inline ExPoly operator*(const ExPoly& a, const ExPoly& b) {
  ExPoly ret = a;
  ret *= b;
  return ret;
}

inline ExPoly operator/(const ExPoly& a, const ExPoly& b) {
  ExPoly ret = a;
  ret /= b;
  return ret;
}

inline ExPoly operator%(const ExPoly& a, const ExPoly& b) {
  ExPoly ret = a;
  ret %= b;
  return ret;
}

inline ExPoly operator+(const ExPoly& a, const Rat& b) {
  ExPoly ret = a;
  ret += b;
  return ret;
}

inline ExPoly operator-(const ExPoly& a, const Rat& b) {
  ExPoly ret = a;
  ret -= b;
  return ret;
}

inline ExPoly operator*(const ExPoly& a, const Rat& b) {
  ExPoly ret = a;
  ret *= b;
  return ret;
}

inline ExPoly operator/(const ExPoly& a, const Rat& b) {
  ExPoly ret = a;
  ret /= b;
  return ret;
}

inline ExPoly operator%(const ExPoly& a, const Rat& b) {
  ExPoly ret = a;
  ret %= b;
  return ret;
}

inline ExPoly operator+(const Rat& a, const ExPoly& b) {
  ExPoly ret = b;
  ret += a;
  return ret;
}

inline ExPoly operator-(const Rat& a, const ExPoly& b) {
  ExPoly ret = b;
  ret *= -1;
  ret += a;
  return ret;
}

inline ExPoly operator*(const Rat& a, const ExPoly& b) {
  ExPoly ret = b;
  ret *= a;
  return ret;
}

inline ExPoly operator-(const ExPoly& a) {
  ExPoly ret = a;
  ret *= -1;
  return ret;
}

#endif

