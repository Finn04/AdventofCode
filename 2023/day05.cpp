#include <iostream>
#include <fstream>
#include <ranges>
#include <string>
#include <vector>
#include <sstream>
#include <map>

void p1(std::ifstream &input);

void p2(std::ifstream &input);

int main() {
    std::ifstream input(R"(..\input05.txt)");
    p1(input);
    input.close();
    std::ifstream input2(R"(..\input05.txt)");
    p2(input2);
    input2.close();
}

void p1(std::ifstream &input) {
    std::vector<std::vector<long long int>> seeds_map;
    std::string line;
    getline(input, line, ':');
    getline(input, line);
    std::stringstream ss(line.substr(1, line.length()));
    while (getline(ss, line, ' ')) {
        std::vector<long long int> tmp;
        tmp.push_back(std::stoll(line));
        seeds_map.push_back(tmp);
    }

    int i = 0;
    for (; getline(input, line);) {
        if (line.empty()) {
            for (auto &seeds: seeds_map) {
                if (seeds.size() < i + 1) {
                    seeds.push_back(seeds.at(i - 1));
                }
            }
            i++;
            getline(input, line);
            continue;
        }
        std::stringstream ss2(line);
        getline(ss2, line, ' ');
        long long int dst_start = std::stoll(line);
        getline(ss2, line, ' ');
        long long int source_start = std::stoll(line);
        getline(ss2, line, ' ');
        long long int range = std::stoll(line);
        for (auto &seeds: seeds_map) {
            if (seeds.at(i - 1) < source_start + range && seeds.at(i - 1) >= source_start) {
                seeds.push_back(dst_start + (seeds.at(i - 1) - source_start));
            }
        }
    }
    long long int res = LONG_LONG_MAX;
    for (auto &seeds: seeds_map) {
        if (seeds.at(seeds.size() - 1) < res) res = seeds.at(seeds.size() - 1);
    }
    std::cout << "p1:" << res << "\n";
}

void get_mapping(std::ifstream &input, std::map<std::pair<long long int, long long int>, long long int> *map) {
    for (std::string line; getline(input, line);) {
        if (line.empty()) break;
        std::stringstream ss2(line);
        getline(ss2, line, ' ');
        long long int dst_start = std::stoll(line);
        getline(ss2, line, ' ');
        long long int source_start = std::stoll(line);
        getline(ss2, line, ' ');
        long long int range = std::stoll(line);
        map->insert({std::make_pair(dst_start, source_start), range});
    }
}

long long int get_i_map(long long int i, std::map<std::pair<long long int, long long int>, long long int> &map) {
    for (auto &mapping: map) {
        if (i < mapping.first.first + mapping.second && i >= mapping.first.first) {
            return (i - mapping.first.first) + mapping.first.second;
        }
    }
    return i;
}

void p2(std::ifstream &input) {
    std::vector<std::pair<long long int, long long int>> seeds_map;
    std::vector<std::map<std::pair<long long int, long long int>, long long int>> vec(7);
    std::string line;
    getline(input, line, ':');
    getline(input, line);
    std::stringstream ss(line.substr(1, line.length()));
    while (getline(ss, line, ' ')) {
        std::string line2;
        getline(ss, line2, ' ');
        seeds_map.emplace_back(std::stoll(line), std::stoll(line) + std::stoll(line2));
    }
    getline(input, line);
    for (auto &toMap: vec) {
        getline(input, line);
        get_mapping(input, &toMap);
    }
    for (long long int i = 0; i < LONG_LONG_MAX; i++) {
        long long int j = i;
        for (auto &mapping: std::ranges::reverse_view(vec)) {
            j = get_i_map(j, mapping);
        }
        for (auto &p: seeds_map) {
            if (j >= p.first && j < p.second) {
                std::cout << "p2:" << i << "\n";
                return;
            }
        }
    }
}