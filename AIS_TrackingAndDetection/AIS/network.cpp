/*!
 * \file network.cpp
 * \author Helen Harman (heh14@aber.ac.uk)
 * \date 06/03/2015
 * \version 1.0
 *
 * \brief The source code for the Network class.
 */
#include "network.h"

//--------------------------------------------------------------------

Network::Network(Mat initialApperance, Location currentLocation, DistanceBase *distanceMeasure, double objectThreshold, double stimulationThreshold, bool usePredictedLocation)
{
    this->usePredictedLocation = usePredictedLocation;
    currentLocation.rotation = 0;
    currentLocation.scaleX = 1;
    currentLocation.scaleY = 1;
    ARB *newArb = new ARB(initialApperance);
    this->aRBs.push_back(newArb);//new ARB(initialApperance));
    numARBs = 1;
    this->predictedLocation = currentLocation;
    this->previousLocation = currentLocation;

    previousARB = this->aRBs[0];
    this->distanceMeasure = distanceMeasure;
    this->averageResourceLevel = 0;

    this->objectThreshold = objectThreshold;
    this->stimulationThreshold = stimulationThreshold;
    // TODO find out what the linkThreshold should be set to.
    this->linkThreshold = stimulationThreshold + ((objectThreshold-stimulationThreshold)/2);
}

//--------------------------------------------------------------------

Location Network::addAppearance(Mat appearance, Location currentLocation)
{
    double smallestDistance = 1;
    double distance = 1;
    ARB * closestArb = NULL;
    std::map<ARB *, double> arbsBelowLinkThreshold;

    // find the most stimulated ARB
    for(int i = 0; i < this->numARBs; i++)
    {
        distance = this->distanceMeasure->getDistanceBetweenAppearances(appearance, this->aRBs[i]->getAppearance());//(this->aRBs[i]->getAppearance(), appearance);

        if((distance < this->stimulationThreshold) && (distance < smallestDistance))
        {
            smallestDistance = distance;
            closestArb = this->aRBs[i];
            break;
        }
        else if ((NULL == closestArb) && (distance < this->linkThreshold))
        {
            arbsBelowLinkThreshold[this->aRBs[i]] = distance;
        }

        if (distance < smallestDistance)
        {
            smallestDistance = distance;
        }
    }
//std::cout << "smallestDistance : " << smallestDistance << std::endl;

    // Add to ARB, add new ARB and add links, or add unconnected ARB
    if(closestArb != NULL)
    {
        closestArb->increaseResourceLevel(smallestDistance);
        this->previousARB = closestArb;
        this->setPredictedLocation(currentLocation);
    }
    else if (!arbsBelowLinkThreshold.empty())
    {
        ARB *newArb = new ARB(appearance);
        this->aRBs.push_back(newArb);//new ARB(appearance));//, this->previousARB, distanceToPreviousARB));
        this->previousARB = this->aRBs[this->numARBs];

        for(std::map<ARB *, double>::iterator arb = arbsBelowLinkThreshold.begin(); arb != arbsBelowLinkThreshold.end(); ++arb)
        {
            arb->first->addNewLink(this->aRBs[this->numARBs], arbsBelowLinkThreshold[arb->first]);
        }
        this->numARBs++;
        this->setPredictedLocation(currentLocation);
    }
    else if(smallestDistance < this->objectThreshold)
    {
        //change constructor
        ARB *newArb = new ARB(appearance);
        this->aRBs.push_back(newArb);//new ARB(appearance));//, this->previousARB, distanceToPreviousARB));
        this->previousARB = this->aRBs[this->numARBs];
        this->numARBs++;
        this->setPredictedLocation(currentLocation);
    }
    else // assumme object has moved as predicted
    {
        this->setPredictedLocation(this->predictedLocation);
    }


    //decrease stimulation of all but closest
    for(int i = 0; i < this->numARBs; i++)
    {
        if (this->aRBs[i] != closestArb)
        {
            this->aRBs[i]->decayResourceLevel();
        }
    }

    this->removeARBs();

    //std::cout << "this->numARBs : " << this->numARBs << std::endl;

    return this->previousLocation;
}

//--------------------------------------------------------------------

void Network::setPredictedLocation(Location currentLocation)
{
    if (this->usePredictedLocation)
    {
        this->calculatePredictedLocation(currentLocation);
    }
    else
    {
        this->predictedLocation.x = currentLocation.x;
        this->predictedLocation.y = currentLocation.y;
        this->predictedLocation.scaleX = currentLocation.scaleX;
        this->predictedLocation.scaleY = currentLocation.scaleY;
        this->predictedLocation.rotation = currentLocation.rotation;
    }
    this->previousLocation = currentLocation;
}

//--------------------------------------------------------------------

void Network::calculatePredictedLocation(Location currentLocation)
{
    this->predictedLocation.x = currentLocation.x + (currentLocation.x - this->previousLocation.x);
    this->predictedLocation.y = currentLocation.y + (currentLocation.y - this->previousLocation.y);
    this->predictedLocation.scaleX = currentLocation.scaleX + (currentLocation.scaleX - this->previousLocation.scaleX);
    this->predictedLocation.scaleY = currentLocation.scaleY + (currentLocation.scaleY - this->previousLocation.scaleY);
    this->predictedLocation.rotation = currentLocation.rotation + (currentLocation.rotation - this->previousLocation.rotation);
}

//--------------------------------------------------------------------

void Network::setUsePredictedLocation(bool usePredictedLocation)
{
    this->usePredictedLocation = usePredictedLocation;
}

//--------------------------------------------------------------------

vector<Mat> Network::getLastAndConnectedARBs()
{
    vector<Mat> mostLikely;
    mostLikely.push_back(this->previousARB->getAppearance());

    for(int i = 0; i < (int)this->previousARB->getLinks().size(); i++)
    {
        mostLikely.push_back(this->previousARB->getLinks()[i]->getAppearance());
    }
    return mostLikely;
}

//--------------------------------------------------------------------

vector<Mat> Network::getHighestRLAndConnectedARBs()
{
    vector<Mat> mostLikely;
    int highestResourceIndex = 0;
    double highestResource = -1;
    for(int i = 0; i < this->numARBs; i++)
    {
        if((aRBs[i]->getResourceLevel() > highestResource))
        {
            highestResourceIndex = i;
            highestResource = aRBs[i]->getResourceLevel();
        }
    }
    mostLikely.push_back(aRBs[highestResourceIndex]->getAppearance());

    for(int i = 0; i < (int)aRBs[highestResourceIndex]->getLinks().size(); i++)
    {
        mostLikely.push_back(aRBs[highestResourceIndex]->getLinks()[i]->getAppearance());
    }

    return mostLikely;
}

//--------------------------------------------------------------------

vector<Mat> Network::getARBsWithAboveAverageRL()
{
    vector<Mat> mostLikely;

    for(int i = 0; i < this->numARBs; i++)
    {
        if((aRBs[i]->getResourceLevel() > this->averageResourceLevel))
        {
            mostLikely.push_back(aRBs[i]->getAppearance());            
        }
    }
    return mostLikely;
}

//--------------------------------------------------------------------

vector<Mat> Network::getLastAndHighestARBs()
{
    vector<Mat> mostLikely;
    mostLikely.push_back(this->previousARB->getAppearance());

    int highestResourceIndex = 0;
    double highestResource = -1;
    for(int i = 0; i < this->numARBs; i++)
    {
        if((aRBs[i]->getResourceLevel() > highestResource))
        {
            highestResourceIndex = i;
            highestResource = aRBs[i]->getResourceLevel();
        }
    }

    if(aRBs[highestResourceIndex] != this->previousARB)
    {
        mostLikely.push_back(aRBs[highestResourceIndex]->getAppearance());
    }
    return mostLikely;
}


//--------------------------------------------------------------------

vector<Mat> Network::getAllAppearances()
{
    vector<Mat> allAppearances;
    for(int i = 0; i < this->numARBs; i++)
    {
        allAppearances.push_back(aRBs[i]->getAppearance());
    }

    return allAppearances;
}

//--------------------------------------------------------------------

void Network::removeARBs()
{
    double sumResourceLevel = 0;
    for(int i = 0; i < this->numARBs; i++)
    {
        //std::cout << this->aRBs[i]->getResourceLevel() << std::endl;
        if(this->numARBs == 1) break;
        if(this->previousARB == this->aRBs[i]) continue;


        //std::cout << "this->aRBs[i]->getResourceLevel() : "<< this->aRBs[i]->getResourceLevel() << std::endl;
        if(this->aRBs[i]->getResourceLevel() < REMOVAL_THRESHOLD)
        {
            std::cout << "removeNode" << std::endl;
            ARB * tempARB = this->aRBs[i];
            this->aRBs[i] = this->aRBs[this->numARBs-1];
            this->aRBs.pop_back();
            delete(tempARB); // calls the deconstructor that will remove all the links
            this->numARBs--;
        }
        else
        {
            sumResourceLevel = sumResourceLevel + this->aRBs[i]->getResourceLevel();
        }
    }

    // calculate the average resource level
    if (sumResourceLevel > 0)
    {
        this->averageResourceLevel = sumResourceLevel / this->numARBs;
    }
    else
    {
        this->averageResourceLevel = 0;
    }
}

//--------------------------------------------------------------------

int Network::getNumberOfARBs()
{
    return this->numARBs;
}

//--------------------------------------------------------------------

Location Network::getPredictedLocation()
{
    return this->predictedLocation;
}

//--------------------------------------------------------------------

vector<ARB*> Network::getARBs()
{
    return this->aRBs;
}

//--------------------------------------------------------------------

void Network::setObejctThreshold(double objectThreshold)
{
    this->objectThreshold = objectThreshold;
}

//--------------------------------------------------------------------

void Network::setStimulationThreshold(double stimulationThreshold)
{
    this->stimulationThreshold = stimulationThreshold;
}

//--------------------------------------------------------------------

Network::~Network()
{
    for(int i = 0; i < this->numARBs; i++)
    {
        delete(aRBs[i]);
    }
    aRBs.clear();
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------
