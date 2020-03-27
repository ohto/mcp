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
#include <stdexcept>
#include "../include/RatMatrix.hpp"

void RatMatrix::resize(size_t n) {
  size_t sz = mat_.size();
  if (n == sz) return;
  if (n > sz) {
    mat_.resize(n);
    mem_alloc(mat_.begin() + sz, mat_.end(), n);
  } else {
    mem_del(mat_.begin() + n, mat_.end());
    mat_.resize(n);
  }
  for(auto p = mat_.begin(); p != mat_.end(); ++p) (*p)->resize(n);
}


inline void delete_until_endline(std::ifstream& ifs) {
  std::string comment;
  std::getline(ifs, comment);
}

size_t RatMatrix::get_size(std::ifstream& ifs) {
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


void RatMatrix::set_edges(std::ifstream& ifs) {
  size_t v1, v2;
  while(!ifs.eof()) {
    if(ifs.get() == 'e') {
      ifs >> v1 >> v2;
      set(v1 - 1, v2 - 1);
    }
    delete_until_endline(ifs);
  }
}


void RatMatrix::load(const std::string& fn, bool to_expand) {
  std::ifstream ifs(fn);
  if(!ifs.is_open()) {
    throw std::runtime_error("file is not exist: " + fn);
  }

  size_t n = get_size(ifs);
  if(0 == n) {
    throw std::runtime_error("some format error: " + fn);
  }

  if((expanded_ = to_expand)) {
    resize(n + 1);
    for(size_t i = 0; i < n; ++i) set(i, n);
 } else resize(n);

  set_edges(ifs);
}


void RatMatrix::print(std::ostream& os) const {
  os << "matrix";
  if(expanded_) os << "(expanded)";
  os << std::endl;

  size_t sz = size();
  for(size_t i = 0; i < sz; ++i) {
    for(size_t j = 0; j < sz; ++j) {
      std::cout << get(i,j) << ", ";
    }
    std::cout << std::endl;
  }
}

