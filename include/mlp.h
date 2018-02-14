#pragma once

#include "mathTrainingSet.h"

#include <string>
#include <vector>
#include <iostream>

#include "opencv2/core/core_c.h"
#include "opencv2/ml/ml.hpp"

using namespace std;
using namespace cv;

typedef struct {
	string name;
	int method;
	double methodParam;
	int maxIter;
	vector<int> hidden_layers;
} Method;

void build_mlp_classifier(Method method_struct, const TrainingSet& training_set);
