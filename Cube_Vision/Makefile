CFLAGS=-std=c++11 -Wall -ggdb `pkg-config --cflags --libs opencv`

all: solve

solve: main.cpp one_face.o RubiksCube.o
	g++ main.cpp *.o -D CALIBRATE=0 -o $@ $(CFLAGS)

calibrate: FORCE test_main.cpp one_face.o
	g++ test_main.cpp *.o -D CALIBRATE=1 -o $@ $(CFLAGS)

test_main: test_main.cpp one_face.o
	g++ test_main.cpp *.o -D CALIBRATE=0 -o $@ $(CFLAGS)

one_face.o: one_face.cpp face_finder.o face_affine.o face_colors.o
	g++ one_face.cpp -c $(CFLAGS)

face_finder.o: face_finder.cpp
	g++ face_finder.cpp -c $(CFLAGS)

face_affine.o: face_affine.cpp
	g++ face_affine.cpp -c $(CFLAGS)

face_colors.o: face_colors.cpp
	g++ face_colors.cpp -c $(CFLAGS)

RubiksCube.o: ../Shared/RubiksCube.cpp ../Shared/RubiksCube.h
	g++ ../Shared/RubiksCube.cpp -c $(CFLAGS)

FORCE:

clean:
	rm -f *.o
