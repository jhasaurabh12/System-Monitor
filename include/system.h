#ifndef SYSTEM_H
#define SYSTEM_H


#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>
#include<fstream>
#include<sstream>
#include<algorithm>
#include<iostream>

#include "process.h"
#include "processor.h"

class System {
 public:
  Processor& Cpu();                   
  std::vector<Process>& Processes();  
  float MemoryUtilization();          
  long UpTime();                      
  int TotalProcesses();               
  int RunningProcesses();             
  std::string Kernel();               
  std::string OperatingSystem();      

  // Define any necessary private members
 private:
  Processor cpu_ = {};
  std::vector<Process> processes_ = {};
};

#endif