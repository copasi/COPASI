#include "CBaseIdentifier.h"

CBaseIdentifier::CBaseIdentifier() {mType = 0;}

CBaseIdentifier::~CBaseIdentifier() {}

void CBaseIdentifier::setName(const string & name) {mName = name;}

void CBaseIdentifier::setType(char type) {mType = type;}

string CBaseIdentifier::getName() const {return mName;}

char CBaseIdentifier::getType() const {return mType;}
