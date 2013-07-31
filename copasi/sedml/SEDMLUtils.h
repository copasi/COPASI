/*
 * SEDMLUtils.h
 *
 *  Created on: 15 Jul 2013
 *      Author: dada
 */

#ifndef SEDMLUTILS_H_
#define SEDMLUTILS_H_

#include <string>

class SEDMLUtils {
public:
	int processArchive(const std::string & archiveFile,
			std::string &fileName, std::string &fileContent);

//	void resmoveUnwantedChars(std::string & str, char chars[]);

	SEDMLUtils();

	virtual ~SEDMLUtils();
};

#endif /* SEDMLUTILS_H_ */
