/*
 * SEDMLUtils.cpp
 *
 *  Created on: 15 Jul 2013
 *      Author: dada
 */

#include <zip.h>
#include <sstream>
#include <iostream>
#include <vector>
#include "SEDMLUtils.h"

int SEDMLUtils::processArchive(const std::string & archiveFile,
		std::string &fileName, std::string &fileContent)
{
	int err = 0;
	const char * cArchive = archiveFile.c_str();

    //Open the ZIP archive
    zip *zip = zip_open(cArchive, 0, &err);

    //Search for file using its given name
    const char *nameOfFile = fileName.c_str();
    struct zip_stat st;
    zip_stat_init(&st);
    zip_stat(zip, nameOfFile, 0, &st);

    //Alloc memory for its uncompressed contents
    char *fileCont = new char[st.size];

    //Read the compressed file
	zip_file *file = zip_fopen(zip, nameOfFile, 0);
	zip_fread(file, fileCont, st.size);

	std::ostringstream fileContentStream;
	size_t i, iMax = st.size;
	for(i = 0; i<iMax; ++i){
		fileContentStream << fileCont[i];
	}
	fileContent = fileContentStream.str();

	//close the file and archive
	zip_fclose(file);
	zip_close(zip);

    return err;
}

/*void SEDMLUtils::resmoveUnwantedChars(std::string & str, char chars[]) {
	for (unsigned int i = 0; i < strlen(chars); ++i) {

		str.erase(std::remove(str.begin(), str.end(), chars[i]), str.end());
	}
}
*/
SEDMLUtils::SEDMLUtils() {
	// TODO Auto-generated constructor stub

}

SEDMLUtils::~SEDMLUtils() {
	// TODO Auto-generated destructor stub
}

