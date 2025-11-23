//
// Created by cddhi on 7/10/2025.
//

#include "ChefRepository.h"
#include <stdexcept>

ChefRepository::ChefRepository(const std::string& filename) : filename(filename) {
    loadFromFile();
}

void ChefRepository::addChef(const Chef& chef) {
    for (const auto& existingChef : chefs) {
        if (existingChef.getName() == chef.getName()) {
            throw std::runtime_error("Chef with the same name already exists");
        }
    }
    chefs.push_back(chef);
}

std::vector<Chef> ChefRepository::getAllChefs() const {
    return chefs;
}

Chef& ChefRepository::getChefByName(const std::string& name) {
    for (auto& chef : chefs) {
        if (chef.getName() == name) {
            return chef;
        }
    }
    throw std::runtime_error("Chef not found");
}

void ChefRepository::loadFromFile() {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string name, cuisineSpecialty;

        if (std::getline(iss, name, ',') && std::getline(iss, cuisineSpecialty)) {
            // Trim potential whitespaces
            if (!cuisineSpecialty.empty() && cuisineSpecialty[0] == ' ')
                cuisineSpecialty.erase(0, 1);

            chefs.emplace_back(name, cuisineSpecialty);
        }
    }

    file.close();
}

void ChefRepository::saveToFile() const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file for writing: " + filename);
    }

    for (const auto& chef : chefs) {
        file << chef.getName() << ", " << chef.getCuisineSpecialty() << "\n";
    }

    file.close();
}