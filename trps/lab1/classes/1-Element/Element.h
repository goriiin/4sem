//
// Created by dmitry on 03.03.2024.
//

#ifndef LAB1_ELEMENT_H
#define LAB1_ELEMENT_H

#include <iostream>

class Element{
    size_t elementCode; // код детали
    size_t materialCode; // код материала
    size_t workshopNum; // номер цеха
    size_t flowRate; // норма расхода
    std::string unit; // единица измерения
public:
    size_t getElementCode();
    void setElementCode();
    size_t getMaterialCode();
    void setMaterialCode();
    size_t getWorkshopNum();
    void setWorkshopNum();
    size_t getFlowRate();
    void setFlowRate();
    std::string getUnit();
    void setUnit();
};


#endif //LAB1_ELEMENT_H
