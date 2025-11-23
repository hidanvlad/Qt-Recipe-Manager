cmake_minimum_required(VERSION 3.30)
project(e-retake-hidanvlad)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_STANDARD 20)

    set(CMAKE_PREFIX_PATH "D:/QT/6.5.3/mingw_64")
    find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(e-retake-hidanvlad main.cpp
        domain/Chef.h domain/Chef.cpp
        domain/Recipe.h domain/Recipe.cpp
        repository/ChefRepository.h repository/ChefRepository.cpp
        repository/RecipeRepository.h repository/RecipeRepository.cpp
        service/ChefService.h service/ChefService.cpp
        service/RecipeService.h service/RecipeService.cpp
        observer/Observer.h observer/Subject.h
        gui/ChefWindow.h gui/ChefWindow.cpp
        gui/RecipesGraphicalView.h gui/RecipesGraphicalView.cpp


)

target_link_libraries(e-retake-hidanvlad PRIVATE Qt6::Widgets)