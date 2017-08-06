DEPS_DIR = ../../dependencies

GTEST_DIR = $(DEPS_DIR)/googletest

FPCONV_DIR = $(DEPS_DIR)/fpconv/src

USER_DIR = ..

TESTS = TableParser_spec

#TESTS = InputBuffer_spec DynamicString_spec DynamicArray_spec IndexedDynamicArray_spec\
ConstString_spec FixedSizeString_spec ValidationException_spec Number_spec NumberParser_spec\
StringParser_spec NumberCell_spec StringNumberCell_spec TableCell_spec NumberCell_spec StringNumberCell_spec\
StringCell_spec EmptyCell_spec ErrorCell_spec CircRefCell_spec DivByZeroCell_spec\
RootOfNegNumCell_spec ZeroRaisedOnZeroCell_spec Row_spec Table_spec TableCellParser_spec Reader_spec

.PHONY: all clean test chrome-open-coverage

all: $(TESTS)

clean:
	rm -f $(TESTS) gtest.a gtest_main.a *.o *.gc* *.info -R coverage

GTEST_INCLUDE = $(GTEST_DIR)/include

CPPFLAGS += -isystem $(GTEST_INCLUDE)

CXXBASEFLAGS = -g -std=c++14 -Wall -Wextra -Wpedantic -O -O0

CXXFLAGS += $(CXXBASEFLAGS) -pthread

COVER = --coverage

GTEST_HEADERS = $(GTEST_INCLUDE)/gtest/*.h $(GTEST_INCLUDE)/gtest/internal/*.h

GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

COMPILER = $(CXX) $(CPPFLAGS) $(CXXFLAGS)

COMPILE_GTEST = $(COMPILER) -I$(GTEST_DIR) -c $(GTEST_DIR)/src

AR_GTEST = $(AR) $(ARFLAGS) $@ $^

LCOV_CURR_DIR = lcov --base-directory . --directory .

COMPILE_COMPONENT = $(COMPILER) -c -D __TEST__ $(USER_DIR)

ownDeps = $(USER_DIR)/$(1)/$(1).h $(USER_DIR)/$(1)/$(1).cc $(USER_DIR)/$(1)/$(1)_spec.cc

specDeps = $(GTEST_HEADERS) $(USER_DIR)/It/It.h

unitDeps = $(ownDeps) $(specDeps)

objDeps = $(1).o $(1)_spec.o

dirDeps = $(USER_DIR)/$(1)/$(2)/$(2).h $(USER_DIR)/$(1)/$(2)/$(2).cc $(USER_DIR)/$(1)/$(2)/$(2)_spec.cc

define spec
$(1).o: $(call unitDeps,$(1)) $(2)
	$(COMPILE_COMPONENT)/$(1)/$(1).cc $(COVER)

$(1)_spec.o: $(call unitDeps,$(1)) $(2)
	$(COMPILE_COMPONENT)/$(1)/$(1)_spec.cc

$(1)_spec: $(call objDeps,$(1)) gtest_main.a It.o $(2)
	$(COMPILER) $(COVER) -lpthread $$^ -o $$@
endef

define specInDir
$(2).o: $(call dirDeps,$(1),$(2)) $(3) $(4)
	$(COMPILE_COMPONENT)/$(1)/$(2)/$(2).cc $(COVER)

$(2)_spec.o: $(call dirDeps,$(1),$(2)) $(specDeps) $(3) $(4)
	$(COMPILE_COMPONENT)/$(1)/$(2)/$(2)_spec.cc

$(2)_spec: $(call objDeps,$(2)) gtest_main.a It.o $(3) $(4)
	$(COMPILER) $(COVER) -lpthread $$^ -o $$@
endef

define templateInDir
$(2)_eti.o: $(USER_DIR)/$(1)/$(2)/$(2).htd $(USER_DIR)/$(1)/$(2)/$(2).tci $(USER_DIR)/$(1)/$(2)/$(2)_eti.cc $(specDeps) $(3)
	$(COMPILE_COMPONENT)/$(1)/$(2)/$(2)_eti.cc $(COVER)

$(2)_spec.o: $(USER_DIR)/$(1)/$(2)/$(2)_spec.cc $(specDeps) $(3)
	$(COMPILE_COMPONENT)/$(1)/$(2)/$(2)_spec.cc

$(2)_spec: $(2)_eti.o $(2)_spec.o gtest_main.a It.o $(3)
	$(COMPILER) $(COVER) -lpthread $$^ -o $$@
endef

define endl


endef

gtest-all.o: $(GTEST_SRCS_)
	$(COMPILE_GTEST)/gtest-all.cc

gtest_main.o: $(GTEST_SRCS_)
	$(COMPILE_GTEST)/gtest_main.cc

gtest.a: gtest-all.o
	$(AR_GTEST)

gtest_main.a: gtest-all.o gtest_main.o
	$(AR_GTEST)

fpconv.o: $(FPCONV_DIR)/powers.h $(FPCONV_DIR)/fpconv.h $(FPCONV_DIR)/fpconv.c
	$(CXX) $(CXXBASEFLAGS) -c $(FPCONV_DIR)/fpconv.c

It.o: $(USER_DIR)/It/It.h $(USER_DIR)/It/It.cc
	$(COMPILE_COMPONENT)/It/It.cc

BasicString.o: $(USER_DIR)/String/ImmutableString.h $(USER_DIR)/String/BasicString/BasicString.h $(USER_DIR)/String/BasicString/BasicString.cc $(specDeps)
	$(COMPILE_COMPONENT)/String/BasicString/BasicString.cc $(COVER)

$(eval $(call templateInDir,Container,DynamicArray))

$(eval $(call templateInDir,Container,IndexedDynamicArray))

$(eval $(call spec,Number))

$(eval $(call specInDir,String,ConstString,BasicString.o))

$(eval $(call specInDir,String,FixedSizeString,BasicString.o ConstString.o))

$(eval $(call specInDir,String,DynamicString,BasicString.o ConstString.o))

$(eval $(call specInDir,IO,InputBuffer,BasicString.o ConstString.o))

$(eval $(call specInDir,Parser,TypeParser,BasicString.o ValidationException.o))

$(eval $(call specInDir,Parser,NumberParser,BasicString.o ConstString.o TypeParser.o ValidationException.o Number.o))

$(eval $(call specInDir,Parser,StringParser,BasicString.o ConstString.o FixedSizeString.o TypeParser.o ValidationException.o))

$(eval $(call specInDir,Parser,ValidationException))

$(eval $(call spec,TableCell,Number.o))

$(eval $(call specInDir,TableCell,EmptyCell,TableCell.o Number.o))

$(eval $(call specInDir,TableCell,NumberCell,TableCell.o Number.o fpconv.o EmptyCell.o))

$(eval $(call specInDir,TableCell,StringNumberCell,TableCell.o NumberCell.o Number.o fpconv.o EmptyCell.o))

$(eval $(call specInDir,TableCell,StringCell,TableCell.o Number.o BasicString.o ConstString.o FixedSizeString.o EmptyCell.o))	

$(eval $(call specInDir,TableCell,ErrorCell,TableCell.o Number.o BasicString.o ConstString.o EmptyCell.o))

$(eval $(call specInDir,TableCell,CircRefCell,TableCell.o Number.o BasicString.o ConstString.o ErrorCell.o EmptyCell.o))

$(eval $(call specInDir,TableCell,DivByZeroCell,TableCell.o Number.o BasicString.o ConstString.o ErrorCell.o EmptyCell.o))

$(eval $(call specInDir,TableCell,RootOfNegNumCell,TableCell.o Number.o BasicString.o ConstString.o ErrorCell.o EmptyCell.o))

$(eval $(call specInDir,TableCell,ZeroRaisedOnZeroCell,TableCell.o Number.o BasicString.o ConstString.o ErrorCell.o EmptyCell.o))

$(eval $(call specInDir,Table,Row,TableCell.o Number.o BasicString.o ConstString.o EmptyCell.o NumberCell.o fpconv.o StringNumberCell.o StringCell.o BasicString.o ConstString.o ErrorCell.o FixedSizeString.o CircRefCell.o DivByZeroCell.o RootOfNegNumCell.o ZeroRaisedOnZeroCell.o))

$(eval $(call spec,Table,TableCell.o Number.o BasicString.o ConstString.o EmptyCell.o NumberCell.o fpconv.o StringNumberCell.o StringCell.o BasicString.o ConstString.o ErrorCell.o FixedSizeString.o CircRefCell.o DivByZeroCell.o RootOfNegNumCell.o ZeroRaisedOnZeroCell.o Row.o))

$(eval $(call specInDir,Parser,TableCellParser,Number.o BasicString.o ConstString.o TableCell.o EmptyCell.o NumberCell.o fpconv.o StringNumberCell.o StringCell.o ErrorCell.o FixedSizeString.o CircRefCell.o DivByZeroCell.o RootOfNegNumCell.o ZeroRaisedOnZeroCell.o TypeParser.o NumberParser.o StringParser.o ValidationException.o))

$(eval $(call specInDir,IO,InputStream))

$(eval $(call specInDir,IO,Reader,InputStream.o InputBuffer.o BasicString.o ConstString.o))

$(eval $(call specInDir,Parser,TableParser,TableCell.o Number.o BasicString.o ConstString.o EmptyCell.o NumberCell.o fpconv.o StringNumberCell.o StringCell.o BasicString.o ConstString.o ErrorCell.o FixedSizeString.o CircRefCell.o DivByZeroCell.o RootOfNegNumCell.o ZeroRaisedOnZeroCell.o Row.o Table.o TypeParser.o NumberParser.o StringParser.o ValidationException.o TableCellParser.o Reader.o InputStream.o InputBuffer.o))

test: all
	$(LCOV_CURR_DIR) --zerocounters
	$(foreach test,$(TESTS),./$(test) --gtest_color=yes$(endl))
	$(LCOV_CURR_DIR) --capture -o test.info
	lcov --remove test.info "/*/include/*" -o spec.info
	genhtml spec.info --highlight --legend --demangle-cpp -o coverage

chrome-open-coverage:
	google-chrome coverage/index.html