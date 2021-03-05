/*
 * Random.h
 *
 *  Created on: Feb 27, 2014
 *      Author: root
 */

#ifndef RANDOM_H_
#define RANDOM_H_
#include <stdint.h>

namespace cgl {

class Random {
    static void seed();
    static bool ranOnce;

public:
    //float in [0,1)
    static float frand();

    //double in [0,1)
    static double drand();

    //int in [0, max)
    static uint32_t rand(uint32_t max);


};



}



#endif /* RANDOM_H_ */
