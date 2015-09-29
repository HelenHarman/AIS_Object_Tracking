#include "testEuclideanDistance.h"

//-----------------------------------------------------------------

void EuclideanDistanceTest::initTestCase()
{
    this->appereance = imread("/Users/helen/Documents/UniWork/Dissertation/EuclideanDistance/tests/testData/apperance.jpg");
    this->frame = imread("/Users/helen/Documents/UniWork/Dissertation/EuclideanDistance/tests/testData/frame.jpg");
    resize(this->appereance, this->appereance, Size(), 0.2, 0.2);
    resize(this->frame, this->frame, Size(), 0.2, 0.2);
    this->euclideanDistance = new EuclideanDistance(this->frame, this->appereance);
}

//-----------------------------------------------------------------

void EuclideanDistanceTest::sameAppearanceTest()
{
    EuclideanDistance *euclideanDistance = new EuclideanDistance();
    //qDebug("%f", euclideanDistance->getDistance(this->appereance, this->appereance));
    //QCOMPARE((int)euclideanDistance->getDistance(this->appereance, this->appereance), 0);
}

//-----------------------------------------------------------------

void EuclideanDistanceTest::maxEuclideanDistanceTest()
{
    QCOMPARE((int)this->euclideanDistance->getMaxDistance(), 10605);
}

//-----------------------------------------------------------------

void EuclideanDistanceTest::sameAppearanceDiffSizes()
{
    Mat smallerImage;
    resize(this->appereance, smallerImage, Size(), 0.8, 0.8, INTER_AREA);
    //std::cout << euclideanDistance->getDistance(this->appereance, smallerImage) << std::endl;
    //QVERIFY(euclideanDistance->getDistance(this->appereance, smallerImage) < 0.32);
}

//-----------------------------------------------------------------

void EuclideanDistanceTest::differentAppearanceTest()
{
    Mat appearance2 = imread("/Users/helen/Documents/UniWork/Dissertation/EuclideanDistance/tests/testData/appearance2.jpg");
    resize(appearance2, appearance2, Size(), 0.2, 0.2);
    //double result = this->euclideanDistance->getDistance(this->appereance, appearance2);
    //qDebug("this distance : %f", result);
   // QVERIFY(result > 0.5 && result < 0.54);
}

//-----------------------------------------------------------------




void EuclideanDistanceTest::withTransformationTest()
{
    /*
    EuclideanDistance *euclideanDistance = new EuclideanDistance();
    this->appereance = imread("/Users/helen/Documents/UniWork/Dissertation/EuclideanDistance/tests/testData/apperance.jpg");
    this->frame = imread("/Users/helen/Documents/UniWork/Dissertation/EuclideanDistance/tests/testData/frame.jpg");

    AIS_Options::Location loc;
    loc.rotation = -50;
    loc.scaleX = 1;
    loc.scaleY = 1;
    loc.x = 400;
    loc.y = 400;
    double distance = euclideanDistance->getDistanceTransformation(frame, appereance, loc);
    qDebug("getDistanceTransformation = %f", distance);

    loc.rotation = 50;
Mat rotatingFrame;
frame.copyTo(rotatingFrame);
    Point2f pt(rotatingFrame.cols/2., rotatingFrame.rows/2.);
    Mat r = getRotationMatrix2D(pt, loc.rotation, 1.0);
    warpAffine(rotatingFrame, rotatingFrame, r, rotatingFrame.size());
    namedWindow( "frame", WINDOW_AUTOSIZE );
    imshow( "frame", rotatingFrame);

    int locX = loc.x;
    int locY = loc.y;
    int rotationCenterX = frame.size().width / 2;
    int rotationCenterY = frame.size().height / 2;

    double radians = (double)loc.rotation * (M_PI / 180.00);
    double translatedX = (double)(locX - rotationCenterX);
    double translatedY = (double)(locY - rotationCenterY);

    double rotatedX = (translatedX * cos(radians)) - (translatedY * sin(radians));
    double rotatedY = (translatedX * sin(radians)) + (translatedY * cos(radians));

    locX = rotatedX + rotationCenterX;
    locY = rotatedY + rotationCenterY;
    Rect selectionRect(locX, locY, appereance.size().width, appereance.size().height);
    Mat image;

    image = rotatingFrame(selectionRect);
    namedWindow( "other", WINDOW_AUTOSIZE );
    imshow( "other", image);

    //distance = euclideanDistance->getUnnormalisedDistance(image, appereance);
    //qDebug("getUnnormalisedDistance = %f", distance);

    //for(;;);*/
}






void EuclideanDistanceTest::cleanupTestCase()
{
    delete(this->euclideanDistance);
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------



