#Author: Carlos Carrillo
#Date:   10/27/2015
#Description: This is the makefile for Lab_5

#This target will compile the entire program
All: total

total:	encryption.o  
	g++ encryption.o -o encryption

gameOfLife.o: encryption.cpp
	g++ -c encryption.cpp

clean:
	rm -rf *o total