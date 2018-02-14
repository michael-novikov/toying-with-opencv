#include "mlp.h"

void build_mlp_classifier(Method method_struct, const TrainingSet& training_set)
{
	int packSize = training_set.first.rows;
	int class_count = training_set.second.cols;

	CvMat *data = cvCreateMat(packSize, training_set.first.cols, CV_32F);
	CvMat *responses = cvCreateMat(packSize, class_count, CV_32F);

	*data = training_set.first;
	*responses = training_set.second;

	int nSamplesAll = 0, nSamplesTrain = 0;
	double trainHr = 0, testHr = 0;
	CvMat trainData;
	CvMat *trainResponses;
	CvMat* mlpResponse = 0;
	CvANN_MLP mlp;

	// Задаем сколько элементов из выборки для обучения
	nSamplesAll = data->rows;
	nSamplesTrain = (int)(nSamplesAll * 0.8);

	// Вытаскиваем из всей выборки элементы для обучения
	trainResponses = cvCreateMat(nSamplesTrain, class_count, CV_32F);
	cvGetRows(responses, trainResponses, 0, nSamplesTrain);
	cvGetRows(data, &trainData, 0, nSamplesTrain);

	// Cоздание классификатора
	vector<int> layers = { data->cols };
	layers.insert(++layers.begin(), method_struct.hidden_layers.begin(), method_struct.hidden_layers.end());
	layers.push_back(class_count);

	CvMat layersSizes = cvMat(1, (int)method_struct.hidden_layers.size() + 2, CV_32S, layers.data());
	mlp.create(&layersSizes);

	// Обучение классификатора
	cout << "Training classifier.." << endl;

	int method = method_struct.method;
	double methodParam = method_struct.methodParam;
	int maxIter = method_struct.maxIter;

	int kk = mlp.train(&trainData, trainResponses, 0, 0,
		CvANN_MLP_TrainParams(cvTermCriteria(CV_TERMCRIT_ITER, maxIter, 0.01), method, methodParam));
	cvReleaseMat(&trainResponses);
	cout << "Number of iterations: " << kk << endl;

	// Тестирование классификатора
	mlpResponse = cvCreateMat(1, class_count, CV_32F);
	for (int i = 0; i < nSamplesAll; i++)
	{
		// получаю текущий образец из выборки
		int resultClass, expectedClass;
		CvMat sample;
		cvGetRow(data, &sample, i);

		// пропускаю через классификатор и смотрю выход
		mlp.predict(&sample, mlpResponse);
		for (int j = 0; j < class_count; j++)
			if (mlpResponse->data.fl[j] > 0)
				resultClass = j;

		for (int j = 0; j < class_count; j++)
		{
			//cout << CV_MAT_ELEM(*responses, float, i, j) << " ";
			if (CV_MAT_ELEM(*responses, float, i, j) > 0)
				expectedClass = j;
		}

		// сравниваю выход с ответов из выборки
		int r = resultClass == expectedClass ? 1 : 0;
		if (i < nSamplesTrain)
			trainHr += r;
		else
			testHr += r;
	}

	testHr /= (double)(nSamplesAll - nSamplesTrain);
	trainHr /= (double)(nSamplesTrain);

	cout << "Recognition rate: train = " << trainHr * 100 << "%" << ", test = " << testHr * 100 << "%" << endl;
}