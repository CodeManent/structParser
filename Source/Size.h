#ifndef Source_Size_H_
#define Source_Size_H_

#pragma once

#include <string>

#include <stdint.h>

namespace Source{


/*
 * Represents the Size of file and/or the position in a binary stream.
 * The resolution of the measurement is bits. The byte position/size
 *can be retrieved through te methods.
 */
class Size{
public:
	static unsigned int BYTESIZE;					// The size of a byte in bits
	Size(uint64_t bytes = 0, uint64_t bits = 0);	// Default constructor. 0 is initial position
	~Size();										// Default destructor
	
	const Size operator+( const Size& rhs) const;	// Adds two sizes
	const Size operator-( const Size& rhs) const;	// Subtracts two sizes

	bool operator> (const Size& rhs) const;			// Tests if first size if bigger than the second
	bool operator< (const Size& rhs) const;			// Tests if the first size is smaller than the second
	bool operator>=(const Size& rhs) const;			// Tests if the first size is greater or equal than the second
	bool operator<=(const Size& rhs) const;			// Tests if the first size is smaller or equal than the second
	bool operator==(const Size& rhs) const;			// Tests if the two sizes are equal
	bool operator!=(const Size& rhs) const;			// Tests if the two sizes are not equal

	uint64_t storageBytes() const;					// Returns the numbers of bytes needed to store data as big as the current size
	uint64_t byteSize() const;						// The number of full bytes in the current size
	uint64_t byteOffset() const;					// The number of bits after the full bytes

	uint64_t bitSize() const;						// Returns the size in bits

	std::string toString() const;					// Rteurns a string representation of the size in the form "byte:bit"

private:
	uint64_t bitSize_;								// The size measured in bits
};
}

#endif
