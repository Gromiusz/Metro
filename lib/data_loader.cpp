#include "data_loader.hpp"

void DataLoader::load(const std::string &filename,
                      int &time,
                      int &simulationLength,
                      int &trackLength,
                      std::vector<std::pair<std::shared_ptr<Train>, int>> &trains,
                      std::vector<std::pair<std::shared_ptr<Station>, int>> &stations,
                      std::vector<bool> &reverseFlags)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        throw std::runtime_error("Nie można otworzyć pliku: " + filename);
    }

    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string type;
        std::getline(iss, type, ',');

        if (type == "Time")
        {
            iss >> time;
        }
        else if (type == "SimulationLength")
        {
            iss >> simulationLength;
        }
        else if (type == "TrackLength")
        {
            iss >> trackLength;
        }
        else if (type == "Train")
        {
            loadTrain(iss, trains, reverseFlags);
        }
        else if (type == "Station")
        {
            loadStation(iss, stations);
        }
    }
}

void DataLoader::loadTrain(std::istringstream &iss, std::vector<std::pair<std::shared_ptr<Train>, int>> &trains, std::vector<bool> &reverseFlags)
{
    std::string line;
    std::getline(iss, line); // Wczytujemy całą linię

    std::istringstream lineStream(line);
    std::vector<std::string> tokens;
    std::string token;

    while (std::getline(lineStream, token, ','))
    { // Rozdzielamy linię na tokeny rozdzielone przecinkami
        tokens.push_back(token);
    }

    if (tokens.size() < 5)
    {
        throw std::runtime_error("Nieprawidłowa liczba argumentów dla pociągu.");
    }

    int id = std::stoi(tokens[0]);
    std::string name = tokens[1];
    int capacity = std::stoi(tokens[2]);
    int numberOfDoors = std::stoi(tokens[3]);
    int position = std::stoi(tokens[4]);

    bool isReverse = tokens.size() > 5 && tokens[5] == "reverse";

    std::shared_ptr<Train> train = std::make_shared<Train>(id, name, capacity, numberOfDoors);
    trains.emplace_back(train, position);
    reverseFlags.push_back(isReverse);
}

void DataLoader::loadStation(std::istringstream &iss, std::vector<std::pair<std::shared_ptr<Station>, int>> &stations)
{
    std::string line;
    std::getline(iss, line); // Wczytujemy całą linię

    std::istringstream lineStream(line);
    std::vector<std::string> tokens;
    std::string token;

    while (std::getline(lineStream, token, ','))
    { // Rozdzielamy linię na tokeny rozdzielone przecinkami
        tokens.push_back(token);
    }

    if (tokens.size() < 3)
    {
        throw std::runtime_error("Nieprawidłowa liczba argumentów dla stacji.");
    }

    int id = std::stoi(tokens[0]);
    std::string name = tokens[1];
    int position = std::stoi(tokens[2]);

    std::shared_ptr<Station> station = std::make_shared<Station>(id, name);
    stations.emplace_back(station, position);
}