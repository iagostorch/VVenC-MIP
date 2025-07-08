/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   storchmain.cpp
 * Author: iagostorch
 * 
 * Created on 2 de Julho de 2025, 17:02
 */

#include "storchmain.h"

// CUstom input parameters 

int storch::sTRACE_xCompressCU;
int storch::sEXTRACT_frames;
int storch::sGPU_alternativeRefsMIP;

double storch::rmdTime, storch::rmdMipTime, storch::rdoTime;

struct timeval storch::rmd1, storch::rmd2, storch::rmdMip1, storch::rmdMip2, storch::rdo1, storch::rdo2;

storch::storch(){
  storch::rmdTime = 0.0;
  storch::rmdMipTime = 0.0;
  storch::rdoTime = 0.0;
}

void storch::startIntraRmd(){
  gettimeofday(&rmd1, NULL);
}

void storch::finishIntraRmd(){
  gettimeofday(&rmd2, NULL);
  storch::rmdTime += (double) (storch::rmd2.tv_usec - storch::rmd1.tv_usec)/1000000 + (double) (storch::rmd2.tv_sec - storch::rmd1.tv_sec);
}

void storch::startIntraRmdMip(){
  gettimeofday(&rmdMip1, NULL);
}

void storch::finishIntraRmdMip(){
  gettimeofday(&rmdMip2, NULL);
  storch::rmdMipTime += (double) (storch::rmdMip2.tv_usec - storch::rmdMip1.tv_usec)/1000000 + (double) (storch::rmdMip2.tv_sec - storch::rmdMip1.tv_sec);
}

void storch::startIntraRdo(){
  gettimeofday(&rdo1, NULL);
}

void storch::finishIntraRdo(){
  gettimeofday(&rdo2, NULL);
  storch::rdoTime += (double) (storch::rdo2.tv_usec - storch::rdo1.tv_usec)/1000000 + (double) (storch::rdo2.tv_sec - storch::rdo1.tv_sec);
}

void storch::exportSamplesFrame(vvenc::Picture* pic, SamplesType t){
  
  std::ofstream fileHandle;
  std::string fileName;
          
  vvenc::CPelBuf samples;
  int poc = pic->getPOC();
  
  switch(t){
    case ORIGINAL:
      samples = pic->getOrigBuf(vvenc::COMP_Y);
      fileName = (std::string) "original_" + std::to_string(poc);
      fileHandle.open(fileName + ".csv");
      break;
    case RECONSTRUCTED:
      samples = pic->getRecoBuf(vvenc::COMP_Y);
      fileName = (std::string) "reconstructed_" + std::to_string(poc);
      fileHandle.open(fileName + ".csv");
      break;
    default:
      printf("ERROR: Incorrect SamplesType in exportSamplesFrame()\n");
      exit(0);
      break;
  }
  
  const int frameWidth = samples.width;
  const int frameHeight= samples.height;
  
  int w,h;
  for(h=0; h<frameHeight; h++){
    for(w=0; w<frameWidth-1; w++){
      fileHandle << samples.at(w,h) << ",";
    }
    fileHandle << samples.at(w,h) << std::endl;
  }
  fileHandle.close();
  
  
}

void storch::reportTime(){
  printf("\n\n\n");
  printf("-=-=-=-=-=- Custom trace -=-=-=-=-=-\n");
  printf("RMD Time:          %f\n", storch::rmdTime);
  printf("  RMD MIP Time:    %f\n", storch::rmdMipTime);
  printf("RDO Time:          %f\n", storch::rdoTime);
}
