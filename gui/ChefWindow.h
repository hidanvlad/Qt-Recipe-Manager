#ifndef CHEFWINDOW_H
#define CHEFWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QMessageBox>
#include "../service/RecipeService.h"
#include "../service/ChefService.h"
#include "../domain/Chef.h"
#include "../observer/Observer.h"
#include "RecipesGraphicalView.h"

class ChefWindow : public QMainWindow, public Observer {
    Q_OBJECT

private:
    Chef chef;
    RecipeService& recipeService;
    RecipesGraphicalView* graphicalView;

    // UI components
    QListWidget* recipeListWidget;
    QCheckBox* filterByCuisineCheckBox;
    QLineEdit* ingredientsSearchLineEdit;
    QLineEdit* recipeNameLineEdit;
    QLineEdit* prepTimeLineEdit;
    QLineEdit* ingredientsLineEdit;
    QPushButton* addRecipeButton;
    QPushButton* viewGraphicalButton;

    ///GUI setup
    void setupUI();
    void populateRecipeList();
    void connectSignalsAndSlots();

public:
    ChefWindow(const Chef& chef, RecipeService& recipeService, QWidget* parent = nullptr);
    ~ChefWindow();

    //observer implementation
    void update() override;

    private slots:
    void onFilterCheckBoxToggled(bool checked);
    void onIngredientSearchTextChanged(const QString& text);
    void onAddRecipeClicked();
    void onViewGraphicalClicked();
};

#endif