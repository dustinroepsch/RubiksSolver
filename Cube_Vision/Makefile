CFLAGS=-std=c++11 `pkg-config --cflags --libs opencv`

all: test_main

test_main: face_finder.o face_affine.o face_colors.o
	g++ test_main.cpp *.o -o $@ $(CFLAGS)

face_finder.o: face_finder.cpp
	g++ face_finder.cpp -c $(CFLAGS)

face_affine.o: face_affine.cpp
	g++ face_affine.cpp -c $(CFLAGS)

face_colors.o: face_colors.cpp
	g++ face_colors.cpp -c $(CFLAGS)

clean:
	rm -f *.o
