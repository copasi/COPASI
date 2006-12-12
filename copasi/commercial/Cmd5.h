/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/commercial/Attic/Cmd5.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/12/12 21:22:08 $
   End CVS Header */

// Copyright © 2006 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

// MD5.CC - source code for the C++/object oriented translation and
//          modification of MD5.

// Translation and modification (c) 1995 by Mordechai T. Abzug

// This translation/ modification is provided "as is," without express or
// implied warranty of any kind.

// The translator/ modifier does not claim (1) that MD5 will do what you think
// it does; (2) that this translation/ modification is accurate; or (3) that
// this software is "merchantible."  (Language for this disclaimer partially
// copied from the disclaimer below).

/* based on:

   MD5.H - header file for MD5C.C
   MDDRIVER.C - test driver for MD2, MD4 and MD5

   Copyright (C) 1991-2, RSA Data Security, Inc. Created 1991. All
rights reserved.

License to copy and use this software is granted provided that it
is identified as the "RSA Data Security, Inc. MD5 Message-Digest
Algorithm" in all material mentioning or referencing this software
or this function.

License is also granted to make and use derivative works provided
that such works are identified as "derived from the RSA Data
Security, Inc. MD5 Message-Digest Algorithm" in all material
mentioning or referencing the derived work.

RSA Data Security, Inc. makes no representations concerning either
the merchantability of this software or the suitability of this
software for any particular purpose. It is provided "as is"
without express or implied warranty of any kind.

These notices must be retained in any copies of any part of this
documentation and/or software.

 */

#ifndef COPASI_Cmd5
#define COPASI_Cmd5

#include <iostream>

class Cmd5
  {
  public:
    // Operations
    // methods to acquire finalized result
    static std::string digest(std::istream & message);  // digest as a 33-byte ascii-hex string

  private:
    // methods for controlled operation:
    Cmd5(std::istream & message);      // digest stream, close, finalize

    void update(std::istream & stream);
    void update(unsigned char *input,
                unsigned C_INT32 input_length);
    void finalize();

    // last, the private methods, mostly static:
    void init();               // called by all constructors
    void transform(unsigned char *buffer);  // does the real update work.  Note
    // that length is implied to be 64.

    static void encode(unsigned char *dest,
                       unsigned C_INT32 *src,
                       unsigned C_INT32 length);
    static void decode(unsigned C_INT32 *dest,
                       unsigned char *src,
                       unsigned C_INT32 length);

    static inline unsigned C_INT32 rotate_left(unsigned C_INT32 x,
        unsigned C_INT32 n);

    static inline unsigned C_INT32 F(unsigned C_INT32 x,
                                     unsigned C_INT32 y,
                                     unsigned C_INT32 z);
    static inline unsigned C_INT32 G(unsigned C_INT32 x,
                                     unsigned C_INT32 y,
                                     unsigned C_INT32 z);
    static inline unsigned C_INT32 H(unsigned C_INT32 x,
                                     unsigned C_INT32 y,
                                     unsigned C_INT32 z);
    static inline unsigned C_INT32 I(unsigned C_INT32 x,
                                     unsigned C_INT32 y,
                                     unsigned C_INT32 z);

    static inline void FF(unsigned C_INT32& a,
                          unsigned C_INT32 b,
                          unsigned C_INT32 c,
                          unsigned C_INT32 d,
                          unsigned C_INT32 x,
                          unsigned C_INT32 s,
                          unsigned C_INT32 ac);
    static inline void GG(unsigned C_INT32& a,
                          unsigned C_INT32 b,
                          unsigned C_INT32 c,
                          unsigned C_INT32 d,
                          unsigned C_INT32 x,
                          unsigned C_INT32 s,
                          unsigned C_INT32 ac);
    static inline void HH(unsigned C_INT32& a,
                          unsigned C_INT32 b,
                          unsigned C_INT32 c,
                          unsigned C_INT32 d,
                          unsigned C_INT32 x,
                          unsigned C_INT32 s,
                          unsigned C_INT32 ac);
    static inline void II(unsigned C_INT32& a,
                          unsigned C_INT32 b,
                          unsigned C_INT32 c,
                          unsigned C_INT32 d,
                          unsigned C_INT32 x,
                          unsigned C_INT32 s,
                          unsigned C_INT32 ac);

  private:
    // Attributes
    typedef unsigned short int uint2; // assumes short integer is 2 words long

    // next, the private data:
    unsigned C_INT32 mState[4];
    unsigned C_INT32 mCount[2];     // number of *bits*, mod 2^64
    unsigned char mBuffer[64];   // input buffer
    unsigned char mDigest[16];
    bool mFinalized;
  };

#endif // COPASI_Cmd5
