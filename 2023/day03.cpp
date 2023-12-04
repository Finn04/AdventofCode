#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <set>
#include <map>

void p1(std::ifstream &input);

void p2(std::ifstream &input);

int main() {
    std::ifstream input(R"(..\input03.txt)");
    p1(input);
    input.close();
    std::ifstream input2(R"(..\input03.txt)");
    p2(input2);
    input2.close();
}

void p1(std::ifstream &input) {
    int i = 0;
    int j = 0;
    int res = 1;
    int curNum = 0;
    std::vector<std::pair<int, int>> vec;
    std::set<int> added;
    std::ifstream input2(R"(..\input03.txt)");
    for (std::string line; getline(input, line);) {
        for (char c: line) {
            if (!(47 < c && c < 58) && c != '.') {
                vec.emplace_back(i, j);
            }
            j++;
        }
        j = 0;
        i++;
    }
    i = 0;
    j = 0;
    for (std::string line; getline(input2, line);) {
        for (char c: line) {
            if (47 < c && c < 58) {
                curNum = (curNum * 10) + (c - 48);
            } else {
                if (curNum != 0) {
                    for (std::pair<int, int> pair: vec) {
                        if ((pair.second >= j - ceil(log10(curNum)) - 1) && (pair.second <= j) &&
                            (pair.first <= i + 1) &&
                            (pair.first >= i - 1)) {
                            res += curNum;
                            break;
                        }
                    }
                    curNum = 0;
                }
            }
            j++;
        }
        if (curNum != 0) {
            for (std::pair<int, int> pair: vec) {
                if ((pair.second >= j - ceil(log10(curNum)) - 1) && (pair.second <= j) &&
                    (pair.first <= i + 1) &&
                    (pair.first >= i - 1)) {
                    res += curNum;
                    break;
                }
            }
        }
        curNum = 0;
        j = 0;
        i++;
    }
    std::cout << "p1:" << res << "\n";
}

void p2(std::ifstream &input) {
    int i = 0;
    int j = 0;
    int res = 0;
    int curNum = 0;
    std::map<std::pair<int, int>, std::vector<int>> m;
    std::set<int> added;
    std::ifstream input2(R"(..\input03.txt)");
    for (std::string line; getline(input, line);) {
        for (char c: line) {
            if (c == '*') {
                m.insert({std::make_pair(i, j), std::vector<int>()});
            }
            j++;
        }
        j = 0;
        i++;
    }
    i = 0;
    j = 0;
    for (std::string line; getline(input2, line);) {
        for (char c: line) {
            if (47 < c && c < 58) {
                curNum = (curNum * 10) + (c - 48);
            } else {
                if (curNum != 0) {
                    for (auto &pair: m) {
                        if ((pair.first.second >= j - ceil(log10(curNum)) - 1) && (pair.first.second <= j) &&
                            (pair.first.first <= i + 1) &&
                            (pair.first.first >= i - 1)) {
                            pair.second.push_back(curNum);
                        }
                    }
                    curNum = 0;
                }
            }
            j++;
        }
        if (curNum != 0) {
            for (auto &pair: m) {
                if ((pair.first.second >= j - ceil(log10(curNum)) - 1) && (pair.first.second <= j) &&
                    (pair.first.first <= i + 1) &&
                    (pair.first.first >= i - 1)) {
                    pair.second.push_back(curNum);
                }
            }
        }
        curNum = 0;
        j = 0;
        i++;
    }
    for (auto &pair: m) {
        if (pair.second.size() == 2) {
            int temp1 = pair.second.back();
            pair.second.pop_back();
            int temp2 = pair.second.back();
            pair.second.pop_back();
            res += (temp1 * temp2);
        }
    }
    std::cout << "p2:" << res << "\n";
}