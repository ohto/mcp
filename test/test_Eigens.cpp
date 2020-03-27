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
#include "../include/Eigens.hpp"

int main() {
  // x^2 -3 x + 2
  std::list<Rat> coeff;
  coeff.push_back(2);
  coeff.push_back(-3);
  coeff.push_back(1);
  Eigens eigens(coeff.begin(), coeff.end(), 3);

  std::cout << eigens.eigens(0) << std::endl;
  std::cout << eigens.eigens(1) << std::endl;
  std::cout << eigens.eigens(2) << std::endl;
  return 0;
}

