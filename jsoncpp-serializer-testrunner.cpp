#include <chrono>
#include <iostream>
#include <fstream>
#include <json/json.h>

using namespace std;

static int32_t ntimes = 1000;

int main(int argc, char** argv) {
    
    if (argc < 3)
        return -1;
    
    ifstream inputfile(argv[1]);
    ntimes = std::stoi(string(argv[2]));
    std::string to_parse;

    inputfile.seekg(0, std::ios::end);   
    to_parse.reserve(inputfile.tellg());
    inputfile.seekg(0, std::ios::beg);

    to_parse.assign((std::istreambuf_iterator<char>(inputfile)),
                     std::istreambuf_iterator<char>());
    
    Json::Value parsed_object;
    Json::Reader parser;
    bool result = parser.parse(to_parse, parsed_object);
    chrono::steady_clock::time_point start_time = chrono::steady_clock::now();
    for (int i = 0; i < ntimes; ++i) {
        Json::FastWriter writer;
        string output = writer.write(parsed_object);
    }
    chrono::steady_clock::time_point end_time = chrono::steady_clock::now();
    chrono::microseconds us = chrono::duration_cast<chrono::microseconds>(
                               end_time - start_time);
    cout << "[+] Finished successfully with an average of: " << (us.count() / ntimes) << " us\n";
}
