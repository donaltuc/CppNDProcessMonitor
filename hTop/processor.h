#ifndef READ_CPU_H
#define READ_CPU_H

#include "ReadFile.h"
#include <iostream>
#include <vector>
using namespace std;
   
const int NUM_CPU_STATES = 10;
class CPUData: public ReadFile{
       
      private:
        string _cpu;
        size_t _times[10];     
      protected:  
        const string _path{"/proc/stat"};
        
      public:
        CPUData():ReadFile(_path ){

        };
        //ReadFile constructor called with path to /proc/stat/
       /* CPUData(string path):_path(path), ReadFile(path){

            
        }  */
        string getPath(){
          return _path;
        }
         
        
        void ReadStatsCPU(vector<CPUData> &entries);
        size_t GetActiveTime(const CPUData & e);
        size_t GetIdleTime(const CPUData & e);
        float calculatePercentage( vector<int>& cpu_data );
        void PrintStats(const vector<CPUData> & entries1, const vector<CPUData> & entries2);

       
        vector<int> getDesiredValues() {
            vector<int> output;
            ReadFile::readFile();

            ReadFile::parseFileDataWhitespace();
            vector<string> data =  ReadFile::getParsedDataFile();
            output = {stoi(data[2]), stoi(data[3]), stoi(data[4]), stoi(data[5]),stoi(data[6])};
           
        return output;
    }  
};
#endif