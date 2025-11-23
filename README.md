# Qt Recipe Manager 👨‍🍳

A comprehensive C++ desktop application developed using the **Qt framework**. This project demonstrates advanced software engineering principles, including **Layered Architecture** and the **Observer Design Pattern**, to manage chefs and their culinary recipes.

## 🚀 Key Features

* **Recipe Management:** Add, view, and organize recipes linked to specific chefs.
* **Advanced Filtering:** Filter recipes by cuisine type or filter by specific ingredients using real-time search.
* **Graphical Visualization:** A custom graphical view using `QPainter` that renders recipes as shapes (circles/rectangles) based on string properties, with colors indicating preparation time intensity.
* **Live Updates:** Uses the **Observer Pattern** to automatically update the graphical view and list view whenever the data changes (without refreshing manually).

## 🛠️ Technical Stack & Concepts

* **Language:** C++ (Standard 17/20)
* **GUI Framework:** Qt 6 (Widgets, Layouts, Signal/Slots, QPainter)
* **Architecture:** Layered Architecture (separation of concerns):
    * **Domain:** `Chef`, `Recipe` entities.
    * **Repository:** Data persistence layer.
    * **Service:** Business logic and filtering operations.
    * **GUI:** `ChefWindow`, `RecipesGraphicalView`.
* **Design Patterns:**
    * **Observer Pattern:** Implemented to sync the GUI with the Service state.
    * **MVC Principles:** Clean separation between data and view.

## 📂 Project Structure

```text
├── domain/       # Entity classes (Chef, Recipe)
├── repository/   # Data storage logic
├── service/      # Business logic (filtering, sorting)
├── observer/     # Observer pattern interfaces
└── gui/          # Qt Windows and Custom Painting
