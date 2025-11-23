#ifndef CHEF_H
#define CHEF_H

#include <string>
#include <vector>

class Chef {
private:
    std::string name;
    std::string cuisineSpecialty; // e.g., Italian, Mexican

public:
    // Constructors
    Chef() = default;
    Chef(const std::string& name, const std::string& cuisineSpecialty)
        : name(name), cuisineSpecialty(cuisineSpecialty) {}

    // Getters
    const std::string& getName() const { return name; }
    const std::string& getCuisineSpecialty() const { return cuisineSpecialty; }

    // Setters
    void setName(const std::string& newName) { name = newName; }
    void setCuisineSpecialty(const std::string& newCuisineSpecialty) { cuisineSpecialty = newCuisineSpecialty; }

    // Comparison operators
    bool operator==(const Chef& other) const {
        return name == other.name;
    }
};

#endif //CHEF_H