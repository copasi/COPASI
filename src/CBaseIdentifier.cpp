#include "CBaseIdentifier.h"

CBaseIdentifier::CBaseIdentifier() {mType = 0;}

CBaseIdentifier::~CBaseIdentifier() {}

void CBaseIdentifier::SetName(const string & name) {mName = name;}

void CBaseIdentifier::SetType(char type) {mType = type;}

string CBaseIdentifier::GetName() const {return mName;}

char CBaseIdentifier::GetType() const {return mType;}
