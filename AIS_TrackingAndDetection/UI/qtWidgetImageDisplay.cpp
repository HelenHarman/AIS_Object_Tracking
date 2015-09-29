/*! \file qtWidgetImageDisplay.cpp
 *  \author Helen Harman (heh14@aber.ac.uk)
 *  \date 12/03/2015
 *  \version 1.0
 *
 * \brief The source code for the QtWidgetImageDisplay class.
 */
#include "qtWidgetImageDisplay.h"

//--------------------------------------------------------------

void QtWidgetImageDisplay::displayMat(uchar* data, int cols, int rows)
{
    //test++;
   // std::cout << test << std::endl;
    _qimage = QImage(data, cols, rows, cols*3, QImage::Format_RGB888);
    this->setFixedSize(cols, rows);
    repaint();
}

//-------------------------------------------------------------------

void QtWidgetImageDisplay::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawImage(QPoint(0,0), _qimage);

    if(state == SELECTING)
    { // Draw a rectagle around the area the user is selecting
        painter.drawRect( MIN(this->mouseCurrentPosition[0], this->mousePressedPosition[0]),
                          MIN(this->mouseCurrentPosition[1], this->mousePressedPosition[1]),
                          abs(this->mousePressedPosition[0] - this->mouseCurrentPosition[0]),
                          abs(this->mousePressedPosition[1] - this->mouseCurrentPosition[1]) );
    }
    else if(state == TRACKING)
    { // Object has been detected so, draw restangle around it  
        //painter.drawRect( this->trackingX, this->trackingY, this->trackingWidth, this->trackingHeight );
//std::cout << "r : " << this->trackingRotation << std::endl;

        int xTopLeft = this->trackingX;
        int yTopLeft = this->trackingY;

        int xTopRight = this->trackingX + this->trackingWidth;
        int yTopRight = this->trackingY;

        int xBottomRight = this->trackingX + this->trackingWidth;
        int yBottomRight = this->trackingY + this->trackingHeight;

        int xBottomLeft = this->trackingX;
        int yBottomLeft = this->trackingY + this->trackingHeight;

        if(this->trackingRotation != 0)
        {
            int rotationPointX = _qimage.width() / 2;//this->trackingWidth / 2;//this->trackingX;//this->trackingWidth/2;
            int rotationPointY = _qimage.height() / 2;//this->trackingY;//this->trackingHeight/2;

            this->rotatePosition(this->trackingRotation, &xTopLeft, &yTopLeft, rotationPointX, rotationPointY);
            this->rotatePosition(this->trackingRotation, &xTopRight, &yTopRight, rotationPointX, rotationPointY);
            this->rotatePosition(this->trackingRotation, &xBottomRight, &yBottomRight, rotationPointX, rotationPointY);
            this->rotatePosition(this->trackingRotation, &xBottomLeft, &yBottomLeft, rotationPointX, rotationPointY);
        }


        painter.drawLine(xBottomLeft, yBottomLeft, xBottomRight, yBottomRight);
        painter.drawLine(xBottomRight, yBottomRight, xTopRight, yTopRight);
        painter.drawLine(xBottomLeft, yBottomLeft, xTopLeft, yTopLeft);
        painter.drawLine(xTopLeft, yTopLeft, xTopRight, yTopRight);

        painter.drawText(QPoint(_qimage.width()-20,_qimage.height()-5), QString::number(this->numARBs));

        this->numberOfFrames++;
        time_t currentTime;
        time(&currentTime);
        double framesPerSecond = this->numberOfFrames / difftime(currentTime, this->startedTime);
        this->frameRates.push_back(framesPerSecond);
        painter.drawText(QPoint(_qimage.width()-100,_qimage.height()-5), QString::number(framesPerSecond));

    }
    painter.end();
}

//-------------------------------------------------------------------

void QtWidgetImageDisplay::mousePressEvent(QMouseEvent *event)
{
    this->trackingX = 1;
    this->trackingY = 1;
    this->trackingWidth = 1;
    this->trackingHeight = 1;

    if (state == UNINITIALISED)
    {
        this->mousePressedPosition[0] = event->x();
        this->mousePressedPosition[1] = event->y();

        this->mouseCurrentPosition[0] = event->x();
        this->mouseCurrentPosition[1] = event->y();
        state = SELECTING;
        emit(setState(state));
    }
}

//-------------------------------------------------------------------

void QtWidgetImageDisplay::mouseMoveEvent(QMouseEvent *event)
{
    if (state == SELECTING)
    {
        this->mouseCurrentPosition[0] = event->x();
        this->mouseCurrentPosition[1] = event->y();
    }
}

//-------------------------------------------------------------------

void QtWidgetImageDisplay::mouseReleaseEvent(QMouseEvent *event)
{
    if (state == SELECTING)
    {
        this->mouseCurrentPosition[0] = event->x();
        this->mouseCurrentPosition[1] = event->y();
        state = TRACKING;

        int x = MIN(this->mouseCurrentPosition[0], this->mousePressedPosition[0]);
        int y = MIN(this->mouseCurrentPosition[1], this->mousePressedPosition[1]);
        int width = abs(this->mousePressedPosition[0] - this->mouseCurrentPosition[0]);
        int height = abs(this->mousePressedPosition[1] - this->mouseCurrentPosition[1]);
        numARBs = 1;
        emit(setInitialTrackingPostion(x, y, width, height));
        this->numberOfFrames = 0;
        time(&this->startedTime);
    }
}

//-------------------------------------------------------------------

void QtWidgetImageDisplay::useRotationChanged(bool useRotation)
{
    emit(setUseRotation(useRotation));
}

//-------------------------------------------------------------------

void QtWidgetImageDisplay::useScaleChanged(bool useScale)
{
    emit(setUseScale(useScale));
}

//-------------------------------------------------------------------

void QtWidgetImageDisplay::usePredictedLocationChanged(bool usePredictedLocation)
{
    emit(setUsePredictedLocation(usePredictedLocation));
}

//-------------------------------------------------------------------

void QtWidgetImageDisplay::whichARBsToSearchWithChanged(ARBsToSearchWith whichARBsToSearchWith)
{
    emit(setWhichARBsToSearchWith(whichARBsToSearchWith));
}

//-------------------------------------------------------------------

void QtWidgetImageDisplay::distanceMeasureChanged(DistanceMeasureType distanceMeasureType)
{
    emit(setDistanceMeasure(distanceMeasureType));
}

//-------------------------------------------------------------------

void QtWidgetImageDisplay::setTrackingPosition(int x, int y, int rotation, int width, int height)
{
    this->state = TRACKING;
    this->trackingX = x;
    this->trackingY = y;
    this->trackingWidth = width;
    this->trackingHeight = height;
    this->trackingRotation = rotation;


   // int location[5] = {x, y, width, height, rotation};
    locations.push_back({{x, y, width, height, rotation}});
}

//-------------------------------------------------------------------

void QtWidgetImageDisplay::setNumARBs(int numARBs)
{
    //std::cout << "numARBs : " << numARBs << std::endl;
    this->numARBs = numARBs;
    this->numARBsList.push_back(numARBs);
}

//-------------------------------------------------------------------

void QtWidgetImageDisplay::videoInputChanged(VideoInputType videoInputType)
{
    this->state = UNINITIALISED;
    this->numARBs = 0;
    this->numARBsList.clear();
    this->inputType = videoInputType;    

    emit(setVideoType(videoInputType));
    this->numberOfFrames = 0;
    this->frameRates.clear();
    time(&this->startedTime);
}

//-------------------------------------------------------------------

void QtWidgetImageDisplay::getVideoFileConfig()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open AIS Video File Config"), "", tr("Video Files (*.ais_config)"));
    std::cout << fileName.toStdString() << std::endl;
    state = TRACKING;
    emit(setVideoFileConfigFilePath(fileName.toStdString()));
    //test=0;
}

//-------------------------------------------------------------------

void QtWidgetImageDisplay::printNumberArbsInNetwork()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Open file to write to"), "", tr("Text file (*.txt)"));
    std::cout << fileName.toStdString() << std::endl;
    outputData.writeNumOfARBs(fileName.toStdString(), this->numARBsList);
}

//-------------------------------------------------------------------

void QtWidgetImageDisplay::saveNetwork()
{
    emit(getNetwork());
}
//-------------------------------------------------------------------

void QtWidgetImageDisplay::stimulationThresholdChanged(double stimulationThreshold)
{
    emit(setStimulationThreshold(stimulationThreshold));
}

//-------------------------------------------------------------------

void QtWidgetImageDisplay::objectThresholdChanged(double objectThreshold)
{
    emit(setObjectThreshold(objectThreshold));
}

//-------------------------------------------------------------------

void QtWidgetImageDisplay::setNetworkToSaveNetwork(Network *network)
{
    QString directoryName = QFileDialog::getExistingDirectory(this, tr("Open directory to write to"));
    outputData.saveNetwork(directoryName.toStdString(), network);
    outputData.writeNumOfARBs(directoryName.toStdString() + "/numberOfArbs.txt", this->numARBsList);
    outputData.writeFrameRates(directoryName.toStdString() + "/frameRate.txt", this->frameRates);
    outputData.writeLocations(directoryName.toStdString() + "/locations.txt", this->locations);
}

void QtWidgetImageDisplay::saveNetworkToPath(Network *network, string path)
{
    outputData.saveNetwork(path, network);
    outputData.writeNumOfARBs(path + "/numberOfArbs.txt", this->numARBsList);
    outputData.writeFrameRates(path + "/frameRate.txt", this->frameRates);
    outputData.writeLocations(path + "/locations.txt", this->locations);

    this->locations.clear();
    this->numARBs = 0;
    this->numberOfFrames = 0;
    this->numARBsList.clear();
    this->frameRates.clear();
    time(&this->startedTime);
    this->trackingRotation=0;
}

//-------------------------------------------------------------------
//-------------------------------------------------------------------


