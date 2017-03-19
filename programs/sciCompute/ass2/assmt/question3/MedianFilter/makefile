all: medianFilt_linear medianFilt_parallel

medianFilt_linear: medianFilt.c
	gcc -o medianFilt_linear -fopenmp medianFilt.c -lm -ltiff 

medianFilt_parallel: medianFilt.c
	gcc -o medianFilt_parallel -fopenmp medianFilt.c -lm -ltiff -DOPENMP

clean:
	rm medianFilt_linear medianFilt_parallel
