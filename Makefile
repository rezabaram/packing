CFLAGS=-std=c++11 
CC=clang

pack: *.h main.cc
	@g++  -I/Users/reza/workstation/Eigen main.cc -o pack $(CFLAGS)

run: pack
	@./pack


plot: pack
	@./pack > coord.dat && coord2ps coord.dat > coord.ps && ps2pdf coord.ps && open coord.pdf
