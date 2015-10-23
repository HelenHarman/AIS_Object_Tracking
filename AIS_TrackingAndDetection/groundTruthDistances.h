#ifndef GROUNDTRUTHDISTANCES_H
#define GROUNDTRUTHDISTANCES_H

#include <fstream>

#include "distanceBase.h"
#include "euclideanDistance.h"
#include "options.h"
#include "videoFileInput.h"

using namespace std;
using namespace AIS_Options;

class GroundTruthDistances
{
public:
    GroundTruthDistances();
    void compareDistances(string gtFileName, string outputFileName, string videoFileName);
    ~GroundTruthDistances();
};

#endif // GROUNDTRUTHDISTANCES_H
