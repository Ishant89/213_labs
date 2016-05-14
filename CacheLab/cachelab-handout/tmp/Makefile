#
# Student makefile for Cache Lab
# 
CC = gcc
CFLAGS = -g -Wall -Werror -std=c99

all: temp 

temp: temp.c temp.h 
	$(CC) $(CFLAGS) -o temp temp.c -lm 



#
# Clean the src dirctory
#
clean:
	rm -f temp 
