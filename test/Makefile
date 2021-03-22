CFLAGS  = -Wall -g
LDFLAGS = -g
LDLIBS_CMOCKA = -lcmocka
LDFLAGS_CMOCKA = -Wl,--wrap=write -Wl,--wrap=read

all : test

test : test.o 
	$(LINK.o) $(LDFLAGS_CMOCKA) $^ $(LDLIBS) $(LDLIBS_CMOCKA) -o $@
test.o : test.c

.PHONY: test_mocka
test_mocka : test
	./test

.PHONY: clean
clean:
	rm -f test *.o  