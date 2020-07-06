#include<bits/stdc++.h>
#include <unistd.h>
using namespace std;
const string proc_dirPath="/proc/22976";
int main()
{
     string uptime;
    long uptimeS;
    long utimeS,stimeS,cutimeS,cstimeS,starttimeS;
    string UptimePath="/proc/uptime";
    ifstream fin(UptimePath);
    if(fin)
    {   string line;
        getline(fin,line);
        istringstream stream(line);
        stream>>uptime;
        uptimeS=stol(uptime);
    }
    // cout<<uptimeS<<endl;
    fin.close();
    fin.open(proc_dirPath+"/stat");
    float percent;
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
        percent= ((float)totaltime/activetime)*100;
    }
    cout<<percent<<endl; 
    return 0;
}