#include<bits/stdc++.h>
#include<algorithm>
#include <fstream>
#include <regex>
#include <string>
#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>

using namespace std;

const std::string kProcDirectory{"/proc/"};
class Process
{
  public:
    int PID();
    string COMMAND();
    string USER();
    string RAM();
    Process(int pid, string procpath);
  private:
    int pid_;
    string UID_;
    string procpath_;
};
Process::Process(int pid, string procpath)
{
  pid_=pid;
  procpath_=procpath;
}
int Process::PID()
{
  return pid_;
}

string Process::COMMAND()
{
    string cmdPath=procpath_+"/cmdline";
    ifstream fin(cmdPath);
    string line;
    if(fin)
        getline(fin,line);
    
    return line;
}
string Process::RAM()
{
  string memUtilPath=procpath_+"/status";
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
        }
    }
    return mem;
}

string Process::USER()
{   
    string memUtilPath=procpath_+"/status";
    string key,value,line,mem,UID;
    ifstream fin(memUtilPath);
    if(fin)
    {
        
        while(getline(fin,line))
        {
            istringstream stream(line);
            stream>>key>>value;
            if(key=="Uid:")
                UID=value;
        }
    }
    fin.close();

    string SearchUserFilepath="/etc/passwd";
     fin.open(SearchUserFilepath);
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
vector<int> PIDS()
{
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), [](char c){return (c>='1' && c<='9');})) 
      {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}
void DISPLAY(vector<Process> &pv)
{
    for(int i=0;i<pv.size();i++)
    {
      cout<<pv[i].PID()<<"   "<<pv[i].USER()<<"   "<<pv[i].RAM()<<"   "<<pv[i].COMMAND()<<endl;
    }
}
int main()
{
  
    vector<int> pids=PIDS();
    int n=pids.size();
    vector<Process> proc_vec;
    for(int i=0;i<n;i++)
    {
        string temp=kProcDirectory+to_string(pids[i]);
        Process p(pids[i],temp);
        proc_vec.push_back(p);
    }
    vector<int> k={1781};
    DISPLAY(proc_vec);
    return 0; 
}