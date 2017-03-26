GTEST_DIR = ../../googletest

USER_DIR = ..

TESTS = TableCell_spec

all : $(TESTS)

clean :
	rm -f $(TESTS) gtest.a gtest_main.a *.o *.gc* *.info -R coverage

GTEST_INCLUDE = $(GTEST_DIR)/include

CPPFLAGS += -isystem $(GTEST_INCLUDE)

CXXFLAGS += -g -std=c++11 -Wall -Wextra -pthread

COVER = --coverage

GTEST_HEADERS = $(GTEST_INCLUDE)/gtest/*.h $(GTEST_INCLUDE)/gtest/internal/*.h

GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

COMPILER = $(CXX) $(CPPFLAGS) $(CXXFLAGS)

COMPILE_GTEST = $(COMPILER) -I$(GTEST_DIR) -c $(GTEST_DIR)/src

AR_GTEST = $(AR) $(ARFLAGS) $@ $^

LCOV_CURR_DIR = lcov --base-directory . --directory .

COMPILE_COMPONENT = $(COMPILER) -c $(USER_DIR)

ownDeps = $(USER_DIR)/$(1).h $(USER_DIR)/$(1).cc

unitDeps = $(ownDeps) $(GTEST_HEADERS)

objDeps = $(1).o $(1)_spec.o

define spec
$(1).o : $(call unitDeps,$(1))
	$(COMPILE_COMPONENT)/$(1).cc $(COVER)

$(1)_spec.o : $(call unitDeps,$(1))
	$(COMPILE_COMPONENT)/$(1)_spec.cc
endef

define endl


endef

gtest-all.o : $(GTEST_SRCS_)
	$(COMPILE_GTEST)/gtest-all.cc

gtest_main.o : $(GTEST_SRCS_)
	$(COMPILE_GTEST)/gtest_main.cc

gtest.a : gtest-all.o
	$(AR_GTEST)

gtest_main.a : gtest-all.o gtest_main.o
	$(AR_GTEST)

$(eval $(call spec,TableCell))

TableCell_spec : $(call objDeps,TableCell) gtest_main.a
	$(COMPILER) $(COVER) -lpthread $^ -o $@

test :
	$(MAKE) clean
	$(MAKE)
	$(LCOV_CURR_DIR) --zerocounters
	$(foreach test,$(TESTS),./$(test) --gtest_color=yes$(endl))
	$(LCOV_CURR_DIR) --capture -o test.info
	lcov --remove test.info "/*/include/*" -o spec.info
	genhtml spec.info --highlight --legend --demangle-cpp -o coverage
