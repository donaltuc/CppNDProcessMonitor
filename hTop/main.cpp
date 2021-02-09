#include "ReadFile.h"
#include "processor.h"
#include<iostream>
#include <chrono>
#include <thread>
using namespace std;

int main(){
    vector<CPUData> entries;
    vector<CPUData> entries1;
    vector<CPUData> entries2;
    CPUData cpuData;

	cpuData.getDesiredValues();
    cpuData.ReadStatsCPU(entries);

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    cpuData.ReadStatsCPU(entries1);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    cpuData.ReadStatsCPU(entries2);

    /* vector<string> vec = cpuData.getParsedDataFile();

    for(vector<string>::iterator it = vec.begin(); it != vec.end(); ++it) {
        cout << *it; 
    }*/
    
    cpuData.PrintStats( entries1, entries2  );
    return 0;

}