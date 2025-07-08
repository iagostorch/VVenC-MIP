/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   storchmain.h
 * Author: iagostorch
 *
 * Created on 2 de Julho de 2025, 17:02
 */

#ifndef STORCHMAIN_H
#define STORCHMAIN_H 1

#include <time.h>
#include <sys/time.h>
#include <string>
#include <fstream>
#include <string>

#include "Picture.h"
#include "CommonDef.h"

typedef enum
{
  ORIGINAL,
  RECONSTRUCTED
} SamplesType;

class storch{
  public:
    storch();
    
    static int sTRACE_xCompressCU;
    static int sEXTRACT_frames;
    
    static void startIntraRmd();
    static void finishIntraRmd();
    static void startIntraRmdMip();
    static void finishIntraRmdMip();
    static void startIntraRdo();
    static void finishIntraRdo();
    
    static void reportTime();
    
    static void exportSamplesFrame(vvenc::Picture* pic, SamplesType t);
    
  
  private:
    static struct timeval rmd1, rmd2, rmdMip1, rmdMip2, rdo1, rdo2;
    static double rmdTime, rmdMipTime, rdoTime;
  
  
};


#endif /* STORCHMAIN_H */
