#include <stdio.h>
#include <stdlib.h>
#include<math.h>
#include<omp.h>
#include <tiffio.h>

#define number_of_threads 4

void process(uint8* img,int size)
{
	int mean_R=0,mean_G=0,mean_B=0,sigma_R=0,sigma_G=0,sigma_B=0;
	double start;
	start=omp_get_wtime();
	omp_set_num_threads(number_of_threads);
	//#pragma parallel omp for schedule(auto)
	#pragma parallel omp for reduction(+:mean_R,mean_G,mean_B) schedule(dynamic)
	{
		int i;
		for(i=0;i<size;i=i+3) mean_R+=img[i];
		for(i=0;i<size-1;i=i+3) mean_G+=img[i+1];
		for(i=0;i<size-2;i=i+3) mean_B+=img[i+2];
	}

	printf("Time Taken for Finding Mean:%f\n",omp_get_wtime()-start);
	mean_R=(int)mean_R/(int)(size/3);
	mean_G=(int)mean_G/(int)(size/3);
	mean_B=(int)mean_B/(int)(size/3);
	printf("Mean R:%d Mean G:%d Mean B:%d\n",mean_R,mean_G,mean_B);
	start=omp_get_wtime();
	#pragma parallel omp for reduction(+:sigma_R,sigma_G,sigma_B) schedule(dynamic)
	{
		int i;
		for(i=0;i<size;i=i+3) sigma_R+=(img[i]-mean_R)*(img[i]-mean_R);
		for(i=0;i<size-1;i=i+3) sigma_G+=(img[i+1]-mean_G)*(img[i+1]-mean_G);
		for(i=0;i<size-2;i=i+3) sigma_B+=(img[i+2]-mean_B)*(img[i+2]-mean_B);
	}
	printf("Time Taken for Finding Standard Deviation:%f\n",omp_get_wtime()-start);
	sigma_R=sqrt(sigma_R/((size)/3));
	sigma_G=sqrt(sigma_G/((size)/3));
	sigma_B=sqrt(sigma_B/((size)/3));
	printf("STD R:%d STD G:%d STD B:%d\n",sigma_R,sigma_G,sigma_B);
	start=omp_get_wtime();
	#pragma parallel omp for schedule(dynamic)
	{
		int i;
		for(i=0;i<size;i=i+3) img[i]=(img[i]-mean_R)/sigma_R;
		for(i=0;i<size-1;i=i+3) img[i+1]=(img[i+1]-mean_G)/sigma_G;
		for(i=0;i<size-2;i=i+3) img[i+2]=(img[i+2]-mean_B)/sigma_B;
	}
	printf("Time Taken for normalizing Pixels :%f\n",omp_get_wtime()-start);

}


int main()
{
int size;
TIFF* tif = TIFFOpen("4.2.07.tiff","r");
TIFF* tif_edit = TIFFOpen("4.2.07_normalized.tiff","w");
    if (tif) {
		    uint32  h,w,bps,cp,pRGB,spp;
		    uint32 rps,pcc,run,otl;
		    uint8* data;
		    tdata_t buf;
		    uint32 row;
		    uint32 col;
		    TIFFGetField(tif, TIFFTAG_IMAGELENGTH, &h);
		    TIFFGetField(tif, TIFFTAG_IMAGEWIDTH, &w);
		    
		    TIFFGetField(tif, TIFFTAG_BITSPERSAMPLE, &bps);
		    TIFFGetField(tif, TIFFTAG_COMPRESSION, &cp);
		    TIFFGetField(tif, TIFFTAG_PHOTOMETRIC, &pRGB);
		    TIFFGetField(tif, TIFFTAG_SAMPLESPERPIXEL, &spp);
		    TIFFGetField(tif, TIFFTAG_ROWSPERSTRIP, &rps);
		    TIFFGetField(tif, TIFFTAG_PLANARCONFIG, &pcc);
		    TIFFGetField(tif, TIFFTAG_RESOLUTIONUNIT, &run);
		    TIFFGetField(tif, TIFFTAG_ORIENTATION, &otl);        

		    
		    TIFFSetField(tif_edit, TIFFTAG_IMAGEWIDTH, w);
		    TIFFSetField(tif_edit, TIFFTAG_IMAGELENGTH, h);
		    TIFFSetField(tif_edit, TIFFTAG_BITSPERSAMPLE, bps);
		    TIFFSetField(tif_edit, TIFFTAG_PHOTOMETRIC, pRGB);
		    TIFFSetField(tif_edit, TIFFTAG_SAMPLESPERPIXEL,spp);
		    TIFFSetField(tif_edit, TIFFTAG_ORIENTATION, ORIENTATION_TOPLEFT);
		    TIFFSetField(tif_edit, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);
		    
		    size=h*w*spp;
		    printf("BITs/Pixel: %d\n",bps);
		    printf("Total Size of Array:%u\n",h*w*spp);
		    printf("H:%d W:%d\n spp:%d",h,w,spp);
		    uint8 *img;
		    img=(uint8*)malloc(sizeof(uint8)*h*w*spp);
		    buf = _TIFFmalloc(TIFFScanlineSize(tif));
		    printf("TIFFScanlineSize(tif):%d\n",TIFFScanlineSize(tif));
		    for (row = 0; row < h; row++)
		    {
		        TIFFReadScanline(tif, buf, row,0);
		        data=(uint8*)buf;
				for(col=0;col < w*spp; col++)
				{
					img[(row*w*spp)+col]=data[col];
				}
		    }
        
        
        process(img,size);
        
        
        for (row = 0; row < h; row++)
        {
			for(col=0;col < w*spp; col++)
			{
				data[col]=img[(row*(w*spp))+col];
			}
			buf=(uint32*)data;
			TIFFWriteScanline(tif_edit, buf, row,0);
        }
        _TIFFfree(buf);
        TIFFClose(tif);
        TIFFClose(tif_edit);
    }
    return 0;
}
