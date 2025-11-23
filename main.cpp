//
// Created by cddhi on 7/10/2025.
//
#include <QApplication>
#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include "repository/ChefRepository.h"
#include "repository/RecipeRepository.h"
#include "service/ChefService.h"
#include "service/RecipeService.h"
#include "gui/ChefWindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    std::string chefsFile = "chef.txt";
    std::string recipesFile = "recipes.txt";

    try {
        //initialize REPO
        std::shared_ptr<ChefRepository> chefRepository = std::make_shared<ChefRepository>(chefsFile);
        std::shared_ptr<RecipeRepository> recipeRepository = std::make_shared<RecipeRepository>(recipesFile);
        /// Service create
        std::shared_ptr<ChefService> chefService = std::make_shared<ChefService>(*chefRepository);
        std::shared_ptr<RecipeService> recipeService = std::make_shared<RecipeService>(*recipeRepository);

        //get all chef
        std::vector<Chef> chefs = chefService->getAllChefs();
        if (chefs.empty()) {
            std::cerr << "No chefs found in the file. Application will exit." << std::endl;
            return 1;
        }



        // create windows for each chef
        std::vector<std::unique_ptr<ChefWindow>> chefWindows;
        for (const auto& chef : chefs) {
            auto window = std::make_unique<ChefWindow>(chef, *recipeService);
            chefWindows.push_back(std::move(window));
        }

        // show indows
        int xOffset = 50, yOffset = 50;
        for (size_t i = 0; i < chefWindows.size(); i++) {
            chefWindows[i]->move(xOffset * i, yOffset * i);
            chefWindows[i]->show();
        }

        // Save on exit
        QObject::connect(&app, &QApplication::aboutToQuit, [&]() {
            try {
                recipeService->saveRecipes();
                std::cout << "Recipes saved successfully." << std::endl;
            } catch (const std::exception& e) {
                std::cerr << "Error saving recipes: " << e.what() << std::endl;
            }
        });

        return app.exec();

    } catch (const std::exception& e) {
        std::cerr << "Error initializing application: " << e.what() << std::endl;
        return 1;
    }
}

///imi mmerge comit ?

///problema 10