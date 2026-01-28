#include "App.hpp"
#include "main.h"

#include <algorithm>
#include <vector>


extern "C" void App_Init(void)
{

  App_ProcessData<int>(42);
  App_ProcessData<double>(42);
  App_ProcessData<float>(42);

  std::vector<int> data = {1, 2, 3, 4, 5};
  
  std::transform(data.begin(), data.end(), data.begin(), App_ProcessData<int>);
}
