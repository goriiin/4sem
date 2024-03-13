//
// Created by dmitry
//

#ifndef LAB1_ALTERNATIVE_H
#define LAB1_ALTERNATIVE_H
#include <vector>
#include <map>
#include "../1-Element/Element.h"
#include <algorithm>
class Alternative{
private:
    std::map<int, std::vector<Element>> data;
public:
    void reserve();
    void del(size_t ElementCode, size_t workshopNum, size_t flowRate, std::string unit, std::string materialCode);
    std::pair<size_t, size_t> binarySearch(size_t ElementCode, size_t workshopNum, size_t flowRate, std::string unit, std::string materialCode);
    void insert(const Element& el); // добавление с сохранением порядка по возрастанию
    void push(const Element& el); // добавление в конец
    void remove(const Element& el); // удаление с сохранением порядка -- эффективно для поиска
    void fastRemove(const Element& el); // замена данного элемента и последнего в векторе и уменьшение real-size на 1
    std::vector<Element> getVec(size_t elementCode);// выдача вектора элементов с одним кодом элемента - можно быстро найти замену
    void quickSort();
};




#endif //LAB1_ALTERNATIVE_H
