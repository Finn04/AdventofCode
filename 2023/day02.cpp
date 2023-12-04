#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#define RED_LIMIT 12
#define GREEN_LIMIT 13
#define BLUE_LIMIT 14

void p1(std::ifstream &input);

void p2(std::ifstream &input);

int main() {
    std::ifstream input(R"(..\input02.txt)");
    p1(input);
    input.close();
    std::ifstream input2(R"(..\input02.txt)");
    p2(input2);
    input2.close();
}

void p1(std::ifstream &input) {
    int res = 0;
    for (std::string line; getline(input, line);) {
        bool valid = true;
        int id;
        std::stringstream ss(line);
        getline(ss, line, ':');
        id = std::stoi(line.substr(5, line.length()));
        while (getline(ss, line, ';')) {
            std::stringstream ss2(line);
            while (getline(ss2, line, ',')) {
                std::stringstream ss3(line.substr(1, line.length()));
                getline(ss3, line, ' ');
                int num = std::stoi(line);
                getline(ss3, line);
                if ((line == "green" && num > GREEN_LIMIT) || (line == "blue" && num > BLUE_LIMIT) ||
                    (line == "red" && num > RED_LIMIT))
                    valid = false;
            }
        }
        if (valid) res += id;
    }
    std::cout << "Part 1 is:" << res << "\n";
}

void p2(std::ifstream &input) {
    int res = 0;
    for (std::string line; getline(input, line);) {
        std::stringstream ss(line);
        getline(ss, line, ':');
        int max_green = 0;
        int max_red = 0;
        int max_blue = 0;
        while (getline(ss, line, ';')) {
            std::stringstream ss2(line);
            while (getline(ss2, line, ',')) {
                std::stringstream ss3(line.substr(1, line.length()));
                getline(ss3, line, ' ');
                int num = std::stoi(line);
                getline(ss3, line);
                if (line == "green" && num > max_green) max_green = num;
                else if (line == "blue" && num > max_blue) max_blue = num;
                else if (line == "red" && num > max_red) max_red = num;
            }
        }
        res += (max_green * max_blue * max_red);
    }
    std::cout << "Part 2 is:" << res << "\n";
}