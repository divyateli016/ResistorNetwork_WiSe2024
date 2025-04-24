#include "ParallelResistorConnection.h"

ParallelResistorConnection::ParallelResistorConnection(std::string name) :
		ResistorConnection(name)
{
}

char ParallelResistorConnection::separator() const
{
	return '|';
}

float ParallelResistorConnection::nominalValue() const
{
	float nominator = 1;
	float dinominator = 0;
	for (const auto &res : resistors)
	{
		nominator = nominator * res->nominalValue();
		dinominator += res->nominalValue();
	}
	return nominator / dinominator;
}

float ParallelResistorConnection::minimalValue() const
{
	float nominator = 1;
	float dinominator = 0;
	for (const auto &res : resistors)
	{
		nominator = nominator * res->minimalValue();
		dinominator += res->minimalValue();
	}
	return nominator / dinominator;
}

float ParallelResistorConnection::maximumValue() const
{
	float nominator = 1;
	float dinominator = 0;
	for (const auto &res : resistors)
	{
		nominator = nominator * res->maximumValue();
		dinominator += res->maximumValue();
	}
	return nominator / dinominator;
}
