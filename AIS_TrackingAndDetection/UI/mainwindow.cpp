/*!
 * \file mainwindow.cpp
 * \author Helen Harman (heh14@aber.ac.uk)
 * \date 06/03/2015
 * \version 1.0
 *
 * \brief The source code for the MainWindow class.
 */
#include "mainwindow.h"
#include "ui_mainwindow.h"

//--------------------------------------------------------------

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->imageWidget = new QtWidgetImageDisplay();
    this->setCentralWidget(this->imageWidget);

    // connect all the menu buttons to this class
    this->connect(ui->actionWebcam, SIGNAL(triggered()), this, SLOT(setVideoInputToWebcam()));
    this->connect(ui->actionFile, SIGNAL(triggered()), this, SLOT(setVideoInputToFile()));

    this->connect(ui->actionRotation, SIGNAL(triggered()), this, SLOT(useRotationChanged()));
    this->connect(ui->actionScale, SIGNAL(triggered()), this, SLOT(useScaleChanged()));
    this->connect(ui->actionPredict_Location, SIGNAL(triggered()), this, SLOT(usePredictedLocationChanged()));

    //this->connect(ui->actionUse_Most_Likely_ARBs, SIGNAL(triggered()), this, SLOT(useMostLikelyAppearancesChanged()));
    this->connect(ui->actionAll_ARBs, SIGNAL(triggered()), this, SLOT(whichARBsToSearchWithChangedToALL()));
    this->connect(ui->actionAbove_Avarage_RL, SIGNAL(triggered()), this, SLOT(whichARBsToSearchWithChangedToAboveAverageRL()));
    this->connect(ui->actionLatest_Highest_RL, SIGNAL(triggered()), this, SLOT(whichARBsToSearchWithChangedToLatestAndHighestRL()));
    this->connect(ui->actionLatest_Connected, SIGNAL(triggered()), this, SLOT(whichARBsToSearchWithChangedToLatestAndConnected()));
    this->connect(ui->actionHighest_Connected, SIGNAL(triggered()), this, SLOT(whichARBsToSearchWithChangedToHighestAndConnected()));


    this->connect(ui->actionOT, SIGNAL(triggered()), this, SLOT(changeObjectThreshold()));
    this->connect(ui->actionST, SIGNAL(triggered()), this, SLOT(changeStimulationThreshold()));

    this->connect(ui->actionSSD, SIGNAL(triggered()), this, SLOT(distanceMeasureChangedToSSD()));
    this->connect(ui->actionEuclidean, SIGNAL(triggered()), this, SLOT(distanceMeasureChangedToEuclidean()));

    //this->connect(ui->actionPrint, SIGNAL(triggered()), this->imageWidget, SLOT(printNumberArbsInNetwork()));
    this->connect(ui->actionSave_Network, SIGNAL(triggered()), this->imageWidget, SLOT(saveNetwork()));

    this->connect(ui->actionReset, SIGNAL(triggered()), this, SLOT(reset()));
}

//-----------------------------------------------------

void MainWindow::useRotationChanged()
{
   this->imageWidget->useRotationChanged(ui->actionRotation->isChecked());
}

//-----------------------------------------------------

void MainWindow::usePredictedLocationChanged()
{
   this->imageWidget->usePredictedLocationChanged(ui->actionPredict_Location->isChecked());
}

//-----------------------------------------------------

void MainWindow::distanceMeasureChangedToSSD()
{
    ui->actionEuclidean->setChecked(false);
    this->imageWidget->distanceMeasureChanged(SUM_OF_SQUARED_DIFFERENCE);
}

//-----------------------------------------------------

void MainWindow::distanceMeasureChangedToEuclidean()
{
    ui->actionSSD->setChecked(false);
    this->imageWidget->distanceMeasureChanged(EUCLIDEAN_DISTANCE);
}

//-----------------------------------------------------

void MainWindow::whichARBsToSearchWithChangedToALL()
{
    ui->actionAbove_Avarage_RL->setChecked(false);
    ui->actionLatest_Highest_RL->setChecked(false);
    ui->actionLatest_Connected->setChecked(false);
    ui->actionHighest_Connected->setChecked(false);
    this->imageWidget->whichARBsToSearchWithChanged(ARBsToSearchWith::ALL);
}

//-----------------------------------------------------

void MainWindow::whichARBsToSearchWithChangedToAboveAverageRL()
{
    ui->actionAll_ARBs->setChecked(false);
    ui->actionLatest_Highest_RL->setChecked(false);
    ui->actionLatest_Connected->setChecked(false);
    ui->actionHighest_Connected->setChecked(false);
    this->imageWidget->whichARBsToSearchWithChanged(ARBsToSearchWith::ABOVE_AVERAGE);
}

//-----------------------------------------------------

void MainWindow::whichARBsToSearchWithChangedToLatestAndHighestRL()
{
    ui->actionAll_ARBs->setChecked(false);
    ui->actionAbove_Avarage_RL->setChecked(false);
    ui->actionLatest_Connected->setChecked(false);
    ui->actionHighest_Connected->setChecked(false);
    this->imageWidget->whichARBsToSearchWithChanged(ARBsToSearchWith::LAST_AND_HIGHEST);
}

//-----------------------------------------------------

void MainWindow::whichARBsToSearchWithChangedToLatestAndConnected()
{
    ui->actionAll_ARBs->setChecked(false);
    ui->actionAbove_Avarage_RL->setChecked(false);
    ui->actionLatest_Highest_RL->setChecked(false);
    ui->actionHighest_Connected->setChecked(false);
    ui->actionLatest_Connected->setChecked(true);
    this->imageWidget->whichARBsToSearchWithChanged(ARBsToSearchWith::LAST_AND_CONNECTED);
}

//-----------------------------------------------------

void MainWindow::whichARBsToSearchWithChangedToHighestAndConnected()
{
    ui->actionAll_ARBs->setChecked(false);
    ui->actionAbove_Avarage_RL->setChecked(false);
    ui->actionLatest_Highest_RL->setChecked(false);
    ui->actionLatest_Connected->setChecked(false);
    ui->actionHighest_Connected->setChecked(true);
    this->imageWidget->whichARBsToSearchWithChanged(ARBsToSearchWith::HIGHEST_AND_CONNECTED);
}

//-----------------------------------------------------

void MainWindow::changeObjectThreshold()
{
    double objectThreshold = QInputDialog::getDouble(this, tr("Object Threshold"), tr("Enter new object threshold : "), 0.0, 0.0, 1.0, 3);
    this->imageWidget->objectThresholdChanged(objectThreshold);
}

//-----------------------------------------------------

void MainWindow::changeStimulationThreshold()
{
    double stimulationThreshold = QInputDialog::getDouble(this, tr("Stimulation Threshold"), tr("Enter new stimulation threshold : "), 0.0, 0.0, 1.0, 3);
    this->imageWidget->stimulationThresholdChanged(stimulationThreshold);
}

//-----------------------------------------------------

void MainWindow::reset()
{
    this->imageWidget->setVideoType(WEBCAM);
}

//-----------------------------------------------------

void MainWindow::useScaleChanged()
{
   this->imageWidget->useScaleChanged(ui->actionScale->isChecked());
}

//-----------------------------------------------------

QtWidgetImageDisplay* MainWindow::getImageWidget()
{
    return imageWidget;
}

//-----------------------------------------------------

void MainWindow::setVideoInputToWebcam()
{
    this->ui->actionFile->setChecked(false);
    this->ui->actionWebcam->setChecked(true);
    this->imageWidget->videoInputChanged(WEBCAM);
}

//-----------------------------------------------------

void MainWindow::setVideoInputToFile()
{
    this->ui->actionWebcam->setChecked(false);
    this->ui->actionFile->setChecked(true);
    this->imageWidget->videoInputChanged(FILE_INPUT);
}

//-----------------------------------------------------

MainWindow::~MainWindow()
{
    delete ui;
}

//--------------------------------------------------------------
//--------------------------------------------------------------

