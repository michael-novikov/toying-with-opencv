#include "test_mlp.h"

#include <iostream>

void main() {
	vector<Method> methods = {BACKPROP_METHOD_3_H_LAYERS, RPROP_METHOD_3_H_LAYERS};
	test_method(methods);

	system("pause");
}
