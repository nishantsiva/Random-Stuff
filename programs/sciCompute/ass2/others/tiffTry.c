#include <stdio.h>
#include <stdlib.h>
#include <tiffio.h>
#include<math.h>

void normalize(uint8* imageArr, int size){
	int iter,_size;
	float meanR, meanG, meanB;
	float varR, varG, varB;
	float svarR, svarB, svarG;
	float stdR, stdB, stdG;
	
	_size = size / 3;
	meanR = meanG = meanB = 0.0;
	for (iter = 0; iter < size-2; iter += 3) {
		meanR += imageArr[iter];
		meanG += imageArr[iter + 1];
		meanB += imageArr[iter + 2];
	}
	
	meanR /= (float)_size;
	meanG /= (float)_size;
	meanB /= (float)_size;
	printf("%f %f %f %d\n",meanR,meanG,meanB,size);
	varR = varG = varB = 0.0;
	for (iter = 0; iter < size-2; iter += 3) {
		svarR = (float)(imageArr[iter]) - meanR;
		svarG = (float)(imageArr[iter + 1]) - meanG;
		svarB = (float)(imageArr[iter + 2]) - meanB;
		
		varR += svarR * svarR;
		varG += svarG * svarG;
		varB += svarB * svarB;
	}
	
	varR /= (float)_size;
	varG /= (float)_size;
	varB /= (float)_size;
	printf("%f %f %f %d\n",varR,varG,varB,size);
	stdR = sqrt(varR); stdG = sqrt(varG); stdB = sqrt(varB);
	
	for (iter = 0; iter < size-2; iter += 3) {
		imageArr[iter] 		= fabs(imageArr[iter] - meanR) / stdR;
		imageArr[iter + 1] 	= fabs(imageArr[iter + 1] - meanG) / stdG;
		imageArr[iter + 2] 	= fabs(imageArr[iter + 2] - meanB) / stdB;
		//printf("%d %d %d\n",imageArr[iter],imageArr[iter+1],imageArr[iter+2]);
	}
}

int main (int argc, char *argv[]) {
	tdata_t buf;
	uint32 row,col;
	TIFF* tif = TIFFOpen("4.2.07.tiff","r");
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
        printf("%d %d %d\n", w, splPerPx, (int)TIFFScanlineSize(tif));
        imgArr = (uint8*)malloc(sizeof(uint8) * h * w * splPerPx);
        
        for (row = 0; row < h; row++)
        {
            TIFFReadScanline(tif, buf, row,0);
            ptr = (uint8*)buf;
            for(col = 0; col < w * splPerPx; col+=1){
            	imgArr[row*w*splPerPx + col] = ptr[col];
            }
		}
		normalize(imgArr,h * w * splPerPx);
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
