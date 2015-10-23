#include "groundTruthDistances.h"

GroundTruthDistances::GroundTruthDistances()
{
}

void GroundTruthDistances::compareDistances(string gtFileName, string outputFileName, string videoFileName)
{
    DistanceBase *distanceMeasure;

    VideoFileInput *videoInput = new VideoFileInput();
    videoInput->startCamera(videoFileName);

    ofstream outputFile;
    outputFile.open(outputFileName);

    ifstream gtFile( gtFileName);

    Mat previousAppearance;

    while (gtFile)
    {
        Mat frame = videoInput->getNextFrame();

        // read in the file
        string line;
        if (!getline(gtFile, line)) break;

        istringstream ss(line);
        vector <int> record;
        while (ss)
        {
            string value;
            if (!getline(ss, value, ',')) break;
            record.push_back(atoi(value.c_str()));
        }

        // get the appearance
        int x = record[0];
        int y = record[1];
        int width = record[2];//76;//
        int height = record[3];//84;//
        Rect selectionRect(x, y, width, height);
        Mat currentApperance;
        currentApperance = frame(selectionRect);

        // calculate the distance and write it to file
        if (previousAppearance.cols != 0)
        {
            //double distance = norm(currentApperance, previousAppearance, NORM_L2);
            double distance = distanceMeasure->getDistanceBetweenAppearances(currentApperance, previousAppearance);
            outputFile << distance << '\n';
        }
        else
        {
            distanceMeasure = new EuclideanDistance(frame, currentApperance);
        }
        currentApperance.copyTo(previousAppearance);
    }
    outputFile.close();
    gtFile.close();
}


GroundTruthDistances::~GroundTruthDistances()
{

}

