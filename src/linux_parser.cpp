
#include "../include/linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;
using std::istringstream;


// Returns int vector containing the PIDS
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), [](char c){return (c>='1' && c<='9');})) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

long LinuxParser::SystemUptime()
{
  string idle,uptime="0";
    std::ifstream fin(UptimeFilepath);
    if(fin)
    {
        string line;
        getline(fin,line);
        istringstream stream(line);
        stream>>uptime>>idle;
        
    }
    return stol(uptime);
}