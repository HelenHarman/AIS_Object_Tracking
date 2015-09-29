/*!
 * \file outputData.cpp
 * \author Helen Harman (heh14@aber.ac.uk)
 * \date 06/03/2015
 * \version 1.0
 *
 * \brief The source code for the OutputData class.
 */
#include "outputData.h"

void OutputData::writeNumOfARBs(string fileName, vector<int> numARBsList)
{
    ofstream arbFile;
    arbFile.open(fileName);

    for(int i = 0; i < (int)numARBsList.size(); i++)
    {
        arbFile << to_string(numARBsList[i]) << '\n';
    }
    arbFile.close();
}

//-----------------------------------------------------

void OutputData::saveNetwork(string directoryName, Network *network)
{
    ofstream arbFile;
    arbFile.open(directoryName + "/network.txt");

    vector<ARB*> arbs = network->getARBs();

    for(int i = 0; i < (int)arbs.size(); i++)
    {
        Mat rgbAppearance;
        cvtColor(arbs[i]->getAppearance(),rgbAppearance, CV_Lab2BGR);
        imwrite(directoryName + "/" + to_string(i) + ".png", rgbAppearance);
        //imwrite(directoryName + "/" + to_string(arbs[i]->getResourceLevel()) + ".png", rgbAppearance);
        arbFile << i << " : " ;
        // list the ARBs arbs[i] is linked to
        vector<ARB*> arbLinks = arbs[i]->getLinks();
        for(int j = 0; j < (int)arbs.size(); j++)
        {
            for(int k = 0; k < (int)arbLinks.size(); k++)
            {
                if(arbs[j] == arbLinks[k])
                {
                    arbFile << j << ", " ;
                }
            }
        }
        arbFile << '\n';
    }
    arbFile.close();
}

//-----------------------------------------------------

void OutputData::writeFrameRates(string fileName, vector<double> frameRates)
{
    ofstream frameRateFile;
    frameRateFile.open(fileName);

    for(int i = 0; i < (int)frameRates.size(); i++)
    {
        frameRateFile << to_string(frameRates[i]) << '\n';
    }
    frameRateFile.close();
}

//-----------------------------------------------------

void OutputData::writeLocations(string fileName, vector<std::array<int, 5> > locations)
{
    ofstream file;
    file.open(fileName);
    for(int i = 0; i < (int)locations.size(); i++)
    {
        file << to_string(locations[i][0]) << "," << to_string(locations[i][1]) << "," << to_string(locations[i][2]) << "," << to_string(locations[i][3]) << '\n';
    }
    file.close();
}

//-----------------------------------------------------
//-----------------------------------------------------

