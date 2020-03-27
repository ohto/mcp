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
#include "../include/Frobenius.hpp"


size_t Frobenius::find_non_zero_row(size_t i) const {
  for(size_t k = i; k < size(); ++k) {
    if(get(k, i-1) != 0) return k;
  }
  return 0; // if not exist
}

void Frobenius::trans() {
  for(size_t i = 1; i < size(); ++i) {
    const size_t k = find_non_zero_row(i);
    if(k == 0) continue;
    if(k != i) index_.swap(k, i);
    trans(i);
  }
}


void Frobenius::trans(size_t i) {
  const Rat& pivot = get(i, i-1);
  const size_t sz = size();
  size_t j, k;

  for(j = 0; j < sz; ++j) {
    if(i == j) {
      right_factor[j] = 1;
      left_factor[j]  = 0;
    } else {
      const Rat& d = get(j, i-1);
      if(d == 0) right_factor[j] = left_factor[j] = 0;
      else {
        right_factor[j] = d / pivot;
        left_factor[j]  = - right_factor[j];
      }
    }
  }

  // apply right factor
  for(j = 0; j < sz; ++j) {
    Rat r = 0;
    for(k = 0; k < sz; ++k) {
      r += get(j, k) * right_factor[k];
    }
    get(j, i) = r;
  }

  // apply left factor
  for(j = 0; j < sz; ++j) {
    for(k = 0; k < sz; ++k) {
      tmp_column->operator[](index_[k]) = get(k,j) + left_factor[k] * get(i,j);
    }
    std::swap(tmp_column, mat_[index_[j]]);
  }
}


void Frobenius::print(std::ostream& os) const {
  os << "frobenius matrix";
  if(is_expanded()) os << "(expanded)";
  os << std::endl;

  size_t sz = size();
  for(size_t i = 0; i < sz; ++i) {
    for(size_t j = 0; j < sz; ++j) {
      std::cout << get(i,j) << ", ";
    }
    std::cout << std::endl;
  }
}


/*
 * methods for debug
 */
void Frobenius::_debug_show_vector(const RatColumn& vec) {
  for(size_t i = 0; i < vec.size(); ++i) {
    std::cout << vec[i] << ", ";
  }
  std::cout << std::endl;
}

void Frobenius::_debug_show_vector() {
  for(size_t i = 0; i < tmp_column->size(); ++i) {
    std::cout << tmp_column->operator[](index_[i]) << ", ";
  }
  std::cout << std::endl;
}

