
#
#Filename: makefile
#Auther: Brian Labrum, Benjamin Skeen
#last modified: 2/5/2015
#version: 1
#
#
# The first rule is the default

default:	inventory.cpp FoodItem.o warehouse.o
	g++ inventory.cpp FoodItem.o warehouse.o -lboost_date_time -std=c++0x

FoodItem.o: FoodItem.cpp FoodItem.h
	g++ -c FoodItem.cpp
	
warehouse.o: warehouse.cpp warehouse.h FoodItem.h
	g++ -c warehouse.cpp
	
debug:	inventory.cpp FoodItem_debug.o warehouse_debug.o
	g++ -g -o debug.o inventory.cpp FoodItem_debug.o warehouse_debug.o -lboost_date_time

warehouse_debug.o:	warehouse.cpp warehouse.h FoodItem.h
	g++ -g -c -o warehouse_debug.o warehouse.cpp

FoodItem_debug.o:	FoodItem.cpp FoodItem.h
	g++ -g -c -o FoodItem_debug.o FoodItem.cpp
clean:
	rm -f *.o *.out

