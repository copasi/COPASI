#include "CRandom.h"
#include <time.h>
#include <cmath>

static const C_INT32 tableSize = 64;
static const C_INT32 multiplier = 48271;
static const C_INT32 modulus = 2147483647;
static const C_INT32 qval = 44488;
static const C_INT32 rval = 3399;

CRandom::CRandom(C_INT32 seed)
    : mNumber(0)
{
    initialize(seed);
}

CRandom::~CRandom() {}

void CRandom::initialize(C_INT32 seed)
{
    // deal with default or zero-valued seeds
    if (0 == seed)
    {
        seed = static_cast<C_INT32> (time(0));
    }
    mNumber = seed;
    mShuffleTable.reserve(tableSize);
    C_INT16 i;
    C_INT32 tmp;
    // populate the shuffle table
    for (i = 0; i < tableSize; i++)
    {
        // The following generates a random number between 1 and modulus
        // we use: z % m = z - m * (z/m)
        tmp = mNumber / qval;
        mNumber = multiplier * (mNumber - tmp * qval) - rval * (tmp);
        if (mNumber < 0)
        {
            mNumber += modulus;
        }
        mShuffleTable.push_back(mNumber);
    }
    mNumber = mShuffleTable[0];
}

C_INT32 CRandom::getRandom()
{
    // computes a random number between 0 and 2^31 - 1
    C_INT32 tmp = mNumber / qval;
    C_INT32 newnum = multiplier * (mNumber - tmp * qval) - rval * (tmp);
    if (newnum < 0)
    {
        newnum += modulus;
    }
    // use the old value of mNumber to select a value from the table
    // make sure 0 <= i < tableSize
    C_INT32 ntmp = 1 + (modulus - 1) / tableSize;
    double n = mNumber / ntmp;
    int i = static_cast<int> (n);
    C_INT32 retval = mShuffleTable[i];
    mNumber = mShuffleTable[i] = newnum;
    return retval;
}

C_FLOAT64 CRandom::getUniformRandom()
{
    return getRandom() * (1.0 / modulus);
}

#ifdef TEST_RANDOM

#include <fstream>
#include <iostream>
#include <iomanip>

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        cout << "Usage: test_random npoints nbins" << endl;
        exit(1);
    }
    long long npoints = atoll(argv[1]);
    C_INT32 nbins = atoi(argv[2]);
    cout << "Dropping " << npoints << " points into " << nbins << " bins.\n";

    CRandom generator;
    vector <C_INT32> store;
    for (C_INT32 i = 0; i < nbins; i++)
    {
        store.push_back(0);
    }
    C_INT32 j = 0;
    for (j = 0; j < npoints; j++)
    {
        C_FLOAT64 rnd = generator.getUniform();
        C_INT32 k = static_cast<C_INT32> (rnd * nbins);
        if (k >= nbins) {cout << " k too big \n"; exit(2);}
	else if (k < 0) {cout << " k too small \n"; exit(2);}
        store[k] += 1;
    }
    ofstream fout("test_random.dat");
    cout << "Generated " << j << " points\n";
    fout << "# Generated " << j << " points\n";
    C_FLOAT64 min = pow(2.0,63), max = 0, mean = 0;
    for (C_INT32 l = 0; l < nbins; l++)
    {
        cout << l << "  " << store[l] << endl;
        fout << l << "  " << store[l] << endl;
	if (store[l] > max) max = store[l];
	if (store[l] < min) min = store[l];
	mean += store[l];
    }
    cout << "Total points = " << setprecision (12) << mean << endl,
    mean = mean / nbins;
    C_FLOAT64 deviation = ((max - mean) > (mean - min))?(max-mean):(mean-min);
    deviation = deviation / mean;
    //    cout << "Average = " << setprecision (12) << setw (12) << mean << "  Deviation = " << deviation << endl;
    cout << "Average = " << setprecision (12) << mean << "  Deviation = " << deviation << endl;
    fout << "#Average = " << setprecision (12) << mean << "  Deviation = " << deviation << endl;
    return 0;
}

#endif // TEST_RANDOM
    
