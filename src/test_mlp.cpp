#include "test_mlp.h"
#include "mathTrainingSet.h"
#include "mlp.h"

#include <iostream>
#include <vector>

using namespace std;

void test_classifier(TrainingSetCreator createSet, const TrainingSetParameters& params, const vector<Method>& learn_methods) {
	cout << "Creating training set..." << endl;
	cout << endl;
	cout << "Training set parameters: " << endl;
	cout << "size: " << params.size << endl;
	cout << "xMin: " << params.xMin << endl;
	cout << "xMax: " << params.xMax << endl;
	cout << "yMin: " << params.yMin << endl;
	cout << "yMax: " << params.yMax << endl;
	cout << endl;

	auto training_set = createSet(params);

	cout << "Training set ready, run build_mlp_classifier..." << endl;
	for (auto method : learn_methods) {
		cout << "Build clasifier for " << method.name << endl;
		cout << "Method parameter: " << method.methodParam << endl;
		cout << "Max iter: " << method.maxIter << endl;
		build_mlp_classifier(method, training_set);
		cout << endl;
	}
	cout << endl;
}

void test_method(const vector<Method>& methods) {
	cout << "1) Test mlp classifier for parabola training set" << endl;
	test_classifier(createParabolaSet, PARABOLA_PARAMS, methods);

	cout << "2) Test mlp classifier for complex figure training set" << endl;
	test_classifier(createComplexFigureSet, COMPLEX_FIGURE_PARAMS, methods);

	cout << "3) Test mlp classifier for f(x) = sin(x) + cos(x) training set" << endl;
	test_classifier(createSinPlusCosSet, SIN_PLUS_COS_PARAMS, methods);
}