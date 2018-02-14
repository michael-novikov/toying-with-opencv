#pragma once

#include "mlp.h"

#include <vector>

const Method BACKPROP_METHOD_3_H_LAYERS = {
	"backprop",
	CvANN_MLP_TrainParams::BACKPROP,
	0.001,
	300,
	{10, 50, 100}
};

const Method RPROP_METHOD_3_H_LAYERS = {
	"rprop",
	CvANN_MLP_TrainParams::RPROP,
	0.1,
	1000,
	{ 10, 50, 100 }
};

const TrainingSetParameters PARABOLA_PARAMS = { 
	20'000, 
	-10.f, 
	10.f, 
	-100.f, 
	100.f 
};

const TrainingSetParameters COMPLEX_FIGURE_PARAMS = {
	20'000,
	-10.f,
	10.f,
	-100.f,
	100.f
};

const TrainingSetParameters SIN_PLUS_COS_PARAMS = {
	20'000,
	-20.f,
	20.f,
	-2.f,
	2.f
};

void test_classifier(TrainingSetCreator createSet, const TrainingSetParameters& params, const vector<Method>& learn_methods);
void test_method(const vector<Method>& methods);
