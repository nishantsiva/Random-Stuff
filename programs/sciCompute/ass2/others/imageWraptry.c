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

void imageWrap(uint8* imageArr, int hieght, int width, int spx){
	uint8 *outR, *outG, *outB, *inR, *inG, *inB;
	int x, y, xnew, ynew, cx, cy;
	float radius, theta, PI = 3.141527f, DRAD = 180.0f / PI;
	
	outR = (uint8*)calloc(sizeof(uint8), hieght *width);
	outG = (uint8*)calloc(sizeof(uint8), hieght *width);
	outB = (uint8*)calloc(sizeof(uint8), hieght *width);
	inR  = (uint8*)calloc(sizeof(uint8), hieght *width);
	inG  = (uint8*)calloc(sizeof(uint8), hieght *width);
	inB  = (uint8*)calloc(sizeof(uint8), hieght *width);

	omp_set_num_threads(N_THREADS);
	const double startTime = omp_get_wtime();
#pragma omp parallel for \
shared(imageArr, inR, inG, inB, hieght, width, spx) \
private(x, y)
	for(x = 0; x < hieght; x += 1) {
		for (y = 0; y < width; y += 1) {
			inR[x*width + y] = TIFFGetR(imageArr[x*width*spx + y*spx]);
			inG[x*width + y] = TIFFGetG(imageArr[x*width*spx + y*spx]);
			inB[x*width + y] = TIFFGetB(imageArr[x*width*spx + y*spx]);
		}
	}
	
	cx = hieght / 2;
	cy = width / 2;
	
#pragma omp parallel for \
shared(outR, outG, outB, inR, inG, inB, hieght, width, cx, cy) \
private(x, y, radius, theta, xnew, ynew)
	for (x = 0; x < hieght; x += 1) {
		for (y = 0; y < width; y += 1) {
			radius = sqrt(pow(x - cx,2) + pow(y - cy,2));
			theta = -radius / 6666 * DRAD;
			
			xnew = cos(theta) * (x - cx) - sin(theta) * (y - cy) + cx;
			ynew = sin(theta) * (x - cx) + cos(theta) * (y - cy) + cy;
			
			if(xnew < 0 || xnew > hieght || ynew < 0 || ynew > width) {
				continue;
			}
			
			outR[x*width + y] = inR[xnew*width + ynew];
			outG[x*width + y] = inG[xnew*width + ynew];
			outB[x*width + y] = inB[xnew*width + ynew];
		}
	}
#pragma omp parallel for \
shared(outR, outG, outB, imageArr, hieght, width, spx) \
private(x, y)
	for(x = 0; x < hieght; x += 1) {
		for (y = 0; y < width; y += 1) {
			imageArr[x*width*spx + y*spx] 		= outR[x*width + y];
			imageArr[x*width*spx + y*spx + 1] 	= outG[x*width + y];
			imageArr[x*width*spx + y*spx + 2] 	= outB[x*width + y];
		}
	}
	const double endTime = omp_get_wtime();
 
    printf("Duration = %lf\n", (endTime - startTime));
    free(outR);
	free(outG);
	free(outB);
	free(inR);
	free(inG);
	free(inB);
}

int main (int argc, char *argv[]) {
	tdata_t buf;
	uint32 row,col;
	TIFF* tif = TIFFOpen("VenusTransitIngress_stand.1Kx1K.00001.tif","r");
	TIFF* tif_out = TIFFOpen("4.2.07_edit.tiff","w");
	if(tif){
		uint32 h, w;
		uint32 bps, compres, pMetric, splPerPx, rPerStrip, plConfic, rsltnUnit, orient;
		uint8 *imgArr;
		uint8 *ptr;
		
		TIFFGetField(tif, TIFFTAG_IMAGELENGTH, &h);
        TIFFGetField(tif, TIFFTAG_IMAGEWIDTH, &w);
        
        TIFFGetField(tif, TIFFTAG_BITSPERSAMPLE, &bps);
        TIFFGetField(tif, TIFFTAG_COMPRESSION, &compres);
        TIFFGetField(tif, TIFFTAG_PHOTOMETRIC, &pMetric);
        TIFFGetField(tif, TIFFTAG_SAMPLESPERPIXEL, &splPerPx);
        TIFFGetField(tif, TIFFTAG_ROWSPERSTRIP, &rPerStrip);
        TIFFGetField(tif, TIFFTAG_PLANARCONFIG, &plConfic);
        TIFFGetField(tif, TIFFTAG_RESOLUTIONUNIT, &rsltnUnit);
        TIFFGetField(tif, TIFFTAG_ORIENTATION, &orient);        

        TIFFSetField(tif_out, TIFFTAG_IMAGEWIDTH, w);
        TIFFSetField(tif_out, TIFFTAG_IMAGELENGTH, h);
        TIFFSetField(tif_out, TIFFTAG_BITSPERSAMPLE, bps);
        TIFFSetField(tif_out, TIFFTAG_PHOTOMETRIC, pMetric);
        TIFFSetField(tif_out, TIFFTAG_SAMPLESPERPIXEL,splPerPx);
        TIFFSetField(tif_out, TIFFTAG_ORIENTATION, ORIENTATION_TOPLEFT);
        TIFFSetField(tif_out, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);
        
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
		imageWrap(imgArr, h, w,splPerPx);
		for (row = 0; row < h; row += 1) {
			for (col = 0; col < w*splPerPx; col += 1) {
				ptr[col] = imgArr[row*w*splPerPx + col];
			}
			buf = (uint32*)ptr;
            TIFFWriteScanline(tif_out, buf, row,0);
		}
		_TIFFfree(buf);
        TIFFClose(tif);
        TIFFClose(tif_out);
			
	}
	return 0;
}
