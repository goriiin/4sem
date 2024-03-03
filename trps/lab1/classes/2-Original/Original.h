//
// Created by dmitry on 03.03.2024.
//

#ifndef LAB1_ORIGINAL_H
#define LAB1_ORIGINAL_H

#include "../1-Element/Element.h"

class Original {
private:
    Element* mas = nullptr;
    int size = 0;
    int capacity = 0;
public:
    Element& get(int index);
    Element& BinarySearch();
    void delMarker();
    void resize();
    void reserve();
    void mergeSort();
};

#endif //LAB1_ORIGINAL_H
