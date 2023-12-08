#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <sstream>
#include <vector>
#include <cmath>
#include <numeric>


void p1(std::ifstream &input);

void p2(std::ifstream &input);

int main() {
    std::ifstream input(R"(..\input08.txt)");
    p1(input);
    input.close();
    std::ifstream input2(R"(..\input08.txt)");
    p2(input2);
    input2.close();
}

void p1(std::ifstream &input) {
    std::unordered_map<std::string, std::pair<std::string, std::string>> graph;
    std::string instructions;
    getline(input, instructions);
    for (std::string line; getline(input, line);) {
        if (line.empty()) continue;
        std::stringstream ss(line);
        std::string key;
        getline(ss, key, '=');
        key = key.substr(0, key.length() - 1);
        std::pair<std::string, std::string> p = std::make_pair("", "");
        getline(ss, p.first, ',');
        p.first = p.first.substr(2, p.first.length() - 1);
        getline(ss, p.second, ')');
        p.second = p.second.substr(1, p.second.length());
        graph.insert({key, p});
    }
    int i = 0;
    int steps = 0;
    std::string curLoc = "AAA";
    while (curLoc != "ZZZ") {
        curLoc = instructions[i] == 'L' ? graph.at(curLoc).first : graph.at(curLoc).second;
        i++;
        steps++;
        if (i == instructions.length()) i = 0;
    }
    std::cout << "p1:" << steps << "\n";
}

void p2(std::ifstream &input) {
    std::vector<std::string> startLoc;
    std::unordered_map<std::string, std::pair<std::string, std::string>> graph;
    std::string instructions;
    getline(input, instructions);
    for (std::string line; getline(input, line);) {
        if (line.empty()) continue;
        std::stringstream ss(line);
        std::string key;
        getline(ss, key, '=');
        key = key.substr(0, key.length() - 1);
        std::pair<std::string, std::string> p = std::make_pair("", "");
        getline(ss, p.first, ',');
        p.first = p.first.substr(2, p.first.length() - 1);
        getline(ss, p.second, ')');
        p.second = p.second.substr(1, p.second.length());
        graph.insert({key, p});
        if (key[key.length() - 1] == 'A') startLoc.push_back(key);
    }
    std::vector<int> stepAmount;
    for (auto p: startLoc) {
        int i = 0;
        int steps = 0;
        while (p[2] != 'Z') {
            p = instructions[i] == 'L' ? graph.at(p).first : graph.at(p).second;
            i++;
            steps++;
            if (i == instructions.length()) i = 0;
        }
        stepAmount.push_back(steps);
    }
    std::cout << (unsigned long long int)std::accumulate(stepAmount.begin(),stepAmount.end(),(unsigned long long int)1,[](unsigned long long int a,unsigned long long int b) -> unsigned long long int{return (unsigned long long int)std::lcm(a,b);}) << "\n";
}