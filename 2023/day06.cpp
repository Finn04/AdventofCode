#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

void p1(std::ifstream &input);

void p2(std::ifstream &input);

int main() {
    std::ifstream input(R"(../input06.txt)");
    p1(input);
    input.close();
    std::ifstream input2(R"(../input06.txt)");
    p2(input2);
    input2.close();
}

long long int determine_possible_wins(std::pair<long long int,long long int> p) {
    long long int res = 0;
    for (long long i = 0; i < p.first; i++) {
        long long int time_left = p.first - i;
        if (time_left * i > p.second) res++;
    }
    return res;
}

void p1(std::ifstream &input) {
    std::vector<std::pair<int, int>> race;
    int i = 0;
    int res = 1;
    for (std::string line; getline(input, line);) {
        std::stringstream ss(line);
        int j = 0;
        getline(ss, line, ':');
        while (getline(ss, line, ' ')) {
            if (line.empty()) continue;
            if (i == 0) race.emplace_back(std::stoi(line), 0);
            if (i == 1) race.at(j).second = std::stoi(line);
            j++;
        }
        i++;
    }
    for (auto &p: race) {
        res *= (int) determine_possible_wins(p);
    }
    std::cout << res << "\n";
}


void p2(std::ifstream &input) {
    std::pair<long long int, long long int> race;
    int i = 0;
    for (std::string line; getline(input, line);) {
        std::string temp ;
        std::stringstream ss(line);
        int j = 0;
        getline(ss, line, ':');
        while (getline(ss, line, ' ')) {
            if (line.empty()) continue;
            temp += line;
            j++;
        }
        if (i == 0) race.first = std::stoll(temp);
        if (i == 1) race.second = std::stoll(temp);
        i++;
    }
    long long int res = determine_possible_wins(race);
    std::cout << res << "\n";
}
