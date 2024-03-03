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
    size_t getElementCode() const;
    void setElementCode(size_t new_code);
    size_t getMaterialCode() const;
    void setMaterialCode(size_t new_code);
    size_t getWorkshopNum() const;
    void setWorkshopNum(size_t new_num);
    size_t getFlowRate() const;
    void setFlowRate(size_t new_rate);
    std::string getUnit() const;
    void setUnit(std::string new_unit);
};


#endif //LAB1_ELEMENT_H
