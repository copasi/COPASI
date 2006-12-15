/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/commercial/Attic/GenericDecode.c,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/12/15 16:21:08 $
   End CVS Header */

// Copyright © 2006 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/*
 *  Copyright(c) 2004  Kagi.  All Rights Reserved.
 * Permission is granted to use this code module for development of decoding algorithm
 * for the generic acg.No warranty is made as to the suitability to your application
 *
 *     BECAUSE THE REFERENCE IS LICENSED FREE OF CHARGE, THERE IS NO
 *     WARRANTY FOR THE REFERENCE, TO THE EXTENT PERMITTED BY APPLICABLE LAW.
 *     EXCEPT WHEN OTHERWISE STATED IN WRITING THE COPYRIGHT HOLDERS AND/OR
 *     OTHER PARTIES PROVIDE THE REFERENCE "AS IS" WITHOUT WARRANTY OF ANY
 *     KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, THE
 *     IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 *     PURPOSE.  THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE
 *     REFERENCE IS WITH YOU.  SHOULD THE REFERENCE PROVE DEFECTIVE, YOU ASSUME
 *     THE COST OF ALL NECESSARY SERVICING, REPAIR OR CORRECTION.
 *     If you make any corrections to the basic reference or have suggestions
 *     please send them to acg@kagi.com so other may benefit.
 *
 *  If you make any corrections to the basic module or have suggestions
 *   please send them to acg@kagi.com so others may benefit
 *  VERSION HISTORY
 *      Alpha   3/1/2004
 *      1.0     Implementaion of the corrections suggested by Ty.
    Fixed the bug in method unformatCode(), for registration codes larger
    than the length of the format string.
    Fixed the bug so that largest length registration code can be decoded.
 *     1.0.1  5/14/2004 Correctly decode registration codes with the format
         string having specification for additional character in the
         formatted code([-#], [-76#])
          Allow for decoding of multiple codes in a single run: Bug reported by
          Aquafadas sales.
               Fixed the bug reported by Ben Rister for max length registration codes.
               Feature to generate user seed from given name and email for a configuration.
  1.0.2 7/26/2004
     Fixed bug reported by Aquafadas about the reverse operation on '09'
     The condition used to be if(number < 9)  number = number*10 changed
     to if(number <= 9)   number = number*10 so that the reverse of 09 is
     returned as 90 and not as 09
     1.0.3 8/25/2004
    Fixed some minor declaration changes as suggested by Ondra Cada
  1.0.4 2/14/2005 Fixed memory leak fixes guven by Al Evans

 *
 **/

/**
 * This program denotes how to obtain the user seed,
 * the contant value , the sequence number and date from the regisrtation code
 * You require two pieces of data the registration code and the configuration
 * that was used to create the registration code.
 * To compile
 */

#include "GenericDecode.h"
#include "BigInt.h"
#ifdef DEBUG
#include "mallocTracking.h"
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int regcodelength; //length of unformatted regcode
int namelength; //length of name seed
int emaillength; //length of email seed
int hotsynclength; //length of email seed
char* seedcombo; //the seed combo ee en ne nn hh
int userseedlength; //lenght of user seed
int seedlength;  //length of the seed
int constlength; //lenght of teh constant
char* constvalue; // value of the constant
int seqlength; //length of the sequence
char* scrambleSequence; //scrambling order for the seed
char* asciidigit; //number of digits fro ascii to number conversion
char* mathoperations; //string containing list of math operations
char* base; //the base into which the number was converted
char* basedigit; //the base character set
char* regformat; //the format of the registration code
char checkdigit; // the check digit received with the registration code
char* regcode; // the unformatted registration code
char* operations[40]; // stores the arithmetic operation for the seed characters
char* scrambleOrder[40]; //stores the scramble order information about the seed characters
int seedasinteger[40]; //the seed in numeric format
char seed[31]; // the user seed
char date[5]; // the date the regisration code was created
char sequence[4]; // the sequence
char constant[4]; // the constant
char baseTenNumber[130]; // the number after converting to baseten
char* configuration;
char* registrationcode;
int CHAR_TYPE = 1;
int INT_TYPE = 2;
char debugBuffer[200];
char * debugMessage = 0;
int debugBufferCount;
char userName[21];
char userEmail[21];
char createdUserSeed[31];

/** Decodes the registration code */
int decodeGenericRegCode(const char * c , const char * r)
{

  int size = strlen(c);
  configuration = (char *)allocateMemory(size, CHAR_TYPE);
  strncpy(configuration , c , size);

  size = strlen(r);
  registrationcode = (char *)allocateMemory(size, CHAR_TYPE);
  resetVariables();
  strncpy(registrationcode , r , size);
  //parse the configuration data and intialize the global variables
  initializeConfigData(configuration);
  //now remove format information and static text from the reg code
  //and seperate into the registration code and check digit
  unformat();
  // if the calculated checkdigit matches the one received with
  // the registration code the proceed with the decoding
  if (verifyCheckDigit() == 1)
    {
      convertToBaseTen();
      undoarithmetic(baseTenNumber);
      unScrambleSeed();
      return 0;
    }
  else
    {
      //the checkdigit could not be verified
#ifdef DEBUG
      debugBufferCount = sprintf (debugBuffer,
                                  "The calculated and received checkdigit do not match.\n");
      setDebugMessage(debugBufferCount, debugBuffer);
#endif
      return 1;
    }
}

/**
 * This method reset variables to 0  and pionters tonull
 * before a registration code can be decoded
 */
void resetVariables(void)
{
  int i;
  for (i = 0 ; i < 130 ; ++i)
    {
      baseTenNumber[i] = '\0';
    }
}

/**
  This method parses the configuration data and uses
  it to intialize the variables.The configuration data consist of name
  value pairs (eg SUPPLIERID:softedge) seperated by the character %
  */
void initializeConfigData(char* config)
{
  char *pch;
  char *p;
  int dataID = 0;
  int length;

  pch = strtok(config, "%");  //tokenize the configuration string

  while (pch != NULL)
    {
#ifdef DEBUG
      debugBufferCount = sprintf (debugBuffer, "%s\n", pch);
      setDebugMessage(debugBufferCount, debugBuffer);
#endif
      //split the name value pair into key and value
      p = strchr(pch, ':');
#ifdef DEBUG
      debugBufferCount = sprintf (debugBuffer, "%s\t%d \n", p + 1, dataID);
      setDebugMessage(debugBufferCount, debugBuffer);
#endif
      //the length of the key
      length = strlen(p + 1);

      //store the value associated with this key
      storeData(length, p + 1, dataID);
      //get the next name value pair
      pch = strtok(NULL, "%");
      ++dataID;
    }
  //we have finished intializing the variables from the configuration data
  //now calculate the seed length
  //printf("\nTHe seed length\t%d\t%d\t%d\t",userseedlength ,constlength , seqlength);
  seedlength = userseedlength + constlength + seqlength + 4;
  // seed = (char *)allocateMemory(userseedlength , CHAR_TYPE);

  //split the math operation string ,store operation corresponding to each
  // seed charcater in an array
  parseMathOperations();
  //split the scramble string ,store scramble information corresponding to each
  // seed charcater in an array
  parseScrambleSequence();
#ifdef DEBUG
  debugBufferCount = sprintf (debugBuffer, "The seed is %d length", seedlength);
  setDebugMessage(debugBufferCount, debugBuffer);
#endif
}

/**
This intializes the global variabled based on configuration data
len - the length of the buffer to be allocated.
data - pointer to the variable value
type - type of configuration data
 */
void storeData(int len, char* data, int type)
{
  char* temp ; //temporary storege for values
  switch (type)
    {

    case 1: //minimum length of the name part of user seed
      temp = (char *) allocateMemory(len , CHAR_TYPE);
      strncpy(temp, data, len);
      namelength = atoi(temp);
      free(temp);
      break;
    case 2: // minimum length of email part of user seed
      temp = (char *) allocateMemory(len , CHAR_TYPE);
      strncpy(temp, data , len);
      emaillength = atoi(temp);
      free(temp);
      break;

    case 3: // minimum length of hotsyncid part of user seed
      temp = (char *) allocateMemory(len , CHAR_TYPE);
      strncpy(temp, data , len);
      hotsynclength = atoi(temp);
      free(temp);
      break;

    case 4: // the seed combo ee en ne nn hh
      seedcombo = (char *) allocateMemory(len , CHAR_TYPE);
      strncpy(seedcombo, data, len);
      break;

    case 5: // the length of the user seed
      temp = (char *) allocateMemory(len , CHAR_TYPE);
      strncpy(temp, data, len);
      userseedlength = atoi(temp);
      free(temp);
      break;

    case 6:   // the length of the constant
      temp = (char *) allocateMemory(len , CHAR_TYPE);
      strncpy(temp, data, len);
      constlength = atoi(temp);
      free(temp);
      break;

    case 7:  // the constant value
      constvalue = (char *) allocateMemory(len , CHAR_TYPE);
      strncpy(constvalue, data, len);
      break;
    case 8:   // the maximum length of a sequence number
      temp = (char *) allocateMemory(len , CHAR_TYPE);
      strncpy(temp, data, len);
      seqlength = atoi(temp);
      free(temp);
      break;
    case 10: // the scramble order
      scrambleSequence = (char *)allocateMemory(len , CHAR_TYPE);
      strncpy(scrambleSequence, data, len);
      break;
    case 11: // digits for ascii to number conversion
      asciidigit = (char *) allocateMemory(len , CHAR_TYPE);
      strncpy(asciidigit, data, len);
      break;
    case 12: // the list of arithmetic operations
      mathoperations = (char *)allocateMemory(len , CHAR_TYPE);
      strncpy(mathoperations, data, len);
      break;
    case 13: // the base of the new number
      base = (char *)allocateMemory(len , CHAR_TYPE);
      strncpy(base, data, len);
      break;
    case 14:  // the new base character set
      basedigit = (char *) allocateMemory(len , CHAR_TYPE);
      strncpy(basedigit, data , len);
      break;
    case 15:   //the fromat of the registration code
      regformat = (char *) allocateMemory(len , CHAR_TYPE);
      strncpy(regformat, data , len);
      break;
    default:
      break;
    }
}

/**
 Parse the arithmetic operation string and store the math operation
 for each character in an array.
 */
void parseMathOperations()
{
  int count = 0;
  //each math operation is seperated by ,,
  char* pch = strtok(mathoperations, ",,");

  while (pch != NULL)
    {
#ifdef DEBUG
      debugBufferCount = sprintf (debugBuffer, "[%d]=%s\n", count, pch);
      setDebugMessage(debugBufferCount, debugBuffer);
#endif
      //store math operation for this index position.
      operations[count] = pch;
      //get the next math operation
      pch = strtok(NULL, ",,");
      count++;
    }
}
/**
 Parse the scramble order string and store the scramble symbol
 for each character in an array.
 */
void parseScrambleSequence()
{
  int count = 0;
  //each seed symbol is seperated by ''
  char* pch = strtok(scrambleSequence, ",,");
  while (pch != NULL)
    {
#ifdef DEBUG
      debugBufferCount = sprintf (debugBuffer, "[%d]=%s\n", count, pch);
      setDebugMessage(debugBufferCount, debugBuffer);
#endif
      scrambleOrder[count] = pch;
      //get the next seed symbol
      pch = strtok(NULL, ",,");
      count++;
    }
}

/**
  Remove format information and static text from the reg code.
  Also seperate the check digit received with the registration code
  */
void unformat()
{

  char unformattedcode[100];
  int i = 0;
  int formatlength = strlen(regformat);
  int codelength = strlen(registrationcode);
  // Copy these, since we're doing pointer arithmetic and want
  // to free them later --AE 02/05
  char *regFormatCpy = regformat;
  char *regCodeCpy = registrationcode;

  while (*regFormatCpy != '\0')
    {
      //if the regformat charcter is '#' then include the
      //corresponding charcter from the registration code
      if (*regFormatCpy == '#')
        {
          unformattedcode[i] = *regCodeCpy;
          ++i;
        }
      //if the character i s'^' then its the check digit
      else if (*regFormatCpy == '^')
        {
          checkdigit = *regCodeCpy;
        }
      else if (*regFormatCpy == '[' || *regFormatCpy == ']')
        {
          regFormatCpy++;
          continue;
        }
      //go to the next character
      regFormatCpy++;
      if (*regCodeCpy != '\0')
        {
          regCodeCpy++;
        }
      else
        {
          break;
        }
    }
  //handle case where registration code is bigger than the format
  //code.
  if (codelength > formatlength)
    {
      while (*regCodeCpy != '\0')
        {
          unformattedcode[i] = *regCodeCpy;
          regCodeCpy++;
          ++i;
        }
    }
  unformattedcode[i] = '\0';
  regcode = (char *) allocateMemory(i , CHAR_TYPE);
  regcodelength = i;    //this the actual length of the reg code
  strncpy(regcode, unformattedcode , i);   //store the regcode
#ifdef DEBUG
  debugBufferCount = sprintf (debugBuffer, "Unformatted code %s\t and has length %u.\n",
                              regcode, strlen(unformattedcode));
  setDebugMessage(debugBufferCount, debugBuffer);
  debugBufferCount = sprintf (debugBuffer, "The check digit is %c.\n", checkdigit);
  setDebugMessage(debugBufferCount, debugBuffer);
#endif
}

/**
  This method verifies theat the check digit received with the registration code
  matches the one calculated using the unformatted registration code.
  The checkdigit is obtained by alternately multiplying the reg code character
  with weight 1 and 2, starting from the right and weight = 2. Adding them up and
  finding the remainder obtained by dividing the sum with the base.
  */
int verifyCheckDigit()
{

  int i = regcodelength - 1; //account fro start index of 0
  int weight = 2;  //  weight to multiply each charcter with
  int sum = 0;   // hold the addition of the charcter values
  int digitValue ; //value of each character
  int temp;
  int numberBase = atoi(base); //the new base
#ifdef DEBUG
  debugBufferCount = sprintf (debugBuffer, "Verifying the check digit.");
  setDebugMessage(debugBufferCount, debugBuffer);
#endif
  for (;i >= 0 ;i--)
    {
      //start with the  rightmost character
      char c = *(regcode + i);
      //get the value of the digit
      digitValue = getDigitValue(c);
      //multiply the character value by the weight
      // and add it to the result of the previous charcters.
      sum = sum + (weight * digitValue);
      //change the weight for the next character to 1
      if (weight == 2)
        weight = 1;
      else
        weight = 2;
#ifdef DEBUG
      debugBufferCount = sprintf (debugBuffer, "%c\t%d", c, sum);
      setDebugMessage(debugBufferCount, debugBuffer);
#endif
    }
  temp = sum % (numberBase);
#ifdef DEBUG
  debugBufferCount = sprintf (debugBuffer, " \n%d mod %d  = %d\nThe checkdigit is %c",
                              sum, numberBase, temp, (char)getDigit(temp));
  setDebugMessage(debugBufferCount, debugBuffer);
#endif
  // verify the calculated check digit matches
  // the one received wit the registration code
  if (getDigit(temp) == checkdigit)
    return 1;
  else    //checkdigit could not be verified so return false
    return 0;
}

/**This function returns the value for a given base character
 */
int getDigitValue(char c)
{
  int done = 0;
  int digit = 0;
  while (!done)
    {
      //get the character at the position indicated by
      //digit
      char c1 = *(basedigit + digit);
      if (c == c1)
        {
          //if the character at the position indicated by digit
          //matches the character value c, then the digit is the value
          // of the charcter.
          break;
        }
      ++digit;
    }
  return digit;
}
/**
 This function returns the character associated with a given
 number value
 */
char getDigit(int value)
{
  char temp = *(basedigit + value);
  return temp;
}

/**
 This function converts the regcode number to base ten
 */
void convertToBaseTen()
{
  char buffer[1];
  int index = regcodelength - 1;
  int pow, x;
  int resultlength;
  char c;
  int size;
  int temp = 1;
  int* sum = (int *)allocateMemory(1 , INT_TYPE);
  //value of base charcter
  char * digitValue;
  //the weight by which is character is to multiplied
  // to convert to base ten
  int *weight;
  // result of multiplying two digits
  int* result;
  // result of adding value of 1 base character with
  //value of previous base characters

  *sum = 0;
  // weight is allocated by power(), don't need it here --AE 02/05
  // weight =  (int *)allocateMemory(1 , INT_TYPE);
  digitValue = (char *)allocateMemory(3 , CHAR_TYPE);

#ifdef DEBUG
  debugBufferCount = sprintf (debugBuffer, "\nConverting to base ten %s.\n", regcode);
  setDebugMessage(debugBufferCount, debugBuffer);
#endif
  for (pow = 0; pow < regcodelength ; ++pow)
    {
      // Temp holder for sum while it's recalculated --AE 02/05
      int *tempSum;
      //find the weight to multiply each digit with.
      weight = power(base, pow);
      //get the number of digits in the weight
      size = getResultSize();
#ifdef DEBUG
      debugBufferCount = sprintf (debugBuffer, "Weight : ");
      setDebugMessage(debugBufferCount, debugBuffer);
      for (x = 0 ;x < size ;++x)
        {
          debugBufferCount = sprintf (debugBuffer, "%d", *(weight + x));
          setDebugMessage(debugBufferCount, debugBuffer);
        }
#endif

      //get the digit
      c = *(regcode + index);
      //get the digit value
      // itoa(getDigitValue(c), digitValue, 10);
      sprintf(digitValue, "%d", getDigitValue(c));

      // multiply weight by the digit.
#ifdef DEBUG
      debugBufferCount = sprintf (debugBuffer, "* %s\n", digitValue);
      setDebugMessage(debugBufferCount, debugBuffer);
#endif
      result = multiply(weight, size, digitValue);
      resultlength = getResultLength();
#ifdef DEBUG
      debugBufferCount = sprintf (debugBuffer, "Value : ");
      setDebugMessage(debugBufferCount, debugBuffer);
      for (x = 0 ;x < resultlength ;++x)
        {
          debugBufferCount = sprintf (debugBuffer, "%d", *(result + x));
          setDebugMessage(debugBufferCount, debugBuffer);
        }
      debugBufferCount = sprintf (debugBuffer, " \n");
      setDebugMessage(debugBufferCount, debugBuffer);
#endif
      //add the value of this digit position
      tempSum = sum;
      sum = add(sum, temp, result, resultlength);
      free(tempSum);
      temp = getResultLength();

      // Added free()s --AE 02/05
      free(result);
      free(weight);
      --index;
    }
#ifdef DEBUG
  debugBufferCount = sprintf (debugBuffer, "The base ten number is:");
  setDebugMessage(debugBufferCount, debugBuffer);
  for (x = 0 ;x < getResultLength(); ++x)
    {
      debugBufferCount = sprintf (debugBuffer, "%d", *(sum + x));
      setDebugMessage(debugBufferCount, debugBuffer);
    }
  debugBufferCount = sprintf (debugBuffer, "\n");
  setDebugMessage(debugBufferCount, debugBuffer);
#endif
  for (x = 0 ;x < getResultLength(); ++x)
    {

      sprintf(buffer, "%d", *(sum + x));
      //get the ascii character
      baseTenNumber[x] = buffer[0];
    }
  // Free last sum --AE 02/05
  free(sum);
  free(digitValue);
  // Done above --AE 02/05
  //   free(weight);
}

/** This function breaks down the base ten number into groups of 2 or 3
 depending on the the value asciidigits(used for text to number conversion).
 It then undoes the arithmetic operation performed while generatig the registration
 code
 */
void undoarithmetic(const char * baseten)
{

  int ascii ; //number of digit for text to number conversion
  int i = 0;
  int number;
  char two[3]; //store two digit ascii
  char three[4]; // stores 3 digit ascii
  int charposn = 0;
  int digitCount = strlen(baseten);
  ascii = atoi(asciidigit);

#ifdef DEBUG
  debugBufferCount = sprintf (debugBuffer, "Reversing arithmetic operations%s\n",
                              baseten);
  setDebugMessage(debugBufferCount, debugBuffer);
#endif
  while (*(baseten + i) != '\0')
    {
      if (ascii == 2)
        {
          if (i == 0 && digitCount % 2 != 0)
            {
              two[0] = '0';
            }
          else
            {
              //split  the base ten number into group of two digits
              two[0] = *(baseten + i);
              i = i + 1;
            }
          two[1] = *(baseten + i);
          i = i + 1;
          two[2] = '\0';
          //convert ascii to number
          number = atoi(two);
          //undo the arithmetic operation
          number = domath(number, charposn);
          //this gives the seed as an integer
          seedasinteger[charposn] = number;
        }
      else if (ascii == 3)
        {
          if (i == 0 && digitCount % 3 != 0)
            {
              three[0] = '0';
            }
          else
            {
              //split the base ten number into group of three digits
              three[0] = *(baseten + i);
              i = i + 1;
            }
          three[1] = *(baseten + i);
          i = i + 1;
          three[2] = *(baseten + i);
          i = i + 1;
          three[3] = '\0';
          number = atoi(three);
          //undo arithmetic operations
          number = domath(number, charposn);
          //this number represents the seed character
          // as integer value
          seedasinteger[charposn] = number;
        }
      ++charposn;
    }
#ifdef DEBUG
  for (i = 0 ; i < charposn ;++i)
    {
      debugBufferCount = sprintf (debugBuffer, "[%d]=%d\t", i, seedasinteger[i]);
      setDebugMessage(debugBufferCount, debugBuffer);
    }
#endif
}

/**This function performs the oppposite  math operation on
 a number which represents a character in the seed
 */
int domath(int number, int position)
{
  char *operation;
  char* operand;
  char math;
  int x , y, len;
  char * token = NULL;
  int ioperand;
  char temp[3];
  operation = operations[position];
#ifdef DEBUG
  debugBufferCount = sprintf (debugBuffer, "Performing operation (%s) for %d at %d\n",
                              operation, number, position);
  setDebugMessage(debugBufferCount, debugBuffer);
#endif
  len = strlen(operation);
  if (len > 1)
    {
      //find the operation
      math = *(operation + len - 1);
      if (math == 'A')
        token = "A";
      else if (math == 'S')
        token = "S";
      else if (math == 'M')
        token = "M";
      //find the operand
      operand = strtok(operation, token);
      ioperand = atoi(operand);
      //undo the arithmetic operations
      if (math == 'A')
        {

          number = number - ioperand;
        }
      else if (math == 'S')
        {
          number = number + ioperand;
        }
      else if (math == 'M')
        {
          number = number / ioperand;
        }
#ifdef DEBUG
      debugBufferCount = sprintf (debugBuffer, "match %c\t%s\n", math, operand);
      setDebugMessage(debugBufferCount, debugBuffer);
#endif
    }
  else
    {
      // the operation is reverse the number
      sprintf(temp, "%d", number);
      //itoa(number,temp,10);
      for (x = 0, y = strlen(temp) - 1; x < y ;x++, y--)
        {
          math = temp[x];
          temp[x] = temp[y];
          temp[y] = math;
        }
      number = atoi(temp);
      if (number <= 9)
        number = number * 10;
    }
#ifdef DEBUG
  debugBufferCount = sprintf (debugBuffer, "The number is :%d \n", number);
  setDebugMessage(debugBufferCount, debugBuffer);
#endif
  return number;
}

/**This function unscrambles the seed into the user seed, date
   the constant value and sequence
   */

void unScrambleSeed()
{
  int x , charposn;
  char* scrambletoken;
  char symbol;
  char* posn;
  // char * temp;
  for (x = 0 ; x < seedlength ;++x)
    {

      /*seed = (char *)allocateMemory(seedlength, CHAR_TYPE);
      sequence = (char *)allocateMemory(seqlength, CHAR_TYPE);
      constant = (char *)allocateMemory(constlength, CHAR_TYPE);*/
      scrambletoken = scrambleOrder[x];
      symbol = *(scrambletoken);
      posn = scrambletoken + 1;
      charposn = atoi(posn);
#ifdef DEBUG
      debugBufferCount = sprintf (debugBuffer, "\n%c : %s : %d\t: %c\n"
                                  , symbol, posn, seedasinteger[x], seedasinteger[x]);
      setDebugMessage(debugBufferCount, debugBuffer);
#endif

      if (symbol == 'U')
        {
          seed[charposn] = (char)seedasinteger[x];
        }
      else if (symbol == 'S')
        {
          sequence[charposn] = (char)seedasinteger[x];
        }
      else if (symbol == 'D')
        {
          date[charposn] = (char)seedasinteger[x];
        }
      else if (symbol == 'C')
        {
          constant[charposn] = (char)seedasinteger[x];
        }
    }
}

/*This function returns the user seed */

char * getUserSeed()
{
  return seed;
}
/* This function returns the constant value  */
char * getConstant()
{
  return constant;
}

/* This function returns the sequence number */
char * getSequenceNumber()
{
  return sequence;
}

/* This function returns the date the registration code was generated */
char* getDate()
{
  return date;
}

void freememory()
{
  free(seedcombo);
  free(constvalue);
  free(scrambleSequence);
  free(asciidigit);
  free(mathoperations);
  free(base);
  free(basedigit);
  free(regcode);
  free(regformat);
  // Only if we've allocated it --AE 02/05
  if (debugMessage)
    free(debugMessage);
  // These weren't free()d before --AE 02/05
  free(registrationcode);
  free(configuration);
}

/* This method allocates memory depending on data type */
void * allocateMemory(int size, int dataType)
{
  void * ptr = 0;
  if (dataType == CHAR_TYPE)
    {
      ptr = calloc((size + 1), sizeof(char));
    }
  else if (dataType == INT_TYPE)
    {
      ptr = calloc((size + 1), sizeof(int));
    }
  if (ptr == NULL)
    exit (1);
  return ptr;
}

/*This method stores the debug message in a buffer */
void setDebugMessage(int size, const char * msg)
{

  int msgLength;
  if (debugMessage == 0)
    {
      debugMessage = allocateMemory(size, CHAR_TYPE);
      debugMessage = msg;
    }
  else
    {
      msgLength = strlen(debugMessage);
      debugMessage = (char *)realloc(debugMessage ,
                                     (msgLength + size + 1) * sizeof(char));
      strcat(debugMessage , msg);
      free(msg);
    }
}

/** This method returns the debug messages */
char* getDebugMessage()
{
  return debugMessage;
}

/**Set the user name for generating reg code */
void setUserName(const char * name)
{
  int i;
  //reset the data
  for (i = 0 ; i < 20; ++i)
    {
      userName[i] = '\0';
    }
  i = 0;
  while (*name != '\0')
    {
      if (isalnum(*name))
        {
          userName[i] = toupper(*name);
          ++i;
        }
      name++;
    }
#ifdef DEBUG
  debugBufferCount = sprintf (debugBuffer, "User name is:%s", userName);
  setDebugMessage(debugBufferCount, debugBuffer);
#endif
}

/** This method sets the user email */
void setUserEmail(const char * email)
{
  int i;
  //reset the data
  for (i = 0 ; i < 20; ++i)
    {
      userEmail[i] = '\0';
    }
  i = 0;
  while (*email != '\0')
    {
      if (isalnum(*email))
        {
          userEmail[i] = toupper(*email);
          ++i;
        }
      email++;
    }
#ifdef DEBUG
  debugBufferCount = sprintf (debugBuffer, "User email is:%s", userEmail);
  setDebugMessage(debugBufferCount, debugBuffer);
#endif
}

/** This method creates the user seed depending on the seed type
  * and using the user name and/or user email */
void createUserSeed()
{
  int length , charCount, i;
  char* seedbasis;
  int maxSize = strlen(userName) + strlen(userEmail);

  seedbasis = allocateMemory(maxSize, CHAR_TYPE);
  for (i = 0 ; i < 30 ;++i)
    {
      createdUserSeed[i] = '\0';
    }
  if (strncmp(seedcombo , "nn", 2) == 0) //if name only
    {
      strcat(seedbasis, userName);
    }
  else if (strncmp(seedcombo , "en", 2) == 0) //if email + name
    {
      strcat(seedbasis, userEmail);
      strcat(seedbasis, userName);
    }
  else if (strncmp(seedcombo , "ne", 2) == 0) //if name + email
    {
      strcat(seedbasis, userName);
      strcat(seedbasis, userEmail);
    }
  else if (strncmp(seedcombo , "ee", 2) == 0) //if email
    {
      strcat(seedbasis, userEmail);
    }
  else if (strncmp(seedcombo, "hh", 2) == 0)
    {
      strcat(seedbasis, userName);
    }
  if (*seedbasis == 0)
    {
      free(seedbasis);
      return;
    }
  strncat(createdUserSeed, seedbasis, userseedlength);
  length = strlen(createdUserSeed);
  while (length < userseedlength)
    {
      charCount = userseedlength - length;
      strncat(createdUserSeed, seedbasis, charCount);
      length = strlen(createdUserSeed);
    }

#ifdef DEBUG
  debugBufferCount = sprintf (debugBuffer, "UserSeed: %s(%d) ",
                              createdUserSeed, strlen(createdUserSeed));
  setDebugMessage(debugBufferCount, debugBuffer);
#endif
  // Need to free local variable --AE 02/05
  free(seedbasis);
}

/** This method returns the user seed generated using the
  * user seed name and email
  */
char* getCreatedUserSeed()
{
  return createdUserSeed;
}
