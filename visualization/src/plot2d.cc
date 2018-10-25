#include "visualization/include/plot2d.h"

namespace mnyrve {
namespace visualization {

Plot2d::Plot2d() {}

void Plot2d::PlotSimple() {


  PyObject *pName, *pModule, *pFunc;
  PyObject *pArgs, *pValue;
  PyObject *sysPath, *pythonPath;


  Py_Initialize();


  // Reading the python paths from the text file
  std::ifstream python_paths_file("tools/data/python_paths.txt");

  if (!python_paths_file) {
    std::cerr << "Unable to open python_paths.txt" << std::endl;
    exit(-3);
  }

  sysPath = PySys_GetObject("path");
  std::string python_path;

  while (std::getline(python_paths_file, python_path)) {

    pythonPath = PyUnicode_DecodeFSDefault(python_path.c_str());
    PyList_Append(sysPath, pythonPath);

  }



  std::string python_file_name = "plot2d";
  pName = PyUnicode_DecodeFSDefault(python_file_name.c_str());

  pModule = PyImport_Import(pName);
  pFunc = PyObject_GetAttrString(pModule, "plot_sample");

  if (PyCallable_Check(pFunc)) {

    PyObject_CallObject(pFunc, NULL);

  } else {

    std::cerr << "Cannot find plot2d.py" << std::endl;
    PyErr_Print();
    exit(-3);

  }

  Py_XDECREF(pModule);
  Py_XDECREF(pName);
  Py_XDECREF(sysPath);
  Py_XDECREF(pythonPath);

  Py_Finalize();


}


} // visualization
} // mnyrve
