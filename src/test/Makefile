GTEST_DIR = ../../googletest

USER_DIR = ..

TESTS = TableCell_spec ConstString_spec FixedSizeString_spec ValidationException_spec numberTextUtils_spec IntegerParser_spec

all : $(TESTS)

clean :
	rm -f $(TESTS) gtest.a gtest_main.a *.o *.gc* *.info -R coverage

GTEST_INCLUDE = $(GTEST_DIR)/include

CPPFLAGS += -isystem $(GTEST_INCLUDE)

CXXFLAGS += -g -std=c++14 -Wall -Wextra -Wpedantic -pthread -O -O0

COVER = --coverage

GTEST_HEADERS = $(GTEST_INCLUDE)/gtest/*.h $(GTEST_INCLUDE)/gtest/internal/*.h

GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

COMPILER = $(CXX) $(CPPFLAGS) $(CXXFLAGS)

COMPILE_GTEST = $(COMPILER) -I$(GTEST_DIR) -c $(GTEST_DIR)/src

AR_GTEST = $(AR) $(ARFLAGS) $@ $^

LCOV_CURR_DIR = lcov --base-directory . --directory .

COMPILE_COMPONENT = $(COMPILER) -c $(USER_DIR)

ownDeps = $(USER_DIR)/$(1)/$(1).h $(USER_DIR)/$(1)/$(1).cc

specDeps = $(GTEST_HEADERS) $(USER_DIR)/It/It.h

unitDeps = $(ownDeps) $(specDeps)

objDeps = $(1).o $(1)_spec.o

dirDeps = $(USER_DIR)/$(1)/$(2)/$(2).h $(USER_DIR)/$(1)/$(2)/$(2).cc $(specDeps)

define spec
$(1).o : $(call unitDeps,$(1)) $(2)
	$(COMPILE_COMPONENT)/$(1)/$(1).cc $(COVER)

$(1)_spec.o : $(call unitDeps,$(1)) $(2)
	$(COMPILE_COMPONENT)/$(1)/$(1)_spec.cc

$(1)_spec : $(call objDeps,$(1)) gtest_main.a It.o $(2)
	$(COMPILER) $(COVER) -lpthread $$^ -o $$@
endef

define specInDir
$(2).o : $(call dirDeps,$(1),$(2)) $(3)
	$(COMPILE_COMPONENT)/$(1)/$(2)/$(2).cc $(COVER)

$(2)_spec.o : $(call dirDeps,$(1),$(2)) $(3)
	$(COMPILE_COMPONENT)/$(1)/$(2)/$(2)_spec.cc

$(2)_spec : $(call objDeps,$(2)) gtest_main.a It.o $(3)
	$(COMPILER) $(COVER) -lpthread $$^ -o $$@
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

It.o: $(call ownDeps,It)
	$(COMPILE_COMPONENT)/It/It.cc

BasicString.o : $(USER_DIR)/String/ImmutableString.h $(USER_DIR)/String/BasicString/BasicString.h $(USER_DIR)/String/BasicString/BasicString.cc $(specDeps)
	$(COMPILE_COMPONENT)/String/BasicString/BasicString.cc $(COVER)

ConstString_spec.o : $(USER_DIR)/String/ImmutableString.h $(USER_DIR)/String/BasicString/BasicString.h $(USER_DIR)/String/BasicString/BasicString.cc $(specDeps)
	$(COMPILE_COMPONENT)/String/ConstString/ConstString_spec.cc

ConstString_spec : $(USER_DIR)/String/ConstString/ConstString.h gtest_main.a It.o BasicString.o ConstString_spec.o
	$(COMPILER) $(COVER) -lpthread $^ -o $@

$(eval $(call specInDir,String,FixedSizeString,BasicString.o))

$(eval $(call spec,TableCell))

$(eval $(call specInDir,Parser,TypeParser,BasicString.o))

$(eval $(call specInDir,Parser,IntegerParser,BasicString.o TypeParser.o numberTextUtils.o ValidationException.o))

$(eval $(call specInDir,Parser,ValidationException))

$(eval $(call specInDir,utils,numberTextUtils))	

test :
	$(MAKE) clean
	$(MAKE)
	$(LCOV_CURR_DIR) --zerocounters
	$(foreach test,$(TESTS),./$(test) --gtest_color=yes$(endl))
	$(LCOV_CURR_DIR) --capture -o test.info
	lcov --remove test.info "/*/include/*" -o spec.info
	genhtml spec.info --highlight --legend --demangle-cpp -o coverage
