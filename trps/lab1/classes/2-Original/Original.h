//
// Created by dmitry on 03.03.2024.
//

#ifndef LAB1_ORIGINAL_H
#define LAB1_ORIGINAL_H

#include "../1-Element/Element.h"

class Original {
private:
    Element* mas = nullptr;
    size_t size = 0;
    size_t capacity = 0;
    size_t delCount = 0;
public:
    Element& get(int index); // получить элемент по индексу
    size_t BinarySearch(); // Бинарный поиск
    void delMarker( size_t elementCode, size_t materialCode,
                    size_t workshopNum, size_t flowRate, std::string unit); // удаление маркером
    void resize(size_t new_capacity); // прринудительно выделить/освободить память
    void reserve(size_t new_capacity); // new_cap > old_cap
    void mergeSort(); // сортировка
    void insert(Element& element); // вставка
};

#endif //LAB1_ORIGINAL_H
