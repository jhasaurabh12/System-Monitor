#ifndef SYSTEM_PARSER_H
#define SYSTEM_PARSER_H

#include <fstream>
#include <regex>
#include <string>
#include <dirent.h>
#include <vector>


namespace LinuxParser 
{
  const std::string kProcDirectory{"/proc/"};
  const std::string UptimeFilepath="/proc/uptime";
  std::vector<int> Pids();
  long SystemUptime();
};  // namespace LinuxParser

#endif