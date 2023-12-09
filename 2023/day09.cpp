#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <ranges>

void p1(std::ifstream &input);

void p2(std::ifstream &input);

int main() {
    std::ifstream input(R"(..\input09.txt)");
    p1(input);
    input.close();
    std::ifstream input2(R"(..\input09.txt)");
    p2(input2);
    input2.close();
}

void p1(std::ifstream &input) {
    std::vector<std::vector<std::vector<long long int>>> history;
    for (std::string line; getline(input, line);) {
        std::stringstream ss(line);
        history.emplace_back();
        history.at(history.size() - 1).emplace_back();
        for (; getline(ss, line, ' ');) {
            history.at(history.size() - 1).at(0).push_back(std::stoll(line));
        }
    }
    for (auto &oline: history) {
        int n = 0;
        bool allZeros = false;
        while (!allZeros) {
            allZeros = true;
            oline.emplace_back();
            for (int i = 1; i < oline.at(n).size(); i++) {
                long long int tmp = oline.at(n).at(i) - oline.at(n).at(i - 1);
                oline.at(n + 1).push_back(tmp);
                if (tmp != 0) allZeros = false;
            }
            if (allZeros && oline.at(n + 1).empty()) oline.pop_back();
            n++;
        }
    }
    unsigned long long int res = 0;
    for (auto &oline: history) {
        long long int tmp = 0;
        for (auto &ooline: std::ranges::reverse_view(oline)) {
            tmp += ooline.at(ooline.size() - 1);
        }
        res += tmp;
    }
    std::cout << res << "\n";
}

void p2(std::ifstream &input) {
    std::vector<std::vector<std::vector<long long int>>> history;
    for (std::string line; getline(input, line);) {
        std::stringstream ss(line);
        history.emplace_back();
        history.at(history.size() - 1).emplace_back();
        for (; getline(ss, line, ' ');) {
            history.at(history.size() - 1).at(0).push_back(std::stoll(line));
        }
    }
    for (auto &oline: history) {
        int n = 0;
        bool allZeros = false;
        while (!allZeros) {
            allZeros = true;
            oline.emplace_back();
            for (int i = 1; i < oline.at(n).size(); i++) {
                long long int tmp = oline.at(n).at(i) - oline.at(n).at(i - 1);
                oline.at(n + 1).push_back(tmp);
                if (tmp != 0) allZeros = false;
            }
            if (allZeros && oline.at(n + 1).empty()) oline.pop_back();
            n++;
        }
    }
    long long int res = 0;
    for (auto &oline: history) {
        long long int tmp = 0;
        long long int toSub = 0;
        for (auto &ooline: std::ranges::reverse_view(oline)) {
            toSub = tmp;
            tmp = ooline.at(0);
            tmp = tmp - toSub;
        }
        res += tmp;
    }
    std::cout << res << "\n";
}