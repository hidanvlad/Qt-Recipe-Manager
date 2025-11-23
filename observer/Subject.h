//
// Created by cddhi on 7/10/2025.
//

#ifndef SUBJECT_H
#define SUBJECT_H

#include "Observer.h"
#include <vector>
#include <algorithm>

class Subject {
private:
    std::vector<Observer*> observers;

public:
    virtual ~Subject() = default;

    // add observer
    void addObserver(Observer* observer) {
        observers.push_back(observer);
    }

    /// remove observer
    void removeObserver(Observer* observer) {
        observers.erase(
            std::remove(observers.begin(), observers.end(), observer),
            observers.end()
        );
    }

    // Notify ALL , used to update all observers
    void notify() {
        for (Observer* observer : observers) {
            observer->update();
        }
    }
};

#endif //SUBJECT_H