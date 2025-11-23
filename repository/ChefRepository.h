//
// Created by cddhi on 7/10/2025.
//

#ifndef CHEFREPOSITORY_H
#define CHEFREPOSITORY_H

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "../domain/Chef.h"

class ChefRepository {
private:
    std::vector<Chef> chefs;
    std::string filename;

public:
    explicit ChefRepository(const std::string& filename);


    void addChef(const Chef& chef);
    std::vector<Chef> getAllChefs() const;
    Chef& getChefByName(const std::string& name);

    // op for file
    void loadFromFile();
    void saveToFile() const;
};

#endif //CHEFREPOSITORY_H