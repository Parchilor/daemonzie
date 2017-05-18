ifeq ($(shell uname -s), Linux)
export OSTYPE = linux
endif

ifeq ($(OSTYPE),linux)
export ROOT = $(shell pwd)
include $(ROOT)/config.$(OSTYPE).mk
export BINARYDIR = $(ROOT)/$(OUTPUTDIR)/bin
export LIBRARYDIR = $(ROOT)/$(OUTPUTDIR)/lib
export INCLUDEDIR = $(ROOT)/$(OUTPUTDIR)/include
all:
	mkdir -p $(BINARYDIR) $(LIBRARYDIR) $(INCLUDEDIR)
	@for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir; \
	done
.PHONY:all
clean:
	@for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir clean; \
	done
	$(RM) -r $(OUTPUTDIR)
.PHONY: clean
endif
