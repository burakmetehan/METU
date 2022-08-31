CC= gcc
CXX= g++
CFLAGS= -pedantic
ERROR_FLAGS= -Wall -Wextra -Werror -Wshadow -Wsign-conversion
CXXFLAGS= -std=c++17

metu: Metu.cpp Metu.h
	$(CXX) $(CFLAGS) $(ERROR_FLAGS) Metu.cpp -o metu

student: Student.cpp Course.cpp Student.h Course.h
	$(CXX) $(CFLAGS) $(ERROR_FLAGS) Student.cpp Course.cpp -o student

course: Course.cpp Course.h
	$(CXX) $(CFLAGS) $(ERROR_FLAGS) Course.cpp -o course
