############################################
#
# This makefile will automatically build
# the Subjective Logic code.
#
# Recall the library is header-only, and
# thus all this builds is test code.
#
############################################


############################################
# Variables.

# Toolchain Variables.
CC = g++
COPT = -03
CPPFLAGS = $(COPT) -Wall -pedantic -I$(H_FLDR)
LNFLAGS = 

H_FLDR = headers
TEST_FLDR = tests
TEMP_FLDR = temp

# files involved with the project... 
# note: if we ever seperate prototypes from implementation, this will no longer work.
H_SOURCES = $(shell ls $(H_FLDR) | grep .*\.cpp)
H_OBJS = $(H_SOURCES:.cpp=.o)
TESTS = $(shell ls $(TEST_FLDR) | grep .*\.cpp)

# Source files for the main program.
SRCS = main.cpp

# The executable.
EXE = main

############################################
# DO NOT EDIT THESE RULES. THEY'RE VERY
# FRAGILE.

# Get all test cases.
TESTEXES = $(TESTS:.cpp=)

# Targets.

all: headers tests $(EXE) 

$(EXE): $(SRCS) 
	$(CC) $(CPPFLAGS) $(H_OBJS:%=$(TEMP_FLDR)/%) $(SRCS) -o $(EXE) $(LNFLAGS)

headers: $(H_OBJS)

# for precompiling headers.
$(H_OBJS): %.o: $(H_FLDR)/%.cpp
	$(CC) -c -o $(TEMP_FLDR)/$@ $(H_FLDR)/$(@:.o=.cpp)

tests: $(TESTEXES)

$(TESTEXES): %: $(TEST_FLDR)/%.cpp 
	$(CC) $(CPPFLAGS) $(H_OBJS:%=$(TEMP_FLDR)/%) $< -o $@ $(LNFLAGS)

%.d: $(%:$(TEMP_FLDR)=).cpp
	$(SHELL) -ec '$(CXX) $(CXXFLAGS) -MM -MT "$<" $< > $@'
%.d_objs: $(%:$(TEMP_FLDR)=).cpp
	$(SHELL) -ec '$(CXX) $(CXXFLAGS) -MM -MT "$<" $< | sed s/\.hpp/\.o/g  > $@'

ifeq (0, $(words $(findstring $(MAKECMDGOALS), $(NODEPS))))
# -include $(TEST_FLDR)/$(TESTEXES:=.d)

# -include $(TEST_FLDR)/$(SRCS:=.d)

# -include $(TEST_FLDR)/$(TESTEXES:=.d_objs)
tester:
	@echo "in tester in if stmt"
# -include $(TEST_FLDR)/$(SRCS:=.d_objs)
endif

debug: CPPFLAGS += -DDEBUG -g
debug: all

love:
	@echo Not War

clean:
	rm -f $(EXE) $(TESTEXES) $(TEMP_FLDR)/$(H_OBJS)
