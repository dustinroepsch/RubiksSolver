CFLAGS=-std=c++11 -Wall `pkg-config --cflags --libs opencv`

all: solve

solve: main.cpp face_finder.o face_affine.o face_colors.o
	g++ main.cpp *.o -o $@ $(CFLAGS)


test_main: test_main.cpp face_finder.o face_affine.o face_colors.o
	g++ test_main.cpp *.o -o $@ $(CFLAGS)

face_finder.o: face_finder.cpp
	g++ face_finder.cpp -c $(CFLAGS)

face_affine.o: face_affine.cpp
	g++ face_affine.cpp -c $(CFLAGS)

face_colors.o: face_colors.cpp
	g++ face_colors.cpp -c $(CFLAGS)

clean:
	rm -f *.o
