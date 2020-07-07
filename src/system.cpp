
#include "../include/process.h"
#include "../include/processor.h"
#include "../include/system.h"
#include "../include/linux_parser.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;
using std::ifstream;
using std::istringstream;
using std::to_string;

const string KernelNameFilepath ="/proc/version"; 
const string OSnameFilePath="/etc/os-release";
const string StatFilepath="/proc/stat";
const string UptimeFilepath="/proc/uptime";
const string MeminfoFilepath="/proc/meminfo";

// Return the system's CPU
Processor& System::Cpu() { return cpu_; }

// Return a container composed of the system's processes
vector<Process>& System::Processes() 
{ 
    vector<int> pids=LinuxParser::Pids();
    int n=pids.size();
    processes_.clear();
    const string procpath="/proc/";
    for(int i=0;i<n;i++)
    {
        string filepath=procpath+to_string(pids[i]);
        Process p(filepath,pids[i]);
        processes_.push_back(p);
    }
    std::sort(processes_.begin(),processes_.end());
    return processes_;
}

// Return the system's kernel identifier (string)
std::string System::Kernel() { 
    
    string temp1,temp2;
    string version="";
    ifstream fin(KernelNameFilepath);
    if(fin)
    {
        fin>>temp1>>temp2>>version;
    }
    return version;  
}
// Return the system's memory utilization
float System::MemoryUtilization() { 
    
    string key,memfree="0",memtotal="1";
    ifstream fin(MeminfoFilepath);
    string line;
    while(getline(fin,line))
    {
        istringstream stream(line);
        stream>>key;
        if(key=="MemTotal:")
            stream>>memtotal;
        else if(key=="MemFree:")
        {
            stream>>memfree;
            break;
        }
    }
    float F_memfree=stof(memfree);
    float F_memtotal=stof(memtotal);
    return ((F_memtotal-F_memfree)/F_memtotal)*100; 
}

// Return the operating system name
std::string System::OperatingSystem()
{ 
    string OSname="",Osversion;
    string temp,temp2,key;
    ifstream fin(OSnameFilePath);
    if(fin)
    {   string line;
        while(getline(fin,line))
        {
            std::replace(line.begin(),line.end(),' ','_');
            std::replace(line.begin(),line.end(),'=',' ');
            std::replace(line.begin(),line.end(),'"',' ');
            istringstream stream(line);
            if(stream>>key>>OSname)
            {
              if(key=="PRETTY_NAME")
                break;
            }
            
        }
        std::replace(OSname.begin(),OSname.end(),'_',' ');
    }
    return OSname; 
}

// Return the number of processes actively running on the system
int System::RunningProcesses() { 
    string key,line,running="0";
    ifstream fin(StatFilepath);
    while(fin)
    {
        getline(fin,line);
        istringstream stream(line);
        if(stream>>key)
        {
            if(key=="procs_running")
            {
                stream>>running;
                break;
            }
        }
    }  
    return stoi(running); 
}

// Return the total number of processes on the system
int System::TotalProcesses() { 
   string key,line,totalproc="0";
    ifstream fin(StatFilepath);
    while(fin)
    {
        getline(fin,line);
        istringstream stream(line);
        if(stream>>key)
        {
            if(key=="processes")
            {
                stream>>totalproc;
                break;
            }
        }
    }  
    return stoi(totalproc); 
}

//Return the number of seconds since the system started running
long int System::UpTime() { 
    return LinuxParser::SystemUptime();
}