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
#include "../include/ExPoly.hpp"

int main() {
  boost::array<mp_int, 4> const d3a = {{10, -6, -4, 3}};
  ExPoly poly(d3a.begin(), d3a.end());

  std::cout << poly << std::endl;
  std::cout << poly(2) << std::endl;
  std::cout << poly(-2) << std::endl;

  poly.differential();
  std::cout << poly << std::endl;

  return 0;
}

