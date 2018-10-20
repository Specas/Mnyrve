#include "visualization/include/plot2d.h"
#include <iostream>

namespace mnyrve {
namespace visualization {

Plot2d::Plot2d() {}

void Plot2d::PlotSample() {

  PyObject *pName, *pModule, *pFunc, *pDict;
  PyObject *pArgs, *pValue;

  Py_Initialize();
  pName = PyUnicode_DecodeFSDefault("plot2d");

  
  pModule = PyImport_Import(pName);

  pFunc = PyObject_GetAttrString(pModule, "plot_sample");

  if (PyCallable_Check(pFunc)) {
    std::cout << "Calling" << std::endl;

    PyObject_CallObject(pFunc, NULL);

  } else {
    std::cout << "Not" << std::endl;

    PyErr_Print();

  }

  Py_DECREF(pModule);
  Py_DECREF(pName);
  //Py_DECREF(repr);

  //Py_Finalize();


}


} // visualization
} // mnyrve
