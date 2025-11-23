

#ifndef RECIPE_H
#define RECIPE_H

#include <string>
#include <vector>

class Recipe {
private:
    std::string name;
    std::string cuisine;
    int preparationTime; // integer min
    std::vector<std::string> ingredients;

public:
    // Constructors
    Recipe() = default;
    Recipe(const std::string& name, const std::string& cuisine, int preparationTime,
           const std::vector<std::string>& ingredients)
        : name(name), cuisine(cuisine), preparationTime(preparationTime), ingredients(ingredients) {}

    ///geteter
    const std::string& getName() const { return name; }
    const std::string& getCuisine() const { return cuisine; }
    int getPreparationTime() const { return preparationTime; }
    const std::vector<std::string>& getIngredients() const { return ingredients; }

    // Sertters
    void setName(const std::string& newName) { name = newName; }
    void setCuisine(const std::string& newCuisine) { cuisine = newCuisine; }
    void setPreparationTime(int newPreparationTime) { preparationTime = newPreparationTime; }
    void setIngredients(const std::vector<std::string>& newIngredients) { ingredients = newIngredients; }

    // compare for sort
    bool operator<(const Recipe& other) const {
        if (cuisine != other.cuisine)
            return cuisine < other.cuisine;
        return preparationTime < other.preparationTime;
    }

    bool operator==(const Recipe& other) const {
        return name == other.name;
    }

    // checking for spec ingredients
    bool containsIngredients(const std::vector<std::string>& searchIngredients) const;
};



#endif //RECIPE_H

