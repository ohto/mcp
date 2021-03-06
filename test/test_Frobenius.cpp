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
#include "../include/Frobenius.hpp"
#include "../include/EigensSet.hpp"

int main() {
  Frobenius fro;
  fro.resize(4);
  fro.get(0,2) = 1;
  fro.get(2,0) = 7;
  fro.get(2,1) = 1;
  fro.get(2,3) = 1;
  fro.get(3,0) = 5;
  std::cout << "input: " << fro << std::endl;

  fro.trans();
  std::cout << "transed: " << fro << std::endl;

  return 0;
}

