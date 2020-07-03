#include <string>

#include "../include/format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string convert( int x)
{
    if(x>=10)
     return std::to_string(x);
    else
    {
        string temp =std::to_string(x);
        string temp1="0";
        return temp+temp1;
    }
}
string Format::ElapsedTime(long seconds) { 
    int h=seconds/3600;
    int m = (seconds-(h*3600))/60;
    int s = seconds%60;
    string hh,mm,ss;

    string uptime=convert(h)+":"+convert(m)+":"+convert(s);
    return uptime;
}