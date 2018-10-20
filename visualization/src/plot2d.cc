#include "visualization/include/plot2d.h"
#include <iostream>

namespace mnyrve {
namespace visualization {

Plot2d::Plot2d() {}

void Plot2d::PlotSample() {

  PyObject *pName, *pModule, *pFunc, *pDict;
  PyObject *pArgs, *pValue;

  Py_Initialize();
  pName = PyUnicode_DecodeFSDefault("test2");
  //pName = PyString_FromString("plot2d");
  pModule = PyImport_Import(pName);
  Py_DECREF(pName);

  pFunc = PyObject_GetAttrString(pModule, "test_func");

  //pDict = PyModule_GetDict(pModule);

  //PyObject* repr = PyObject_Repr(pDict);
  //const char* s = PyUnicode_AsUTF8(repr);
  //std::cout << s << std::endl;

  //pFunc = PyDict_GetItemString(pDict, "test_func");

  //if (PyCallable_Check(pFunc)) {
  //  std::cout << "Calling" << std::endl;

  //  PyObject_CallObject(pFunc, NULL);

  //} else {
  //  std::cout << "Not" << std::endl;

  //  PyErr_Print();

  //}

  //Py_DECREF(pModule);
  //Py_DECREF(pName);
  //Py_DECREF(repr);

  //Py_Finalize();


}


} // visualization
} // mnyrve
