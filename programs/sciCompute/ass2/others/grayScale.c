#include <stdio.h>
#include <stdlib.h>
#include <tiffio.h>

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
        TIFFSetField(tif_out, TIFFTAG_PHOTOMETRIC, 1);
        TIFFSetField(tif_out, TIFFTAG_SAMPLESPERPIXEL,1);
        TIFFSetField(tif_out, TIFFTAG_ORIENTATION, ORIENTATION_TOPLEFT);
        TIFFSetField(tif_out, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);
        
        buf = _TIFFmalloc(TIFFScanlineSize(tif));
        printf("%d %d %d\n", w, splPerPx, (int)TIFFScanlineSize(tif));
        imgArr = (uint8*)malloc(sizeof(uint8) * h * w);
        
        for (row = 0; row < h; row++)
        {
            TIFFReadScanline(tif, buf, row,0);
            ptr = (uint8*)buf;
            for(col = 0; col < h * splPerPx; col+=3){
            	imgArr[row*w + col/3] = 0.29*ptr[col] + ptr[col+1]*0.59 + ptr[col+2]*0.11;
            	
            }
		}
		
		for (row = 0; row < h; row += 1) {
			for (col = 0; col < w; col += 1) {
				ptr[col] = imgArr[row*w + col];
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
