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
#ifndef RAT_MATRIX_HPP
#define RAT_MATRIX_HPP

#include <fstream>
#include <vector>
#include "Rat.hpp"

class RatMatrix {
protected:
  using RatColumn = std::vector<Rat>;
  std::vector<RatColumn*> mat_;

private:
  bool expanded_ = false;

  template <class I> void mem_alloc(const I s, const I e, size_t n);
  template <class I> void mem_del(const I s, const I e);

  size_t get_size(std::ifstream&);
  void set_edges(std::ifstream&);
  void set(size_t i, size_t j, int v) { get(i,j) = v; get(j,i) = v; }

public:
  RatMatrix() : mat_(), expanded_(false) {}
  RatMatrix(size_t n);
  ~RatMatrix() { mem_del(mat_.begin(), mat_.end()); }

  size_t size() const { return mat_.size(); }
  bool is_expanded() const { return expanded_; }
  void resize(size_t n);

  Rat& get(size_t i, size_t j) { return mat_[j]->operator[](i); }
  const Rat& get(size_t i, size_t j) const { return mat_[j]->operator[](i); }

  void set(size_t i, size_t j) { set(i, j, 1); }
  void reset(size_t i, size_t j) { set(i, j, 0); }

  void load(const std::string& fn, bool to_expand = false);
  void print(std::ostream& os) const;
};


template <class I> void RatMatrix::mem_alloc(const I s, const I e, size_t n) {
  for(auto p = s; p != e; ++p) {
    *p = new std::vector<Rat>(n);
  }
}

template <class I> void RatMatrix::mem_del(const I s, const I e) {
  for(auto p = s; p != e; ++p) delete *p;
}

inline RatMatrix::RatMatrix(size_t n)
: mat_(std::vector<RatColumn*>(n)), expanded_(false) {
  mem_alloc(mat_.begin(), mat_.end(), n);
}

inline std::ostream& operator<<(std::ostream& os, const RatMatrix& mat) {
  mat.print(os);
  return os;
}

#endif

