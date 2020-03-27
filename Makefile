#
# Licensed to the Apache Software Foundation (ASF) under one
# or more contributor license agreements.  See the NOTICE file
# distributed with this work for additional information
# regarding copyright ownership.  The ASF licenses this file
# to you under the Apache License, Version 2.0 (the
# "License"); you may not use this file except in compliance
# with the License.  You may obtain a copy of the License at
# <p/>
# http://www.apache.org/licenses/LICENSE-2.0
# <p/>
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

BUILDDIR = ./build
OBJDIR = $(BUILDDIR)/obj
SRCDIR = ./source
INCDIRS = ./include
LIBDIRS = #-L

## Target name
TARGET = $(BUILDDIR)/mcp_size

## Compiler options
CC = gcc
CFLAGS = -O2 -Wall
CXX = g++
CXXFLAGS = -O3 -Wall -std=c++17 -pipe
#CXXFLAGS = -O3 -Wall -std=c++17
LDFLAGS =

SRCS := $(shell find $(SRCDIR) -name *.cpp -or -name *.c -or -name *.s)
OBJS := $(SRCS:%=$(OBJDIR)/%.o)
DEPS := $(OBJS:.o=.d)
LIBS = #-lboost_system -lboost_thread

INCLUDE := $(shell find $(INCDIRS) -type d)
INCLUDE := $(addprefix -I,$(INCLUDE))

CPPFLAGS := $(INCLUDE) -MMD -MP
LDFLAGS += $(LIBDIRS) $(LIBS)

# Target
default:
	make all

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS)

# assembly
$(OBJDIR)/%.s.o: %.s
	$(MKDIR_P) $(dir $@)
	$(AS) $(ASFLAGS) -c $< -o $@

# c source
$(OBJDIR)/%.c.o: %.c
	$(MKDIR_P) $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# c++ source
$(OBJDIR)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@
	
.PHONY: all clean rebuild

clean:
	$(RM) -r $(BUILDDIR)

rebuild:
	make clean && make

-include $(DEPS)

MKDIR_P = mkdir -p

