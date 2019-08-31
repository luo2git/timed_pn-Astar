
#include "h_evaluate.h"
#include "output.h"
#include "tf_model_py.h"






float h_eval(AstarTree *Tr)
{
	Astardata_process(Tr);
	float h;
	const char *path = "A_data/1.txt";
	h = testAstar(path);
	return h;
}

