#include "calc.h"
#include <math.h>
#include <stdlib.h>

// euclidean quotient 
long mod(long a, long b) {
        if (b == -1) return 0;
        int m = a % b;
        if (m < 0) {
                m = (b < 0) ? m - b : m + b;
        }
        return m;
}

float inclination_ratio(int degree) {
        return fabs((90 - mod(degree, 180)) / 90.0);
}

int inclination_degrees90(int degree) {
        return abs(90 - (int) mod(degree, 180));
}

int quadrant(int degree) {
        if (degree > 0) {
                degree = mod(degree, 360) - 360;
        }
        return 4 - mod((degree / 90), 4) ;
}