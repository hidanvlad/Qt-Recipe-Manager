//
// Created by cddhi on 7/10/2025.
//

#ifndef CHEFSERVICE_H
#define CHEFSERVICE_H

#include "../repository/ChefRepository.h"
#include "../observer/Observer.h"
#include <vector>
#include <string>

class ChefService {
private:
    ChefRepository& chefRepository;

public:
    explicit ChefService(ChefRepository& chefRepository);


    std::vector<Chef> getAllChefs() const;
    Chef getChefByName(const std::string& name) const;

    void loadChefs();
};

#endif //CHEFSERVICE_H