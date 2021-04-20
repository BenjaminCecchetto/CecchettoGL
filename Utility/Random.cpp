/*
 * Random.cpp
 *
 *  Created on: Feb 27, 2014
 *      Author: root
 */

#include "Random.h"

#include <stdlib.h>
#include <time.h>

namespace cgl {

bool Random::ranOnce = false;

float Random::frand() {
  seed();

  return static_cast<float>(drand());
}

double Random::drand() {
  seed();

  return drand();
}

uint32_t Random::rand(uint32_t max) {
  seed();

  return static_cast<uint32_t>(drand() * max);
}

void Random::seed() {
  if (!ranOnce) {
    srand(time(0));
    ranOnce = true;
  }
}

}  // namespace cgl
