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

//#define TRACE_xCompressCU 0

class storch{
  public:
    storch();
    
    static int sTRACE_xCompressCU;
    
    static void startIntraRmd();
    static void finishIntraRmd();
    static void startIntraRmdMip();
    static void finishIntraRmdMip();
    static void startIntraRdo();
    static void finishIntraRdo();
    
    static void reportTime();
    
    
    
  
  private:
    static struct timeval rmd1, rmd2, rmdMip1, rmdMip2, rdo1, rdo2;
    static double rmdTime, rmdMipTime, rdoTime;
  
  
};


#endif /* STORCHMAIN_H */
