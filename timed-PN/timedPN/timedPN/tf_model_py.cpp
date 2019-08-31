
#include "tf_model_py.h"


float testAstar(const char * path)
{
	/*try {*/
	Py_Initialize();
	PyEval_InitThreads();
	PyObject*pFunc = NULL;
	PyObject*pArg = NULL;
	PyObject* module = NULL;


	module = PyImport_ImportModule("A_star_test");//myModel:Python文件名??
	if (!module) {
		printf("cannot open module!");
		Py_Finalize();
		return -1.0;
	}
	pFunc = PyObject_GetAttrString(module, "Astar_Predict");//Astar_Predict:Python文件中的函数名??
	if (!pFunc) {
		printf("cannot open FUNC!");
		Py_Finalize();
		return -1.0;
	}
	//开始调用model??
	pArg = Py_BuildValue("(s)", path);
	//cout << pArg;
	if (module != NULL) {
		//PyGILState_STATE gstate;
		//gstate = PyGILState_Ensure();
		PyObject *pRet = PyObject_CallObject(pFunc, pArg);
		float  n = -0.01f;
		PyArg_Parse(pRet, "f", &n);
		printf("%f \n", n);
		//PyGILState_Release(gstate);
		return n;
	}
	//}
	//catch (exception& e)
	//{
	//	cout << "Standard exception: " << e.what() << endl;
	//}
}