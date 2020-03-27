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
#ifndef FROBENIUS_HPP
#define FROBENIUS_HPP

#include "RatMatrix.hpp"
#include "IndexVector.hpp"

class Frobenius : public RatMatrix {
private:
  IndexVector index_;
  RatColumn right_factor, left_factor, *tmp_column;


private:
  // for debug
  void _debug_show_vector(const RatColumn& vec);
  void _debug_show_vector();

  void swap(size_t a, size_t b){ index_.swap(a,b); }
  size_t find_non_zero_row(size_t i) const;
  void trans(size_t i);

public:
  Frobenius();
  Frobenius(size_t n);
  ~Frobenius() { delete tmp_column; }

  void resize(size_t n);

  Rat& get(size_t i, size_t j);
  const Rat& get(size_t i, size_t j) const;
  void trans();

  void load(const std::string& fn, bool to_expand);
  void print(std::ostream& os) const;
};


inline Frobenius::Frobenius()
: RatMatrix(), index_(), right_factor(), left_factor(),
tmp_column(new RatColumn()) {}

inline Frobenius::Frobenius(size_t n)
: RatMatrix(n), index_(n), right_factor(n), left_factor(n),
tmp_column(new RatColumn(n)) {}

inline void Frobenius::resize(size_t n) {
  RatMatrix::resize(n);
  index_.resize(n);
  right_factor.resize(n);
  left_factor.resize(n);
  tmp_column->resize(n);
 }

inline Rat& Frobenius::get(size_t i, size_t j) {
  return RatMatrix::get(index_[i], index_[j]);
}

inline const Rat& Frobenius::get(size_t i, size_t j) const {
  return RatMatrix::get(index_[i], index_[j]);
}

inline void Frobenius::load(const std::string& fn, bool to_expand = false) {
  RatMatrix::load(fn, to_expand);
  size_t n = size();
  index_.resize(n);
  right_factor.resize(n);
  left_factor.resize(n);
  tmp_column->resize(n);
}

inline std::ostream& operator<<(std::ostream& os, const Frobenius& fro) {
  fro.print(os);
  return os;
}

#endif

