#sample makefile to generate strcmp.so alias.so version.so shared object files
CC=g++ 
CFLAGS=-shared -fPIC -o

all:strcmp.so alias.so version.so

alias.so : c_alias_unalias.cc
	$(CC) $(CFLAGS) alias.so c_alias_unalias.cc

strcmp.so : c_strcmp.cc
	$(CC) $(CFLAGS) strcmp.so c_strcmp.cc

version.so : c_version.cc
	$(CC) $(CFLAGS) version.so c_version.cc








 
	
