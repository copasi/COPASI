/* Begin CVS Header
  $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/utility.cpp,v $
  $Revision: 1.27.24.1 $
  $Name:  $
  $Author: shoops $
  $Date: 2008/10/21 20:30:53 $
  End CVS Header */

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "mathematics.h"
#include <stdio.h>
#include <time.h>

#ifdef WIN32
# include <windows.h>
#endif // WIN32

#if (defined SunOS || defined Linux)
# include <errno.h>
# include <iconv.h>
# include <langinfo.h>
#endif // SunOS || Linux

#include "copasi.h"

#include "utility.h"

std::string ISODateTime(tm * pTime)
{
  char str[20];

  if (pTime)
    {
      sprintf(str, "%d-%.02d-%.02d %.02d:%.02d:%.02d",
              pTime->tm_year + 1900,
              pTime->tm_mon + 1,
              pTime->tm_mday,
              pTime->tm_hour,
              pTime->tm_min,
              pTime->tm_sec);
    }
  else
    {
      sprintf(str, "0000-00-00 00:00:00");
    }

  return (std::string) str;
}

std::string LocalTimeStamp()
{
  time_t Time;
  time(&Time);

  tm *sTime = NULL;
  sTime = localtime(&Time);

  return ISODateTime(sTime);
}

std::string UTCTimeStamp()
{
  time_t Time;
  time(&Time);

  tm *sTime = NULL;
  sTime = gmtime(&Time);

  return ISODateTime(sTime);
}

bool isNumber(const std::string & str)
{
  if (str.find_first_of("+-.0123456789")) return false;

  char * Tail;
  strtod(str.c_str(), & Tail);

  if (*Tail) return false;
  return true;
}

std::string StringPrint(const char * format, ...)
{
  C_INT32 TextSize = INITIALTEXTSIZE;
  C_INT32 Printed = 0;

  char *Text = NULL;

  Text = new char[TextSize + 1];

  va_list Arguments; // = NULL;
  va_start(Arguments, format);
  Printed = vsnprintf(Text, TextSize + 1, format, Arguments);
  va_end(Arguments);

  while (Printed < 0 || TextSize < Printed)
    {
      delete [] Text;

      (Printed < 0) ? TextSize *= 2 : TextSize = Printed;
      Text = new char[TextSize + 1];

      va_list Arguments; // = NULL;
      va_start(Arguments, format);
      Printed = vsnprintf(Text, TextSize + 1, format, Arguments);
      va_end(Arguments);
    }

  std::string Result = Text;

  delete [] Text;
  return Result;
}

std::string unQuote(const std::string & name)
{
  std::string Name = name;
  std::string::size_type len = Name.length();

  if (len > 1 && Name[0] == '"' && Name[len - 1] == '"')
    {
      // Remove surrounding double quotes.
      Name = Name.substr(1, len - 2);

      // Remove escape seqences.
      std::string::size_type pos = Name.find("\\");

      while (pos != std::string::npos)
        {
          Name.erase(pos, 1);
          pos++;
          pos = Name.find("\\", pos);
        }
    }

  return Name;
}

std::string quote(const std::string & name,
                  const std::string & additionalEscapes)
{
  if (name.find_first_of(" \"" + additionalEscapes) == std::string::npos)
    return name;

#define toBeEscaped "\\\""
  std::string Escaped(name);
  std::string::size_type pos = Escaped.find_first_of(toBeEscaped);

  while (pos != std::string::npos)
    {
      Escaped.insert(pos, "\\");
      pos += 2;
      pos = Escaped.find_first_of(toBeEscaped, pos);
    }

  return "\"" + Escaped + "\"";
#undef toBeEscaped
}

/*
 * Fixes a string to be a SName element from SBML
 * (this is a destructive function, some changes are irreversible)
 *
 */

void FixSName(const std::string &original, std::string &fixed)
{
  int i, len;
  // check reserved names
  if (original == "abs") {fixed = "_abs"; return;}
  if (original == "acos") {fixed = "_acos"; return;}
  if (original == "and") {fixed = "_and"; return;}
  if (original == "asin") {fixed = "_asin"; return;}
  if (original == "atan") {fixed = "_atan"; return;}
  if (original == "ceil") {fixed = "_ceil"; return;}
  if (original == "cos") {fixed = "_cos"; return;}
  if (original == "exp") {fixed = "_exp"; return;}
  if (original == "floor") {fixed = "_floor"; return;}
  if (original == "hilli") {fixed = "_hilli"; return;}
  if (original == "hillmmr") {fixed = "_hillmmr"; return;}
  if (original == "hillmr") {fixed = "_hillmr"; return;}
  if (original == "hillr") {fixed = "_hillr"; return;}
  if (original == "isouur") {fixed = "_isouur"; return;}
  if (original == "log") {fixed = "_log"; return;}
  if (original == "log10") {fixed = "_log10"; return;}
  if (original == "massi") {fixed = "_massi"; return;}
  if (original == "massr") {fixed = "_massr"; return;}
  if (original == "not") {fixed = "_not"; return;}
  if (original == "or") {fixed = "_or"; return;}
  if (original == "ordbbr") {fixed = "_ordbbr"; return;}
  if (original == "ordbur") {fixed = "_ordbur"; return;}
  if (original == "ordubr") {fixed = "_ordubr"; return;}
  if (original == "pow") {fixed = "_pow"; return;}
  if (original == "ppbr") {fixed = "_ppbr"; return;}
  if (original == "sin") {fixed = "_sin"; return;}
  if (original == "sqr") {fixed = "_sqr"; return;}
  if (original == "sqrt") {fixed = "_sqrt"; return;}
  if (original == "substance") {fixed = "_substance"; return;}
  if (original == "time") {fixed = "_time"; return;}
  if (original == "tan") {fixed = "_tan"; return;}
  if (original == "umai") {fixed = "_umai"; return;}
  if (original == "umar") {fixed = "_umar"; return;}
  if (original == "uai") {fixed = "_uai"; return;}
  if (original == "ualii") {fixed = "_ualii"; return;}
  if (original == "uar") {fixed = "_uar"; return;}
  if (original == "ucii") {fixed = "_ucii"; return;}
  if (original == "ucir") {fixed = "_ucir"; return;}
  if (original == "ucti") {fixed = "_ucti"; return;}
  if (original == "uctr") {fixed = "_uctr"; return;}
  if (original == "uhmi") {fixed = "_uhmi"; return;}
  if (original == "uhmr") {fixed = "_uhmr"; return;}
  if (original == "umi") {fixed = "_umi"; return;}
  if (original == "unii") {fixed = "_unii"; return;}
  if (original == "unir") {fixed = "_unir"; return;}
  if (original == "uuhr") {fixed = "_uuhr"; return;}
  if (original == "umr") {fixed = "_umr"; return;}
  if (original == "usii") {fixed = "_usii"; return;}
  if (original == "usir") {fixed = "_usir"; return;}
  if (original == "uuci") {fixed = "_uuci"; return;}
  if (original == "uucr") {fixed = "_uucr"; return;}
  if (original == "uui") {fixed = "_uui"; return;}
  if (original == "uur") {fixed = "_uur"; return;}
  if (original == "volume") {fixed = "_volume"; return;}
  if (original == "xor") {fixed = "_xor"; return;}
  len = original.length();
  // check rule for initial characters
  // if first not a letter...
  if (((original[0] < 'A') || (original[0] > 'z')) && (original[0] != '_'))
    {
      if ((original[0] >= '0') && (original[0] <= '9'))
        fixed = "_" + original;
      else
      {fixed = original; fixed [0] = '_';}
    }
  else
    fixed = original;
  len = fixed.length();

  for (i = 1; i < len; i++)
    if ((fixed [i] != '_') && ((fixed [i] < 'A') || (fixed [i] > 'z')) &&
        ((fixed [i] < '0') || (fixed [i] > '9')))
      fixed [i] = '_';
}

/*
 * Fixes a string to a XHTML valid equivalent
 */
void FixXHTML(const std::string &original, std::string &fixed)
{
  C_INT32 i, p, len;
  std::string Str;
  // find the next illegal character
  Str = original;
  fixed.erase();
  for (i = 0; i != -1;)
    {
      p = Str.find_first_of("&><\"¡¢£¤¥¦§¨©ª«¬­®¯°±²³´µ¶·¸¹º»¼½¾¿ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØÙÚÛÜÝÞßàáâãäåæçèéêëìíîïðñòóôõö÷øùúûüýþÿ");
      fixed += Str.substr(0, p)
;
      len = Str.length();
      i = Str.find_first_of("&><\"¡¢£¤¥¦§¨©ª«¬­®¯°±²³´µ¶·¸¹º»¼½¾¿ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØÙÚÛÜÝÞßàáâãäåæçèéêëìíîïðñòóôõö÷øùúûüýþÿ");
      if (i != -1)
        {
          switch (Str[i])
            {
            case '&':
              fixed += "&amp; ";
              break;
            case '>':
              fixed += "&gt; ";
              break;
            case '<':
              fixed += "&lt; ";
              break;
            case '"':
              fixed += "&quot; ";
              break;
            case '¡':
              fixed += "&#161; ";
              break;
            case '¢':
              fixed += "&#162; ";
              break;
            case '£':
              fixed += "&#163; ";
              break;
            case '¤':
              fixed += "&#164; ";
              break;
            case '¥':
              fixed += "&#165; ";
              break;
            case '¦':
              fixed += "&#166; ";
              break;
            case '§':
              fixed += "&#167; ";
              break;
            case '¨':
              fixed += "&#168; ";
              break;
            case '©':
              fixed += "&#169; ";
              break;
            case 'ª':
              fixed += "&#170; ";
              break;
            case '«':
              fixed += "&#171; ";
              break;
            case '¬':
              fixed += "&#172; ";
              break;
            case '­':
              fixed += "&#173; ";
              break;
            case '®':
              fixed += "&#174; ";
              break;
            case '¯':
              fixed += "&#175; ";
              break;
            case '°':
              fixed += "&#176; ";
              break;
            case '±':
              fixed += "&#177; ";
              break;
            case '²':
              fixed += "&#178; ";
              break;
            case '³':
              fixed += "&#179; ";
              break;
            case '´':
              fixed += "&#180; ";
              break;
            case 'µ':
              fixed += "&#181; ";
              break;
            case '¶':
              fixed += "&#182; ";
              break;
            case '·':
              fixed += "&#183; ";
              break;
            case '¸':
              fixed += "&#184; ";
              break;
            case '¹':
              fixed += "&#185; ";
              break;
            case 'º':
              fixed += "&#186; ";
              break;
            case '»':
              fixed += "&#187; ";
              break;
            case '¼':
              fixed += "&#188; ";
              break;
            case '½':
              fixed += "&#189; ";
              break;
            case '¾':
              fixed += "&#190; ";
              break;
            case '¿':
              fixed += "&#191; ";
              break;
            case 'À':
              fixed += "&#192; ";
              break;
            case 'Á':
              fixed += "&#193; ";
              break;
            case 'Â':
              fixed += "&#194; ";
              break;
            case 'Ã':
              fixed += "&#195; ";
              break;
            case 'Ä':
              fixed += "&#196; ";
              break;
            case 'Å':
              fixed += "&#197; ";
              break;
            case 'Æ':
              fixed += "&#198; ";
              break;
            case 'Ç':
              fixed += "&#199; ";
              break;
            case 'È':
              fixed += "&#200; ";
              break;
            case 'É':
              fixed += "&#201; ";
              break;
            case 'Ê':
              fixed += "&#202; ";
              break;
            case 'Ë':
              fixed += "&#203; ";
              break;
            case 'Ì':
              fixed += "&#204; ";
              break;
            case 'Í':
              fixed += "&#205; ";
              break;
            case 'Î':
              fixed += "&#206; ";
              break;
            case 'Ï':
              fixed += "&#207; ";
              break;
            case 'Ð':
              fixed += "&#208; ";
              break;
            case 'Ñ':
              fixed += "&#209; ";
              break;
            case 'Ò':
              fixed += "&#210; ";
              break;
            case 'Ó':
              fixed += "&#211; ";
              break;
            case 'Ô':
              fixed += "&#212; ";
              break;
            case 'Õ':
              fixed += "&#213; ";
              break;
            case 'Ö':
              fixed += "&#214; ";
              break;
            case '×':
              fixed += "&#215; ";
              break;
            case 'Ø':
              fixed += "&#216; ";
              break;
            case 'Ù':
              fixed += "&#217; ";
              break;
            case 'Ú':
              fixed += "&#218; ";
              break;
            case 'Û':
              fixed += "&#219; ";
              break;
            case 'Ü':
              fixed += "&#220; ";
              break;
            case 'Ý':
              fixed += "&#221; ";
              break;
            case 'Þ':
              fixed += "&#222; ";
              break;
            case 'ß':
              fixed += "&#223; ";
              break;
            case 'à':
              fixed += "&#224; ";
              break;
            case 'á':
              fixed += "&#225; ";
              break;
            case 'â':
              fixed += "&#226; ";
              break;
            case 'ã':
              fixed += "&#227; ";
              break;
            case 'ä':
              fixed += "&#228; ";
              break;
            case 'å':
              fixed += "&#229; ";
              break;
            case 'æ':
              fixed += "&#230; ";
              break;
            case 'ç':
              fixed += "&#231; ";
              break;
            case 'è':
              fixed += "&#232; ";
              break;
            case 'é':
              fixed += "&#233; ";
              break;
            case 'ê':
              fixed += "&#234; ";
              break;
            case 'ë':
              fixed += "&#235; ";
              break;
            case 'ì':
              fixed += "&#236; ";
              break;
            case 'í':
              fixed += "&#237; ";
              break;
            case 'î':
              fixed += "&#238; ";
              break;
            case 'ï':
              fixed += "&#239; ";
              break;
            case 'ð':
              fixed += "&#240; ";
              break;
            case 'ñ':
              fixed += "&#241; ";
              break;
            case 'ò':
              fixed += "&#242; ";
              break;
            case 'ó':
              fixed += "&#243; ";
              break;
            case 'ô':
              fixed += "&#244; ";
              break;
            case 'õ':
              fixed += "&#245; ";
              break;
            case 'ö':
              fixed += "&#246; ";
              break;
            case '÷':
              fixed += "&#247; ";
              break;
            case 'ø':
              fixed += "&#248; ";
              break;
            case 'ù':
              fixed += "&#249; ";
              break;
            case 'ú':
              fixed += "&#250; ";
              break;
            case 'û':
              fixed += "&#251; ";
              break;
            case 'ü':
              fixed += "&#252; ";
              break;
            case 'ý':
              fixed += "&#253; ";
              break;
            case 'þ':
              fixed += "&#254; ";
              break;
            case 'ÿ':
              fixed += "&#255; ";
              break;
            }
        }
      Str = Str.substr(len - i - 1);
    }
}

int toEnum(const char * attribute,
           const char ** enumNames)
{
  if (!attribute) return - 1;

  for (int i = 0; *enumNames; i++, enumNames++)
    if (!strcmp(attribute, *enumNames)) return i;

  return - 1;
}

#if (defined SunOS || defined Linux)
const char * findLocale()
{
  static char * Locale = NULL;

  if (Locale == NULL)
    Locale = strdup(nl_langinfo(CODESET));

#ifdef SunOS
  if (strcmp(Locale, "646") == 0)
    pfree(Locale);

  if (Locale == NULL)
    Locale = strdup("8859-1");
#else
  if (Locale == NULL)
    Locale = strdup("ISO-8859-1");
#endif

  return Locale;
}
#endif // SunOS || Linux

std::string utf8ToLocale(const std::string & utf8)
{
#ifdef WIN32
  C_INT32 size;

  size = MultiByteToWideChar(CP_UTF8, // code page
                             MB_ERR_INVALID_CHARS, // character-type options
                             utf8.c_str(), // address of string to map
                             -1, // NULL terminated
                             NULL, // address of wide-character buffer
                             0) + 1;               // size of buffer

  WCHAR * pWideChar = new WCHAR[size];

  MultiByteToWideChar(CP_UTF8, // code page
                      MB_ERR_INVALID_CHARS, // character-type options
                      utf8.c_str(), // address of string to map
                      -1, // NULL terminated
                      pWideChar, // address of wide-character buffer
                      size);                // size of buffer

  int UsedDefaultChar = 0;

  size = WideCharToMultiByte(CP_THREAD_ACP, // code page
                             WC_COMPOSITECHECK |
                             WC_DEFAULTCHAR, // performance and mapping flags
                             pWideChar, // address of wide-character string
                             -1, // NULL terminated
                             NULL, // address of buffer for new string
                             0, // size of buffer
                             "?", // address of default for unmappable characters
                             & UsedDefaultChar) + 1; // address of flag set when default char used

  char * pLocal = new char[size];

  WideCharToMultiByte(CP_THREAD_ACP, // code page
                      WC_COMPOSITECHECK |
                      WC_DEFAULTCHAR, // performance and mapping flags
                      pWideChar, // address of wide-character string
                      -1, // NULL terminated
                      pLocal, // address of buffer for new string
                      size, // size of buffer
                      "?", // address of default for unmappable characters
                      & UsedDefaultChar);     // address of flag set when default char used

  std::string Local = pLocal;

  delete [] pWideChar;
  delete [] pLocal;

  return Local;
#endif // WIN32

#if (defined SunOS || defined Linux)
  static iconv_t Converter = NULL;

  if (Converter == NULL)
    {
      char From[] = "UTF-8";
      const char * To = findLocale();

      Converter = iconv_open(To, From);
    }

  if (Converter == (iconv_t)(-1))
    return utf8;

  size_t Utf8Length = utf8.length();
  char * Utf8 = strdup(utf8.c_str());
#ifdef SunOS // non standard iconv declaration :(
  const char * pUtf8 = Utf8;
#else
  char * pUtf8 = Utf8;
#endif

  size_t LocaleLength = Utf8Length + 1;
  size_t SpaceLeft = Utf8Length;
  char * Locale = new char[LocaleLength];
  char * pLocale = Locale;

  while (Utf8Length)
    if ((size_t)(-1) ==
        iconv(Converter, &pUtf8, &Utf8Length, &pLocale, &SpaceLeft))
      {
        switch (errno)
          {
          case EILSEQ:
            pUtf8 = Utf8;
            LocaleLength = 0;
            break;

          case EINVAL:
            pLocale = Locale;
            Utf8Length = 0;
            break;

          case E2BIG:
            char * pTmp = Locale;
            size_t OldLength = LocaleLength;
            LocaleLength += 2 * Utf8Length;

            Locale = new char[LocaleLength];
            memcpy(Locale, pTmp,
                   sizeof(char) * (OldLength - SpaceLeft - 1));
            pLocale = Locale + OldLength - SpaceLeft - 1;
            SpaceLeft += 2 * Utf8Length;
            delete [] pTmp;

            break;
          }

        continue;
      }

  *pLocale = 0x00; // NULL terminate the string.
  std::string Result = Locale;

  // Reset the Converter
  iconv(Converter, NULL, &Utf8Length, NULL, &LocaleLength);

  // Release memory
  free(Utf8);
  delete [] Locale;

  return Result;
#endif // SunOS || Linux

  return utf8;
}

std::string localeToUtf8(const std::string & locale)
{
#ifdef WIN32
  C_INT32 size;

  size = MultiByteToWideChar(CP_THREAD_ACP, // code page
                             MB_ERR_INVALID_CHARS, // character-type options
                             locale.c_str(), // address of string to map
                             -1, // NULL terminated
                             NULL, // address of wide-character buffer
                             0) + 1;               // size of buffer

  WCHAR * pWideChar = new WCHAR[size];

  MultiByteToWideChar(CP_THREAD_ACP, // code page
                      MB_ERR_INVALID_CHARS, // character-type options
                      locale.c_str(), // address of string to map
                      -1, // NULL terminated
                      pWideChar, // address of wide-character buffer
                      size);                // size of buffer

  int UsedDefaultChar = 0;

  size = WideCharToMultiByte(CP_UTF8, // code page
                             0, // performance and mapping flags
                             pWideChar, // address of wide-character string
                             -1, // NULL terminated
                             NULL, // address of buffer for new string
                             0, // size of buffer
                             NULL, // address of default for unmappable characters
                             NULL) + 1; // address of flag set when default char used

  char * pUtf8 = new char[size];

  WideCharToMultiByte(CP_UTF8, // code page
                      0, // address of wide-character string
                      pWideChar, // address of wide-character string
                      -1, // NULL terminated
                      pUtf8, // address of buffer for new string
                      size, // size of buffer
                      NULL, // address of default for unmappable characters
                      NULL);     // address of flag set when default char used

  std::string Utf8 = pUtf8;

  delete [] pWideChar;
  delete [] pUtf8;

  return Utf8;
#endif // WIN32

#if (defined SunOS || defined Linux)
  static iconv_t Converter = NULL;

  if (Converter == NULL)
    {
      char To[] = "UTF-8";
      const char * From = findLocale();

      Converter = iconv_open(To, From);
    }

  if (Converter == (iconv_t)(-1))
    return locale;

  size_t LocaleLength = locale.length();
  char * Locale = strdup(locale.c_str());
#ifdef SunOS // non standard iconv declaration :(
  const char * pLocale = Locale;
#else
  char * pLocale = Locale;
#endif

  size_t Utf8Length = LocaleLength + 1;
  size_t SpaceLeft = LocaleLength;
  char * Utf8 = new char[Utf8Length];
  char * pUtf8 = Utf8;

  while (LocaleLength)
    if ((size_t)(-1) ==
        iconv(Converter, &pLocale, &LocaleLength, &pUtf8, &SpaceLeft))
      {
        switch (errno)
          {
          case EILSEQ:
            pUtf8 = Utf8;
            LocaleLength = 0;
            break;

          case EINVAL:
            pUtf8 = Utf8;
            LocaleLength = 0;
            break;

          case E2BIG:
            char * pTmp = Utf8;
            size_t OldLength = Utf8Length;
            Utf8Length += 2 * LocaleLength;

            Utf8 = new char[Utf8Length];
            memcpy(Utf8, pTmp,
                   sizeof(char) * (OldLength - SpaceLeft - 1));
            pUtf8 = Utf8 + OldLength - SpaceLeft - 1;
            SpaceLeft += 2 * LocaleLength;
            delete [] pTmp;

            break;
          }

        continue;
      }

  *pUtf8 = 0x00; // NULL terminate the string.
  std::string Result = Utf8;

  // Reset the Converter
  iconv(Converter, NULL, &LocaleLength, NULL, &Utf8Length);

  // Release memory
  free(Locale);
  delete [] Utf8;

  return Result;
#endif // SunOS || Linux

  return locale;
}
