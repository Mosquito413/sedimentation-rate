# meine
PROCESSES=main
BUILDTARGETS=$(addsuffix .build,$(PROCESSES))
CLEANTARGETS=$(addsuffix .clean,$(PROCESSES))

all: $(BUILDTARGETS)

%.build: %/
	make -C $<

# .PHONY: clean $(CLEANTARGETS) $(BUILDTARGETS)
clean: $(CLEANTARGETS)
%.clean: %/
	make -C $< clean
