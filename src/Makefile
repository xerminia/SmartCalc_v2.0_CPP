GXX = g++
CFLAGS = -Wall -Werror -Wextra
STD = -std=c++17
GFLAG = -lgtest
MODEL = SmartCalc/Model/
GCOV = --coverage

all:  clean install test

build:
	mkdir build
	cd ./build/ && qmake ../ && make

install: build
	mkdir $(HOME)/Applications/SmartCalc/
	cp -rf build/SmartCalc_v2.app $(HOME)/Applications/SmartCalc/
	make clean

uninstall:
	rm -rf $(HOME)/Applications/SmartCalc/

test:
	$(GXX) $(CFLAGS) $(MODEL)SmartCalcModel.cpp \
	$(MODEL)CreditCalcModel.cpp test.cpp $(STD) $(GFLAG) -o test
	./test

gcov: clean
	$(GXX) $(GCOV) $(CFLAGS) $(MODEL)SmartCalcModel.cpp \
	$(MODEL)CreditCalcModel.cpp test.cpp $(STD) $(GFLAG) -o test
	./test
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info
	open report/index.html

dist:
	rm -rf SmartCalc_v2
	mkdir SmartCalc_v2
	mkdir SmartCalc_v2/src
	cp Makefile *.h *.cpp *.pro *.html .clang-format SmartCalc_v2/src/
	cp -R SmartCalc SmartCalc_v2/src/
	tar -cvzf SmartCalc_v2.tar.gz SmartCalc_v2
	mv SmartCalc_v2.tar.gz $(HOME)/Desktop/
	rm -rf SmartCalc_v2/

dvi:
	open documentation.html

leaks: test
	CK_FORK=no leaks --atExit -- ./test

check:
	clang-format -i *.cpp SmartCalc/*.cpp SmartCalc/Model/*.cpp SmartCalc/View/*.cpp SmartCalc/Controller/*.cpp
	clang-format -n *.cpp SmartCalc/*.cpp SmartCalc/Model/*.cpp SmartCalc/View/*.cpp SmartCalc/Controller/*.cpp

clean:
	rm -rf *.o test build report *.gc* *.info 
