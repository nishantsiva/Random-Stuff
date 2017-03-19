#include <stdio.h>
#include <stdlib.h>
#include <tiffio.h>
#include <math.h>
#include <omp.h>

#ifdef OPENMP
	#define N_THREADS 10
#else
	#define N_THREADS 0
#endif

#define MAX(a,b) ((a)>(b))?(a):(b)
#define MIN(a,b) ((a)<(b))?(a):(b)

int compare (const void * p1, const void * p2)
{
	return ( *(uint8*)p1 - *(uint8*)p2 );
}

uint8 getMeadian(uint8* imageArr, uint8* nborArr, int halfWidth, int x, int y, int h, int w, int spx){
	int imin, imax, jmin, jmax;
	int i, j, iter;
	
	omp_set_num_threads(N_THREADS);
	imin = MAX(x-halfWidth, 0);
	imax = MIN(x+halfWidth, h-1);
	jmin = MAX(y-(halfWidth*spx), y%spx);
	jmax = MIN(y+(halfWidth*spx), w*spx-1);

	iter = 0;
	for (i = imin; i <= imax; i += 1) {
		for (j = jmin; j <= jmax; j += spx, iter += 1) {
			nborArr[iter] = imageArr[i*w*spx + j];
		}
	}
	qsort (nborArr, iter, sizeof(uint8), compare);
	return nborArr[iter/2];
}

void medianFilter(uint8* imageArr, int hieght, int width, int spx, int halfWidth){
	uint8 *outImage;
	int x, y, chunk = 100;
	int nborSize;
	
	nborSize = 2 * halfWidth + 1;
	nborSize *= nborSize;
	outImage = (uint8*)malloc(sizeof(uint8) * hieght * width * spx);
	
	omp_set_num_threads(N_THREADS);
	const double startTime = omp_get_wtime();
	
	#pragma omp parallel for \
	shared(outImage, hieght, width, halfWidth, spx) \
	private(x, y)
	for (x = 0; x < hieght; x += 1) {
		for (y = 0; y < width*spx; y += spx) {
			uint8* nborArr = (uint8*)malloc(sizeof(uint8) * nborSize);
			outImage[x*width*spx + y] = \
				getMeadian(imageArr, nborArr, halfWidth, x, y, hieght, width, spx);
			if(spx == 1) continue;
			outImage[x*width*spx + y+1] = \
				getMeadian(imageArr, nborArr, halfWidth, x, y+1, hieght, width, spx);
			if(spx == 2) continue;
			outImage[x*width*spx + y+2] = \
				getMeadian(imageArr, nborArr, halfWidth, x, y+2, hieght, width, spx);
			free(nborArr);
		}
	}
	
	#pragma omp parallel for \
	shared(imageArr, outImage, hieght, width, spx) \
	private(x)
	for (x = 0; x < hieght*width*spx; x += spx) {
		imageArr[x] = outImage[x];
		if(spx == 1) continue;
		imageArr[x+1] = outImage[x+1];
		if(spx == 2) continue;
		imageArr[x+2] = outImage[x+2];
	}
	const double endTime = omp_get_wtime();
    printf("Duration = %lf\n", (endTime - startTime));
}

int main (int argc, char *argv[]) {
	tdata_t buf;
	uint32 row, col, h, w, bps, splPerPx;
	uint32 pMetric, rPerStrip, plConfic, orient;
	uint8 *imgArr, *ptr;
	char outFile[100];
	char ext[25] = "_medianFiltered.tiff";
	int i, j, halfWidth;
	
	if(argc < 2){
		printf("Ussage :\n\t./a.out [input image file name] [halfWidth(default = 3)]\n");
		return 0;
	}
	
	TIFF* tif = TIFFOpen(argv[1],"r");
	
	if(tif){
		
		TIFFGetField(tif, TIFFTAG_IMAGELENGTH, &h);
        TIFFGetField(tif, TIFFTAG_IMAGEWIDTH, &w);
        TIFFGetField(tif, TIFFTAG_BITSPERSAMPLE, &bps);
        TIFFGetField(tif, TIFFTAG_PHOTOMETRIC, &pMetric);
        TIFFGetField(tif, TIFFTAG_SAMPLESPERPIXEL, &splPerPx);
        TIFFGetField(tif, TIFFTAG_ROWSPERSTRIP, &rPerStrip);
        TIFFGetField(tif, TIFFTAG_PLANARCONFIG, &plConfic);
        TIFFGetField(tif, TIFFTAG_ORIENTATION, &orient);    
        
        for (i = 0; argv[1][i] != '\0'; i += 1) outFile[i] = argv[1][i];
		for (i--; outFile[i] != '.'; i -= 1);
	
		if(argc > 2) halfWidth = atoi(argv[2]);
		else halfWidth = 3;
		
		sprintf(ext, "_medianFiltered_%d.tiff", halfWidth);
		
		for (j = 0; ext[j] != '\0'; j += 1) outFile[i++] = ext[j];
		outFile[i] = '\0';    
		
		TIFF* tif_out = TIFFOpen(outFile,"w");
		
		if(tif_out) {
		   	
		    TIFFSetField(tif_out, TIFFTAG_IMAGELENGTH, h);
		    TIFFSetField(tif_out, TIFFTAG_IMAGEWIDTH, w);
		    TIFFSetField(tif_out, TIFFTAG_BITSPERSAMPLE, bps);
		    TIFFSetField(tif_out, TIFFTAG_PHOTOMETRIC, pMetric);
		    TIFFSetField(tif_out, TIFFTAG_SAMPLESPERPIXEL,splPerPx);
		    TIFFSetField(tif_out, TIFFTAG_PLANARCONFIG, plConfic);
		    TIFFSetField(tif_out, TIFFTAG_ORIENTATION, ORIENTATION_TOPLEFT);
		    
		    buf = _TIFFmalloc(TIFFScanlineSize(tif));
		    imgArr = (uint8*)malloc(sizeof(uint8) * h * w * splPerPx);
		    
		    for (row = 0; row < h; row++)
		    {
		        TIFFReadScanline(tif, buf, row,0);
		        ptr = (uint8*)buf;
		        for(col = 0; col < w * splPerPx; col+=1){
		        	imgArr[row*w*splPerPx + col] = ptr[col];
		        }
			}
	
			printf("Half Width = %d\n", halfWidth);
			medianFilter(imgArr, h, w, splPerPx, halfWidth);
		
			for (row = 0; row < h; row += 1) {
				for (col = 0; col < w*splPerPx; col += 1) {
					ptr[col] = imgArr[row*w*splPerPx + col];
				}
				buf = (uint32*)ptr;
		        TIFFWriteScanline(tif_out, buf, row,0);
			}
			free(imgArr);
			_TIFFfree(buf);
			TIFFClose(tif_out);
		}
        TIFFClose(tif);
        
			
	}
	return 0;
}
