//
// Created by dmitry on 03.03.2024.
//

#include "Element.h"

size_t Element::getElementCode() const {
    return elementCode;
}

void Element::setElementCode(size_t new_code) {
    elementCode = new_code;
}

size_t Element::getMaterialCode() const {
    return materialCode;
}

void Element::setMaterialCode(size_t new_code) {
    materialCode = new_code;
}

size_t Element::getWorkshopNum() const {
    return workshopNum;
}

void Element::setWorkshopNum(size_t new_num){
    workshopNum = new_num;
}

size_t Element::getFlowRate() const {
    return flowRate;
}

void Element::setFlowRate(size_t new_rate) {
    flowRate = new_rate;
}

std::string Element::getUnit() const {
    return unit;
}

void Element::setUnit(std::string new_unit) {
    unit = std::move(new_unit);
}
