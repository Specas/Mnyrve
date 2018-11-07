#include "environments/grid_world/include/grid_world.h"

namespace mnyrve {
namespace environments {

GridWorld::GridWorld(int num_states, 
                     int num_actions, 
                     double normal_reward, 
                     double obstacle_reward, 
                     double goal_reward):
  num_states_(num_states), num_actions_(num_actions), 
  normal_reward_(normal_reward), obstacle_reward_(obstacle_reward), 
  goal_reward_(goal_reward) {

    MN_REQUIRE((std::sqrt(num_states_) == std::floor(std::sqrt(num_states_))), 
        "The number of states must be a perfect square.");
    cell_state_.reserve(num_states_);

  }

int GridWorld::GetNumStates() {
  return num_states_;
}

int GridWorld::GetNumActions() {
  return num_actions_;
}

double GridWorld::GetNormalReward() {
  return normal_reward_;
}

double GridWorld::GetObstacleReward() {
  return obstacle_reward_;
}

double GridWorld::GetGoalReward() {
  return goal_reward_;
}

std::vector<double> GridWorld::GetCellState() {
  return cell_state_;
}

void GridWorld::SetNumStates(int num_states) {

  MN_REQUIRE((std::sqrt(num_states) == std::floor(std::sqrt(num_states))), 
      "The number of states must be a perfect square.");
  num_states_ = num_states;

}

void GridWorld::SetNumActions(int num_actions) {
  num_actions_ = num_actions;
}

void GridWorld::SetNormalReward(double normal_reward) {
  normal_reward_ = normal_reward;
}

void GridWorld::SetObstacleReward(double obstacle_reward) {
  obstacle_reward_ = obstacle_reward;
}

void GridWorld::SetGoalReward(double goal_reward) {
  goal_reward_ = goal_reward;
}

void GridWorld::SetCellState(std::vector<double> cell_state) {

  MN_REQUIRE((int(cell_state.size()) == num_states_), 
      "The size of the vector must equal the number of states.");
  cell_state_ = cell_state;
}

void GridWorld::SetUp() {

  PyObject *pName, *pModule, *pFunc;
  PyObject *pArgs, *pValue, *pListCellState, *pElem; 
  PyObject *sysPath, *pythonPath;

  Py_Initialize();
  //size_t argv_size = strlen(argv) + 1;
  //PySys_SetArgv(argc, argv.c_str());

  // Reading the python paths from the text file in data/
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

  std::string python_filel_name = "grid_world";
  std::string python_function_name = "setup_grid_world";
  pName = PyUnicode_DecodeFSDefault(python_filel_name.c_str());
  pModule = PyImport_Import(pName);

  if (pModule != NULL) {

    pFunc = PyObject_GetAttrString(pModule, python_function_name.c_str());

    if (pFunc && PyCallable_Check(pFunc)) {

      pArgs = PyTuple_New(1);
      pListCellState = PyList_New(num_states_);
      
      int set_error_code;

      pElem = PyLong_FromLong(num_states_);
      set_error_code = PyTuple_SetItem(pArgs, 0, pElem);
      MN_REQUIRE((set_error_code == 0), 
          "Failed to add number of states to argument.");

      pValue = PyObject_CallObject(pFunc, pArgs);

      // Addting to cell_state_
      for (int i = 0; i < num_states_; i++) {

        cell_state_.push_back(PyFloat_AsDouble(PyList_GetItem(pValue, i)));

      }


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



}

} // namespace environments
} // namespace mnyrve
