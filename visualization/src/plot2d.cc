#include "visualization/include/plot2d.h"

namespace mnyrve {
namespace visualization {

Plot2d::Plot2d() {}

void Plot2d::PlotSimple(Eigen::VectorXd x, Eigen::VectorXd y) {

  MN_REQUIRE((x.size() == y.size()), 
      "x and y must have the same number of elements");

  PyObject *pName, *pModule, *pFunc;
  PyObject *pArgs, *pListX, *pListY, *pElem;
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
  std::string python_function_name = "plot_simple";
  pName = PyUnicode_DecodeFSDefault(python_file_name.c_str());
  pModule = PyImport_Import(pName);


  if (pModule != NULL) {

    pFunc = PyObject_GetAttrString(pModule, python_function_name.c_str());

    if (pFunc && PyCallable_Check(pFunc)) {

      pArgs = PyTuple_New(2);
      pListX = PyList_New(x.size());
      pListY = PyList_New(y.size());

      int set_error_code;

      for (int i = 0; i < x.size(); i++) {

        pElem = PyFloat_FromDouble(x(i));
        set_error_code = PyList_SetItem(pListX, i, pElem);
        MN_REQUIRE((set_error_code == 0), 
            "Failed to add element to x");

      }

      for (int i = 0; i < y.size(); i++) {

        pElem = PyFloat_FromDouble(y(i));
        set_error_code = PyList_SetItem(pListY, i, pElem);
        MN_REQUIRE((set_error_code == 0), 
            "Failed to add element to y");

      }

      // Adding the individual objects to the arguments tuple
      set_error_code = PyTuple_SetItem(pArgs, 0, pListX);
      MN_REQUIRE((set_error_code == 0), 
          "Failed to add list to argument");

      set_error_code = PyTuple_SetItem(pArgs, 1, pListY);
      MN_REQUIRE((set_error_code == 0), 
          "Failed to add list to argument");

      PyObject_CallObject(pFunc, pArgs);

    } else {

      std::cerr << "Cannot find function." << std::endl;
      PyErr_Print();
      exit(-3);

    }


  } else {

    PyErr_Print();
    std::cerr << "Cannot find file." << std::endl;
    exit(-3);

  }


  Py_XDECREF(pArgs);
  Py_XDECREF(pListX);
  Py_XDECREF(pListY);
  Py_XDECREF(pElem);
  Py_XDECREF(sysPath);
  Py_XDECREF(pythonPath);
  Py_XDECREF(pName);
  Py_XDECREF(pFunc);
  Py_XDECREF(pModule);

  Py_Finalize();


}


void Plot2d::PlotComplete(
    Eigen::VectorXd x, 
    Eigen::VectorXd y, 
    mnyrve::common::types::PlotDetails plot_details) {



  MN_REQUIRE((x.size() == y.size()), 
      "x and y must have the same number of elements");

  PyObject *pName, *pModule, *pFunc;
  PyObject *pArgs, *pListX, *pListY, *pElem;
  PyObject *pDictDetails, *pDictXLimits, *pDictYLimits;
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
  std::string python_function_name = "plot_complete";
  pName = PyUnicode_DecodeFSDefault(python_file_name.c_str());
  pModule = PyImport_Import(pName);


  if (pModule != NULL) {

    pFunc = PyObject_GetAttrString(pModule, python_function_name.c_str());

    if (pFunc && PyCallable_Check(pFunc)) {

      pArgs = PyTuple_New(3);
      pListX = PyList_New(x.size());
      pListY = PyList_New(y.size());

      int set_error_code;

      // Creating the x list
      for (int i = 0; i < x.size(); i++) {

        pElem = PyFloat_FromDouble(x(i));
        set_error_code = PyList_SetItem(pListX, i, pElem);
        MN_REQUIRE((set_error_code == 0), 
            "Failed to add element to x");

      }

      // Creating the y list
      for (int i = 0; i < y.size(); i++) {

        pElem = PyFloat_FromDouble(y(i));
        set_error_code = PyList_SetItem(pListY, i, pElem);
        MN_REQUIRE((set_error_code == 0), 
            "Failed to add element to y");

      }

      // Creating the details dictionary
      pDictDetails = PyDict_New();
      pDictXLimits = PyDict_New();
      pDictYLimits = PyDict_New();


      // Adding the x limits
      pElem = PyFloat_FromDouble(plot_details.x_limits.lower);
      set_error_code = PyDict_SetItemString(pDictXLimits, "lower", pElem);
      MN_REQUIRE((set_error_code == 0), 
          "Failed to add lower x_limits element");

      pElem = PyFloat_FromDouble(plot_details.x_limits.upper);
      set_error_code = PyDict_SetItemString(pDictXLimits, "upper", pElem);
      MN_REQUIRE((set_error_code == 0), 
          "Failed to add upper x_limits element");


      // Adding the y limits
      pElem = PyFloat_FromDouble(plot_details.y_limits.lower);
      set_error_code = PyDict_SetItemString(pDictYLimits, "lower", pElem);
      MN_REQUIRE((set_error_code == 0), 
          "Failed to add lower y_limits element");

      pElem = PyFloat_FromDouble(plot_details.y_limits.upper);
      set_error_code = PyDict_SetItemString(pDictYLimits, "upper", pElem);
      MN_REQUIRE((set_error_code == 0), 
          "Failed to add upper y_limits element");


      // Adding the string details
      pElem = PyUnicode_FromString(plot_details.figure_title.c_str());
      set_error_code = PyDict_SetItemString(pDictDetails, "figure_title", pElem);
      MN_REQUIRE((set_error_code == 0), 
          "Failed to add figure_title element");

      pElem = PyUnicode_FromString(plot_details.plot_title.c_str());
      set_error_code = PyDict_SetItemString(pDictDetails, "plot_title", pElem);
      MN_REQUIRE((set_error_code == 0), 
          "Failed to add plot_title element");

      pElem = PyUnicode_FromString(plot_details.x_label.c_str());
      set_error_code = PyDict_SetItemString(pDictDetails, "x_label", pElem);
      MN_REQUIRE((set_error_code == 0), 
          "Failed to add x_label element");

      pElem = PyUnicode_FromString(plot_details.y_label.c_str());
      set_error_code = PyDict_SetItemString(pDictDetails, "y_label", pElem);
      MN_REQUIRE((set_error_code == 0), 
          "Failed to add y_label element");

      pElem = PyUnicode_FromString(plot_details.fmt.c_str());
      set_error_code = PyDict_SetItemString(pDictDetails, "fmt", pElem);
      MN_REQUIRE((set_error_code == 0), 
          "Failed to add fmt element");


      // Adding the limits to the dict
      set_error_code = PyDict_SetItemString(
          pDictDetails, "x_limits", pDictXLimits);
      MN_REQUIRE((set_error_code == 0), 
          "Failed to add x_limits element");

      set_error_code = PyDict_SetItemString(
          pDictDetails, "y_limits", pDictYLimits);
      MN_REQUIRE((set_error_code == 0), 
          "Failed to add y_limits element");



      // Adding the individual objects to the arguments tuple
      set_error_code = PyTuple_SetItem(pArgs, 0, pListX);
      MN_REQUIRE((set_error_code == 0), 
          "Failed to add x to argument");

      set_error_code = PyTuple_SetItem(pArgs, 1, pListY);
      MN_REQUIRE((set_error_code == 0), 
          "Failed to add y to argument");

      set_error_code = PyTuple_SetItem(pArgs, 2, pDictDetails);
      MN_REQUIRE((set_error_code == 0), 
          "Failed to add plot_details to argument");

      PyObject_CallObject(pFunc, pArgs);

    } else {

      std::cerr << "Cannot find function." << std::endl;
      PyErr_Print();
      exit(-3);

    }


  } else {

    PyErr_Print();
    std::cerr << "Cannot find file." << std::endl;
    exit(-3);

  }


  Py_XDECREF(pArgs);
  Py_XDECREF(pListX);
  Py_XDECREF(pListY);
  Py_XDECREF(pElem);
  Py_XDECREF(pDictDetails);
  Py_XDECREF(pDictXLimits);
  Py_XDECREF(pDictYLimits);
  Py_XDECREF(sysPath);
  Py_XDECREF(pythonPath);
  Py_XDECREF(pName);
  Py_XDECREF(pFunc);
  Py_XDECREF(pModule);

  Py_Finalize();


}


} // visualization
} // mnyrve
