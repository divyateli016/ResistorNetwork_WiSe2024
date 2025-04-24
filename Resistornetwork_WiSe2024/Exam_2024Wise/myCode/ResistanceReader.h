#ifndef RESISTANCEREADER_H_
#define RESISTANCEREADER_H_

#include <istream>
#include <map>
#include <memory>

#include "Resistance.h"

/**
 * Restores resistances from an input stream.
 */
class ResistanceReader {
public:
    /**
     * Reads resistances from an input stream. The input stream is
     * expected to be in the format created by {@link Resistance#write}.
     *
     * The resistances are stored in the given map. The resulting map
     * contains only "top-level" resistances, i.e. resistances that are
     * not part of a resistor connection. (17 points)
     *
     * (If you have problems handling the unique_ptrs, you can change
     * the type of "found" to std::map<std::string, Resistance*> and
     * the return type of the Resistors's "from" methods to Resistance*.
     * This will, however, result in a reduction of points.)
     *
     * @param in the input stream
     * @param found the map
     */
    static void read(std::istream& in,
            std::map<std::string, ResistancePtr>& found);

};

#endif /* RESISTANCEREADER_H_ */
