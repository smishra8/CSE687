// MathLibrary.cpp : Defines the exported functions for the DLL.
#include "pch.h"
#include "framework.h"
#include "CMapper.h"
#include <iostream>
 
// Create Object
CMAPPERLIBRARY_API ICMapper* _cdecl CreateMapperObject() {
    return new CMapper();
};

double CMapper::Add(double a, double b) {
    std::cout << "Inside Mapper (filename,strline)";
    return a + b;
};

void CMapper::Map(std::string filename, std::string strline) {
    std::cout << "Inside Mapper (filename,strline)";
    tokenize_line(strline);
};

void CMapper::tokenize_line(std::string strLine) {
    int bufferSize = 10;
    std::string templine = boost::erase_all_regex_copy(strLine, boost::regex("[^a-zA-Z0-9 ]+"));
    std::vector<std::string> words;

    // split to tokens line seperated by space and store in vector.
    char space_char = ' ';
    boost::split(words, templine, boost::is_any_of(" "));

    for (int i = 0; i < words.size(); i++)
    {
        if (words[i].length() == 0)
            continue;
        wordMap.insert(std::pair<std::string, int>(words[i], 1));
    }
};
/*
* The export function will buffer output in memory and periodically write the data out to disk (periodicity can be based on the size of the buffer).
  The intermediate data will be written to the temporary directory (specified via command line).
  The buffer to be written is passed back to workflow so that fileManager class can be utilized to write output to disk.
*/
std::multimap<std::string, int, std::less<std::string>> CMapper::exportData() {
    return wordMap;
};

void CMapper::bufferFlush() {
    // clear buffer 
    wordMap.clear();
};
