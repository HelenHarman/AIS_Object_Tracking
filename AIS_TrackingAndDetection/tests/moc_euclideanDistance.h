#ifndef MOC_EUCLIDEANDISTANCE
#define MOC_EUCLIDEANDISTANCE


#include "distanceBase.h"
/*!
 * \brief The EuclideanDistance class : A moc version of the EuclideanDistance class to allow the testing of the network.
 */
class Moc_EuclideanDistance  : public DistanceBase
{
    public:
        Moc_EuclideanDistance(){}
        double test[16] = {0.3, 0.08, 0.3, 0.3, 0.3, 0.08, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3};
        int i = -1;
        double getDistance(Mat image, Mat appearance)
        {
            i++;
            //std::cout << test[i] << std::endl;
            return test[i];
        }
};


#endif // MOC_EUCLIDEANDISTANCE

