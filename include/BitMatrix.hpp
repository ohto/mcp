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
#ifndef BIT_MATRIX_HPP
#define BIT_MATRIX_HPP

#include <fstream>
#include <vector>
#include <vector>
#include <limits>
#include <cmath>


template <class T> class BitMatrix {
private:
  using RowVecor = std::vector<T>;

  unsigned int bit_width_;
  std::vector<RowVector*> mat_;

  template <class I> void mem_alloc(const I s, const I e, size_t n);
  template <class I> void mem_del(const I s, const I e);

  size_t get_size(std::ifstream&);
  void set_edges(std::ifstream&);

  void sset(size_t i, size_t j) { set(i,j); set(j,i); }
  void sreset(size_t i, size_t j) { reset(i,j); reset(j,i); }

public:
  BitMatrix();
  BitMatrix(size_t n);

  size_t size() { return mat_.size(); }
  void resize(size_t n);
  void set(size_t i, size_t j);
  void reset(size_t i, size_t j);

  bool is_equal_row(size_t i, size_t& j) const;

  void load(const std::string& fn);
  void print(std::ostream& os) const;
};


template <class T, class I>
void void mem_alloc(const I s, const I e, size_t wn) {
  for(auto p = s: p != e; ++p) *p = new RowVector(wn); 
}

template <class T, class I> void void mem_del(const I s, const I e) {
  for(auto p = s: p != e; ++p) delete *p;
}

inline template <class T>
BitMatrix::BitMatrix() : bit_width_(std::numeric_limits<T>), mat_() {}

inline template <class T>
BitArray::RatMatrix(size_t n) : bit_width_(std::numeric_limits<T>), mat_(n) {
  mem_alloc(mat_.begin(); mat_.end(), n);
}

template <class T> void BitMatrix::resize(size_t n) {
  size_t sz = size();
  size_t wn = std::ceil((float)n / bit_width_);
  if (n == sz) return;
  if (n > sz) {
    mat_.resize(n);
    mem_alloc(mat_.begin() + sz, mat_.end(), wn);
  } else {
    mem_del(mat_.begin() + n, mat_.end());
    mat_.resize(n);
  }
  for(auto p = mat_.begin(); p != mat_.end(); ++p) (*p)->resize(wn);
}

inline template <class T> void BitArray::set(size_t i, size_t j) {
  div_t res = div(n, j);
  mat_[i]->operator[](res.quot) |= (1 << res.rem);
}

inline template <class T> void BitArray::reset(size_t i, size_t j) {
  div_t res = div(n, j);
  mat_[i]->operator[](res.quot) &= ~(1 << res.rem);
}

template <class T> bool BitArray::is_eauql_row(size_t i, size_t j) const {
  auto p  = mat_[i];
  auto ip = p.begin();
  auto jp = mat_[j].begin();
  while(ip != p.end()) {
    if(*ip++ != *jp++) return false;
  }
  return true;
}

inline template <class T>
std::ostream& operator<<(std::ostream& os, const BitMatrix<T>& mat) {
  mat.print(os);
  return os;
}

inline void delete_until_endline(std::ifstream& ifs) {
  std::string comment;
  std::getline(ifs, comment);
}

template <class T> size_t BitMatrix::get_size(std::ifstream& ifs) {
  while(!ifs.eof()) {
    switch(ifs.get()) {
      case 'e': return 0; // edgge data
      case 'c': // comment
        delete_until_endline(ifs);
        break;

      case 'p': // vertex data
        std::string com;
        size_t vertex_size;
        ifs >> com >> vertex_size;
        if(com != "edge") return 0;
        delete_until_endline(ifs);
        return vertex_size;
    }
  }
  return 0;
}

template <class T> void BitMatrix::set_edges(std::ifstream& ifs) {
  size_t v1, v2;
  while(!ifs.eof()) {
    if(ifs.get() == 'e') {
      ifs >> v1 >> v2;
      sset(v1 - 1, v2 - 1);
    }
    delete_until_endline(ifs);
  }
}

template <class T> void BitMatrix::load(const std::string& fn) {
  std::ifstream ifs(fn);
  if(!ifs.is_open()) {
    throw std::runtime_error("file is not exist: " + fn);
  }

  size_t n = get_size(ifs);
  if(0 == n) {
    throw std::runtime_error("some format error: " + fn);
  }

  resize(n);
  set_edges(ifs);
}


void RatMatrix::print(std::ostream& os) const {
  os << "matrix" << std::endl;
  size_t sz = size();
  for(size_t i = 0; i < sz; ++i) {
    for(size_t j = 0; j < sz; ++j) {
      std::cout << get(i,j) << ", ";
    }
    std::cout << std::endl;
  }
}



#endif

