/*!
 * \file arb.h
 * \author Helen Harman (heh14@aber.ac.uk)
 * \date 06/03/2015
 * \version 1.0
 *
 * \brief Holds the ARB class
 */
#ifndef ARB_H
#define ARB_H
#include <iostream>
#include <vector>
#include <opencv2/core/core.hpp>

using namespace cv;

/*!
 * \class ARB
 * \brief ARB's are the nodes within the network, which contain an appearace of the object.
 */
class ARB
{
public:
    /*!
     * \fn ARB(Mat appearance)
     * \brief Constructor for the first node within the network
     *
     * \param appearance [in] : An appearance of the object being tracked.
     */
    ARB(Mat appearance, double resourceLevel = 1);

    /*!
     * \fn ARB(Mat appearance, ARB * nodeLinkedTo, double distance)
     * \brief Constructor which adds a link to (and from) nodeLinkedTo.
     *
     * \param appearance [in] : An appearance of the object being tracked.
     * \param nodeLinkedTo [in, out] : The previous node to be used, so that the link in the network can be created. Link will be created in both directions.
     * \param distance [in] : Distance between this node and the nodeLinkedTo.
     */
    //ARB(Mat appearance);//, ARB * nodeLinkedTo, double distance);

    /*!
     * \fn addNewLink
     * \brief Adds a link from this node to the newArbNode.
     * \param newArbNode [in] : Node that the link will be created to.
     * \param distance [in] : Distance to the newArbNode.
     */
    void addNewLink(ARB *newArbNode, double distance);

    /*!
     * \fn removeLink
     * \brief Removes the link to the rmArbNode.
     * \param rmArbNode [in] : ARB that is being removed.
     */
    void removeLink(ARB *rmArbNode);

    /*!
     * \fn increaseResourceLevel
     * \brief Increases the resource level based on the distance and the stimulation level \see getStimulationLevel().
     * \param distance [in] : Distance between the this.appearance and the appearance in the latest frame.
     * \return The new resource level
     */
    double increaseResourceLevel(double distance);

    /*!
     * \fn decayResourceLevel
     * \brief Decrease the resource level based on the DECAY_RATE.
     * \return The new resource level
     */
    double decayResourceLevel();

    /*!
     * \fn getResourceLevel
     * \return The resource level
     */
    double getResourceLevel();

    /*!
     * \fn getAppearance
     * \return An appearance of the object being tracked.
     */
    Mat getAppearance();

    /*!
     * \fn getLinks
     * \brief Gets a vector of the ARBs which this ARB is linked to.
     * \return Vector of ARBs
     */
    vector<ARB*> getLinks();

    bool shouldAlwaysKeep();
    void setAlwaysKeep(bool alwaysKeep);

     ~ARB();

private:
    /*!
     * \var DECAY_RATE
     * \brief Used to decay the network each time it is exposed to a new appearance
     */
    const double DECAY_RATE = 0.95;

    bool alwaysKeep = false;

    /*!
     * \struct Link
     * @brief The ARB this node is linked to and the distance to it.
     */
    struct Link
    {
        ARB *arbNode;
        double distance;
    };
    /*!
     * \var links
     * \brief Vector of all the links this ARB links to.
     */
    vector<Link> links;

    /*!
     * \var numLinks
     */
    int numLinks;

    /*!
     * \var appearance
     * \brief The appearance of the object being tracked.
     */
    Mat appearance;

    /*!
     * \var resources
     * \brief Changed by the stimulation level and decay rate.
     * ARBs with higher resource levels will be used to work out if the object has been discovered or not.
     * If this drops bellow the REMOVAL_THRESHOLD then this node will be removed from the network.
     */
    double resourceLevel;

    /*!
     * \fn getStimulationLevel
     * \brief Called when this ARB.appearance is closest
     *  (and bellow the STIMULATION_THRESHOLD) to the new appearance. The stimulation
     *  is : 1-distance + (1/numLinks - (Sum of 1 - each link.distance))
     *
     * \param distance [in] : distance to the new appearance
     * \return the stimulation level
     */
    double getStimulationLevel(double distance);

    /*!
     * \fn linkExists
     * \brief Checks if the arbNode has already been linked to, from this ARB.
     *
     * \param arbNode [in]
     * \return true if the ARB has already been linked too, else returns false
     */
    bool linkExists(ARB *arbNode);
};

#endif // ARB_H
