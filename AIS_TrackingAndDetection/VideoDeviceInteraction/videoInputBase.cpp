/*!
 * \file videoInputBase.cpp
 * \author Helen Harman (heh14@aber.ac.uk)
 * \date 03/04/2015
 * \version 1.0
 *
 * \brief The source code for the VideoInputBase class.
 */
#include "videoInputBase.h"

void VideoInputBase::close()
{
   this->capture.release();
}

//-------------------------------------

VideoInputBase::~VideoInputBase()
{
    //std::cout << "kill" << std::endl;
    this->capture.release();
}

//-------------------------------------
//-------------------------------------
