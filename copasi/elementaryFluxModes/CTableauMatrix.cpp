// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/elementaryFluxModes/CTableauMatrix.cpp,v $
//   $Revision: 1.16.2.4 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/07/08 20:10:52 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 *  CTableauMatrix class.
 *  Used to calculate elementary flux modes
 *
 *  Created for Copasi by Stefan Hoops 2002-05-08
 * (C) Stefan Hoops 2002
 */

#include <iostream>

#include "copasi.h"
#include "CTableauMatrix.h"

CTableauMatrix::CTableauMatrix():
    mLine(),
    mFirstIrreversible(mLine.end())
{}

CTableauMatrix::CTableauMatrix(const std::vector< std::vector< C_FLOAT64 > > & stoi,
                               size_t reversibleNumber):
    mLine(),
    mFirstIrreversible(mLine.end())
{
  size_t ReactionCounter = 0;
  size_t ReactionNumber = stoi.size();

  for (std::vector< std::vector< C_FLOAT64 > >::const_iterator Reaction = stoi.begin();
       Reaction < stoi.end();
       Reaction++, ReactionCounter++)
    {
      mLine.push_back(new CTableauLine(*Reaction,
                                       (ReactionCounter < reversibleNumber) ? true : false,
                                       ReactionCounter,
                                       ReactionNumber));

      if (ReactionCounter == reversibleNumber)
        {
          mFirstIrreversible--;
        }
    }
}

CTableauMatrix::~CTableauMatrix()
{
  for (std::list< const CTableauLine * >::iterator i = mLine.begin();
       i != mLine.end(); i++)
    pdelete(*i);
}

size_t CTableauMatrix::size() const
{return mLine.size();}

std::list< const CTableauLine * >::iterator CTableauMatrix::begin()
{
  return mLine.begin();
}

std::list< const CTableauLine * >::const_iterator CTableauMatrix::begin() const
{
  return mLine.begin();
}

std::list< const CTableauLine * >::iterator CTableauMatrix::end()
{
  return mLine.end();
}

std::list< const CTableauLine * >::const_iterator CTableauMatrix::end() const
{
  return mLine.end();
}

void CTableauMatrix::addLine(const CTableauLine * src,
                             const bool & check)
{
  /* First we check whether we have a valid new flux mode */
  if (!check || isValid(src))
    {
      if (src->isReversible())
        {
          mFirstIrreversible = mLine.insert(mFirstIrreversible, src);
          mFirstIrreversible++;
        }
      else if (mFirstIrreversible == mLine.end())
        {
          mFirstIrreversible = mLine.insert(mFirstIrreversible, src);
        }
      else
        {
          mLine.push_back(src);
        }
    }
  else
    pdelete(src);
}

void CTableauMatrix::removeLine(const std::list< const CTableauLine * >::iterator line)
{
  if (line == mFirstIrreversible && mFirstIrreversible == mLine.begin())
    {
      mLine.pop_front();
      mFirstIrreversible = mLine.begin();
    }
  else if (line == mFirstIrreversible)
    {
      mFirstIrreversible--;
      mLine.erase(line);
      mFirstIrreversible++;
    }
  else
    {
      mLine.erase(line);
    }
}

bool CTableauMatrix::isValid(const CTableauLine * src)
{
  std::list< const CTableauLine * >::iterator i;
  std::list< const CTableauLine * >::iterator tmp;

  /* Check whether we have already better lines */
  for (i = mLine.begin(); i != mLine.end(); i++)
    if ((*i)->getScore() < src->getScore())
      return false;

  i = mLine.begin();

  /* Check whether the new line scores better than existing lines */

  /* If so the existing lines are removed */
  for (i = mLine.begin(); i != mLine.end();)
    if (src->getScore() < (*i)->getScore())
      {
        if (i == mLine.begin())
          {
            removeLine(i);
            i = mLine.begin();
          }
        else
          {
            tmp = i;
            tmp--;
            removeLine(i);
            i = tmp;
            i++;
          }
      }
    else
      i++;

  return true;
}

std::ostream & operator << (std::ostream & os, const CTableauMatrix & m)
{
  os << "Tableau Matrix: Number of Lines = " << m.mLine.size() << std::endl;
  std::list< const CTableauLine * >::const_iterator i;

  for (i = m.mLine.begin(); i != m.mLine.end(); i++)
    {
      os << (**i);
    }

  return os;
}
