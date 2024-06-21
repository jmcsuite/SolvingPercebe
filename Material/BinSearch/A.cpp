// [L, R] , M -> etc.

// L, incremento. L + incremento ->
// Si cumple, L = L + incremento
// Si no cumple, incremento lo divido. 


int sqrt(long long x) {
    long long L = 0;
    long long incremento = x;
    while (incremento != 0) {
        long long intento = L + incremento;
        if (intento > x) {
            incremento /= 2;
            continue;
        }
        if (intento * intento > x) {
            incremento /= 2;
            continue;
        }

        // L + incremento es bueno
        L = intento;
    }
    return L;
}

int sqrt_2(long long x) {
    long long L = 0;
    long long incremento = x;
    while (incremento) {
        if (L + incremento <= x && (L+incremento)*(L+incremento) <= x) L += incremento;
        else incremento /= 2;
    }
    return L;
}
