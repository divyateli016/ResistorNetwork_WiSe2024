#include "Resistance.h"

#include <cmath>
#include <sstream>

Resistance::Resistance(std::string name): name{name} {
}

Resistance::~Resistance() {
}

std::string Resistance::getName() const {
    return name;
}

std::string Resistance::components() const {
    return "";
}

std::string Resistance::toString() const {
    std::string result;
    result = getName()+components()+"="+" Ohm";
    return result;
}

std::ostream& operator<< (std::ostream& out, Resistance& resistor) {
    out << resistor.toString();
    return out;
}

void Resistance::write(std::ostream &out) {
    float tolerance = (maximumValue()-nominalValue())/nominalValue();
out<<getName()<<";"<<std::fixed<<std::setprecision(0)<<nominalValue()<<";"<<
		std::fixed<<std::setprecision(1)<<tolerance<<std::endl;
}
