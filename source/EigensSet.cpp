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
#include <array>
#include <stdexcept>
#include "../include/EigensSet.hpp"

bool EigensSet::exist_avobe(const Rat& val) const {
  for(auto p = eigens_set_p_.begin(); p != eigens_set_p_.end(); ++p) {
    if(p->eigens(val) > 0) return true;
  }
  return false;
}

size_t EigensSet::eigens(const Rat& val, const std::list<Eigens>& es) const {
  size_t sum = 0;
  for(auto p = es.begin(); p != es.end(); ++p) {
    sum += p->eigens(val);
  }
  return sum;
}


size_t EigensSet::floor_max_eigen() const {
  size_t min = 1;
  size_t max = max_ - 1;

  while(max - min > 1) {
    size_t mid = min + (max - min) / 2;
    (exist_avobe(mid)) ? min = mid : max = mid;
  }

std::cout << min << ", " << max << std::endl;

  Rat r = max;
std::cout << eigens(-r, eigens_set_m_) << std::endl;
std::cout << max_ << std::endl;

  return (eigens(-r, eigens_set_m_) != max_)? max + 1 : min;
}


EigensSet::EigensSet(const Frobenius& fro) {
  max_ = fro.size();
  if(max_ < 2) throw std::runtime_error("matrix size should be lager than 1");
  std::vector<Rat> coeff(max_ + 1);
  auto pcoeff = coeff.end();
  *--pcoeff = 1;

  size_t i = max_ - 1;
  size_t column = i;
  Rat factor = 1;
  *--pcoeff = - fro.get(i, column);

  while(i-- > 0) {
    Rat d = fro.get(i + 1, i);
    if(d == 0) {
      add(pcoeff, coeff.end());

      column = i;
      factor = 1;
      pcoeff = coeff.end();
      *--pcoeff = 1;
      *--pcoeff = - fro.get(i, column);

    } else {
      factor *= d;
      *--pcoeff = - fro.get(i, column) * factor;
    }
  }
  add(pcoeff, coeff.end());
}

