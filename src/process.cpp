#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include<algorithm>
#include<fstream>

#include "../include/process.h"
#include"../include/linux_parser.h"

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

// Return this process's ID
int Process::Pid()
{ 
    return pid_;
}

//Return this process's CPU utilization
float Process::CpuUtilization() const 
{ 
    string uptime;
    long uptimeS=1;
    long utimeS=0,stimeS=0,cutimeS=0,cstimeS=0,starttimeS=0;
    string UptimePath="/proc/uptime";
    ifstream fin(UptimePath);
    if(fin)
    {   string line;
        getline(fin,line);
        istringstream stream(line);
        stream>>uptime;
        uptimeS=stol(uptime);
    }
    fin.close();
    fin.open(proc_dirPath+"/stat");
    float percent=0.0;
    if(fin)
    {
        string temp,line;
        getline(fin,line);
        istringstream stream(line);
        for(int i=0;i<22;i++)
        {
            stream>>temp;
            switch(i)
            {
                case(13): utimeS=stol(temp); break;
                case(14): stimeS=stol(temp); break;
                case(15): cutimeS=stol(temp); break;
                case(16): cstimeS=stol(temp); break;
                case(21): starttimeS=stol(temp); break;
                default: break;
            };
        }
        const long int ticks= sysconf(_SC_CLK_TCK);
        long activetime=uptimeS- (starttimeS/ticks);
        long totaltime=utimeS+stimeS+cutimeS+cstimeS;
        totaltime/=ticks;
        percent= ((float)totaltime/activetime);
    }
    return percent; 
}

//Return the command that generated this process
string Process::Command()
{ 
    string cmdPath=proc_dirPath+"/cmdline";
    ifstream fin(cmdPath);
    string line;
    if(fin)
        getline(fin,line);
    fin.close();
    if(line.empty())
    {
        string temp=proc_dirPath+"/status";
        fin.open(temp);
        if(fin)
        {   
            string key,name;
            while(getline(fin,line))
            {
                istringstream stream(line);
                stream>>key>>name;
                if(key=="Name:")
                    break;
            }
            name="["+name+"]";
            line=name;
        }

    }
    return line;
}

//Return this process's memory utilization
string Process::Ram() const
{ 
    string memUtilPath=proc_dirPath+"/status";
    string key,value,line,mem="0",uid;
    ifstream fin(memUtilPath);
    if(fin)
    {
        
        while(getline(fin,line))
        {
            istringstream stream(line);
            stream>>key>>value;
            if(key=="VmSize:")
            {
                mem=value;
                break;
            }
        }
    }
    int memKB= std::stoi(mem);
    int memMB=memKB/1024;
    return to_string(memMB);
}

//Return the user (name) that generated this process   

string Process::User()
{   
    string memUtilPath=proc_dirPath+"/status";
    string key,value,line,UID;
    ifstream fin(memUtilPath);
    if(fin)
    {
        
        while(getline(fin,line))
        {
            istringstream stream(line);
            stream>>key>>value;
            if(key=="Uid:")
            {
                UID=value;
                break;
            }
        }
    }
    fin.close();
    string SearchUserFilepath="/etc/passwd";
    fin.open(SearchUserFilepath);
    string username="username not found",mid,uid;
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

//Return the age of this process (in seconds)
long int Process::UpTime() 
{   //calculating system uptime
    

    string StatfilePath=proc_dirPath+"/stat";
    ifstream fin(StatfilePath);
    string line;
    long int seconds;
    if(fin)
    {
        getline(fin,line);
        istringstream stream(line);
        string ticks="0";
        for(int i=0;i<22;i++)
            stream>>ticks;
        seconds= stoi(ticks)/sysconf(_SC_CLK_TCK);
    }
    return LinuxParser::SystemUptime()-seconds; 
}

//Overload the "less than" comparison operator for Process objects
bool Process::operator<(Process const& a) const 
{ 
    return a.CpuUtilization() < this->CpuUtilization();  
}