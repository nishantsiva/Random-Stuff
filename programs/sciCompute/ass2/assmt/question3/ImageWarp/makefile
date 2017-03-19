all: imageWarp_linear imageWarp_parallel

imageWarp_linear: imageWarp.c
	gcc -o imageWarp_linear -fopenmp imageWarp.c -lm -ltiff 

imageWarp_parallel: imageWarp.c
	gcc -o imageWarp_parallel -fopenmp imageWarp.c -lm -ltiff -DOPENMP

clean:
	rm imageWarp_linear imageWarp_parallel
