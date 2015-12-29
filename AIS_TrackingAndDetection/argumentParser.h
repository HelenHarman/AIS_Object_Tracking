#ifndef ARGUMENTPARSER_H
#define ARGUMENTPARSER_H
#include <iostream>

#include "options.h"
#include "ObjectFinders/simplexObjectDetector.h"

using namespace AIS_Options;
using namespace std;

class ArgumentParser
{
public:
    ArgumentParser(int argc, char *argv[]);

    void getArguments(bool *rotation, bool *scale, DistanceMeasureType *distanceMeasureType, bool *usePredictedLocation, double *stimulationThreshold, double *objectThreshold, double *networkAffiliationThreshold, VideoInputType *inputType, string *configPathName, string *directoryOutput, int *numberOfinitialARBs, int *numIteration);

    ~ArgumentParser();

private:
    int getArgument(const char *id, char *argv[], int argc);

    void parseSimplexArguments();

    char **argv;
    int argc;
};

#endif // ARGUMENTPARSER_H
