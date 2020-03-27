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
#ifndef EIGENS_SET_HPP
#define EIGENS_SET_HPP

#include <list>
#include "Eigens.hpp"
#include "Frobenius.hpp"

class EigensSet {
private:
  size_t max_;
  std::list<Eigens> eigens_set_p_;
  std::list<Eigens> eigens_set_m_;

  bool exist_avobe(const Rat& val) const;
  size_t eigens(const Rat& val, const std::list<Eigens>& es) const;
  template <class I> void add(const I cb, const I ce);

public:
  EigensSet() {}
  EigensSet(const Frobenius& fro);
  size_t floor_max_eigen() const;
};


template <class I> void EigensSet::add(const I cb, const I ce) {
  Eigens eigens(cb, ce, max_);
  eigens_set_p_.push_back(eigens);

  int factor = -1;
  for(auto p = cb + 1; p != ce; ++p) {
    *p *= factor;
    factor *= -1;
  }

  eigens.set(cb, ce, max_);
  eigens_set_m_.push_back(eigens);
}

#endif

