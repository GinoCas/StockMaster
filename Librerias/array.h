#include <iostream>
#include <string.h>

using namespace std;

bool str_contiene(string array[], string elemento) {
    for(int i = 0; i<sizeof(array) / sizeof(int); i++) {
        if (array[i] == elemento) {
            return true;
        }
    }
    return false;
}

bool int_contiene(int array[], int elemento) {
    for(int i = 0; i<sizeof(array) / sizeof(int); i++) {
        if (array[i] == elemento) {
            return true;
        }
    }
    return false;
}

bool chr_contiene(char array[], char elemento) {
    for(int i = 0; i<sizeof(array) / sizeof(int); i++) {
        if (array[i] == elemento) {
            return true;
        }
    }
    return false;
}

bool flt_contiene(float array[], float elemento) {
    for(int i = 0; i<sizeof(array) / sizeof(int); i++) {
        if (array[i] == elemento) {
            return true;
        }
    }
    return false;
}

bool dbl_contiene(double array[], double elemento) {
    for(int i = 0; i<sizeof(array) / sizeof(int); i++) {
        if (array[i] == elemento) {
            return true;
        }
    }
    return false;
}
