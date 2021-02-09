#include "processor.h"
#include <fstream>
#include <sstream>      
#include <iostream>
#include <vector>


enum CPUStates
{
	S_USER = 0,
	S_NICE,
	S_SYSTEM,
	S_IDLE,
	S_IOWAIT,
	S_IRQ,
	S_SOFTIRQ,
	S_STEAL,
	S_GUEST,
	S_GUEST_NICE
};

void CPUData::ReadStatsCPU(vector<CPUData> &entries)
{
	/*vector<CPUData> entries1;
    vector<CPUData> entries2;*/
	//vector<vector<CPUData>> cpuVec;
	CPUData cpuData;
	string path = cpuData.getPath();
    ifstream fileStat( path );

	string line;

	const string STR_CPU("cpu");
	const size_t LEN_STR_CPU = STR_CPU.size();
	const string STR_TOT("tot");

	while(getline(fileStat, line))
	{
		
		// _cpu stats line found
		if(!line.compare(0, LEN_STR_CPU, STR_CPU))
		{			
			
			istringstream inStrStream(line);			
			
			entries.emplace_back(CPUData());//calling a constructor in CPUData
			CPUData & entry =  entries.back();

			// read _cpu label
			inStrStream >> entry._cpu;

			if(entry._cpu.size() > LEN_STR_CPU)
				entry._cpu.erase(0, LEN_STR_CPU);
			else
				entry._cpu = STR_TOT;

			// read _times
			for(int i = 0; i < 10; ++i)
			//populate array times 
				inStrStream >> entry._times[i];
		}
    }
}

size_t CPUData::GetIdleTime(const CPUData & e)
{
    return  e._times[S_IDLE] +
            e._times[S_IOWAIT];
}

size_t CPUData::GetActiveTime(const CPUData & e)
{
    return  e._times[S_USER] +
            e._times[S_NICE] +
            e._times[S_SYSTEM] +
            e._times[S_IRQ] +
            e._times[S_SOFTIRQ] +
            e._times[S_STEAL] +
            e._times[S_GUEST] +
            e._times[S_GUEST_NICE];
}
//Printing stats to console
void CPUData::PrintStats(const vector<CPUData> & entries1, const vector<CPUData> & entries2)
{
	const size_t NUM_ENTRIES = entries1.size();

	for(size_t i = 0; i < NUM_ENTRIES; ++i)
	{
		const CPUData & e1 = entries1[i];
		const CPUData & e2 = entries2[i];

		cout.width(3);
		cout << e1._cpu << "] ";

		const float ACTIVE_TIME	= static_cast<float>(GetActiveTime(e2) - GetActiveTime(e1));
		const float IDLE_TIME	= static_cast<float>(GetIdleTime(e2) - GetIdleTime(e1));
		const float TOTAL_TIME	= ACTIVE_TIME + IDLE_TIME;

		cout << "active: ";
		cout.setf(ios::fixed, ios::floatfield);
		cout.width(6);
		cout.precision(2);
		cout << (100.f * ACTIVE_TIME / TOTAL_TIME) << "%";

		cout << " - idle: ";
		cout.setf(ios::fixed, ios::floatfield);
		cout.width(6);
		cout.precision(2);
		cout << (100.f * IDLE_TIME / TOTAL_TIME) << "%" << endl;
	}
}