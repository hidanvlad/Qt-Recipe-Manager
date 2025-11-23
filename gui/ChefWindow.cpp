#include "ChefWindow.h"
#include <sstream>
#include <QMessageBox>

ChefWindow::ChefWindow(const Chef& chef, RecipeService& recipeService, QWidget* parent)
    : QMainWindow(parent), chef(chef), recipeService(recipeService), graphicalView(nullptr) {
    
    setupUI();
    populateRecipeList();
    connectSignalsAndSlots();
    
    // add as observer for recipe changes
    recipeService.addObserver(this);
}

ChefWindow::~ChefWindow() {
    // remove as observer to prevent dangling pointers
    recipeService.removeObserver(this);

    if (graphicalView) {
        graphicalView->close();
        delete graphicalView;
    }
}

void ChefWindow::setupUI() {
    //Title and size, chef name
    setWindowTitle(QString::fromStdString(chef.getName()));
    setMinimumSize(600, 400);

    ///Main widget and layout
    QWidget* centralWidget = new QWidget(this);
    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);

    //Filters sect
    QHBoxLayout* filterLayout = new QHBoxLayout();
    filterByCuisineCheckBox = new QCheckBox("Show only " + QString::fromStdString(chef.getCuisineSpecialty()) + " cuisine");

    QLabel* searchLabel = new QLabel("Search by ingredients (comma separated):");
    ingredientsSearchLineEdit = new QLineEdit();

    filterLayout->addWidget(filterByCuisineCheckBox);
    filterLayout->addStretch();
    filterLayout->addWidget(searchLabel);
    filterLayout->addWidget(ingredientsSearchLineEdit);

    //THe Recipe list
    recipeListWidget = new QListWidget();

    ///Adding recipe part
    QGroupBox* addRecipeGroup = new QGroupBox("Add New Recipe");
    QGridLayout* formLayout = new QGridLayout();

    formLayout->addWidget(new QLabel("Recipe Name:"), 0, 0);
    recipeNameLineEdit = new QLineEdit();
    formLayout->addWidget(recipeNameLineEdit, 0, 1);
    formLayout->addWidget(new QLabel("Preparation Time (minutes):"), 1, 0);
    prepTimeLineEdit = new QLineEdit();
    formLayout->addWidget(prepTimeLineEdit, 1, 1);
    formLayout->addWidget(new QLabel("Ingredients (comma-separated):"), 2, 0);
    ingredientsLineEdit = new QLineEdit();
    formLayout->addWidget(ingredientsLineEdit, 2, 1);

    addRecipeButton = new QPushButton("Add Recipe");
    formLayout->addWidget(addRecipeButton, 3, 1);

    addRecipeGroup->setLayout(formLayout);

    ///VIEW BUTTON
    viewGraphicalButton = new QPushButton("View Graphical Recipes");

    // Add component to layout
    mainLayout->addLayout(filterLayout);
    mainLayout->addWidget(recipeListWidget);
    mainLayout->addWidget(addRecipeGroup);
    mainLayout->addWidget(viewGraphicalButton);

    setCentralWidget(centralWidget);
}

void ChefWindow::populateRecipeList() {
    recipeListWidget->clear();

    std::vector<Recipe> recipesToShow;

    // cuisine filter if checked
    if (filterByCuisineCheckBox->isChecked()) {
        recipesToShow = recipeService.getRecipesByCuisine(chef.getCuisineSpecialty());
    } else {
        recipesToShow = recipeService.getSortedRecipes();
    }

    //\Apply ingredients filter
    QString ingredientsText = ingredientsSearchLineEdit->text().trimmed();
    if (!ingredientsText.isEmpty()) {
        std::vector<std::string> ingredients;
        std::string ingredientsStr = ingredientsText.toStdString();
        std::istringstream iss(ingredientsStr);
        std::string ingredient;

        while (std::getline(iss, ingredient, ',')) {

            ingredient.erase(0, ingredient.find_first_not_of(' '));
            ingredient.erase(ingredient.find_last_not_of(' ') + 1);
            if (!ingredient.empty()) {
                ingredients.push_back(ingredient);
            }
        }

        recipesToShow = recipeService.filterByIngredients(recipesToShow, ingredients);
    }


    std::map<std::string, std::vector<Recipe>> recipesByCuisine;
    for (const auto& recipe : recipesToShow) {
        recipesByCuisine[recipe.getCuisine()].push_back(recipe);
    }

    //display recipes sorted
    for (const auto& [cuisine, recipes] : recipesByCuisine) {
        QListWidgetItem* cuisineHeader = new QListWidgetItem(QString::fromStdString("--- " + cuisine + " ---"));
        cuisineHeader->setBackground(QColor(230, 230, 230));
        cuisineHeader->setFlags(Qt::NoItemFlags);
        recipeListWidget->addItem(cuisineHeader);

        for (const auto& recipe : recipes) {
            QString itemText = QString::fromStdString(recipe.getName()) +
                              " (" + QString::number(recipe.getPreparationTime()) + " mins)";
            QListWidgetItem* item = new QListWidgetItem(itemText);


            QVariant var;
            var.setValue(QString::fromStdString(recipe.getName()));
            item->setData(Qt::UserRole, var);

            recipeListWidget->addItem(item);
        }
    }
}

void ChefWindow::connectSignalsAndSlots() {
    connect(filterByCuisineCheckBox, &QCheckBox::toggled, this, &ChefWindow::onFilterCheckBoxToggled);
    connect(ingredientsSearchLineEdit, &QLineEdit::textChanged, this, &ChefWindow::onIngredientSearchTextChanged);
    connect(addRecipeButton, &QPushButton::clicked, this, &ChefWindow::onAddRecipeClicked);
    connect(viewGraphicalButton, &QPushButton::clicked, this, &ChefWindow::onViewGraphicalClicked);
}

void ChefWindow::update() {
    ///Update recipe list when notified of changes
    populateRecipeList();

    //update grapgical view if exists
    if (graphicalView) {
        graphicalView->update();
    }
}

void ChefWindow::onFilterCheckBoxToggled(bool checked) {
    populateRecipeList();
}

void ChefWindow::onIngredientSearchTextChanged(const QString& text) {
    populateRecipeList();
}

void ChefWindow::onAddRecipeClicked() {
    QString recipeName = recipeNameLineEdit->text().trimmed();
    QString prepTimeText = prepTimeLineEdit->text().trimmed();
    QString ingredientsText = ingredientsLineEdit->text().trimmed();

    // Validation
    if (recipeName.isEmpty()) {
        QMessageBox::warning(this, "Invalid Input", "Recipe name cannot be empty.");
        return;
    }

    bool ok;
    int prepTime = prepTimeText.toInt(&ok);
    if (!ok || prepTime <= 0) {
        QMessageBox::warning(this, "Invalid Input", "Preparation time must be a positive number.");
        return;
    }

    if (ingredientsText.isEmpty()) {
        QMessageBox::warning(this, "Invalid Input", "Ingredients list cannot be empty.");
        return;
    }

    // Parse ingredients
    std::vector<std::string> ingredients;
    std::string ingredientsStr = ingredientsText.toStdString();
    std::istringstream iss(ingredientsStr);
    std::string ingredient;

    while (std::getline(iss, ingredient, ',')) {
        // Trim leading/trailing spaces
        ingredient.erase(0, ingredient.find_first_not_of(' '));
        ingredient.erase(ingredient.find_last_not_of(' ') + 1);
        if (!ingredient.empty()) {
            ingredients.push_back(ingredient);
        }
    }

    // Add recipe (cuisine is auto-set to chef's specialty)
    try {
        recipeService.addRecipe(recipeName.toStdString(), chef.getCuisineSpecialty(),
                               prepTime, ingredients);

        // Clear form fields after successful addition
        recipeNameLineEdit->clear();
        prepTimeLineEdit->clear();
        ingredientsLineEdit->clear();

    } catch (const std::runtime_error& e) {
        QMessageBox::warning(this, "Error", QString::fromStdString(e.what()));
    }
}


void ChefWindow::onViewGraphicalClicked() {

    RecipesGraphicalView* graphView = new RecipesGraphicalView(recipeService, chef.getCuisineSpecialty(), nullptr);


    graphView->setAttribute(Qt::WA_DeleteOnClose);


    graphView->show();
}