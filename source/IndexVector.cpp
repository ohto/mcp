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
#include "../include/IndexVector.hpp"

void IndexVector::init(size_t i) {
  auto p = index_.begin() + i;
  while(p != index_.end()) *p++ = i++;
}

void IndexVector::resize(size_t n) {
  size_t sz = index_.size();
  if(sz == n) return;
  index_.resize(n);
  if(sz < n) init(sz);
}

void IndexVector::print(std::ostream& os) const {
  for(size_t i = 0; i < index_.size(); ++i) {
    std::cout << index_[i] << ", ";
  }
  std::cout << std::endl;
}

