#define MAIN

#include "game.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

int parseRules(std::pair<unsigned, unsigned>& target, std::string from) {
    std::stringstream ss{from};
    std::string ruleSplit;
    std::getline(ss, ruleSplit, '-');
    target.first = std::stoi(ruleSplit);
    std::getline(ss, ruleSplit, '-');
    (ruleSplit != "") ? target.second = std::stoi(ruleSplit) : target.second = target.first;
    return 0;
}

int main(int argc, char* argv[]) {
    std::pair<unsigned, unsigned> survival{4, 4};
    std::pair<unsigned, unsigned> birth{3, 3};
    uint_fast8_t lifetime;
    unsigned short setting;
    if (argc != 2) {
        std::cerr << "Too few arguments! " << std::endl
                  << "Usage: " << argv [0] << " <SURVIVAL_RANGE>/<BIRTH_RANGE>/<DECAY_TIME>/<SETTING>" << std::endl;
        return 1;
    }

    std::vector<std::string> ruleList;
    {
        std::stringstream sstream(static_cast<std::string>(argv[1]));

        std::string ruleSplit;
        while (std::getline(sstream, ruleSplit, '/')) {
            ruleList.push_back(ruleSplit);
        }
        if (ruleList.size() != 4) {
            std::cerr << "WRONG USAGE!" << std::endl
                      << "Usage: " << argv [0] << " <SURVIVAL_RANGE>/<BIRTH_RANGE>/<DECAY_TIME>/<SETTING>" << std::endl;
            return 1;
        }
    }

    parseRules(survival, ruleList[0]);
    parseRules(birth, ruleList[1]);
    lifetime = std::stoi(ruleList[2]);

    (ruleList[3] == "N") ? setting = Cells::NEUMANN : setting = Cells::MOORE; 

    Game game{survival, birth, lifetime, setting};
    game.gameLoop();
}
