/********************************************************************\

  Name:         adc.c
  Created by:   Stephen Jones
  Modified by:  Retief Neveling

\********************************************************************/


/*-- Include files -------------------------------------------------*/

/* standard includes */
#include <stdio.h>
#include <time.h>

/* midas includes */
#include "midas.h"
#include "experim.h"
#include <math.h>

/* root includes */
#include <TH1F.h>
#include <TH2F.h>
#include <TTree.h>
//#include <TMath.h>


// defined in Parameters.c
extern float *ADC;
extern int ADCModules;
extern int ADCsize;
extern double *ADCOffsets, *ADCGains;

/*-- variables to be used in f-plane.c as extern variables----------*/
//float ADC[128];
int adcevtcount;


/*-- For ODB: from /Analyzer/Parameters/----------------------------*/
ADC_PARAM adc_param;


/*-- Module declaration --------------------------------------------*/
INT adc_event(EVENT_HEADER *, void *);
INT adc_init(void);
INT adc_bor(INT run_number);
INT adc_eor(INT run_number);

ADC_PARAM_STR(adc_param_str);

ANA_MODULE adc_module = {
   "ADC",                       /* module name           */
   "Retief Neveling",           /* author                */
   adc_event,                   /* event routine         */
   adc_bor,                     /* BOR routine           */
   adc_eor,                     /* EOR routine           */
   adc_init,                    /* init routine          */
   NULL,                        /* exit routine          */
   &adc_param,                  /* parameter structure   */
   sizeof(adc_param),           /* structure size        */
   adc_param_str,               /* initial parameters    */
};


/*--------------------------------------------------------------------------*/
#define H1I_BOOK(n,t,b,min,max) (h1_book<TH1I>(n,t,b,min,max))
#define H2I_BOOK(n,t,xb,xmin,xmax,yb,ymin,ymax) (h2_book<TH2I>(n,t,xb,xmin,xmax,yb,ymin,ymax))

/*------------Declarations of predefined Constants ----------------*/
const int ADC_N_BINS = 4096;
const int ADC_X_LOW  = 0;
const int ADC_X_HIGH = 4095;
extern EXP_PARAM exp_param;
extern RUNINFO runinfo;

/*-- Histogramming Data Structures ----------------------------------------*/
static TH2F *hADC2DModule[5];

/*-- init routine --------------------------------------------------*/
INT adc_init(void)
{
   char name[256];
   char title[256];
   int i;
   
   for(int counter=0;counter<5;counter++){
	  sprintf(name,"hADC2DModule%d",counter);
	  sprintf(title,"hADC2DModule %d ",counter);
          hADC2DModule[counter]=H2_BOOK(name,title,4096,0,4096,32,0,32);
   }

   return SUCCESS;
}


/*-- BOR routine ---------------------------------------------------*/

INT adc_bor(INT run_number)
{
   return SUCCESS;
}



/*-- eor routine ---------------------------------------------------*/
INT adc_eor(INT run_number)
{
   return SUCCESS;
}

  enum v792N_DataType {
    v792N_typeMeasurement=0,
    v792N_typeHeader     =2,
    v792N_typeFooter     =4,
    v792N_typeFiller     =6
  };

  typedef union {
    DWORD raw;
    struct EntryN {
      unsigned adc:12; // bit0 here
      unsigned ov:1;
      unsigned un:1;
      unsigned _pad_1:2;
      unsigned channel:5;
      unsigned _pad_2:3;
      unsigned type:3;
      unsigned geo:5;
    } data ;
    struct HeaderN {
      unsigned _pad_1:8; // bit0 here
      unsigned cnt:6;
      unsigned _pad_2:2;
      unsigned crate:8;
      unsigned type:3;
      unsigned geo:5;
    } header;
    struct FooterN {
      unsigned evtCnt:24; // bit0 here
      unsigned type:3;
      unsigned geo:5;
    } footer;
  } v792N_Data; 


/*-- event routine -------------------------------------------------*/
INT adc_event(EVENT_HEADER * pheader, void *pevent)
{
   INT i, nwords;
   DWORD *padc;
   float *adc = new float[32*ADCModules];  
//    printf("adc initialisation: %d\n",32*ADCModules);
   int adcchan,adcnr;
   extern int adc_counter1, adc_counter2;   // defined; declared in analyzer.c
 	
   /* look for ADC0 bank, return if not present */
   nwords=bk_locate(pevent, "ADC0", &padc);
   adc_counter1++;
   if (nwords==0){
      adc_counter2++;
      return 1;
   }
//     printf("adc.c: L185\n");     
   for (i = 0; i < nwords; i++){
        //printf("-------raw data 0x%08x  Nr of words %d \n",padc[i],nwords); 
        if(((padc[i]>>24)&0xff) ==0xfd) {
           if((padc[i]&0xf) ==0) adcnr=0;  //printf(" adc nr 0 \n");}
           if((padc[i]&0xf) ==1) adcnr=1; // printf(" adc nr 1 \n");}
           if((padc[i]&0xf) ==2) adcnr=2;  //printf(" adc nr 2 \n");} 
           if((padc[i]&0xf) ==3) adcnr=3; // printf(" adc nr 3 \n");}
           if((padc[i]&0xf) ==4) adcnr=4;  //printf(" adc nr 4 \n");}
	   //printf("-----raw data 0x%08x ->  data %d adcnr %i \n",padc[i],(padc[i]&0x0fff),adcnr); 
	}
	if(((padc[i]>>24)&0x7) ==0){     // if not then they are not data but header words.
	    adcchan=((padc[i])>>16)&0x1f;
            adcchan=adcchan + adcnr*32;
      	    adc[adcchan] =(float)(padc[i]&0x0fff);
            //printf("raw data 0x%08x -> chan %d data %d adcnr %i words %d \n",padc[i],adcchan,(padc[i]&0x0fff),adcnr,nwords);

            /* fill basic ADC histos */
            if(adcchan<32) {
		hADC2DModule[0]->Fill(adc[adcchan],adcchan);
	    }  
            else if(adcchan<64) {
		hADC2DModule[1]->Fill(adc[adcchan],adcchan-32);
	    }
            else if(adcchan<96) {
		hADC2DModule[2]->Fill(adc[adcchan],adcchan-64);
	    }
            else if(adcchan<128) {
		hADC2DModule[3]->Fill(adc[adcchan],adcchan-96);
	    }
            else if(adcchan<160) hADC2DModule[4]->Fill(adc[adcchan],adcchan-128);  
	}

   }
   //adcevtcount=padc[33]&0xfffff;  // take event counter in the trailer, the 34th word, to 
  				    // f-plane to compare to TDC counter 
   for(i=0; i<ADCsize;i++){
       ADC[i] = 0;		    // Clear out the ADC values - should always be resetting the values because 
				    // we have pedestals but it's worth being proper about it.
       if (adc[i] > 0.0) {  
	   ADC[i]=adc[i];                 // if ( adc[i] > (float) adc_param.histogram_threshold )
       }      
   }  

//   printf("Got to SUCCESS in adc.c\n");
   return SUCCESS;
}





