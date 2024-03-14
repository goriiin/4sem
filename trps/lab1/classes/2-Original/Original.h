//
// Created by dmitry
//

#ifndef LAB1_ORIGINAL_H
#define LAB1_ORIGINAL_H

#include "../1-Element/Element.h"
#include <vector>
#include <algorithm>

class Original {
private:
    std::vector<Element> data;
    bool sorted = false;
    size_t del_count = 0;
    static void merge(std::vector<Element>& buf, size_t l, size_t r, size_t m)
    {
        if (l >= r || m < l || m > r) return;
        if (r == l + 1 && buf[l] > buf[r]) {
            std::swap(buf[l], buf[r]);
            return;
        }

        std::vector<Element> tmp(&buf[l], &buf[l] + (r + 1));

        for (size_t i = l, j = 0, k = m - l + 1; i <= r; ++i) {
            if (j > m - l) {
                buf[i] = tmp[k++];
            } else if(k > r - l) {
                buf[i] = tmp[j++];
            } else {
                buf[i] = (tmp[j] < tmp[k]) ? tmp[j++] : tmp[k++];
            }
        }
    }
    void mergeSort(std::vector<Element>& buf, size_t l, size_t r)
    {
        //! Условие выхода из рекурсии
        if(l >= r) return;

        size_t m = (l + r) / 2;

        //! Рекурсивная сортировка полученных массивов
        mergeSort(buf, l, m);
        mergeSort(buf, m+1, r);
        merge(buf, l, r, m);
    }
public:
    Element& get(int index); // получить элемент по индексу
    [[maybe_unused]] size_t BinarySearch(size_t ElementCode, size_t workshopNum, size_t flowRate, std::string unit, std::string materialCode); // Бинарный поиск
    [[maybe_unused]] void delMarker(size_t ElementCode, size_t workshopNum, size_t flowRate, std::string unit, std::string materialCode); // удаление маркером

    void merge_sort(){
        mergeSort(data,0, data.size());
    }
    void sort(){
        mergeSort(data, 0, data.size());
        sorted = true;
    }
    [[maybe_unused]] void push(Element& element); // вставка

    void markerDel(int ind){
        data[ind].setDeleled(true);
    }

    void qsort(){
        qsortRecursive(data, data.size());
    }

    void del(int ind){
        data[ind] = data[size-1];
        --size
    }

    void qsortRecursive(std::vector<Element> mas, int size) {
        //Указатели в начало и в конец массива
        int i = 0;
        int j = size - 1;

        //Центральный элемент массива
        auto mid = mas[size / 2];

        //Делим массив
        do {
            //Пробегаем элементы, ищем те, которые нужно перекинуть в другую часть
            //В левой части массива пропускаем(оставляем на месте) элементы, которые меньше центрального
            while(mas[i] < mid) {
                i++;
            }
            //В правой части пропускаем элементы, которые больше центрального
            while(mas[j] > mid) {
                j--;
            }

            //Меняем элементы местами
            if (i <= j) {
                auto tmp = mas[i];
                mas[i] = mas[j];
                mas[j] = tmp;

                i++;
                j--;
            }
        } while (i <= j);


        //Рекурсивные вызовы, если осталось, что сортировать
        if(j > 0) {
            //"Левый кусок"
            qsortRecursive(mas, j + 1);
        }
        if (i < size) {
            //"Првый кусок"
            qsortRecursive(mas, size - i);
        }
    }



};

Element &Original::get(int index) {
    return data[index];
}

[[maybe_unused]] void Original::push(Element &element) {
    data.push_back(element);

    sorted = false;
}

[[maybe_unused]] size_t Original::BinarySearch(size_t ElementCode, size_t workshopNum, size_t flowRate, std::string unit, std::string materialCode) {
    Element e(ElementCode, materialCode, workshopNum, flowRate, unit);
    size_t l = 0, r = data.size()-1;
    size_t m;

    while (l < r){
        m = (l+r)/2;

        while (data[m].isDeleted() && m > l && m < r){
            if (l>0)
                ++m;
            else
                --m;
        }

        if (e < data[m])
            r = m;
        else
            l = m + 1;
    }
    if (data[l] == e){
        return l;
    }
    return -1;
}

[[maybe_unused]] void Original::delMarker(size_t ElementCode, size_t workshopNum, size_t flowRate, std::string unit, std::string materialCode) {
    size_t ind = BinarySearch(ElementCode, workshopNum, flowRate, unit, materialCode);
    if (ind != -1)
        ++del_count;
    data[ind].setDeleled(true);
    if (del_count == data.size() / 2) {
        // Эффективный алгоритм очистки вектора
        auto it = std::remove_if(data.begin(), data.end(), [](const Element &ele) { return ele.isDeleted(); });
        data.erase(it, data.end());
    }
}



#endif //LAB1_ORIGINAL_H

