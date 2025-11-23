//
// Created by cddhi on 7/10/2025.
//

#ifndef OBSERVER_H
#define OBSERVER_H

#include <vector>
#include <algorithm>

class Observer {
public:
    virtual void update() = 0;
    virtual ~Observer() = default;
};


#endif //OBSERVER_H
