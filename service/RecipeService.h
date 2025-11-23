//
// Created by cddhi on 7/10/2025.
//

#ifndef RECIPESERVICE_H
#define RECIPESERVICE_H

#include "../repository/RecipeRepository.h"
#include "../observer/Subject.h"
#include <vector>
#include <string>
#include <algorithm>

class RecipeService : public Subject {
private:
    RecipeRepository& recipeRepository;

public:
    explicit RecipeService(RecipeRepository& recipeRepository);


    void addRecipe(const std::string& name, const std::string& cuisine, int preparationTime, const std::vector<std::string>& ingredients);
    std::vector<Recipe> getAllRecipes() const;
    // Filter & searching
    std::vector<Recipe> getRecipesByCuisine(const std::string& cuisine) const;
    std::vector<Recipe> filterByIngredients(const std::vector<Recipe>& recipes, const std::vector<std::string>& ingredients) const;

     void saveRecipes() const;
    std::vector<Recipe> getSortedRecipes() const;


};

#endif //RECIPESERVICE_H



