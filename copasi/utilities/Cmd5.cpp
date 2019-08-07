// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

/* based on:

MD5C.C - RSA Data Security, Inc., MD5 message-digest algorithm
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

#include <string.h>

#include "copasi/copasi.h"

#include "Cmd5.h"

// Cmd5 block update operation. Continues an Cmd5 message-digest
// operation, processing another message block, and updating the
// context.
void Cmd5::update(unsigned char *input,
                  unsigned C_INT32 input_length)
{
  unsigned C_INT32 input_index, buffer_index;
  unsigned C_INT32 buffer_space;      // how much space is left in buffer

  if (mFinalized)
    {
      // so we can't update!
      std::cerr << "Cmd5::update:  Can't update a finalized digest!" << std::endl;
      return;
    }

  // Compute number of bytes mod 64
  buffer_index = (unsigned int)((mCount[0] >> 3) & 0x3F);

  // Update number of bits
  if ((mCount[0] += ((unsigned C_INT32) input_length << 3)) < ((unsigned C_INT32) input_length << 3))
    mCount[1]++;

  mCount[1] += ((unsigned C_INT32) input_length >> 29);

  buffer_space = 64 - buffer_index;  // how much space is left in buffer

  // Transform as many times as possible.
  if (input_length >= buffer_space)
    {
      // ie. we have enough to fill the buffer
      // fill the rest of the buffer and transform
      memcpy(mBuffer + buffer_index, input, buffer_space);
      transform(mBuffer);

      // now, transform each 64-byte piece of the input, bypassing the buffer
      for (input_index = buffer_space; input_index + 63 < input_length;
           input_index += 64)
        transform(input + input_index);

      buffer_index = 0;  // so we can buffer remaining
    }
  else
    input_index = 0;   // so we can buffer the whole input

  // and here we do the buffering:
  memcpy(mBuffer + buffer_index,
         input + input_index,
         input_length - input_index);
}

// Cmd5 update for istreams.
// Like update for files; see above.
void Cmd5::update(std::istream & stream)
{
  unsigned char buffer[1024];
  int len;

  while (stream.good())
    {
      stream.read((char *) buffer, 1024); // note that return value of read is unusable.
      len = stream.gcount();
      update(buffer, len);
    }
}

// Cmd5 finalization. Ends an Cmd5 message-digest operation, writing the
// the message digest and zeroizing the context.
void Cmd5::finalize()
{
  unsigned char bits[8];
  unsigned C_INT32 index, padLen;
  static unsigned char PADDING[64] =
  {
    0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  };

  if (mFinalized)
    {
      std::cerr << "Cmd5::finalize:  Already finalized this digest!" << std::endl;
      return;
    }

  // Save number of bits
  encode(bits, mCount, 8);

  // Pad out to 56 mod 64.
  index = (unsigned C_INT32)((mCount[0] >> 3) & 0x3f);
  padLen = (index < 56) ? (56 - index) : (120 - index);
  update(PADDING, padLen);

  // Append length (before padding)
  update(bits, 8);

  // Store state in digest
  encode(mDigest, mState, 16);

  // Zeroize sensitive information
  memset(mBuffer, 0, sizeof(*mBuffer));

  mFinalized = true;
}

Cmd5::Cmd5(std::istream & stream)
{
  init();  // must called by all constructors
  update(stream);
  finalize();
}

std::string Cmd5::digest(std::istream & message)  // digest as a 33-byte ascii-hex string
{
  Cmd5 Digest(message);

  int i;
  char str[33];
  str[32] = '\0';

  if (!Digest.mFinalized)
    {
      std::cerr << "Cmd5::hex_digest:  Can't get digest if you haven't " <<
                "finalized the digest!" << std::endl;
      return "";
    }

  char * pStr = str;

  for (i = 0; i < 16; i++, pStr += 2)
    sprintf(pStr, "%02x", Digest.mDigest[i]);

  return str;
}

void Cmd5::init()
{
  mFinalized = false;  // we just started!

  // Nothing counted, so count=0
  mCount[0] = 0;
  mCount[1] = 0;

  // Load magic initialization constants.
  mState[0] = 0x67452301;
  mState[1] = 0xefcdab89;
  mState[2] = 0x98badcfe;
  mState[3] = 0x10325476;
}

// Constants for Cmd5Transform routine.
// Although we could use C++ style constants, defines are actually better,
// since they let us easily evade scope clashes.

#define S11 7
#define S12 12
#define S13 17
#define S14 22
#define S21 5
#define S22 9
#define S23 14
#define S24 20
#define S31 4
#define S32 11
#define S33 16
#define S34 23
#define S41 6
#define S42 10
#define S43 15
#define S44 21

// Cmd5 basic transformation. Transforms state based on block.
void Cmd5::transform(unsigned char block[64])
{

  unsigned C_INT32 a = mState[0];
  unsigned C_INT32 b = mState[1];
  unsigned C_INT32 c = mState[2];
  unsigned C_INT32 d = mState[3];
  unsigned C_INT32 x[16];

  decode(x, block, 64);

  assert(!mFinalized);  // not just a user error, since the method is private

  /* Round 1 */
  FF(a, b, c, d, x[ 0], S11, 0xd76aa478); /* 1 */
  FF(d, a, b, c, x[ 1], S12, 0xe8c7b756); /* 2 */
  FF(c, d, a, b, x[ 2], S13, 0x242070db); /* 3 */
  FF(b, c, d, a, x[ 3], S14, 0xc1bdceee); /* 4 */
  FF(a, b, c, d, x[ 4], S11, 0xf57c0faf); /* 5 */
  FF(d, a, b, c, x[ 5], S12, 0x4787c62a); /* 6 */
  FF(c, d, a, b, x[ 6], S13, 0xa8304613); /* 7 */
  FF(b, c, d, a, x[ 7], S14, 0xfd469501); /* 8 */
  FF(a, b, c, d, x[ 8], S11, 0x698098d8); /* 9 */
  FF(d, a, b, c, x[ 9], S12, 0x8b44f7af); /* 10 */
  FF(c, d, a, b, x[10], S13, 0xffff5bb1); /* 11 */
  FF(b, c, d, a, x[11], S14, 0x895cd7be); /* 12 */
  FF(a, b, c, d, x[12], S11, 0x6b901122); /* 13 */
  FF(d, a, b, c, x[13], S12, 0xfd987193); /* 14 */
  FF(c, d, a, b, x[14], S13, 0xa679438e); /* 15 */
  FF(b, c, d, a, x[15], S14, 0x49b40821); /* 16 */

  /* Round 2 */
  GG(a, b, c, d, x[ 1], S21, 0xf61e2562); /* 17 */
  GG(d, a, b, c, x[ 6], S22, 0xc040b340); /* 18 */
  GG(c, d, a, b, x[11], S23, 0x265e5a51); /* 19 */
  GG(b, c, d, a, x[ 0], S24, 0xe9b6c7aa); /* 20 */
  GG(a, b, c, d, x[ 5], S21, 0xd62f105d); /* 21 */
  GG(d, a, b, c, x[10], S22, 0x2441453); /* 22 */
  GG(c, d, a, b, x[15], S23, 0xd8a1e681); /* 23 */
  GG(b, c, d, a, x[ 4], S24, 0xe7d3fbc8); /* 24 */
  GG(a, b, c, d, x[ 9], S21, 0x21e1cde6); /* 25 */
  GG(d, a, b, c, x[14], S22, 0xc33707d6); /* 26 */
  GG(c, d, a, b, x[ 3], S23, 0xf4d50d87); /* 27 */
  GG(b, c, d, a, x[ 8], S24, 0x455a14ed); /* 28 */
  GG(a, b, c, d, x[13], S21, 0xa9e3e905); /* 29 */
  GG(d, a, b, c, x[ 2], S22, 0xfcefa3f8); /* 30 */
  GG(c, d, a, b, x[ 7], S23, 0x676f02d9); /* 31 */
  GG(b, c, d, a, x[12], S24, 0x8d2a4c8a); /* 32 */

  /* Round 3 */
  HH(a, b, c, d, x[ 5], S31, 0xfffa3942); /* 33 */
  HH(d, a, b, c, x[ 8], S32, 0x8771f681); /* 34 */
  HH(c, d, a, b, x[11], S33, 0x6d9d6122); /* 35 */
  HH(b, c, d, a, x[14], S34, 0xfde5380c); /* 36 */
  HH(a, b, c, d, x[ 1], S31, 0xa4beea44); /* 37 */
  HH(d, a, b, c, x[ 4], S32, 0x4bdecfa9); /* 38 */
  HH(c, d, a, b, x[ 7], S33, 0xf6bb4b60); /* 39 */
  HH(b, c, d, a, x[10], S34, 0xbebfbc70); /* 40 */
  HH(a, b, c, d, x[13], S31, 0x289b7ec6); /* 41 */
  HH(d, a, b, c, x[ 0], S32, 0xeaa127fa); /* 42 */
  HH(c, d, a, b, x[ 3], S33, 0xd4ef3085); /* 43 */
  HH(b, c, d, a, x[ 6], S34, 0x4881d05); /* 44 */
  HH(a, b, c, d, x[ 9], S31, 0xd9d4d039); /* 45 */
  HH(d, a, b, c, x[12], S32, 0xe6db99e5); /* 46 */
  HH(c, d, a, b, x[15], S33, 0x1fa27cf8); /* 47 */
  HH(b, c, d, a, x[ 2], S34, 0xc4ac5665); /* 48 */

  /* Round 4 */
  II(a, b, c, d, x[ 0], S41, 0xf4292244); /* 49 */
  II(d, a, b, c, x[ 7], S42, 0x432aff97); /* 50 */
  II(c, d, a, b, x[14], S43, 0xab9423a7); /* 51 */
  II(b, c, d, a, x[ 5], S44, 0xfc93a039); /* 52 */
  II(a, b, c, d, x[12], S41, 0x655b59c3); /* 53 */
  II(d, a, b, c, x[ 3], S42, 0x8f0ccc92); /* 54 */
  II(c, d, a, b, x[10], S43, 0xffeff47d); /* 55 */
  II(b, c, d, a, x[ 1], S44, 0x85845dd1); /* 56 */
  II(a, b, c, d, x[ 8], S41, 0x6fa87e4f); /* 57 */
  II(d, a, b, c, x[15], S42, 0xfe2ce6e0); /* 58 */
  II(c, d, a, b, x[ 6], S43, 0xa3014314); /* 59 */
  II(b, c, d, a, x[13], S44, 0x4e0811a1); /* 60 */
  II(a, b, c, d, x[ 4], S41, 0xf7537e82); /* 61 */
  II(d, a, b, c, x[11], S42, 0xbd3af235); /* 62 */
  II(c, d, a, b, x[ 2], S43, 0x2ad7d2bb); /* 63 */
  II(b, c, d, a, x[ 9], S44, 0xeb86d391); /* 64 */

  mState[0] += a;
  mState[1] += b;
  mState[2] += c;
  mState[3] += d;

  // Zeroize sensitive information.
  memset((unsigned char *) x, 0, sizeof(x));
}

// Encodes input (UINT4) into output (unsigned char). Assumes len is
// a multiple of 4.
void Cmd5::encode(unsigned char *output, unsigned C_INT32 *input, unsigned C_INT32 len)
{

  unsigned int i, j;

  for (i = 0, j = 0; j < len; i++, j += 4)
    {
      output[j] = (unsigned char)(input[i] & 0xff);
      output[j + 1] = (unsigned char)((input[i] >> 8) & 0xff);
      output[j + 2] = (unsigned char)((input[i] >> 16) & 0xff);
      output[j + 3] = (unsigned char)((input[i] >> 24) & 0xff);
    }
}

// Decodes input (unsigned char) into output (UINT4). Assumes len is
// a multiple of 4.
void Cmd5::decode(unsigned C_INT32 *output,
                  unsigned char *input,
                  unsigned C_INT32 len)
{
  unsigned int i, j;

  for (i = 0, j = 0; j < len; i++, j += 4)
    output[i] =
      ((unsigned C_INT32)input[j]) |
      (((unsigned C_INT32)input[j + 1]) << 8) |
      (((unsigned C_INT32)input[j + 2]) << 16) |
      (((unsigned C_INT32)input[j + 3]) << 24);
}

// ROTATE_LEFT rotates x left n bits.

inline unsigned C_INT32 Cmd5::rotate_left(unsigned C_INT32 x, unsigned C_INT32 n)
{return (x << n) | (x >> (32 - n));}

// F, G, H and I are basic Cmd5 functions.

inline unsigned C_INT32 Cmd5::F(unsigned C_INT32 x,
                                unsigned C_INT32 y,
                                unsigned C_INT32 z)
{return (x & y) | (~x & z);}

inline unsigned C_INT32 Cmd5::G(unsigned C_INT32 x,
                                unsigned C_INT32 y,
                                unsigned C_INT32 z)
{return (x & z) | (y & ~z);}

inline unsigned C_INT32 Cmd5::H(unsigned C_INT32 x,
                                unsigned C_INT32 y,
                                unsigned C_INT32 z)
{return x ^ y ^ z;}

inline unsigned C_INT32 Cmd5::I(unsigned C_INT32 x,
                                unsigned C_INT32 y,
                                unsigned C_INT32 z)
{return y ^ (x | ~z);}

// FF, GG, HH, and II transformations for rounds 1, 2, 3, and 4.
// Rotation is separate from addition to prevent recomputation.

inline void Cmd5::FF(unsigned C_INT32 & a,
                     unsigned C_INT32 b,
                     unsigned C_INT32 c,
                     unsigned C_INT32 d,
                     unsigned C_INT32 x,
                     unsigned C_INT32 s,
                     unsigned C_INT32 ac)
{
  a += F(b, c, d) + x + ac;
  a = rotate_left(a, s) + b;
}

inline void Cmd5::GG(unsigned C_INT32 & a,
                     unsigned C_INT32 b,
                     unsigned C_INT32 c,
                     unsigned C_INT32 d,
                     unsigned C_INT32 x,
                     unsigned C_INT32 s,
                     unsigned C_INT32 ac)
{
  a += G(b, c, d) + x + ac;
  a = rotate_left(a, s) + b;
}

inline void Cmd5::HH(unsigned C_INT32 & a,
                     unsigned C_INT32 b,
                     unsigned C_INT32 c,
                     unsigned C_INT32 d,
                     unsigned C_INT32 x,
                     unsigned C_INT32 s,
                     unsigned C_INT32 ac)
{
  a += H(b, c, d) + x + ac;
  a = rotate_left(a, s) + b;
}

inline void Cmd5::II(unsigned C_INT32 & a,
                     unsigned C_INT32 b,
                     unsigned C_INT32 c,
                     unsigned C_INT32 d,
                     unsigned C_INT32 x,
                     unsigned C_INT32 s,
                     unsigned C_INT32 ac)
{
  a += I(b, c, d) + x + ac;
  a = rotate_left(a, s) + b;
}
