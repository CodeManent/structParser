#ifndef Source_FileSource_H_
#define Source_FileSource_H
#pragma once

#include "DataSource.h"

#include <string>		// we need it for the file name/path
#include <fstream>		// We need ifstream for the file

namespace Source{

/*
 * A data source that gets its data from a file.
 */
class FileSource: public DataSource
{
public:
	FileSource(std::string filemane, const Size base = 0, const Size position = 0 );	// Opens a file for reading
	virtual ~FileSource();

	virtual void read(const Size& size, void *dataHolder);		// Reads data from the file and [uts them in the dataHolder
	virtual void seek(const Size& position);					// Changes the reading positio of the file

private:
	std::string name_;		// The name/path of the file
	Size base_;					// A position that acts a a virtual start of the file. for =0 we have accdess to all the contents of the file.
	Size size_;				// The size of the file.
	std::ifstream file_;		// The system data for the (opened file)
};
} 
#endif // !Source_FileSource_H_
