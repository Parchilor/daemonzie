include $(ROOT)/config.$(OSTYPE).mk

OBJS=$(patsubst %.c,%.o,$(wildcard *.c))
MAIN_OBJS = main.o

all:$(BINARYDIR)/main $(MAIN_OBJS)
$(BINARYDIR)/main:$(MAIN_OBJS)
	$(CROSS_COMPILER)$(LD) -o $(BINARYDIR)/main $(MAIN_OBJS) $(LDFLAGS)
	
#main.o:main.c
#	$(CROSS_COMPILER)$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)
.PHONY:clean
