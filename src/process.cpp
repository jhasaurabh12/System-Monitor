#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include<algorithm>
#include<fstream>

#include "../include/process.h"

using std::string;
using std::to_string;
using std::vector;
using std::istringstream;
using std::ifstream;

Process::Process(string filepath, int pid)
{
    proc_dirPath=filepath;
    pid_=pid;
}

// DONE: Return this process's ID
int Process::Pid()
{ 
    return pid_;
}

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { return 0; }

// DONE: Return the command that generated this process
string Process::Command()
{ 
    string cmdPath=proc_dirPath+"/cmdline";
    ifstream fin(cmdPath);
    string line;
    if(fin)
        getline(fin,line);
    
    return line;
}

// DONE: Return this process's memory utilization
string Process::Ram()
{ 
    string memUtilPath=proc_dirPath+"/status";
    string key,value,line,mem,uid;
    ifstream fin(memUtilPath);
    if(fin)
    {
        
        while(getline(fin,line))
        {
            istringstream stream(line);
            stream>>key>>value;
            if(key=="VmSize:")
                mem=value;
            else if(key=="Uid:")
                uid=value;
        }
    }
    UID=uid;
    // int memKB= std::stoi(mem);
    // float memMB=memKB/1024;
    return mem;
}

// TODO: Return the user (name) that generated this process   //working

string Process::User()
{ 
    string SearchUserFilepath="/etc/passwd";
    ifstream fin(SearchUserFilepath);
    string username,mid,uid;
    if(fin)
    {
        string line;
        while(getline(fin,line))
        {
            std::replace(line.begin(),line.end(),':',' ');
            istringstream stream(line);
            stream>>username>>mid>>uid;
            if(uid==UID)
            {
                break;
            }
        }
    }  
    return username;
}

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return 0; }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a[[maybe_unused]]) const { return true; }