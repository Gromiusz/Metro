#pragma once
#include <vector>
#include <string>
#include <memory>
#include <fstream>
#include <sstream>
#include <stdexcept>

#include "train.hpp"
#include "station.hpp"
#include "track.hpp"

class DataLoader {
public:
    void load(const std::string& filename,
              int& time,
              int& simulationLength,
              int& trackLength,
              std::vector<std::pair<std::shared_ptr<Train>, int>>& trains,
              std::vector<std::pair<std::shared_ptr<Station>, int>>& stations,
              std::vector<bool>& reverseFlags);

private:
    void loadTrain(std::istringstream& iss, std::vector<std::pair<std::shared_ptr<Train>, int>>& trains, std::vector<bool>& reverseFlags);
    void loadStation(std::istringstream& iss, std::vector<std::pair<std::shared_ptr<Station>, int>>& stations);
};
