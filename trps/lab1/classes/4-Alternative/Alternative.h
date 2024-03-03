//
// Created by dmitry on 03.03.2024.
//

#ifndef LAB1_ALTERNATIVE_H
#define LAB1_ALTERNATIVE_H


#include "../3-List/List.h"

class Alternative{
private:
    List* mas = nullptr;
    int size = 0;
    int capacity = 0;
public:
    List* getList(int index);
    void resize();
    void reserve();
    void del();
    void lineSearch();
};


#endif //LAB1_ALTERNATIVE_H
