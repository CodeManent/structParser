#include "FileSource.h"

#include <stdexcept>
#include <vector>
#include <iostream>

namespace Source{

/*
 * Constructor.
 * Opens a file and sets the reading pointer at the beginning. If a base is used, the reading position
 * is boosted by the defined amount.
 */
FileSource::FileSource(std::string filename, const Size base, const Size position)
	: DataSource(position)
	, name_(filename)
	, base_ (base)
	, size_ (0)		// We will calculate the actual size in the constructor
	, file_( filename.c_str(), std::ifstream::in | std::ifstream::binary | std::ifstream::ate)
{
	//Check if the file is successfully opened
	if( !file_.good() )
		throw std::runtime_error("FileSource::FileSource: Error opening file:" + filename);

	file_.exceptions( std::ifstream::failbit | std::ifstream::badbit );

	//Because we opened the file with ifstream::ate that puts the read pointer at the ens pf the file
	size_ = Size( file_.tellg() );

	DataSource::seek(size_);
}

/*
 * Destructor.
 * Nothong to be done. The opened file will be closed automatically by it's destructor
 */
FileSource::~FileSource()
{
}


/*
 * TODO: Must add an explanation on how the reading works. It's almost the same with the memory reading.
 * Generally the reading position may not be byte aligned so every resulting byte we may need to contruct
 * it from the source by reading the parts from two consicuetive bytes
 * We assume that the dataHolder has enough space for the requested data.
 */
void FileSource::read( const Size &size, void * dataHolder)
{
	static unsigned char mask[] = {
		0xFF, 0x80, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC, 0xFE, 0x00
	};

	if( size == 0 )
		return;			// Nothing to be read

	unsigned char *dst = static_cast<unsigned char *> ( dataHolder );	//We set the destination pointer

	Size readFrom = base_ + DataSource::tell();							// We start reading from here
	Size readUntil = readFrom + size;									// and stop after the required data size

	uint64_t bytes = readUntil.storageBytes() - readFrom.byteSize();	// The mumber of bytes that must be read from the file.

	unsigned char *src = new unsigned char[static_cast<unsigned int>(bytes)];
	
	seek( DataSource::tell() );
	std::streamoff streamoff_bytes = static_cast<std::streamoff>( bytes );
	file_.read( reinterpret_cast<char*>( src ), streamoff_bytes);

	// data masks
	unsigned char highMask = mask[ readUntil.byteOffset() ];
	unsigned char lowMask  = highMask;
	unsigned char zeroByteMask = ~mask[ Size::BYTESIZE - size.byteOffset() ];

	//left and right shift size
	uint64_t lsh = readUntil.byteOffset();
	uint64_t rsh = ( Size::BYTESIZE - readUntil.byteOffset() ) % Size::BYTESIZE;

	uint64_t readPosition = bytes - size.storageBytes();	// = 0 or 1
	for( uint64_t current = 0; current < size.storageBytes(); ++current )
	{
		unsigned char byte = 0;
		if( readPosition != 0 )
			byte = ( src[ readPosition - 1 ] & lowMask ) << lsh;
		byte |= ( src[ readPosition ] & highMask ) >> rsh;

		if( current != 0 )
			dst[ current ] = byte;
		else
			dst[ current ] = ( dst[ current ] & ~zeroByteMask ) | ( byte & zeroByteMask);

		++readPosition;
	}

	delete[] src;
}

/*
 * Changes the reading position of the file.
 * Silently boosts the reading position if a base is used when constructing the object.
 * If the reading position is after the file boundries, an exception is generated.
 */
void FileSource::seek( const Size& position )
{
	if( position == tell() )
	{
		//if the reading position is already set, do nothing
		return;
	}
	else if( base_ + position > size_ )
	{
		// The requested positionlands beyond the file boundries.
		// An exception is thrown as an indication of the seek error
		throw std::runtime_error( "FileSource::seek: Seek error for file" + name_ + " at position " + tell().toString() + (base_ == Size(0) ? "" : "(base " + base_.toString() + ")" ) );
	}
	else
	{
		// Even if the bit position lands in the same byte, we may have already
		// read that byte from the file to get the previously requested bits so
		// the next bit will occure at the next byte. Here we resret the file
		// pointer to the actual byte so the following read will be correct.
		file_.seekg( static_cast<std::streamoff>( (base_ + position).byteSize() ) );
		DataSource::seek(position);
	}
}


}
