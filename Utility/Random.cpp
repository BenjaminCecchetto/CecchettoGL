/*
 * Random.cpp
 *
 *  Created on: Feb 27, 2014
 *      Author: root
 */

#include <stdlib.h>
#include <time.h>

#include "Random.h"

namespace cgl {

bool Random::ranOnce = false;

float Random::frand() {
    seed();

    return static_cast<float>(drand48());
}

double Random::drand() {
    seed();

    return drand48();
}

uint32_t Random::rand(uint32_t max) {
    seed();

    return static_cast<uint32_t>(drand48()*max);
}

void Random::seed() {
    if (!ranOnce) {
        srand48(time(0));
        ranOnce = true;
    }
}

}
