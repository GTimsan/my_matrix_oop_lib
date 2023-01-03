.PHONY: all clean test s21_matrix_oop.a check valgrind_check gcov_report rebuild install uninstall 

CC=g++
CFLAGS= -std=c++17

LDFLAGS= -Wall -Wextra -Werror 

OS = $(shell uname)
ifeq ($(OS), Linux)
	LIBFLAGS=-lstdc++ `pkg-config --cflags --libs gtest`
else
	LIBFLAGS=-lstdc++ -lm -lgtest
endif

CFILES= tests.cpp s21_matrix_oop.cpp
OFILES=$(CFILES:.cpp=.o)
TARGET = tests
LIB_NAME = s21_matrix_oop.a
LIB_FILES = s21_matrix_oop.o

default: test

rebuild: clean all 

all: $(TARGET)

$(LIB_NAME): s21_matrix_oop.o s21_matrix_oop.h
	@ar -rcs $(LIB_NAME) $?
	@ranlib $@
	@cp $@ lib$@

test: rebuild
	./$(TARGET)

$(TARGET): $(OFILES)
	$(CC) $(LDFLAGS) $(CFLAGS) $(OFILES) -o $(TARGET) $(LIBFLAGS)

%.o: %.cpp
	$(CC) -c $(LDFLAGS) $(CFLAGS)  $<


clean:
	rm -rf $(TARGET)  s21_calc *.a *.o *.out *.cfg fizz *.gc* *.info report CPPLINT.cfg ../build


# g++ -Wall -Wextra -Werror s21_matrix_oop.cpp && ./a.out

# valgrind --leak-check=full --show-leak-kinds=all -s ./a.out

# clang-format -n s21_matrix_oop.cpp 
