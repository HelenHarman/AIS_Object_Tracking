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

Network::Network(Mat initialApperance, Location currentLocation, DistanceBase *distanceMeasure, double objectThreshold, double stimulationThreshold, bool usePredictedLocation, double linkingThreshold)
{
    this->usePredictedLocation = usePredictedLocation;
    this->predictedLocation = currentLocation;
    this->previousLocation = currentLocation;
    this->distanceMeasure = distanceMeasure;
    this->averageResourceLevel = 0;

    ARB *newArb = new ARB(initialApperance, this->initialARBsResourceLevel);
    this->aRBs.push_back(newArb);
    this->previousARB = newArb;
    this->numARBs = 1;

    this->objectThreshold = objectThreshold;
    this->stimulationThreshold = stimulationThreshold;
    if (linkingThreshold == 0)
    {
        this->linkThreshold = stimulationThreshold + ((objectThreshold-stimulationThreshold)/2);
    }
    else
    {
        this->linkThreshold = linkingThreshold;
    }
}

//--------------------------------------------------------------------

Location Network::addAppearance(Mat appearance, Location currentLocation)
{
    double smallestDistance = 1;
    double distance = 1;
    ARB * closestArb = NULL;
    std::map<ARB *, double> arbsBelowLinkThreshold;

    // find the most stimulated ARB
    checkAllARBs(appearance, &arbsBelowLinkThreshold, &closestArb, &smallestDistance);

    if((smallestDistance < this->objectThreshold) && (distance > this->stimulationThreshold))
    {
        ARB *newArb = new ARB(appearance);
        this->aRBs.push_back(newArb);
        //this->previousARB = this->aRBs[this->numARBs];
        this->numARBs++;
        //this->setPredictedLocation(this->predictedLocation);
    }
    if(smallestDistance < this->linkThreshold)
    {
        addLinks(arbsBelowLinkThreshold);
        this->setPredictedLocation(currentLocation);
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
    return this->previousLocation;
}

//--------------------------------------------------------------------

Location Network::initialAppearanceAddition(Mat appearance, Location currentLocation)
{
    double smallestDistance = 1;
    ARB * closestArb = NULL;
    std::map<ARB *, double> arbsBelowLinkThreshold;

    checkAllARBs(appearance, &arbsBelowLinkThreshold, &closestArb, &smallestDistance);

    ARB *newArb = new ARB(appearance, this->initialARBsResourceLevel);
    //newArb->setAlwaysKeep(true);
    this->aRBs.push_back(newArb);
    this->numARBs++;

    addLinks(arbsBelowLinkThreshold);

    this->setPredictedLocation(currentLocation);
    return this->predictedLocation;
}

//--------------------------------------------------------------------

void Network::checkAllARBs(Mat appearance, std::map<ARB *, double> *arbsBelowLinkThreshold, ARB ** closestArb, double *smallestDistance)
{
    double distance = 1;
    for(int i = 0; i < this->numARBs; i++)
    {
        distance = this->distanceMeasure->getDistanceBetweenAppearances(appearance, this->aRBs[i]->getAppearance());//(this->aRBs[i]->getAppearance(), appearance);

        if(distance <= *smallestDistance)//(distance < this->stimulationThreshold) && (distance < smallestDistance))
        {
            *smallestDistance = distance;
            *closestArb = this->aRBs[i];
        }
        if (distance < this->linkThreshold)
        {
            (*arbsBelowLinkThreshold)[this->aRBs[i]] = distance;
        }
    }

    if(*closestArb != NULL)
    {
        (*closestArb)->increaseResourceLevel(*smallestDistance);
        this->previousARB = *closestArb;//this->aRBs[i];
    }
}

//--------------------------------------------------------------------

void Network::addLinks(std::map<ARB *, double> arbsBelowLinkThreshold)
{
    if (!arbsBelowLinkThreshold.empty())
    {
        for(std::map<ARB *, double>::iterator arb = arbsBelowLinkThreshold.begin(); arb != arbsBelowLinkThreshold.end(); ++arb)
        {
            arb->first->addNewLink(this->aRBs[this->numARBs-1], arbsBelowLinkThreshold[arb->first]);
        }
    }
}

//--------------------------------------------------------------------

void Network::setPredictedLocation(Location currentLocation)
{
    if (this->usePredictedLocation)
    { // predict that the object will continue along the same path
        this->calculatePredictedLocation(currentLocation);
    }
    else
    {
        this->predictedLocation = currentLocation;
    }
    this->previousLocation = currentLocation;
}

//--------------------------------------------------------------------

void Network::calculatePredictedLocation(Location currentLocation)
{
    this->predictedLocation.setX(currentLocation.getX() + (currentLocation.getX() - this->previousLocation.getX()));
    this->predictedLocation.setY(currentLocation.getY() + (currentLocation.getY() - this->previousLocation.getY()));
    this->predictedLocation.setScaleX(currentLocation.getScaleX() + (currentLocation.getScaleX() - this->previousLocation.getScaleX()));
    this->predictedLocation.setScaleY(currentLocation.getScaleY() + (currentLocation.getScaleY() - this->previousLocation.getScaleY()));
    this->predictedLocation.setRotation(currentLocation.getRotation() + (currentLocation.getRotation() - this->previousLocation.getRotation()));
}

//--------------------------------------------------------------------

void Network::getHighestRLAndConnectedARBs(vector<ARB*>* mostLikely)
{
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
    mostLikely->push_back(aRBs[highestResourceIndex]);

    for(int i = 0; i < (int)aRBs[highestResourceIndex]->getLinks().size(); i++)
    {
        mostLikely->push_back(aRBs[highestResourceIndex]->getLinks()[i]);
    }
}

//--------------------------------------------------------------------

void Network::getNearestAndConnectedARBs(vector<ARB*>* mostLikely)
{
    mostLikely->push_back(this->previousARB);

    for(int i = 0; i < (int)this->previousARB->getLinks().size(); i++)
    {
        mostLikely->push_back(this->previousARB->getLinks()[i]);
    }
}

//--------------------------------------------------------------------

void Network::removeARBs()
{
    for(int i = 0; i < this->numARBs; i++)
    {
        if(this->numARBs == 1) break;
        if(this->previousARB == this->aRBs[i]) continue;
        if(this->aRBs[i]->shouldAlwaysKeep()) continue;

        if(this->aRBs[i]->getResourceLevel() < REMOVAL_THRESHOLD)
        {
            //std::cout << "removeNode" << std::endl;
            ARB * tempARB = this->aRBs[i];
            this->aRBs[i] = this->aRBs[this->numARBs-1];
            this->aRBs.pop_back();
            delete(tempARB); // calls the deconstructor that will remove all the links
            this->numARBs--;
        }
    }
}

//------------------------------getters and setters ------------

//--------------------------------------------------------------------

void Network::setUsePredictedLocation(bool usePredictedLocation)
{
    this->usePredictedLocation = usePredictedLocation;
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

void Network::resetLocation(Location location)
{
    this->predictedLocation = location;
    this->previousLocation = location;
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


//--------------------------------------------------------------------
/*
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
*/

/*
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
*/
//--------------------------------------------------------------------
/*
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
*/

//--------------------------------------------------------------------
/*
vector<Mat> Network::getAllAppearances()
{
    vector<Mat> allAppearances;
    for(int i = 0; i < this->numARBs; i++)
    {
        allAppearances.push_back(aRBs[i]->getAppearance());
    }

    return allAppearances;
}
*/
