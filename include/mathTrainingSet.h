#pragma once

#include "areaFunction.h"

#include <string>
#include <vector>
#include <iostream>

#include "opencv2/core/core_c.h"
#include "opencv2/ml/ml.hpp"

using namespace std;
using namespace cv;

typedef pair<Mat, Mat> TrainingSet;

typedef struct {
	int size;
	float xMin;
	float xMax;
	float yMin;
	float yMax;
} TrainingSetParameters;

typedef TrainingSet (*TrainingSetCreator)(const TrainingSetParameters& params);

TrainingSet createTrainingSet(const vector<AreaFuncrion> &f, const TrainingSetParameters& params);

TrainingSet createParabolaSet(const TrainingSetParameters& params);
TrainingSet createComplexFigureSet(const TrainingSetParameters& params);
TrainingSet createSinPlusCosSet(const TrainingSetParameters& params);

void createTrainingSetFile(const string& filename, vector<AreaFuncrion> f, const TrainingSetParameters& params);

