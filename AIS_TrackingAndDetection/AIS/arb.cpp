/*!
 * \file arb.cpp
 * \author Helen Harman (heh14@aber.ac.uk)
 * \date 06/03/2015
 * \version 1.0
 *
 * \brief The source code for the ARB class.
 *  The decayResourceLevel(), increaseResourceLevel() and getStimulationLevel() are based on the equations
 *  in "An artificial immune system for continuous analysis of time-varying data" by M.Neal 2002
 */
#include "arb.h"

//--------------------------------------------------------------------

ARB::ARB(Mat appearance)
{
    this->numLinks = 0;
    this->appearance = appearance;

    this->resourceLevel = 1;//DECAY_RATE * this->getStimulationLevel(0);
}

//--------------------------------------------------------------------
/*
ARB::ARB(Mat appearance)//, ARB * nodeLinkedTo, double distance)
{
    this->numLinks = 0;
    this->appearance = appearance;

    // all links are in both directions
    //this->addNewLink(nodeLinkedTo, distance);
    //nodeLinkedTo->addNewLink(this, distance);

    this->resourceLevel = DECAY_RATE * this->getStimulationLevel(0);
}
*/
//--------------------------------------------------------------------

Mat ARB::getAppearance()
{
    return this->appearance;
}

//--------------------------------------------------------------------

double ARB::decayResourceLevel()
{
    //std::cout << "pre decayResourceLevel this->resourceLevel : " << this->resourceLevel << std::endl;

    this->resourceLevel = this->DECAY_RATE * this->resourceLevel;
    //std::cout << "decayResourceLevel this->resourceLevel : " << this->resourceLevel << std::endl;
    return this->resourceLevel;
}

//--------------------------------------------------------------------

double ARB::increaseResourceLevel(double distance)
{
    //std::cout << "pre increaseResourceLevel this->resourceLevel : " << this->resourceLevel << std::endl;

    double stimulationLevel = this->getStimulationLevel(distance);

    //std::cout << "distance : " << distance << " stimulationLevel : " << stimulationLevel << std::endl;

    //std::cout << "this->resourceLevel + stimulationLevel : " << (this->resourceLevel + stimulationLevel) << std::endl;

    this->resourceLevel = this->DECAY_RATE * (this->resourceLevel + stimulationLevel);

    //std::cout << "increaseResourceLevel this->resourceLevel : " << this->resourceLevel << std::endl;
    return this->resourceLevel;
}

//--------------------------------------------------------------------

double ARB::getStimulationLevel(double distance)
{
    double ps = 1 - distance; //distance is between 0 and 1.

    // sum the distances to each of the linked ARBs
    double sumDistance = 0;
    for(int i = 0; i < this->numLinks; i++)
    {
        sumDistance = sumDistance + (1.00 - this->links[i].distance);
    }


    double ns = 0;
    if(this->numLinks > 0 )
    {
        ns = (1.00/this->numLinks)*sumDistance;
    }

    return ps + ns;
}

//--------------------------------------------------------------------

void ARB::addNewLink(ARB *newArbNode, double distance)
{
    if(!this->linkExists(newArbNode))
    {
        Link newLink;
        newLink.arbNode = newArbNode;
        newLink.distance = distance;
        this->links.push_back(newLink);
        this->numLinks++;

        newArbNode->addNewLink(this, distance);
    }
}

//--------------------------------------------------------------------

bool ARB::linkExists(ARB *arbNode)
{
    if (arbNode == this)
    {
        return true;
    }

    for(int i = 0; i < this->numLinks; i++)
    {
        if(this->links[i].arbNode == arbNode)
        {
            return true;
        }
    }
    return false;
}

//--------------------------------------------------------------------

void ARB::removeLink(ARB *rmArbNode)
{
    for(int i = 0; i < this->numLinks; i++)
    {
        if(this->links[i].arbNode == rmArbNode)
        {
            this->links[i] = this->links[this->numLinks-1];
            this->links.pop_back();

            this->numLinks--;
            break;
        }
    }
}

//--------------------------------------------------------------------

double ARB::getResourceLevel()
{
    return this->resourceLevel;
}

//--------------------------------------------------------------------

vector<ARB*> ARB::getLinks()
{
    vector<ARB*> arbs;
    for (int i = 0; i < numLinks; i++)
    {
        arbs.push_back(links[i].arbNode);
    }
    return arbs;
}

//--------------------------------------------------------------------

ARB::~ARB()
{
    for(int i = 0; i < this->numLinks; i++)
    {
        this->links[i].arbNode->removeLink(this);
    }
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------
