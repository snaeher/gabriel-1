/*******************************************************************************
+
+  LEDA 7.0  
+
+
+  streambuf_workaround.h
+
+
+  Copyright (c) 1995-2023
+  by Algorithmic Solutions Software GmbH
+  All rights reserved.
+ 
*******************************************************************************/


#ifndef _LEDA_STREAMBUF_WORKAROUND_H
#define _LEDA_STREAMBUF_WORKAROUND_H

#if !defined(LEDA_ROOT_INCL_ID)
#define LEDA_ROOT_INCL_ID 700191
#include <LEDA/internal/PREAMBLE.h>
#endif

// work-around for Microsoft .NET
#if (_MSC_VER >= 1300)
#define LEDA_COMPRESSION_WA7
#endif

LEDA_BEGIN_NAMESPACE

/*
#ifdef LEDA_COMPRESSION_WA7
*/
// work-around for Microsoft .NET
class local_streambuf_wa7 : public streambuf {};

/*
#else
*/

// work-around for MSVC 6.0 and CXX 5.1 (alpha) and HPUX aCC 

class __exportC local_streambuf_wa1 : public streambuf {
public:
   virtual streamsize xsgetn(char* buffer, streamsize count);
   virtual streamsize xsputn(const char* buffer, streamsize count);
   virtual int sync() { return 0; }

protected:
   virtual int uflow() { int c = underflow(); return c < 0 ? c : sbumpc(); }
};

/*
#endif
*/


#if LEDA_ROOT_INCL_ID == 700191
#undef LEDA_ROOT_INCL_ID
#include <LEDA/internal/POSTAMBLE.h>
#endif

LEDA_END_NAMESPACE

#endif


#if defined(LEDA_COMPRESSION_WA1)
#define LEDA_STREAMBUF local_streambuf_wa1
#elif defined(LEDA_COMPRESSION_WA7)
#define LEDA_STREAMBUF local_streambuf_wa7
#else
#define LEDA_STREAMBUF streambuf
#endif

