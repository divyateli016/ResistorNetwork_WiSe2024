#include "SerialResistorConnection.h"

SerialResistorConnection::SerialResistorConnection
    (std::string name) : ResistorConnection{name} {
}

char SerialResistorConnection::separator() const {
    return '-';
}

float SerialResistorConnection::nominalValue() const {
	float totalnominalvalue=0;
	for(const auto& res : resistors)
	{
		totalnominalvalue+=res->nominalValue();
	}
    return totalnominalvalue;
}

float SerialResistorConnection::minimalValue() const {
    // TODO: implement method
	float totalmin = 0;
	for(const auto& res : resistors)
	{
		totalmin+=res->minimalValue();
	}

    return totalmin;
}

float SerialResistorConnection::maximumValue() const {
    // TODO: implement method
	float totalmax = 0;
	for(const auto& res:resistors)
	{
		totalmax+=res->maximumValue();
	}
    return totalmax;
}
