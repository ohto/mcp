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
#include "../include/ExPoly.hpp"

void ExPoly::differential() {
  std::vector<Rat>& dt = data();
  size_t sz = size();
  switch(sz) {
    case 0: break;
    case 1:
      dt[0] = 0;
      break;

    default:
      for(size_t i = 1; i < sz; ++i) {
        dt[i-1] = dt[i] * i;
      }
      dt.pop_back();
      break;
  }
}


Rat ExPoly::operator()(const Rat& v) const {
  std::vector<Rat> const& dt = data();
  size_t sz = size();
  if(sz == 0) return 0;

  Rat d = v;
  Rat ret = dt[0];
  for(size_t i = 1; i < sz; ++i) {
    ret += dt[i] * d;
    d *= v;
  }
  return ret;
}

