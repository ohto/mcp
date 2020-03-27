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
#ifndef STRUM_HPP
#define STRUM_HPP

#include <list>
#include "ExPoly.hpp"

class Strum {
private:
  std::list<ExPoly> polys_;
  template <class I> void init(const I coeff_begin, const I coeff_end);


public:
  Strum() {}
  template <class I> Strum(const I cb, const I ce) { init(cb, ce); }
  template <class I> void set(const I cb, const I ce);
  size_t alpha(const Rat& val) const;
};


template <class I> void Strum::set(const I cb, const I ce) {
  polys_.clear(); init(cb, ce);
}

template <class I> void Strum::init(const I coeff_begin, const I coeff_end) {
  if(coeff_begin == coeff_end) return;
  ExPoly poly(coeff_begin, coeff_end);
  polys_.push_back(poly);

  if(poly.size() > 1) {
    auto p0 = &poly;
    polys_.push_back(poly);
    auto p1 = &(polys_.back());
    p1->differential();

    while(p1->size() > 1) {
      polys_.push_back(*p0);
      p0 = p1;
      p1 = &(polys_.back());
      *p1 %= *p0;
      *p1 *= -1;
    }
  }
}

#endif

