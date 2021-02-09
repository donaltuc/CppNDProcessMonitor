#include "ReadFile.h"
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <iostream>
#include <vector>
#include<string>
using namespace std;

void ReadFile::readFile(){  

    
    _fileStream.open("/proc/stat");//path to open and read 
    
    _fileStream.exceptions(ifstream::eofbit | ifstream::failbit | ifstream::badbit);
    string fileLine;
    try{
        if(_fileStream){
            
            while( getline(_fileStream, fileLine)){
                 
                _fileData += fileLine + "\n";
                  
                if ( _fileStream.eofbit ) {
                        break;
                    }
            }     

        }
        _fileStream.close();
    }catch( exception const &e){
       cout<< "There was and Error "<< e.what() <<endl;
    }   
    
    
}

void ReadFile::parseFileDataNewLine( int maxIter){
    stringstream strStream(_fileData);
    string subStr;

    int iter = 0;

    while( strStream.good() ){

        if(iter == maxIter){
            break;
        }
        getline(  strStream, subStr,'\n');
        _parsedData.push_back(subStr);
        iter++;
    }

}

void ReadFile::parseFileDataWhitespace(){

    stringstream strStream(_fileData);
    string word;


    while(strStream){
        strStream >> word;
        _parsedData.push_back( word );
       // cout<< word <<endl;
    }
    
}