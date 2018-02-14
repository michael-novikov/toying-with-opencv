#include "mathTrainingSet.h"
#include "areaFunction.h"

#include "opencv2/core/core_c.h"
#include "opencv2/ml/ml.hpp"

#include <random>
#include <vector>


using namespace std;
using namespace cv;

TrainingSet createTrainingSet(const vector<AreaFuncrion>& f, const TrainingSetParameters& params) {
	
	Mat input(params.size, 2, CV_32F);
	Mat output(params.size, (int)f.size(), CV_32F);

	uniform_real_distribution<float> x_unif(params.xMin, params.xMax);
	uniform_real_distribution<float> y_unif(params.yMin, params.yMax);
	default_random_engine re;

	for (int i = 0; i < params.size; i++)
	{
		float x = x_unif(re);
		float y = y_unif(re);

		input.at<float>(i, 0) = x;
		input.at<float>(i, 1) = y;

		for (int j = 0; j < f.size(); ++j) {
			output.at<float>(i, j) = f[j](x, y) ? 1.f : -1.f;
		}

	}

	return TrainingSet(input, output);
}

TrainingSet createParabolaSet(const TrainingSetParameters& params) {
	vector<AreaFuncrion> f = { insideParabola };
	return createTrainingSet(f, params);
}

TrainingSet createComplexFigureSet(const TrainingSetParameters& params) {
	// see figure with class numbers in ComplexFigure.png
	vector<AreaFuncrion> f = { 
		[](float x, float y) { return leftOfLine(x, y) && outsideCircle(x, y); },
		[](float x, float y) { return leftOfLine(x, y) && insideCircle(x, y); },
		[](float x, float y) { return rightOfLine(x, y) && insideCircle(x, y) && outsideParabola(x, y); },
		[](float x, float y) { return rightOfLine(x, y) && outsideCircle(x, y) && outsideParabola(x, y); },
		[](float x, float y) { return rightOfLine(x, y) && insideCircle(x, y) && insideParabola(x, y); },
		[](float x, float y) { return rightOfLine(x, y) && outsideCircle(x, y) && insideParabola(x, y); },
	};

	return createTrainingSet(f, params);
}

TrainingSet createSinPlusCosSet(const TrainingSetParameters& params) {
	vector<AreaFuncrion> f = { equalSinPlusCos };
	return createTrainingSet(f, params);
}

void createTrainingSetFile(const string& filename, vector<AreaFuncrion> f, const TrainingSetParameters& params) {
	auto training_set = createTrainingSet(f, params);

	// TODO
}
