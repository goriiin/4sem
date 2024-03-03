//
// Created by dmitry on 03.03.2024.
//

#ifndef LAB1_LIST_H
#define LAB1_LIST_H


#include "../1-Element/Element.h"

struct List{
    Element data;
    Element* next;

    List(): data(), next(nullptr){}
};

#endif //LAB1_LIST_H
