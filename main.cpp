#include <iostream>
#include <fstream>
#include <string>

void adv01();

int main() {
    adv01();
    return 0;
}

void adv01() {
    std::ifstream input(R"(C:\Users\Finn\CLionProjects\AdventOfCode\input01.txt)");
    int res = 0;
    std::string nums[] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine",
                          "0","1", "2", "3", "4", "5", "6", "7", "8", "9"};
    for (std::string line; getline(input, line);) {
        int i = 0;
        int first = 0;
        int last = 0;
        int firstindex = 9999;
        int lastindex = -1;
        for (std::string &s: nums) {
            i++;
            int pos = 0;
            int index;
            while ((index = (int) line.find(s, pos)) != -1) {
                if (index == -1) break;
                pos = index + 1;
                if (index < firstindex) {
                    firstindex = index;
                    first = 10 * (i % 10);
                }
                if (index > lastindex) {
                    lastindex = index;
                    last = (i % 10);
                }
            }
        }
        res += (first + last);
    }
    std::cout << res;
}