# variable WORKSPACE needs to be set within process specific Makefile with trailing /

BINDIR=$(WORKSPACE)bin
OBJDIR=obj
SRCDIR=$(WORKSPACE)src

# compile settings
GCC=g++
GCCOPTS=-Wall -O0

