#include "Resistor.h"

#include <sstream>
#include <string>


Resistor::Resistor(std::string name, float value, float tolerance)
    : Resistance{name}, value{value}, tolerance{tolerance} {
}

ResistancePtr Resistor::from(std::string line) {
    // TODO: implement method
    std::string name;
    std::string svalue;
    std::string stolerance;
    std::istringstream iss(line);
    getline(iss,name,';');
    getline(iss,svalue,';');
    getline(iss,stolerance,'\n');
    float value = stof(svalue);
    float tolerance = stof(stolerance);
    ResistancePtr ptr = std::make_unique<Resistor>(name,value,tolerance);

    return ptr;
}

float Resistor::nominalValue() const {
    return value;
}

float Resistor::minimalValue() const {
    float maximum = this->value-(this->value*this->tolerance);
    return maximum;
}

float Resistor::maximumValue() const {
    float minimum = this->value+(this->value*this->tolerance);
    return minimum;
}

