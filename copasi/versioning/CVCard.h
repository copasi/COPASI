// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

#ifndef COPASI_CVCard
#define COPASI_CVCard

#include <combine/vcard.h>
class XMLOutputStream;

class CVCard : public VCard
{
public:
  friend XMLOutputStream & operator << (XMLOutputStream & xml, const CVCard & vcard);

  CVCard(const std::string & type = "");

  CVCard(XMLInputStream & stream, const XMLToken & current);

  CVCard(const CVCard & src);

  virtual ~CVCard();

  void setType(const std::string & type);

  const std::string & getType() const;

private:
  std::string mType;
};

XMLOutputStream & operator << (XMLOutputStream & xml, const CVCard & vcard);

#endif // CVCard
