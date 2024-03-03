//
// Created by dmitry on 03.03.2024.
//

#ifndef LAB1_LIST_H
#define LAB1_LIST_H


#include "../1-Element/Element.h"

class List{
private:
    Element data;
    Element* next;
public:
    List(): data(), next(nullptr){}
    List(Element& el) : data(el), next(nullptr){}

    void mergeSort();
    void searchElement(size_t elementCode, size_t materialCode,
                       size_t workshopNum, size_t flowRate, std::string unit);
    void insert(Element& element);
    Element& get(size_t index);
    void remove(size_t index);
};

#endif //LAB1_LIST_H
