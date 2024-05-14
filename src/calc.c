#include "calc.h"
#include <math.h>
#include <stdlib.h>

float inclination(int degree) {
        return fabs((90 - abs(degree % 180)) / 90.0);
}

int quadrant(int degree) {
        if (degree > 0) {
                degree -= 360;
        }
        return 4 - mod((degree / 90), 4) ;
}

// euclidean quotient 
long mod(long a, long b) {
        if (b == -1) return 0;
        int m = a % b;
        if (m < 0) {
                m = (b < 0) ? m - b : m + b;
        }
        return m;
}
