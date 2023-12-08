#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <set>
#include <algorithm>
#include <cstdint>

#define FILEPATH R"(../input07.txt)"

void p1(std::ifstream &input);

void p2(std::ifstream &input);

int main() {
    std::ifstream input(FILEPATH);
    p1(input);
    input.close();
    std::ifstream input2(FILEPATH);
    p2(input2);
    input2.close();
}

unsigned long int getCardVal(char &c, bool p2) {
    switch (c) {
        case 'A':
            return 14;
        case 'K':
            return 13;
        case 'Q':
            return 12;
        case 'J':
            if (!p2) return 11;
            return 1;
        case 'T':
            return 10;
        default:
            return c - 48;
    }
}

unsigned long long int getRank(std::string &str, bool p2) {
    uint8_t same = 1;
    char same_char = ' ';
    uint8_t same2 = 1;
    uint8_t j_count = 0;
    for (char c: str) {
        if (c == 'J') j_count++;
        auto count = std::ranges::count(str, c);
        if (count > same) {
            same2 = same;
            same = count;
            same_char = c;
        } else if (same_char != c && count > same2) {
            same2 = count;
        }
    }
    if (same_char != 'J' && p2) {
        same += j_count;
    } else if (p2) {
        same = same2 + j_count;
        if (same > 5) same = 5;
    }
    unsigned long long int res;
    if (same >= 4) res = 10000000000 * (same + 2);
    else if (same == 3) res = 40000000000 + (same2 - 1) * 10000000000;
    else if (same == 2) res = 20000000000 + (same2 - 1) * 10000000000;
    else res = 10000000000;
    int i = 100000000;
    for (char c: str) {
        res += getCardVal(c, p2) * i;
        i /= 100;
    }
    return res;
}

void p1(std::ifstream &input) {
    long unsigned int res = 0;
    auto cmp = [](std::pair<std::string, int> a, std::pair<std::string, int> b) {
        return getRank(a.first, false) < getRank(b.first, false);
    };
    std::set<std::pair<std::string, int>, decltype(cmp)> hands;
    for (std::string line; getline(input, line);) {
        std::stringstream ss(line);
        getline(ss, line, ' ');
        auto p = std::make_pair(line, 0);
        getline(ss, line);
        p.second = std::stoi(line);
        hands.insert(p);
    }
    int j = 1;
    for (auto &p: hands) {
        res += (j * p.second);
        j++;
    }
    std::cout << res << "\n";
}


void p2(std::ifstream &input) {
    long unsigned int res = 0;
    auto cmp = [](std::pair<std::string, int> a, std::pair<std::string, int> b) {
        return getRank(a.first, true) < getRank(b.first, true);
    };
    std::set<std::pair<std::string, int>, decltype(cmp)> hands;
    for (std::string line; getline(input, line);) {
        std::stringstream ss(line);
        getline(ss, line, ' ');
        auto p = std::make_pair(line, 0);
        getline(ss, line);
        p.second = std::stoi(line);
        hands.insert(p);
    }
    int j = 1;
    for (auto &p: hands) {
        res += (j * p.second);
        j++;
    }
    std::cout << res << "\n";
}

