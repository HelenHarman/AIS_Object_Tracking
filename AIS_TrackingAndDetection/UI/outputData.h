/*!
 * \file outData.h
 * \author Helen Harman (heh14@aber.ac.uk)
 * \date 06/03/2015
 * \version 1.0
 *
 * \brief Holds the OutputData class
 */

#ifndef OUTPUTDATA_H
#define OUTPUTDATA_H

#include <string.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <array>
#include "network.h"

using namespace std;

/*!
 * \class OutputData
 * \brief Allows the AIN to be saved to file
 */
class OutputData
{
public:
    /*!
     * \fn writeNumOfARBs
     * \brief Writes out a file listing the number of
     * ARBs the network has contained.
     * \param fileName [in] : File path name to save the data to.
     * \param numARBsList [in]
     */
    void writeNumOfARBs(string fileName, vector<int> numARBsList);

    /*!
     * \fn saveNetwork
     * \brief Saves the appearances to image files and creates a text file
     * containing information about how the appearances are joined in the network.
     * \param directoryName [in]
     * \param network [in]
     */
    void saveNetwork(string directoryName, Network *network);


    /*!
     * \fn writeFrameRates
     * \brief Writes the list of frame rates to file
     * \param fileName [in]
     * \param frameRates [in]
     */
    void writeFrameRates(string fileName, vector<double> frameRates);

    void writeLocations(string fileName, vector<std::array<int, 5> > locations);

};

#endif // OUTPUTDATA_H
