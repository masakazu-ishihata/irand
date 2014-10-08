# Makefile
TAR = test
CC = gcc -O6 -Wall -g
L = -lm
SHAD = -fPIC -shared
SORC = irand.c mt19937ar.c gamma.c
OBJS = main.o irand.o mt19937ar.o gamma.o
LIB = libirand.so

all : $(TAR) lib
$(TAR): $(OBJS)
	  $(CC) -o $@ $(OBJS) $(L)
clean:
	  rm -f $(OBJS) $(TAR) $(LIB) *~ *.bak

.c.o:	  $(CC) -c $<
lib:
	$(CC) $(SHAD) -o $(LIB) $(SORC) $(L)

main.o: irand.h
irand.o: irand.h mt19937ar.o gamma.o
mt19937ar.o: mt19937ar.h
gamma.o: gamma.h
