EXEC = controller
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
DEPS = $(SRCS:.c=.d)

all: $(EXEC)

$(DEPS): %.d: %.c %.h
	@echo "Generating dependency file $@"
	@set -e; rm -f $@
	@$(CC) $(ALL_CFLAGS) -M $(INCLUDEDIRS) $< > $@.tmp
	@sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.tmp > $@
	@rm -f $@.tmp

include $(DEPS)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f *.o *.d

clear: clean
	rm -f $(EXEC)
