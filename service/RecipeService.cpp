#include "RecipeService.h"
#include <stdexcept>

RecipeService::RecipeService(RecipeRepository& recipeRepository)
    : recipeRepository(recipeRepository) {}

void RecipeService::addRecipe(const std::string& name, const std::string& cuisine,
                             int preparationTime, const std::vector<std::string>& ingredients) {

    if (name.empty()) {
        throw std::runtime_error("Recipe name cannot be empty");
    }


    Recipe newRecipe(name, cuisine, preparationTime, ingredients);
    recipeRepository.addRecipe(newRecipe);

    ///notify observer
    notify();
}

std::vector<Recipe> RecipeService::getAllRecipes() const {
    return recipeRepository.getAllRecipes();
}

std::vector<Recipe> RecipeService::getRecipesByCuisine(const std::string& cuisine) const {
    std::vector<Recipe> allRecipes = recipeRepository.getAllRecipes();
    std::vector<Recipe> filteredRecipes;

    std::copy_if(allRecipes.begin(), allRecipes.end(), std::back_inserter(filteredRecipes),
                [&cuisine](const Recipe& recipe) { return recipe.getCuisine() == cuisine; });

    return filteredRecipes;
}

std::vector<Recipe> RecipeService::filterByIngredients(const std::vector<Recipe>& recipes, const std::vector<std::string>& ingredients) const {
    if (ingredients.empty()) {
        return recipes;
    }

    std::vector<Recipe> filteredRecipes;

    for (const auto& recipe : recipes) {
        bool containsAll = true;
        const auto& recipeIngredients = recipe.getIngredients();

        for (const auto& searchIngredient : ingredients) {
            bool found = false;
            for (const auto& ingredient : recipeIngredients) {

                std::string lowerIngredient = ingredient;
                std::string lowerSearch = searchIngredient;
                std::transform(lowerIngredient.begin(), lowerIngredient.end(),
                              lowerIngredient.begin(), ::tolower);
                std::transform(lowerSearch.begin(), lowerSearch.end(),
                              lowerSearch.begin(), ::tolower);

                if (lowerIngredient.find(lowerSearch) != std::string::npos) {
                    found = true;
                    break;
                }
            }

            if (!found) {
                containsAll = false;
                break;
            }
        }

        if (containsAll) {
            filteredRecipes.push_back(recipe);
        }
    }

    return filteredRecipes;
}

std::vector<Recipe> RecipeService::getSortedRecipes() const {
    std::vector<Recipe> sortedRecipes = recipeRepository.getAllRecipes();
    std::sort(sortedRecipes.begin(), sortedRecipes.end());
    return sortedRecipes;
}

void RecipeService::saveRecipes() const {
    recipeRepository.saveToFile();
}