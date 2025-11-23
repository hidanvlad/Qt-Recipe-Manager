//
// Created by cddhi on 7/10/2025.
//

#ifndef RECIPEREPOSITORY_H
#define RECIPEREPOSITORY_H

#include <vector>
#include <string>
#include <fstream>
#include "../domain/Recipe.h"

class RecipeRepository {
    std::vector<Recipe> recipes;
    std::string filename;
public:
    explicit RecipeRepository(const std::string& filename) ;
     void addRecipe(const Recipe& recipe) ;
    std::vector<Recipe> getAllRecipes() const ;
    Recipe& getRecipeByName(const std::string& name);
    void updateRecipe(const Recipe& recipe);

    // File operations
    void loadFromFile() ;
    void saveToFile() const ;

};



#endif //RECIPEREPOSITORY_H
