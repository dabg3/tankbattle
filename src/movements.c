#include "movements.h"
#include <math.h>
#include <stdlib.h>

float inclination(int degree) {
        return fabs((90 - abs(degree % 180)) / 90.0);
}
