# meine
WORKSPACE=../
include ../common.mk

# gehe einen ordner hoch und dann in ordner bin
# Processpath ../bin/main
PROCESSNAME=main
PROCESSPATH=$(BINDIR)/$(PROCESSNAME)

# extend GCCOPTS
GCCOPTS += -g --std=c++11


all: dircheck $(PROCESSPATH)
.PHONY: dircheck 
dircheck:  $(OBJDIR) $(BINDIR) 

# $@: The filename representing the target
# g++ -Wall -O0 -g --std=c++11 -o ../bin/main obj/main.o
$(PROCESSPATH): $(OBJDIR)/main.o 
	$(GCC) $(GCCOPTS) -o $@ $^ 

# erstellt Obejektdateien
# -c flag generates the .o files
# g++ -Wall -O0 -g --std=c++11 -c  ../src/main.cpp -o obj/main.o
$(OBJDIR)/main.o: $(SRCDIR)/main.cpp
	$(GCC) $(GCCOPTS) -c $< -o $@


# Erstellt die Ordner obj und ../bin falls nicht vorhanden
$(BINDIR):
	mkdir $@
$(OBJDIR):
	mkdir $@


clean:
	-rm -r $(OBJDIR) $(PROCESSPATH)



