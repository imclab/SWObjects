# $Id: Makefile,v 1.56 2009-01-16 11:29:21 eric Exp $
# SWObjects build rules -- you should edit the CONFIG file

# recipies:
#   normal build:
#     make SPARQLfed
#   force the use of the tracing facilities (and redirect to stdout):
#     make -W tests/test_HealthCare1.cpp test
#   have valgrind start a debugger (works as M-x gdb invocation command):
#     valgrind --db-attach=yes --leak-check=yes tests/execute_HealthCare1 tests/query_HealthCare1.rq tests/ruleMap_HealthCare1.rq
#   same, if you aren't working in gdb:
#     make valgrind
#   debugging in emacs:
#     gdb --annotate=3 sample_RuleMap1    (set args query_HealthCare1.rq ruleMap_HealthCare1.rq)

# Edit CONFIG to set your build preferences.
-include CONFIG

FLEX:=flex
YACC:=bison
TEE:=tee
SED:=sed
OPTIM:=-g -O0
PYTHON_HOME:=/usr/include/python2.6
PHP_HOME:=/usr/include/php5 -I/usr/include/php5/Zend -I/usr/include/php5/TSRM -I/usr/include/php5/main
LUA_HOME:=/usr/include/lua5.1
PERL_HOME:=/usr/lib/perl/5.10.1
JAVA_HOME:=/usr/lib/jvm/java-6-openjdk
# GNU Make 3.81 seems to have a built-in echo which doesn't swallow "-e"
#ECHO:=`which echo`
#OSX: ECHO:= /bin/echo
ECHO ?= echo
#LIBS
DEBUG:=-g -O0
OPT=-fPIC
DEFS += -DYYTEXT_POINTER=1
WARN:=-W -Wall -Wextra -Wnon-virtual-dtor -ansi -std=c++98
# --pedantic
# pedantic works on GNU if you uncomment the isatty (int ) throw() patch below

# Apache module stuff
APXS ?= apxs2
CODEA ?= ../codea
CCL ?= ../ccl
APR ?= /usr/include/apr-1.0

INCLUDES += -I${PWD} -I${PWD}/lib -I${PWD}/docs  # . (for config.h) and ./lib (for the rest)
I2=$(subst /, ,$(BISONOBJ:.o=))
I3=$(sort $(I2))
INCLUDES += $(I3:%=-I${PWD}/%)

PWD ?= $(shell pwd -P)


ifeq ($(XML_PARSER), LIBXML2)
  CONFIG_DEFS+= \\\#define XML_PARSER	SWOb_LIBXML2 "\n"
  INCLUDES += -I/usr/include/libxml2
  XML_PARSER_LIB?= -lxml2
else ifeq ($(XML_PARSER), EXPAT1)
  CONFIG_DEFS+= \\\#define XML_PARSER	SWOb_EXPAT1 "\n"
  XML_PARSER_LIB?= -lexpat
else ifeq ($(XML_PARSER), MSXML3)
  CONFIG_DEFS+= \\\#define XML_PARSER	SWOb_MSXML3 "\n"
  XML_PARSER_LIB?= -lmsxml
else
  ifneq ($(XML_PARSER), )
    $(warning $(XML_PARSER) may not be supported)
  endif
  CONFIG_DEFS+= \\\#define XML_PARSER	SWOb_DISABLED "\n"
endif


ifeq ($(CONSOLE_ENCODING), UTF8)
  CONFIG_DEFS+= \\\#define CONSOLE_ENCODING	SWOb_UTF8 "\n"
else
  ifneq ($(CONSOLE_ENCODING), )
    $(warning CONSOLE_ENCODING= $(CONSOLE_ENCODING) may not be supported)
  endif
  CONFIG_DEFS+= \\\#define CONSOLE_ENCODING	SWOb_DISABLED "\n"
endif


ifeq ($(REGEX), BOOST)
  CONFIG_DEFS+= \\\#define REGEX_LIB	SWOb_BOOST "\n"
  REGEX_LIB?= -lboost_regex$(BOOST_VERSION) -lpthread
else
  ifneq ($(REGEX), )
    $(warning $(REGEX_LIB) may not be supported)
  endif
  CONFIG_DEFS+= \\\#define REGEX_LIB	SWOb_DISABLED "\n"
endif


ifeq ($(HTTP_CLIENT), ASIO)
  CONFIG_DEFS+= \\\#define HTTP_CLIENT	SWOb_ASIO "\n"
  HTTP_CLIENT_LIB?= -lboost_system$(BOOST_VERSION)
else ifeq ($(HTTP_CLIENT), DLIB)
  CONFIG_DEFS+= \\\#define HTTP_CLIENT	SWOb_DLIB "\n"
  $(warning DLIB HTTP client code not yet written)
else
  ifneq ($(HTTP_CLIENT), )
    $(warning $(HTTP_CLIENT) may not be supported)
  endif
  CONFIG_DEFS+= \\\#define HTTP_CLIENT	SWOb_DISABLED "\n"
endif


ifeq ($(HTTP_SERVER), ASIO)
  CONFIG_DEFS+= \\\#define HTTP_SERVER	SWOb_ASIO "\n"
  HTTP_SERVER_LIB?= -lboost_system$(BOOST_VERSION) -lboost_thread$(BOOST_VERSION) -lpthread
else ifeq ($(HTTP_SERVER), DLIB)
  CONFIG_DEFS+= \\\#define HTTP_SERVER	SWOb_DLIB "\n"
  DLIB= -DDLIB_TIGHT_LOOP=1 -DNO_MAKEFILE
else
  ifneq ($(HTTP_SERVER), )
    $(warning $(HTTP_SERVER) may not be supported)
  endif
  CONFIG_DEFS+= \\\#define HTTP_SERVER	SWOb_DISABLED "\n"
endif


ifeq ($(SQL_CLIENT), MYSQL)
  CONFIG_DEFS+= \\\#define SQL_CLIENT	SWOb_MYSQL "\n"
  SQL_CLIENT_LIB?= -lmysqlclient -lz
else
  ifneq ($(SQL_CLIENT), )
    $(warning $(SQL_CLIENT) may not be supported)
  endif
  CONFIG_DEFS+= \\\#define SQL_CLIENT	SWOb_DISABLED "\n"
endif


TEST_LIB?= -lboost_unit_test_framework$(BOOST_VERSION)


ifeq ($(LINK), DYNAMIC)
  CONFIG_DEFS+= \\\#define BOOST_ALL_DYN_LINK "\\n"
  STATICITY=
else
  STATICITY= -static
endif


.PHONY: all dep lib test
all:   lib test


config.h: CONFIG
	$(ECHO) "/* Generated from CONFIG.\n" \
	"* In order to keep your link directives appropriate for the features enabled\n" \
	"* by defines in this header, you should edit CONFIG and then \`make config.h\`.\n" \
	"*/\n" \
	"#define SWOb_DISABLED		135\n" \
	"/* XML Parsers: */\n" \
	"#define SWOb_LIBXML2		137\n" \
	"#define SWOb_EXPAT1		138\n" \
	"#define SWOb_MSXML3		139\n" \
	"/* Character Encodings: */\n" \
	"#define SWOb_UTF8		143\n" \
	"/* Regexp Libs: */\n" \
	"#define SWOb_BOOST		144\n" \
	"/* HTTP Libs: */\n" \
	"#define SWOb_ASIO		145\n" \
	"#define SWOb_DLIB		146\n" \
	"/* SQL Libs: */\n" \
	"#define SWOb_MYSQL		148\n" \
	"\n" $(CONFIG_DEFS) "\n" > config.h
	@$(ECHO) config.h updated.

#the gcc commands to make deps used in .d rules
#if -M[M]D is also in the build-clause without -E it update .d's as needed
TOONOISEY=-ansi
#for macports

# fussiness directives removed from CFLAGS:
#   -std=c++0x -- can't count on 0x on all platforms
#   -pedantic-errors -- breaks on OSX, aborts on #pragma
CFLAGS += $(DEFS) $(OPT) $(DEBUG) $(WARN) $(INCLUDES) -pipe -Wno-empty-body -Wno-missing-field-initializers -Wwrite-strings -Wno-deprecated -Wno-unused -Wno-non-virtual-dtor -Wno-variadic-macros -ftemplate-depth-128 -fno-merge-constants
CXXFLAGS += $(CFLAGS)

### absolutely neccessry for c++ linking ###
LD = $(CXX)
LDFLAGS += $(STATICITY) $(LIBINC) $(REGEX_LIB) $(HTTP_CLIENT_LIB) $(XML_PARSER_LIB) $(SQL_CLIENT_LIB)
LDAPPFLAGS += $(LDFLAGS) -lboost_program_options$(BOOST_VERSION) -lboost_filesystem$(BOOST_VERSION)
VER=0.1

#some progressive macports
#CC=llvm-gcc
#CXX=llvm-g++
#LLVMCFLAGS = ` llvm-config --cflags` -O4
#LLVMCXXFLAGS = ` llvm-config --cxxflags` -O4
#LLVMLDFLAGS = ` llvm-config --ldflags --libs `
#LLVMLIBS= ` llvm-config --libs`
# ... you get the idea...
CFLAGS	+= $(LLVMCFLAGS)
LIBINC	+= $(LIBS) -L$(PWD)/lib

### dirt simple generic static module ###
BISONOBJ :=  $(subst .ypp,.o,$(wildcard lib/*/*.ypp)) 
BISONH :=  $(subst .ypp,.hpp,$(wildcard lib/*/*.ypp)) 
FLEXOBJ  :=  $(subst .lpp,.o,$(wildcard lib/*.lpp))
OBJLIST  :=  $(subst .cpp,.o,$(wildcard lib/*.cpp))
BINOBJLIST  :=  $(subst .cpp,.o,$(wildcard bin/*.cpp))
TESTSOBJLIST  :=  $(subst .cpp,.o,$(wildcard tests/*.cpp))
TESTNAMELIST  :=  $(subst .cpp,,$(wildcard tests/test_*.cpp))
LIBNAME  :=  SWObjects
LIB	 :=	 lib/lib$(LIBNAME).a
LIBINC	+=	 -l$(LIBNAME)

$(LIB): $(BISONOBJ) $(FLEXOBJ) $(OBJLIST)
	$(AR) rcvs $@ $^

.PHONY: lib NOGEN
lib: dep $(LIB)

.SECONDARY:

lib/%.dep: lib/%.cpp config.h
	($(ECHO) -n $@ lib/; $(CXX) $(DEFS) $(INCLUDES) -MM $<) > $@ || (rm $@; false)

# The following doesn't fire, so I have to create the specialied rules below:
# lib/%/%.dep: lib/%/%.cpp config.h
# 	($(ECHO) -n $@ ONE lib/%/ TWO; $(CXX) $(DEFS) $(INCLUDES) -MM $<) > $@ || (rm $@; false)

lib/SPARQLfedParser/SPARQLfedParser.dep: lib/SPARQLfedParser/SPARQLfedParser.cpp config.h
	($(ECHO) -n $@ lib/SPARQLfedParser/; $(CXX) $(DEFS) $(INCLUDES) -MM $<) > $@ || (rm $@; false)
lib/MapSetParser/MapSetParser.dep: lib/MapSetParser/MapSetParser.cpp config.h
	($(ECHO) -n $@ lib/MapSetParser/; $(CXX) $(DEFS) $(INCLUDES) -MM $<) > $@ || (rm $@; false)
lib/TurtleSParser/TurtleSParser.dep: lib/TurtleSParser/TurtleSParser.cpp config.h
	($(ECHO) -n $@ lib/TurtleSParser/; $(CXX) $(DEFS) $(INCLUDES) -MM $<) > $@ || (rm $@; false)
lib/TrigSParser/TrigSParser.dep: lib/TrigSParser/TrigSParser.cpp config.h
	($(ECHO) -n $@ lib/TrigSParser/; $(CXX) $(DEFS) $(INCLUDES) -MM $<) > $@ || (rm $@; false)
lib/SQLParser/SQLParser.dep: lib/SQLParser/SQLParser.cpp config.h
	($(ECHO) -n $@ lib/SQLParser/; $(CXX) $(DEFS) $(INCLUDES) -MM $<) > $@ || (rm $@; false)

DEPEND += $(OBJLIST:.o=.dep) $(BISONOBJ:.o=.dep) $(FLEXOBJ:.o=.dep)
GENERATED += $(BISONOBJ:.o=.cpp) $(BISONOBJ:.o=.hpp) $(FLEXOBJ:.o=.cpp)

# don't run flex and bison
NOGEN:
	touch $(GENERATED)
	ln -s win/FlexLexer.h

lib/%.cpp  lib/%.hpp : lib/%.ypp
	$(YACC) -o $(@:.hpp=.cpp) $<
	$(SED) -i~ 's,# define PARSER_HEADER_H,#pragma once,' $(@:.cpp=.hpp)

lib/%.cpp : lib/%.lpp
	$(FLEX) -o $@  $<
	$(SED) -i~ 's,extern "C" int isatty (int );,extern "C" int isatty (int ) throw();,' $@

docs/version.h:
	svn info . | perl -ne 'if (m/([^:]+): (.*)/) { my ($$attr, $$val) = ($$1, $$2); $$attr =~ s/ /_/g; print "#define SVN_$$attr \"$$val\"\n" }' > $@

##### bin dirs ####

bin/%.dep: bin/%.cpp config.h $(BISONH)
	($(ECHO) -n $@ bin/; $(CXX) $(INCLUDES) -MM $<) > $@ || (rm $@; false)
DEPEND += $(BINOBJLIST:.o=.dep)

bin/%.o. : bin/%.cpp bin/.dep/%.d config.h docs/version.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

bin/% : bin/%.o $(LIB) #lib
	$(CXX) -o $@ $< $(LDAPPFLAGS) $(HTTP_SERVER_LIB)

unitTESTS := $(subst tests/test_,t_,$(TESTNAMELIST))
bin: $(BINOBJLIST:.o=)

##### apache #####

# TODO: cleanup mod_sparul build, autoconf dependency paths?
apache/mod_sparul.dep: apache/mod_sparul.cpp config.h
	($(ECHO) $@ \\; $(CXX) -I`$(APXS) -q INCLUDEDIR` -I$(CODEA) -I$(CCL) -I$(APR) $(CXXFLAGS) -MM $<) > $@ || (rm $@; false)

apache/mod_sparul.so: $(LIB) apache/mod_sparul.dep
	gcc -fPIC -Wall `$(APXS) -q CFLAGS` -I`$(APXS) -q INCLUDEDIR` -I$(CODEA) -I$(CCL) -I$(APR) $(INCLUDES) -c apache/mod_sparul.cpp -o apache/mod_sparul.o; \
	$(APXS) -I$(CODEA) -I$(CCL) -I$(APR) -c apache/mod_sparul.o $(CODEA)/codea_hooks.o lib/libSWObjects.a $(LDFLAGS)

clean-mod_sparul:
	rm -f apache/mod_sparul.{o,so,la} apache/.libs/mod_sparul.*

install-mod_sparul: apache/mod_sparul.so
	$(APXS) -i -n sparul_module apache/.libs/mod_sparul.so


##### packaged tests ####

## test inferenced based on T, test_<T>.o=C/C++ query_<T>.rq ruleMap<T>.rq

#notes for ericP
# opts: tests/execute_HealthCare1
# 	valgrind tests/execute_HealthCare1 tests/query_leadTrailOpts.rq tests/ruleMap_leadTrailOpts.rq --stem http://stem.example/

# deep: tests/execute_HealthCare1
# 	valgrind tests/execute_HealthCare1 tests/query_deepNesting.rq tests/ruleMap_deepNesting.rq

# opt1: tests/execute_HealthCare1
# 	valgrind tests/execute_HealthCare1 tests/query_spec-opt1.rq --stem http://hr.example/DB/

# equivOpt1: tests/execute_HealthCare1
# 	valgrind tests/execute_HealthCare1 tests/query_spec-equivOpt1.rq --stem http://hr.example/DB/

# optJoin1: tests/execute_HealthCare1
#	valgrind tests/execute_HealthCare1 tests/query_spec-optJoin1.rq --stem http://hr.example/DB/

unitTESTS := $(subst tests/test_,t_,$(TESTNAMELIST))
unitTESTexes := $(TESTNAMELIST)
# You can override unitTESTS while fiddling with them.
#unitTESTS=t_GraphMatch
#$(error unitTESTS: $(unitTESTS))
# and control which subtests within a unit are run
#TEST_ARGS=--run_test=op_equals/* make -j 4 t_QueryMap
TEST_ARGS ?= ""

t_SPARQL: bin/sparql

tests/test_%.dep: tests/test_%.cpp config.h $(BISONH)
	($(ECHO) -n $@ tests/; $(CXX) $(INCLUDES) -MM $<) > $@ || (rm $@; false)

tests/test_%.o: tests/test_%.cpp $(LIB) tests/.dep/test_%.d config.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

tests/test_%: tests/test_%.o $(LIB)
	$(CXX) -o $@ $< $(LDFLAGS) $(TEST_LIB)

tests/man_%.cpp: tests/test_%.cpp tests/makeMan.pl tests/manualHarness.cpp
	perl tests/makeMan.pl $< $@

tests/man_%.dep: tests/man_%.cpp config.h $(BISONH)
	($(ECHO) -n $@ tests/; $(CXX) $(INCLUDES) -MM $<) > $@ || (rm $@; false)
DEPEND += $(TESTSOBJLIST:.o=.dep)

tests/man_%.o: tests/man_%.cpp $(LIB) tests/.dep/man_%.d config.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

tests/man_%: tests/man_%.o $(LIB)
	$(CXX) -o $@ $< $(LDFLAGS) $(TEST_LIB)

.PHONY: tests/manualHarness.dep


tests/test_WEBagents: tests/test_WEBagents.o $(LIB)
	$(CXX) -o $@ $< -lboost_filesystem$(BOOST_VERSION) -lboost_thread$(BOOST_VERSION) $(LDFLAGS) $(TEST_LIB)

t_%: tests/test_%
	( cd tests && ./$(notdir $<) $(TEST_ARGS) )

v_%: tests/test_%
	( cd tests && valgrind --leak-check=yes  --suppressions=boost-test.supp --xml=no ./$(notdir $<) $(TEST_ARGS) )
# update suppressions with --gen-suppressions=yes and copy to boost-test.supp

# "manual" (non-boost) tests, synthesized from the boost tests.
m_%: tests/man_%
	( cd tests && valgrind --leak-check=yes  --suppressions=boost-test.supp --xml=no ./$(notdir $<) $(TEST_ARGS) )


### Query Map tests tests:

tests/HealthCare1.results: bin/sparql tests/query_HealthCare1.rq tests/ruleMap_HealthCare1.rq
	$< tests/query_HealthCare1.rq tests/ruleMap_HealthCare1.rq --stem http://someClinic.exampe/DB/

tests/HealthCare1.valgrind: bin/sparql tests/query_HealthCare1.rq tests/ruleMap_HealthCare1.rq
	valgrind --leak-check=yes --xml=no $< tests/query_HealthCare1.rq tests/ruleMap_HealthCare1.rq --stem http://someClinic.exampe/DB/

transformTESTS=tests/HealthCare1

transformTEST_RESULTS=$(transformTESTS:=.results)
transformVALGRIND=$(transformTEST_RESULTS:.results=.valgrind)


### sparql server tests:

tests/server_mouseToxicity_remote-all.results: \
	bin/sparql \
	tests/mouseToxicity/remote-all/ToxicAssoc0.rq \
	tests/mouseToxicity/remote-all/MicroArray.map \
	tests/mouseToxicity/remote-all/Uniprot.map \
	tests/mouseToxicity/remote-all/ScreeningAssay.map \
	tests/mouseToxicity/remote-all/ChemStructure.map \
	tests/mouseToxicity/remote-all/MouseToxicity.map
	# Start servers.
	( cd tests/mouseToxicity/remote-all/ &&\
	  ../../../$< --debug 1 --once --serve http://localhost:8881/microArray -m MicroArray.map |\
	  tee ../../../$@.ma )&
	( cd tests/mouseToxicity/remote-all/ &&\
	  ../../../$< --debug 1 --once --serve http://localhost:8882/uniprot -m Uniprot.map |\
	  tee ../../../$@.up )&
	( cd tests/mouseToxicity/remote-all/ &&\
	  ../../../$< --debug 1 --once --serve http://localhost:8883/screeningAssay -m ScreeningAssay.map |\
	  tee ../../../$@.sa )&
	( cd tests/mouseToxicity/remote-all/ &&\
	  ../../../$< --debug 1 --once --serve http://localhost:8884/chemStructure -m ChemStructure.map |\
	  tee ../../../$@.cs )&
	( cd tests/mouseToxicity/remote-all/ &&\
	  ../../../$< --debug 1 --once --serve http://localhost:8885/mouseToxicity -m MouseToxicity.map |\
	  tee ../../../$@.mt )&
	sleep 1 # give the servers time to start up
	( cd tests/mouseToxicity/remote-all/ &&\
	  time ../../../bin/sparql ToxicAssoc0.rq )


tests/7tm_receptors-flat.results: bin/sparql tests/7tm_receptors/flat/q.rq tests/7tm_receptors/flat/receptors.map
	( cd tests/7tm_receptors/flat/ && ../../../$< --once --serve http://localhost:8888/7tm_receptors receptors.map > ../../../$@ )&
	sleep 1
	( cd tests/7tm_receptors/flat/ && ../../../$< q.rq )

tests/7tm_receptors-flat.results2: bin/sparql tests/7tm_receptors/flat/q.rq tests/7tm_receptors/flat/receptors.map
	( cd tests/7tm_receptors/flat/ && ../../../$< --once --serve --serve http://localhost:8888/7tm_receptors --mapset receptors.mapset > ../../../$@ )&
	sleep 1
	( cd tests/7tm_receptors/flat/ && ../../../$< q.rq )

SPARQL_serverTESTS=tests/server_mouseToxicity_remote-screening-assay

SPARQL_serverTEST_RESULTS=$(SPARQL_serverTESTS:=.results)

.PHONY: test valgrind tests/7tm_receptors-flat.results
test: lib $(unitTESTS) $(transformTEST_RESULTS)
valgrind: lib $(transformVALGRIND)

### Generate SWIG Interfaces ###

SWIG ?= swig
# SWIG output fixups:
#   1. const const => const
#   2. in  va_list * temp = reinterpret_cast< va_list * >(argp3);
#          arg3 = *temp;
#      arg3 = *temp => va_copy(arg3, *temp)
SWIG_SUBST = perl -0777 -pi -e 's{const const}{const}g; s{(va_list\s*\*[^\r\n]+\r?\n\s*)(arg\d) = (\*temp)}{$${1}va_copy($$2, $$3)}g;'

SWIG_OBJS = lib/exs.o lib/RdfQueryDB.o lib/ParserCommon.o lib/TurtleSParser/TurtleSParser.o lib/TurtleSScanner.o lib/TrigSParser/TrigSParser.o lib/TrigSScanner.o lib/SPARQLfedParser/SPARQLfedParser.o lib/SPARQLfedScanner.o lib/MapSetParser/MapSetParser.o lib/MapSetScanner.o
SWIG_HEADERS = lib/SWObjects.hpp lib/SWObjects.cpp lib/SWObjectDuplicator.hpp interface/SAXparser.hpp lib/XMLSerializer.hpp lib/RdfDB.cpp lib/ResultSet.hpp lib/ResultSet.cpp lib/RdfDB.hpp lib/SWObjects.cpp lib/SPARQLSerializer.hpp lib/RuleInverter.hpp lib/QueryMapper.hpp lib/MapSetParser/MapSetParser.hpp interface/WEBagent_boostASIO.hpp interface/SAXparser_expat.hpp lib/ParserCommon.hpp lib/SPARQLfedParser/SPARQLfedParser.hpp lib/TurtleSParser/TurtleSParser.hpp lib/TrigSParser/TrigSParser.hpp interface/WEBagent.hpp
SWIG_LIBS =  $(REGEX_LIB) $(HTTP_CLIENT_LIB) $(XML_PARSER_LIB) $(SQL_CLIENT_LIB)

 # Python
swig/python/SWObjects_wrap.cxx: swig/SWObjects.i $(SWIG_HEADERS)
	$(SWIG) -o $@ -c++ -python -I. -Ilib -Iinterface $<
	$(SWIG_SUBST) $@

swig/python/SWObjects_wrap.o: swig/python/SWObjects_wrap.cxx
	g++ $(OPTIM) -I. -Ilib/ -Iinterface/ -fPIC -fno-stack-protector -c -o swig/python/SWObjects_wrap.o swig/python/SWObjects_wrap.cxx -I$(PYTHON_HOME)

swig/python/_SWObjects.so: swig/python/SWObjects_wrap.o $(SWIG_OBJS)
	g++ -shared -o $@ $< $(SWIG_OBJS) $(SWIG_LIBS)

# The _SWObjects.so target can be built with the python distutils package,
# but it's noisier and doesn't re-use the object files in lib:

# swig/python/_SWObjects.so: swig/python/SWObjects_wrap.cxx swig/python/SWObjects_setup.py
# 	python swig/python/SWObjects_setup.py build_ext --inplace -I.:lib/:interface/
# 	mv _SWObjects.so swig/python/

python-test: swig/python/_SWObjects.so
	(cd swig/python/ && python t_SWObjects.py)

python-clean:
	$(RM) -f swig/python/SWObjects.* swig/python/SWObjects_wrap.* swig/python/_SWObjects.so

SWIG-TEST += python-test
SWIG-CLEAN += python-clean

# Java
swig/java/src/AtomFactory.java swig/java/src/SWObjects_wrap.cxx: swig/SWObjects.i $(SWIG_HEADERS)
	-$(RM) swig/java/src/*.java
	$(SWIG) -o swig/java/src/SWObjects_wrap.cxx -c++ -java -I. -Ilib -Iinterface swig/SWObjects.i
	$(SWIG_SUBST) swig/java/src/SWObjects_wrap.cxx

swig/java/src/SWObjects_wrap.o: swig/java/src/SWObjects_wrap.cxx
	g++ $(OPTIM) -I. -Ilib/ -Iinterface/ -fPIC -fno-stack-protector -c -o $@ $< -I$(JAVA_HOME)/include

swig/java/libSWObjects.so: swig/java/src/SWObjects_wrap.o $(SWIG_OBJS)
	g++ -shared -o $@ $< $(SWIG_OBJS) $(SWIG_LIBS)

swig/java/SWObjects.jar: swig/java/src/AtomFactory.java # there are zillions of class files, use AtomFactory as an indicator
	-$(RM) $@
	javac -d swig/java/class swig/java/src/*.java
	jar cf $@ -C swig/java/class .

swig/java/t_SWObjects.class: swig/java/t_SWObjects.java swig/java/SWObjects.jar
	javac -d swig/java -classpath .:/usr/share/java/junit4-4.8.1.jar:swig/java/SWObjects.jar $<

java-test: swig/java/libSWObjects.so swig/java/t_SWObjects.class
	LD_LIBRARY_PATH=swig/java java -classpath .:/usr/share/java/junit4-4.8.1.jar:swig/java:swig/java/SWObjects.jar org.junit.runner.JUnitCore t_SWObjects

java-clean:
	$(RM) -f swig/java/libSWObjects.so swig/java/class/* swig/java/src/* swig/java/t_SWObjects.class

SWIG-TEST += java-test
SWIG-CLEAN += java-clean

# Perl
swig/perl/SWObjects_wrap.cxx: swig/SWObjects.i $(SWIG_HEADERS)
	$(SWIG) -o $@ -c++ -perl5 -I. -Ilib -Iinterface $<
	$(SWIG_SUBST) $@

swig/perl/SWObjects_wrap.o: swig/perl/SWObjects_wrap.cxx
	g++ $(OPTIM) -I. -Ilib/ -Iinterface/ -fPIC -c -o $@ $< -I$(PERL_HOME)/CORE

swig/perl/libSWObjects.so: swig/perl/SWObjects_wrap.o $(SWIG_OBJS)
	g++ -shared -o $@ $< $(SWIG_OBJS) $(SWIG_LIBS)

perl-test: swig/perl/libSWObjects.so
	(cd swig/perl/ && perl t_SWObjects.t)

perl-clean:
	$(RM) -f swig/perl/SWObjects.* swig/perl/SWObjects_wrap.* swig/perl/libSWObjects.so

SWIG-TEST += perl-test
SWIG-CLEAN += perl-clean


# Lua
swig/lua/SWObjects_wrap.cxx: swig/SWObjects.i $(SWIG_HEADERS)
	$(SWIG) -o $@ -c++ -lua -I. -Ilib -Iinterface $<
	$(SWIG_SUBST) $@

swig/lua/SWObjects_wrap.o: swig/lua/SWObjects_wrap.cxx
	g++ $(OPTIM) -I. -Ilib/ -Iinterface/ -fPIC -c -o $@ $< -I$(LUA_HOME)

swig/lua/SWObjects.so: swig/lua/SWObjects_wrap.o $(SWIG_OBJS)
	g++ -shared -o $@ $< $(SWIG_OBJS) $(SWIG_LIBS)

lua-test: swig/lua/SWObjects.so
	(cd swig/lua/ && shake t_SWObjects.lua)

lua-clean:
	$(RM) -f swig/lua/SWObjects.* swig/lua/SWObjects_wrap.* swig/lua/libSWObjects.so

SWIG-TEST += lua-test
SWIG-CLEAN += lua-clean


 # Php
swig/php/SWObjects_wrap.cxx: swig/SWObjects.i $(SWIG_HEADERS)
	$(SWIG) -DYYDEBUG=0 -o $@ -c++ -php -I. -Ilib -Iinterface $<
	$(SWIG_SUBST) $@

swig/php/SWObjects_wrap.o: swig/php/SWObjects_wrap.cxx
	g++ $(OPTIM) -DHAVE_LIBEXPAT=1 -I. -Ilib/ -Iinterface/ -fPIC -fno-stack-protector -c -o swig/php/SWObjects_wrap.o swig/php/SWObjects_wrap.cxx -I$(PHP_HOME)

swig/php/SWObjects.so: swig/php/SWObjects_wrap.o $(SWIG_OBJS)
	g++ -shared -o $@ $< $(SWIG_OBJS) $(SWIG_LIBS)

php-test: swig/php/SWObjects.so
	(cd swig/php/ && php -d extension=./SWObjects.so t_SWObjects.php)

php-clean:
	$(RM) -f swig/php/SWObjects.* swig/php/SWObjects_wrap.* swig/php/_SWObjects.so

SWIG-TEST += php-test
SWIG-CLEAN += php-clean

swig-test: $(SWIG-TEST)
swig-clean: $(SWIG-CLEAN)


# Mac OSX stuff
Sparql.app/Contents/MacOS:
	mkdir -p $@

Sparql.app/Contents/Frameworks:
	mkdir -p $@

.PHONY: RenamedFrameworks

RenamedFrameworks: Sparql.app/Contents/Frameworks
	cp /usr/lib/libstdc++.6.dylib $<
	install_name_tool -id @executable_path/../Frameworks/libstdc++.6.dylib $</libstdc++.6.dylib
	for l in regex system program_options filesystem thread; do \
		cp /opt/local/lib/libboost_$$l-mt.dylib $< && \
		install_name_tool -id @executable_path/../Frameworks/libboost_$$l-mt.dylib $</libboost_$$l-mt.dylib && \
		install_name_tool -change /opt/local/lib/libboost_system-mt.dylib @executable_path/../Frameworks/libboost_system-mt.dylib $</libboost_$$l-mt.dylib; \
	done
	for l in ssl.0.9.8 crypto.0.9.8 z.1; do \
		cp /opt/local/lib/lib$$l.dylib $< && \
		install_name_tool -id @executable_path/../Frameworks/lib$$l.dylib $</lib$$l.dylib && \
		install_name_tool -change /opt/local/lib/libcrypto.0.9.8.dylib @executable_path/../Frameworks/libcrypto.0.9.8.dylib $</lib$$l.dylib && \
		install_name_tool -change /opt/local/lib/libz.1.dylib @executable_path/../Frameworks/libz.1.dylib $</lib$$l.dylib; \
	done
	cp /opt/local/lib/mysql5/mysql/libmysqlclient.16.dylib $<
	install_name_tool -id @executable_path/../Frameworks/libmysqlclient.16.dylib $</libmysqlclient.16.dylib && \
	install_name_tool -change /opt/local/lib/libssl.0.9.8.dylib @executable_path/../Frameworks/libssl.0.9.8.dylib $</libmysqlclient.16.dylib
	install_name_tool -change /opt/local/lib/libcrypto.0.9.8.dylib @executable_path/../Frameworks/libcrypto.0.9.8.dylib $</libmysqlclient.16.dylib
	install_name_tool -change /opt/local/lib/libz.1.dylib @executable_path/../Frameworks/libz.1.dylib $</libmysqlclient.16.dylib

Sparql.app/Contents/MacOS/Sparql: bin/sparql.o $(LIB) Sparql.app/Contents/MacOS RenamedFrameworks
	$(CXX) -o $@ $< -LSparql.app/Contents/Frameworks $(LDAPPFLAGS) $(HTTP_SERVER_LIB)

Sparql.dmg: Sparql.app/Contents/MacOS/Sparql
	rm -f $@
	hdiutil create -srcfolder Sparql.app $@


# Clean - rm everything we remember to rm.
.PHONY: clean cleaner
clean:
	$(RM) */*.o lib/*.a lib/*.dylib lib/*.so lib/*.la */*.bak config.h \
	$(subst .ypp,.o,$(wildcard lib/*/*.ypp)) \
        $(transformTEST_RESULTS) $(transformVALGRIND) \
	$(unitTESTexes) *~ */*.dep */*/*.dep

cleaner: clean swig-clean
	$(RM) \
	$(subst .lpp,.cpp,$(wildcard lib/*.lpp)) \
	$(subst .ypp,.cpp,$(wildcard lib/*/*.ypp)) \
	$(subst .ypp,.hpp,$(wildcard lib/*/*.ypp)) \
	$(BISONHH:%=*/%)

dep: $(DEPEND)

BISONHH=location.hh stack.hh position.hh
#$(BISONHH): $(BISONOBJ)
-include $(DEPEND)
