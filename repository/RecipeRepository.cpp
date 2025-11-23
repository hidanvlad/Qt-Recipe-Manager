#include "RecipeRepository.h"
#include <stdexcept>
#include <sstream>
#include <algorithm>

RecipeRepository::RecipeRepository(const std::string& filename) : filename(filename) {
    loadFromFile();
}

void RecipeRepository::addRecipe(const Recipe& recipe) {
    for (const auto& existingRecipe : recipes) {
        if (existingRecipe.getName() == recipe.getName()) {
            throw std::runtime_error("Recipe with the same name already exists");
        }
    }
    recipes.push_back(recipe);
}

std::vector<Recipe> RecipeRepository::getAllRecipes() const {
    return recipes;
}

Recipe& RecipeRepository::getRecipeByName(const std::string& name) {
    for (auto& recipe : recipes) {
        if (recipe.getName() == name) {
            return recipe;
        }
    }
    static Recipe emptyRecipe; // return empty recipe if not found
    return emptyRecipe;
}

void RecipeRepository::updateRecipe(const Recipe& updatedRecipe) {
    for (auto& recipe : recipes) {
        if (recipe.getName() == updatedRecipe.getName()) {
            recipe = updatedRecipe;
            return;
        }
    }
    throw std::runtime_error("Recipe not found for update");
}

void RecipeRepository::loadFromFile() {
    std::ifstream file(filename);
    if (!file.is_open()) {

        return;
    }
    
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string name, cuisine;
        int preparationTime;
        std::string ingredientsStr;
        
        if (std::getline(iss, name, ',') && 
            std::getline(iss, cuisine, ',') && 
            iss >> preparationTime) {
            
            // Skip the
            iss.ignore();
            
            /// read ingredients
            std::getline(iss, ingredientsStr);
            
            ///parsing the ingredients with comma
            std::vector<std::string> ingredients;
            std::istringstream ingredientStream(ingredientsStr);
            std::string ingredient;
            
            while (std::getline(ingredientStream, ingredient, ',')) {

                if (!ingredient.empty() && ingredient[0] == ' ')
                    ingredient.erase(0, 1);
                    
                ingredients.push_back(ingredient);
            }
            
            recipes.emplace_back(name, cuisine, preparationTime, ingredients);
        }
    }
    
    file.close();
}

void RecipeRepository::saveToFile() const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file for writing: " + filename);
    }
    
    // sort before save
    std::vector<Recipe> sortedRecipes = recipes;
    std::sort(sortedRecipes.begin(), sortedRecipes.end());
    
    for (const auto& recipe : sortedRecipes) {
        file << recipe.getName() << "," 
             << recipe.getCuisine() << "," 
             << recipe.getPreparationTime() << ",";
        //ingredient with comma
        const auto& ingredients = recipe.getIngredients();
        for (size_t i = 0; i < ingredients.size(); ++i) {
            file << ingredients[i];
            if (i < ingredients.size() - 1) {
                file << ", ";
            }
        }
        file << "\n";
    }
    
    file.close();
}