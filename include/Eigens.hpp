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
#ifndef EIGENS_HPP
#define EIGENS_HPP
#include "Strum.hpp"

class Eigens : private Strum {
private:
  size_t max_;

public:
  Eigens() : Strum() {}
  template <class I> Eigens(const I cs, const I ce, size_t max);
  template <class I> void set(const I cs, const I ce, size_t max);

  size_t eigens(const Rat& v) const { return alpha(v) - max_; }
};


template <class I> Eigens::Eigens(const I cs, const I ce, size_t max)
: Strum(cs, ce) {
  max_ = alpha(max);
}

template <class I> void Eigens::set(const I cs, const I ce, size_t max) {
  Strum::set(cs, ce);
}

#endif

