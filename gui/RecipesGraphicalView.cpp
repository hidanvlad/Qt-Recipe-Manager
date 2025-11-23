#include "RecipesGraphicalView.h"

RecipesGraphicalView::RecipesGraphicalView(RecipeService& recipeService, const std::string& cuisine, QWidget* parent)
    : QWidget(parent), recipeService(recipeService), cuisine(cuisine) {

    setWindowTitle(QString::fromStdString("Recipes: " + cuisine));
    resize(600, 400);

    // register as observer to receive updates
    recipeService.addObserver(this);
}
RecipesGraphicalView::~RecipesGraphicalView() {
    // Unregister as observer to prevent dangling pointers
    recipeService.removeObserver(this);
}
void RecipesGraphicalView::paintEvent(QPaintEvent* event) {
    QPainter p(this);
    int y = 30;

    //gget recipes of the specified cuisine
    std::vector<Recipe> recipes = recipeService.getRecipesByCuisine(cuisine);

    for (const auto& recipe : recipes) {
        //draw recipe name
        p.setPen(Qt::black);
        p.drawText(20, y, QString::fromStdString(recipe.getName()));

        //calculat shape size
        int size = std::min(100, recipe.getPreparationTime());

        //set collor based on time
        if (recipe.getPreparationTime() > 100) {
            p.setBrush(Qt::red);
        } else {
            p.setBrush(Qt::green);
        }

        //drawig shape
        if (recipe.getName().length() % 2 == 0) {
            //rectangle
            p.drawRect(150, y - 15, size, size / 2);
        } else {
            //circle
            p.drawEllipse(150, y - 15, size, size / 2);
        }

        //move for next recipe
        y += size / 2 + 30;
    }
}

void RecipesGraphicalView::update() {
    // repaint when data changes
    repaint();
}