#pragma once

#include "stdafx.h"

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
using namespace std;
using namespace cv;

class Brush {
public:
	cv::Mat brush_8UC1;
	Size brush_8UC1_Size;
	cv::Mat brush_mask;
	
	cv::Mat brush_thumbnail;
	cv::Mat bump;
	int brush_no;
};


int BrushInitialization(vector <Brush*> &brush);
//, int _called_once, int render_brush_size[]);
