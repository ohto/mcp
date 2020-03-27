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
#include <iostream>
#include "../include/Strum.hpp"

int main() {
  // x^2 -3 x + 2
  std::list<Rat> coeff;
  coeff.push_back(2);
  coeff.push_back(-3);
  coeff.push_back(1);
  Strum strum(coeff.begin(), coeff.end());

  size_t max = strum.alpha(3);
  std::cout << max << std::endl;
  std::cout << strum.alpha(0) << std::endl;
  std::cout << strum.alpha(1) << std::endl;
  std::cout << strum.alpha(2) << std::endl;
  return 0;
}

