GSL_PATH ?= /usr
GSL_INCLUDE ?= $(GSL_PATH)/include
GSL_LIB ?= $(GSL_PATH)/lib
SRC_FILES ?= src/color.o src/graph_generator.o src/graph_coloring.o src/spread.o src/strategies.o 
LIBP3_FILES ?= src/player3.o $(SRC_FILES)
LIBP4_FILES ?= src/player9etal.o $(SRC_FILES)
LIBP5_FILES ?= src/playerchirir.o $(SRC_FILES)
CC = gcc
C_FLAGS ?= -std=c99 -g -O0 -ftest-coverage
LD_LIBRARY_PATH ?= LD_LIBRARY_PATH=$(shell $(pwd))/src
LDFLAGS ?= -Wl,-rpath=$(shell echo $(shell pwd))/install 
INST = install
SRC = src
TST = tst

ifneq ($(GSL_PATH),/usr/include/gsl)
	GSL_INCLUDE = $(GSL_PATH)/include 
endif

all : build

build : src/server.o test libplayers server

server : src/server.o $(SRC_FILES)
	$(CC) $(C_FLAGS) $^ $(LDFLAGS) -L$(INST) -L$(GSL_LIB) -ldl -lgsl -lgslcblas -lm -o $(SRC)/server


test : tst/alltests.o $(SRC_FILES)
	$(CC) $(C_FLAGS) tst/alltests.o $(SRC_FILES) -L$(GSL_LIB) -lgsl -lgslcblas -lm -ftest-coverage -o $(TST)/alltests

install : build
	mv $(SRC)/libplayer5.so $(INST)
	mv $(SRC)/libplayer4.so $(INST)
	mv $(SRC)/libplayer3.so $(INST)
	mv $(SRC)/server $(INST)/server
	mv $(TST)/alltests $(INST)/alltests


src/% : src/%.o
	gcc $^ -L$(GSL_LIB) -lgsl -ldl -lm -o $@

src/%.o : src/%.c src/*.h 
	$(CC)  -g -fPIC -shared -c $< -I$(GSL_INCLUDE) -lgsl -ldl -lm -o $@

libplayers:  libDynP5 libDynP4 libDynP3

libDynP5 : $(LIBP5_FILES)
	gcc $^  -fPIC -shared -o $(SRC)/libplayer5.so

libDynP4 : $(LIBP4_FILES)
	gcc $^  -fPIC -shared -o $(SRC)/libplayer4.so

libDynP3 : $(LIBP3_FILES)
	gcc $^  -fPIC -shared -o $(SRC)/libplayer3.so


tst/alltests.o : tst/alltests.c src/*h
	gcc $(C_FLAGS) -c $< -I$(GSL_INCLUDE) -lgsl -lm -o $@

tst/test_graph.o : tst/test_graph.c src/*.h
	gcc $(C_FLAGS) -c $< -I$(GSL_INCLUDE) -lgsl -lm -o $@

tst/test_graph : tst/test_graph.o $(SRC_FILES)
	gcc  $(C_FLAGS) $^ -L$(GSL_INCLUDE) -lgsl -lgcov -lm -o $@

tst/test_spread.o : tst/test_spread.c src/*.h
	gcc -c $(C_FLAGS) $< -I$(GSL_INCLUDE) -lgsl -lm -o $@

tst/test_spread : tst/test_spread.o $(SRC_FILES)
	gcc $^ $(C_FLAGS) -L$(GSL_INCLUDE) -lgsl -lgcov -lm -o $@

tst/test_strategies.o : tst/test_strategies.c src/*.h
	gcc -c $(C_FLAGS) $< -I$(GSL_INCLUDE) -lgsl -lm -o $@

tst/test_strategies : tst/test_strategies.o $(SRC_FILES)
	gcc $^ $(C_FLAGS) -L$(GSL_INCLUDE) -lgsl -lgcov -lm -o $@
	

clean : 
	rm -f src/*.o
	rm -f tst/*.o
	rm -f src/server
	rm -f tst/test_graph
	rm -f libplayer.so
	rm -f libobjets.so
	rm -f tst/test_spread
	rm -f tst/test_strategies
	rm -f install/*.so
	rm -f install/alltests
	rm -f install/server
	rm -f tst/*.gcno
	
