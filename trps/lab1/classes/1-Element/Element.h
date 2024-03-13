//
// Created by dmitry
//

#ifndef LAB1_ELEMENT_H
#define LAB1_ELEMENT_H

#include <iostream>

class Element{
    size_t elementCode; // код детали
    std::string materialCode; // код материала
    size_t workshopNum; // номер цеха
    size_t flowRate; // норма расхода
    std::string unit; // единица измерения
    bool deleted = false;
public:
    Element(): elementCode(0), materialCode(""), workshopNum(0), flowRate(0), unit(""){}
    void setDeleled(bool flag){
        deleted = flag;
    }
    bool isDeleted() const {
        return deleted;
    }
    Element(size_t el_code, std::string mat_code, size_t work_num, size_t flow_rate, std::string unit_):
        elementCode(el_code), materialCode(mat_code),workshopNum(work_num),
        flowRate(flow_rate), unit(unit_){}

    size_t getElementCode() const;

    [[maybe_unused]] void setElementCode(size_t new_code);

    [[maybe_unused]] [[nodiscard]] std::string getMaterialCode() const;

    [[maybe_unused]] void setMaterialCode(size_t new_code);

    size_t getWorkshopNum() const;

    [[maybe_unused]] void setWorkshopNum(size_t new_num);

    size_t getFlowRate() const;

    [[maybe_unused]] void setFlowRate(size_t new_rate);

    std::string getUnit() const;

    [[maybe_unused]] void setUnit(std::string new_unit);
};
bool operator < (const Element& left, const Element& right){
    if (left.getElementCode() < right.getElementCode())
        return true;
    else if (left.getElementCode() == right.getElementCode()){
        if (left.getFlowRate() < right.getFlowRate())
            return true;
        else if (left.getFlowRate() == right.getFlowRate())
            if (left.getWorkshopNum() < right.getWorkshopNum())
                return true;
    }
    return false;
}

bool operator > (const Element& left, const Element& right){
    return right < left;
}

bool operator == (const Element& left, const Element& right){
    if (left.getWorkshopNum() == right.getWorkshopNum() && left.getFlowRate() == right.getFlowRate()
            && left.getElementCode() == right.getElementCode() && left.getUnit() == right.getUnit() && left.getMaterialCode() == right.getMaterialCode())
        return true;
    return false;
}

[[maybe_unused]] void Element::setMaterialCode(size_t new_code) {
    materialCode = new_code;
}

size_t Element::getWorkshopNum() const {
    return workshopNum;
}

[[maybe_unused]] void Element::setWorkshopNum(size_t new_num){
    workshopNum = new_num;
}

size_t Element::getFlowRate() const {
    return flowRate;
}

[[maybe_unused]] void Element::setFlowRate(size_t new_rate) {
    flowRate = new_rate;
}

std::string Element::getUnit() const {
    return unit;
}

[[maybe_unused]] void Element::setUnit(std::string new_unit) {
    unit = std::move(new_unit);
}

size_t Element::getElementCode() const{
    return elementCode;
}

[[maybe_unused]] std::string Element::getMaterialCode() const {
    return materialCode;
}

[[maybe_unused]] void Element::setElementCode(size_t new_code) {
    elementCode = new_code;
}

#endif //LAB1_ELEMENT_H
