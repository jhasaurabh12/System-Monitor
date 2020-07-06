#include "../include/processor.h"

//It returns the robust and average Utilization
//It can be upgraded to calculate the recent utilization using delta interval between two calculations

float Processor::Utilization() 
{ 
    
    const string ProcessorPath="/proc/stat";
    ifstream fin(ProcessorPath);
    std::vector<long int> values(10,0);
    if(fin)
    {
        string line,temp;
        getline(fin,line);
        istringstream stream(line);
        stream>>temp;
        for(int i=0;i<10;i++)
        {
            stream>>temp;
            values[i]=std::stol(temp);
        }
    }
    long int idle = values[3]+values[4];
    long int nonidle=values[0]+values[1]+values[2]+values[5]+values[6]+values[7];

    float util=(((float)nonidle)/(idle+nonidle))*100;
    return util; 
}