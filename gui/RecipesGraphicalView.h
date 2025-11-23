#ifndef RECIPESGRAPHICALVIEW_H
#define RECIPESGRAPHICALVIEW_H

#include <QWidget>
#include <QPainter>
#include "../service/RecipeService.h"
#include "../observer/Observer.h"

class RecipesGraphicalView : public QWidget, public Observer {
    Q_OBJECT

private:
    RecipeService& recipeService;
    std::string cuisine;

public:
    RecipesGraphicalView(RecipeService& recipeService, const std::string& cuisine, QWidget* parent = nullptr);
    ~RecipesGraphicalView();

    void paintEvent(QPaintEvent* event) override;
    void update() override;
};

#endif //RECIPESGRAPHICALVIEW_H