CC = gcc

CFLAGS   = -Wall -O -std=c99 -march=native -I. -D_GNU_SOURCE
CFLAGS_SO = -fPIC --shared -I$(EXTRAE_HOME)/include
CLIBS = -L$(EXTRAE_HOME)/lib -lomptrace
TARGETS  = libminiomp.so
all: $(TARGETS) 

libminiomp.so: libminiomp.h libminiomp.c env.c intrinsic.c parallel.c synchronization.c single.c loop.c task.c instrumentation.c
	$(CC) $(CFLAGS_SO) $(CFLAGS) $+ -o $(MINIOMP)/lib/$@ -lpthread $(CLIBS)

clean:
	rm -rf $(MINIOMP)/lib/$(TARGETS)
