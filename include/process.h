#ifndef PROCESS_H
#define PROCESS_H

#include <string>

/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
using std::string;
class Process {
 public:
  int Pid();                              
  std::string User();                     
  std::string Command();                  
  float CpuUtilization() const;           
  std::string Ram() const;                
  long int UpTime();                      
  bool operator<(Process const& a) const; 
  Process(string filepath, int pid);          //constructor

  // Declare any necessary private members
 private:
 int pid_;
 string proc_dirPath;
 string UID;
};

#endif