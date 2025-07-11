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


// Used to toggle export/import MIP costs. We can bypass the prediction by reading pre-computed costs 
#define EXPORT_MIP_COST 0
#define IMPORT_MIP_COST 0

#include <time.h>
#include <sys/time.h>
#include <string>
#include <fstream>
#include <unordered_map>
#include "Picture.h"
#include "CommonDef.h"
#include "TypeDef.h"


// Code to use tuples as keys in unordered_map, copied from
// https://stackoverflow.com/questions/20834838/using-tuple-in-unordered-map @ Leo Goodstadt
#include <tuple>
// function has to live in the std namespace 
// so that it is picked up by argument-dependent name lookup (ADL).
namespace std{
    namespace
    {

        // Code from boost
        // Reciprocal of the golden ratio helps spread entropy
        //     and handles duplicates.
        // See Mike Seymour in magic-numbers-in-boosthash-combine:
        //     https://stackoverflow.com/questions/4948780

        template <class T>
        inline void hash_combine(std::size_t& seed, T const& v)
        {
            seed ^= hash<T>()(v) + 0x9e3779b9 + (seed<<6) + (seed>>2);
        }

        // Recursive template code derived from Matthieu M.
        template <class Tuple, size_t Index = std::tuple_size<Tuple>::value - 1>
        struct HashValueImpl
        {
          static void apply(size_t& seed, Tuple const& tuple)
          {
            HashValueImpl<Tuple, Index-1>::apply(seed, tuple);
            hash_combine(seed, get<Index>(tuple));
          }
        };

        template <class Tuple>
        struct HashValueImpl<Tuple,0>
        {
          static void apply(size_t& seed, Tuple const& tuple)
          {
            hash_combine(seed, get<0>(tuple));
          }
        };
    }

    template <typename ... TT>
    struct hash<std::tuple<TT...>> 
    {
        size_t
        operator()(std::tuple<TT...> const& tt) const
        {                                              
            size_t seed = 0;                             
            HashValueImpl<std::tuple<TT...> >::apply(seed, tt);    
            return seed;                                 
        }                                              

    };
}

#define TRACE_initIntraPatternChType 0

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
    static int sGPU_alternativeRefsMIP;
    
    static void startIntraRmd();
    static void finishIntraRmd();
    static void startIntraRmdMip();
    static void finishIntraRmdMip();
    static void startIntraRdo();
    static void finishIntraRdo();
    
    static void addCuCost(vvenc::IdCU id, vvenc::Distortion dist);
        
    static void reportTime();
    
    static void exportSamplesFrame(vvenc::Picture* pic, SamplesType t);

    static void exportMipCosts();
    static void importMipCosts();
    static vvenc::Distortion getPrecomputedMipCost(int poc, int w, int h, int x, int y, int uiModeFull);
    
    
  
  private:
    static struct timeval rmd1, rmd2, rmdMip1, rmdMip2, rdo1, rdo2;
    static double rmdTime, rmdMipTime, rdoTime;
  
    static std::unordered_map<vvenc::IdCU, vvenc::Distortion> cuCostMap;
    
    static std::ofstream mipCostsFile;
    
};


#endif /* STORCHMAIN_H */
