#include "argumentParser.h"

ArgumentParser::ArgumentParser(int argc, char *argv[])
{
    this->argc = argc;
    this->argv = argv;
}

void ArgumentParser::getArguments(bool *rotation, bool *scale, ARBsToSearchWith *whichARBsToSearchWith, DistanceMeasureType *distanceMeasureType, bool *usePredictedLocation, double *stimulationThreshold, double *objectThreshold, double *linkingThreshold, VideoInputType *inputType, string *configPathName, string *directoryOutput, int *numberOfinitialARBs, int *numIteration)
{
    if (argc > 0)
    {
        int argumentIndex = getArgument("-r", argv, argc);
        if (argumentIndex != -1)
        {
            *rotation = true;
        }

        argumentIndex = getArgument("-s", argv, argc);
        if (argumentIndex != -1)
        {
            *scale = true;
        }

        argumentIndex = getArgument("-whichARBs", argv, argc);
        if (argumentIndex != -1)
        {
            if(strcmp("ALL", argv[argumentIndex+1]) == 0)
            {
                *whichARBsToSearchWith = ALL;
            }
            else if(strcmp("ABOVE_AVERAGE", argv[argumentIndex+1]) == 0)
            {
                *whichARBsToSearchWith = ABOVE_AVERAGE;
            }
            else if(strcmp("LAST_AND_HIGHEST", argv[argumentIndex+1]) == 0)
            {
                *whichARBsToSearchWith = LAST_AND_HIGHEST;
            }
            else if(strcmp("LAST_AND_CONNECTED", argv[argumentIndex+1]) == 0)
            {
                *whichARBsToSearchWith = LAST_AND_CONNECTED;
            }
            else if(strcmp("HIGHEST_AND_CONNECTED", argv[argumentIndex+1]) == 0)
            {
                *whichARBsToSearchWith = HIGHEST_AND_CONNECTED;
            }
        }

        argumentIndex = getArgument("-d", argv, argc);
        if (argumentIndex != -1)
        {
            if(strcmp("euclidean", argv[argumentIndex+1]) == 0)
            {
                *distanceMeasureType = EUCLIDEAN_DISTANCE;
            }
            else if(strcmp("ssd", argv[argumentIndex+1]) == 0)
            {
                *distanceMeasureType = SUM_OF_SQUARED_DIFFERENCE;
            }
        }

        argumentIndex = getArgument("-pl", argv, argc);
        if (argumentIndex != -1)
        {
            *usePredictedLocation = true;
        }

        argumentIndex = getArgument("-st", argv, argc);
        if (argumentIndex != -1)
        {
            *stimulationThreshold = atof(argv[argumentIndex+1]);
        }

        argumentIndex = getArgument("-ot", argv, argc);
        if (argumentIndex != -1)
        {
            *objectThreshold = atof(argv[argumentIndex+1]);
        }

        argumentIndex = getArgument("-nat", argv, argc);
        if (argumentIndex != -1)
        {
            *linkingThreshold = atof(argv[argumentIndex+1]);
        }

        argumentIndex = getArgument("-conf", argv, argc);
        if (argumentIndex != -1)
        {
            *inputType = FILE_INPUT;
            *configPathName = argv[argumentIndex+1];
        }

        // set the simplex step sizes
        argumentIndex = getArgument("-xStep", argv, argc);
        if (argumentIndex != -1)
        {
            SimplexObjectDetector::X_POSITION_STEP_SIZE = atof(argv[argumentIndex+1]);
        }

        argumentIndex = getArgument("-yStep", argv, argc);
        if (argumentIndex != -1)
        {
            SimplexObjectDetector::Y_POSITION_STEP_SIZE = atof(argv[argumentIndex+1]);
        }

        argumentIndex = getArgument("-scaleXStep", argv, argc);
        if (argumentIndex != -1)
        {
            SimplexObjectDetector::SCALE_X_STEP_SIZE = atof(argv[argumentIndex+1]);
        }

        argumentIndex = getArgument("-scaleYStep", argv, argc);
        if (argumentIndex != -1)
        {
            SimplexObjectDetector::SCALE_Y_STEP_SIZE = atof(argv[argumentIndex+1]);
        }

        argumentIndex = getArgument("-rotationStep", argv, argc);
        if (argumentIndex != -1)
        {
            SimplexObjectDetector::ROTATION_STEP_SIZE = atof(argv[argumentIndex+1]);
        }

        argumentIndex = getArgument("-output", argv, argc);
        if (argumentIndex != -1)
        {
            *directoryOutput = argv[argumentIndex+1];
        }

        argumentIndex = getArgument("-NIA", argv, argc);
        if (argumentIndex != -1)
        {
            *numberOfinitialARBs = stoi(argv[argumentIndex+1]);
        }

        argumentIndex = getArgument("-iterations", argv, argc);
        if (argumentIndex != -1)
        {
            *numIteration = stoi(argv[argumentIndex+1]);
        }
    }
}

//----------------------------------------------------------------------

int ArgumentParser::getArgument(const char *id, char *argv[], int argc)
{
    for(int i = 0; i < argc; i++)
    {
        if (strcmp ( id, argv[i]) == 0)
        {
            return i;
        }
    }
    return -1;
}

//----------------------------------------------------------------------

ArgumentParser::~ArgumentParser(){}

//----------------------------------------------------------------------
//----------------------------------------------------------------------
