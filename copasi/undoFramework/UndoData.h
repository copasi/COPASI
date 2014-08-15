/*
 * UndoData.h
 *
 *  Created on: 15 Aug 2014
 *      Author: dada
 */

#ifndef UNDODATA_H_
#define UNDODATA_H_

#include <string>

class UndoData {
public:
	UndoData();
	virtual ~UndoData();
	std::string getName() const;
	void setName(std::string name);
	std::string getType() const;
	void setType(std::string type);

private:
	std::string mName;
	std::string mType;
};

#endif /* UNDODATA_H_ */
