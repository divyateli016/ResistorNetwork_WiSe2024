#include "ResistorConnection.h"

ResistorConnection::ResistorConnection(std::string name) :
		Resistance(name)
{
}

char ResistorConnection::separator() const
{
	return ',';
}

std::string ResistorConnection::components() const
{
	std::string result = "[";
	for (const auto &ptr : resistors)
	{
		result += ptr.get()->getName() + separator();

	}
	result.pop_back();
	result += "]";
	return result;
}

ResistorConnection&
ResistorConnection::operator+=(ResistancePtr resistor)
{
	resistors.push_back(std::move(resistor));
	return *this;
}

void ResistorConnection::write(std::ostream &out)
{
	// TODO: implement method
	//float totalnominal = 0;
	//float max = 0;
	float tolerance = 0;
	for (const auto &ptr : resistors)
	{
		ptr->write(out); // This writes R1;value;tolerance, etc.
	}
	std::string result = getName() + "[";
	for (const auto &ptr : resistors)
	{
		result += ptr->getName() + separator();
		//totalnominal+=+ptr->nominalValue();
		//max +=ptr->maximumValue();
	}
	//tolerance = (max-totalnominal)/totalnominal;
	tolerance = (maximumValue() - nominalValue()) / nominalValue();
	result.pop_back();
	result += "]";
	out << std::fixed << std::setprecision(0) << result << ";" << nominalValue()
			<< ";" << std::fixed << std::setprecision(1) << tolerance
			<< std::endl;

}
