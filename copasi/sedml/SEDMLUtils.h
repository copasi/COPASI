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
	int processArchive(const std::string & archiveFile, std::string &fileName, std::string &fileContent);

	//	void resmoveUnwantedChars(std::string & str, char chars[]);

	SEDMLUtils();

	/**
	 *  This is a hack at the moment better solution for processing XPath string may be developed in the future
	 */
	void splitStrings(const std::string &xpath, char &delim, std::vector<std::string> &stringsContainer);


	virtual ~SEDMLUtils();
};

#endif /* SEDMLUTILS_H_ */
