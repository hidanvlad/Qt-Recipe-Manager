//
// Created by cddhi on 7/10/2025.
//

#include "ChefService.h"

ChefService::ChefService(ChefRepository& chefRepository)
    : chefRepository(chefRepository) {}

std::vector<Chef> ChefService::getAllChefs() const {
    return chefRepository.getAllChefs();
}

Chef ChefService::getChefByName(const std::string& name) const {
    try {
        return chefRepository.getChefByName(name);
    } catch (const std::runtime_error&) {
        throw std::runtime_error("Chef not found: " + name);
    }
}

void ChefService::loadChefs() {
    chefRepository.loadFromFile();
}