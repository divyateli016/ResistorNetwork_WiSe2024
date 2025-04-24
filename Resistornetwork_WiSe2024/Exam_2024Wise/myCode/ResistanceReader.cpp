#include <sstream>
#include "SerialResistorConnection.h"
#include "ParallelResistorConnection.h"
#include "Resistor.h"
#include "ResistanceReader.h"

void ResistanceReader::read(std::istream &in,
		std::map<std::string, ResistancePtr> &found)
{
	std::string line;
	while (std::getline(in, line))
	{
		if (line.empty())
			continue;

		// Split at first semicolon to get name and the rest
		auto pos = line.find(';');
		if (pos == std::string::npos)
			continue;

		std::string name = line.substr(0, pos);
		std::string after = line.substr(pos + 1);

		// Extract numeric fields (nominal and tolerance)
		auto pos2 = after.find(';');
		if (pos2 == std::string::npos)
			continue;
		std::string snom = after.substr(0, pos2);
		std::string stol = after.substr(pos2 + 1);

		float fnom = std::stof(snom);
		float ftol = std::stof(stol);

		// Case 1: a simple resistor (name length == 2)
		if (name.size() == 2)
		{
			auto ptr = std::make_unique<Resistor>(name, fnom, ftol);
			found.emplace(name, std::move(ptr));
		}
		else
		{
			// Case 2: a connection (series if '-', parallel if '|')
			auto dash = name.find('-');
			auto pipe = name.find('|');
			std::string connName = name.substr(0, 2);

			if (dash != std::string::npos)
			{
				// Series connection
				std::string r1 = name.substr(dash - 2, 2);
				std::string r2 = name.substr(dash + 1, 2);
				auto connPtr = std::make_unique<SerialResistorConnection>(
						connName);
				*connPtr += std::move(found.at(r1));
				*connPtr += std::move(found.at(r2));
				found.erase(r1);
				found.erase(r2);
				// Optionally: verify connPtr->nominalValue() == fnom, etc.
				found.emplace(connName, std::move(connPtr));
			}
			else if (pipe != std::string::npos)
			{
				// Parallel connection
				std::string r1 = name.substr(pipe - 2, 2);
				std::string r2 = name.substr(pipe + 1, 2);
				auto connPtr = std::make_unique<ParallelResistorConnection>(
						connName);
				*connPtr += std::move(found.at(r1));
				*connPtr += std::move(found.at(r2));
				found.erase(r1);
				found.erase(r2);
				// Optionally: verify nominal/tolerance
				found.emplace(connName, std::move(connPtr));
			}
		}
	}
}
