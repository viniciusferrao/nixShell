# Universidade Federal do Rio de Janeiro
# Escola Politecnica
# Departamento de Eletronica e de Computacao
# Prof. Simone Markenson
# Linguagens de Programa��o - Turma 2009/2
# Author: Vin�cius Figueiredo Ferr�o
# Description: Default Makefile

CC = g++ #Compiler
LD = g++ #Link-editor

CFLAGS = -march=nocona -O2 -pipe -Wall -c
LFLAGS = -Wall -o

# Executables
EXECS = shell 

# Objects
OBJSHELL = shell.o environment.o parse.o

# Librarys
#LIBNCURSES = -lncurses
#LIBCRYPT = -lcrypt

# Rules
.cpp.o:
	$(CC) $(CFLAGS) $<

all: $(EXECS)

shell: $(OBJSHELL)
	$(LD) $(LFLAGS) $@ $(OBJSHELL) 

clean:
	rm -f *.o
	rm -f *.c~
	rm -f *.h~
	rm -f *.html~
	rm -f *.exe*
