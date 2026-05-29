CC=gcc
FC=gfortran

CFLAGS=

CFILE=toBeDifferentiated.c
FFILE=toBeDifferentiated.f

COBJ=$(CFILE:.c=.o)

OUT=test

ctest: $(COBJ)
	$(CC) $(COBJ) -o c$(OUT)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

ftest:
	$(FC) $(FFILE) -o f$(OUT)

runc: c$(OUT)
	./c$(OUT)

runf: f$(OUT)
	./f$(OUT)

clean:
	rm -f $(COBJ) *$(OUT)

.PHONY: clean, runc, runf
