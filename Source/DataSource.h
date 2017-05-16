#ifndef Source_DataSource_H_
#define Source_DataSource_H_

#include "Size.h"

namespace Source{

/*
 * Represents a source of data. Actual implementqation will be in subclasses.
 */
class DataSource{
public:
	DataSource(const Size &position): position_(position){}
	virtual ~DataSource(){}

	// Reads data from the source and puts them in the dataHolder.
	virtual void read(const Size &size, void *dataHolder) = 0;

	// Returns the curent reading position of the dataSource.
	virtual Size tell()										
	{
		return position_;
	}

	// Changes the position of the dataSource.
	virtual void seek(const Size &position)
	{
		position_ = position;
	}


private:
	//The registered (currently only reading) position in the data source.
	Size position_;
} ;
}
#endif // !Source_DataSource_H_
