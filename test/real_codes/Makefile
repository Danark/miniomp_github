.SUFFIXES: -omp -domp -gomp -dgomp -asm -gasm -sec
CC = gcc
OPENMP	 = -fopenmp
CFLAGS   = -Wall -O -std=c99 -march=native -I.
CLIBS    = -L$(MINIOMP)/lib -lminiomp

.c-asm: 
	$(CC) $(CFLAGS) $(OPENMP) -c -S $< -o $@ $(CLIBS)

.c-gasm:
	$(CC) $(CFLAGS) $(OPENMP) -c -S $< -o $@

.c-omp: 
	$(CC) $(CFLAGS) $(OPENMP) $< -o $@ $(CLIBS) 

.c-gomp: 
	$(CC) $(CFLAGS) $(OPENMP) $< -o $@ 

.c-sec: 
	$(CC) $(CFLAGS) $< -o $@ 


.c-domp: 
	$(CC) -D_DISPLAY_ $(CFLAGS) $(OPENMP) $< -o $@ $(CLIBS) -lX11 -L/usr/X11R6/lib

.c-dgomp: 
	$(CC) -D_DISPLAY_ $(CFLAGS) $(OPENMP) $< -o $@ -lX11 -L/usr/X11R6/lib

clean:
	rm -rf *-omp *-gomp *-asm *-domp *-dgomp

ultraclean:
	rm -rf *-omp *-gomp *-asm *-domp *-dgomp *.prv *.pcf *.row *.dim *.trf *-gasm TRACE.mpits set-0
