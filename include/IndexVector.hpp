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
#ifndef INDEX_VECTOR_HPP
#define INDEX_VECTOR_HPP

#include <vector>
#include <iostream>

class IndexVector {
private:
  std::vector<size_t> index_;

  void init(size_t start);

public:
  IndexVector() {};
  IndexVector(size_t n) : index_(n) { init(0); }

  size_t size() const { return index_.size(); }
  size_t operator[](size_t i) const { return index_[i]; }
  void swap(size_t a, size_t b) { std::swap(index_[a], index_[b]); }
  void resize(size_t n);

  void print(std::ostream& os) const;
};


inline std::ostream& operator<<(std::ostream& os, const IndexVector& index) {
  index.print(os);
  return os;
}

#endif

