#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

void p1(std::ifstream &input);

void p2(std::ifstream &input);

int main() {
    std::ifstream input(R"(..\input04.txt)");
    p1(input);
    input.close();
    std::ifstream input2(R"(..\input04.txt)");
    p2(input2);
    input2.close();
}

void p1(std::ifstream &input) {
    int res = 0;
    for (std::string line; getline(input, line, ':');) {
        std::vector<int> winners;
        std::vector<int> myCards;
        int cardWorth = 0;
        getline(input, line, '|');
        std::stringstream ss(line.substr(1, line.length()));
        while (getline(ss, line, ' ')) {
            if (line.empty()) continue;
            winners.push_back(std::stoi(line));
        }
        getline(input, line);
        std::stringstream ss2(line.substr(1, line.length()));
        while (getline(ss2, line, ' ')) {
            if (line.empty()) continue;
            myCards.push_back(std::stoi(line));
        }
        for (int i: myCards) {
            for (int j: winners) {
                if (i == j) {
                    if (cardWorth == 0) { cardWorth = 1; }
                    else {
                        cardWorth *= 2;
                    }
                }
            }
        }
        res += cardWorth;
    }
    std::cout << "p1:" << res << "\n";
}

int getWinnerAmount(const std::vector<int> &winners, const std::vector<int> &myCards) {
    int res = 0;
    for (int i: myCards) {
        for (int j: winners) {
            if (i == j) res++;
        }
    }
    return res;
}

void p2(std::ifstream &input) {
    std::vector<std::pair<std::vector<int>, std::vector<int>>> cards;
    int res = 0;
    for (std::string line; getline(input, line, ':');) {
        std::vector<int> winners;
        std::vector<int> myCards;
        getline(input, line, '|');
        std::stringstream ss(line.substr(1, line.length()));
        while (getline(ss, line, ' ')) {
            if (line.empty()) continue;
            winners.push_back(std::stoi(line));
        }
        getline(input, line);
        std::stringstream ss2(line.substr(1, line.length()));
        while (getline(ss2, line, ' ')) {
            if (line.empty()) continue;
            myCards.push_back(std::stoi(line));
        }
        cards.emplace_back(winners, myCards);
    }
    std::vector<int> amount(cards.size());
    fill(amount.begin(), amount.end(), 1);
    for (int i = 0; i < cards.size(); i++) {
        for (int k = 1; k <= getWinnerAmount(cards.at(i).first, cards.at(i).second); k++) {
            if (k+i < cards.size()) {
                amount.at(k + i) += amount.at(i);
            }
        }
        res += amount.at(i);
    }
    std::cout << "p2:" << res << "\n";
}