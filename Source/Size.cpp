#include "Size.h"

#include <stdexcept>	// we need stdExcept for operator-
#include <sstream>		// we need stringstream for toString()
namespace Source{

unsigned int Size::BYTESIZE = 8;

/*
 * Constructor. Defaults to (0, 0)
 */
Size::Size(uint64_t bytes, uint64_t bits)
	:bitSize_(bits)
{
	bitSize_ += BYTESIZE * bytes;
}

/*
 * Destructor. Nothing to do for now
 */
Size::~Size()
{
}

/*
 * Adds two sizes.
 * The result is computed by adding the bitSize_ of the two parts
 */
const Size Size::operator+(const Size& rhs) const
{
	return Size(0, bitSize_ + rhs.bitSize_);
}

/*
 * Subtracts two sizes.
 * The result is computed by subtracting the bitSize_ of the two parts
 */
const Size Size::operator-(const Size& rhs) const
{
	if(rhs > *this)
		throw std::runtime_error("Size::operator-: Subtraction returns a negative value");
	return Size(0, bitSize_ - rhs.bitSize_);
}


/*
 * Comparison operators implementation. For all the operators the code
 * is the same. The macro fills in the needed copies of the code
 */
#define SIZE_COMPARISON_OPERATOR_IMPLEMENTATION(x)\
	bool Size::operator x (const Size& rhs) const\
	{\
		return bitSize_ x rhs.bitSize_;\
	}

SIZE_COMPARISON_OPERATOR_IMPLEMENTATION(<)
SIZE_COMPARISON_OPERATOR_IMPLEMENTATION(>)
SIZE_COMPARISON_OPERATOR_IMPLEMENTATION(<=)
SIZE_COMPARISON_OPERATOR_IMPLEMENTATION(>=)
SIZE_COMPARISON_OPERATOR_IMPLEMENTATION(==)
SIZE_COMPARISON_OPERATOR_IMPLEMENTATION(!=)

uint64_t Size::storageBytes() const
{
	return byteOffset() ? byteSize() + 1 : byteSize();
}

uint64_t Size::byteSize() const
{
	return bitSize_ / BYTESIZE;
}

uint64_t Size::byteOffset() const
{
	return bitSize_ % BYTESIZE;
}

/*
 * Returns the size in bits
 */
uint64_t Size::bitSize() const
{
	return bitSize_;
}

/*
 * Return a string representation of the size
 */
std::string Size::toString() const
{
	std::stringstream ss;

	ss << byteSize() << ":" << byteOffset();

	return ss.str();
}


}
