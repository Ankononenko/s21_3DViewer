CC=gcc
STRICT_CFLAGS=-Wall -Werror -Wextra -std=c11 -pedantic

CHECK_CFLAGS=$(shell pkg-config --cflags check)
CHECK_LFLAGS=$(shell pkg-config --libs check)

# GCOVR_CFLAGS=$(shell pkg-config --cflags gcovr)
GCOVR_CFLAGS=-fprofile-arcs -ftest-coverage -fPIC
# -fprofile-arcs -ftest-coverage
# GCOVR_LFLAGS=$(shell pkg-config --libs gcovr)
GCOVR_LFLAGS=-lgcov

REPORT_DIRECTORY=report
DOCUMENTATION_DIRECTORY=doxygen

all: make_target

MakefileGenerated.mk: 3D_Viewer.pro
		qmake -o MakefileGenerated.mk 3D_Viewer.pro

make_target: MakefileGenerated.mk
		make -f MakefileGenerated.mk CC=gcc

clean:	clean_tests
		rm -rf $(REPORT_DIRECTORY)/*
		rm -rf $(DOCUMENTATION_DIRECTORY)/html
		rm -rf $(DOCUMENTATION_DIRECTORY)/latex
		make -f MakefileGenerated.mk distclean
		rm -rf 3D_Viewer.tar
		rm -rf 3D_Viewer.tar.gz

install: MakefileGenerated.mk
		make -f MakefileGenerated.mk install INSTALL_ROOT=../install_directory/

uninstall: MakefileGenerated.mk
		make -f MakefileGenerated.mk uninstall INSTALL_ROOT=../install_directory/



# build directory is different for MACos and Linux, so we need to 
# find out OS and define COPY_DIRECTORY according to OS, otherwise archive will not
# contain 3D_Viewer.app when running target make dist
OSFLAG 				:=
ifeq ($(OS),Windows_NT)
	OSFLAG += -D WIN32
	ifeq ($(PROCESSOR_ARCHITECTURE),AMD64)
		OSFLAG += -D AMD64
	endif
	ifeq ($(PROCESSOR_ARCHITECTURE),x86)
		OSFLAG += -D IA32
	endif
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		OSFLAG += -D LINUX
		COPY_DIRECTORY=.
	endif
	ifeq ($(UNAME_S),Darwin)
		OSFLAG += -D OSX
		COPY_DIRECTORY=3D_Viewer.app/Contents/MacOS
	endif
		UNAME_P := $(shell uname -p)
	ifeq ($(UNAME_P),x86_64)
		OSFLAG += -D AMD64
	endif
		ifneq ($(filter %86,$(UNAME_P)),)
	OSFLAG += -D IA32
		endif
	ifneq ($(filter arm%,$(UNAME_P)),)
		OSFLAG += -D ARM
	endif
endif



dist: make_target dvi
		echo $(COPY_DIRECTORY)
		tar -cvf 3D_Viewer.tar $(COPY_DIRECTORY)/3D_Viewer doxygen/html
		gzip 3D_Viewer.tar

gcov: tests
		mkdir -p $(REPORT_DIRECTORY)
		gcovr . --html --html-details -o $(REPORT_DIRECTORY)/coverage_report.html
		open $(REPORT_DIRECTORY)/coverage_report.html

style: style_google

style_google:
		clang-format --style=Google -i *.cc
		clang-format --style=Google -i *.h
		clang-format --style=Google -i tests/*.c
		clang-format --style=Google -i tests/*.h

tests: tests_check.out
		-./tests_check.out

tests_check.out: tests/tests_main.o tests/tests_move.o tests/tests_rotation.o tests/tests_scale.o tests/tests_parsing.o backend_for_tests.o my_getline_for_tests.o
		$(CC)  -o $@ $^ $(CHECK_LFLAGS) $(GCOVR_LFLAGS)

tests/tests_main.o: tests/tests_main.c tests/tests_main.h 
		$(CC) -c -o $@ $< $(CHECK_CFLAGS)

tests/tests_move.o: tests/tests_move.c tests/tests_main.h 
		$(CC) -c -o $@ $< $(CHECK_CFLAGS)

tests/tests_scale.o: tests/tests_scale.c tests/tests_main.h 
		$(CC) -c -o $@ $< $(CHECK_CFLAGS)

tests/tests_parsing.o: tests/tests_parsing.c tests/tests_main.h 
		$(CC) -c -o $@ $< $(CHECK_CFLAGS)

tests/tests_rotation.o: tests/tests_rotation.c tests/tests_main.h 
		$(CC) -c -o $@ $< $(CHECK_CFLAGS)

backend_for_tests.o: backend.c backend.h
		$(CC) -c $(STRICT_CFLAGS) $< -o $@ $(GCOVR_CFLAGS)

my_getline_for_tests.o: my_getline.c my_getline.h
		$(CC) -c $(STRICT_CFLAGS) $< -o $@ 


clean_tests: 
		rm -rf *_for_tests.o
		rm -rf tests/*.o
		rm -rf tests_check.out
		rm -rf *.gcda
		rm -rf *.gcno

dvi:
		cd doxygen && doxygen Doxyfile && open html/index.html





