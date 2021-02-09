#ifndef Read_File
#define Read_File


#include <string>
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;
class ReadFile
{
private:
    /* data */
    string _path;// /proc/stat/, has to be passed to ReadFile functiomn
    string _fileName;
    ifstream _fileStream;
    string _fileData;//overall file data

    vector<string> _parsedData;

public:
    //constructor, passed relevant file to read
    ReadFile(){

    }
    ReadFile(string p){
        _path = p;
    }//constructor


    void readFile();
    void parseFileDataNewLine( int );
    void parseFileDataWhitespace();
    
    string getFileName()const{
        return _fileName;
    }
    vector<string> getParsedDataFile() const{
        return _parsedData;
    }
    string getRawFileData()const {
        return _fileData;
    }

};

#endif
