/*******************************************************************************
+
+  LEDA 7.0  
+
+
+  system.h
+
+
+  Copyright (c) 1995-2023
+  by Algorithmic Solutions Software GmbH
+  All rights reserved.
+ 
*******************************************************************************/


#ifndef LEDA_SYSTEM_H
#define LEDA_SYSTEM_H


#if defined(__CYGWIN32__)
/*
#include <LEDA/internal/sys/cygwin.h>
*/
#include <LEDA/internal/sys/windows.h>

#elif defined(unix) || defined(__unix__) || defined(__unix) || defined(_AIX) || defined(__APPLE__)
#include <LEDA/internal/sys/unix.h>

#elif defined(__WIN64__) || defined(_WIN64)
#include<LEDA/internal/sys/windows64.h>

#elif defined(__WIN32__) || defined(_WIN32) || (defined(__NT__) && !defined(__win64__))
#include <LEDA/internal/sys/windows.h>


#elif defined(OS2) || defined(__OS2__)
#include <LEDA/internal/sys/os2.h>

#else
// unknown system
#endif

#if defined(_MSC_VER)
#if defined(LEDA_INSTALL)
#pragma warning(disable:4100)
#pragma warning(disable:4127)
#pragma warning(disable:4189)
#pragma warning(disable:4244)
#pragma warning(disable:4310)
#pragma warning(disable:4312)
#pragma warning(disable:4456)
#pragma warning(disable:4457)
#pragma warning(disable:4458)
#pragma warning(disable:4459)
#pragma warning(disable:4505)
#pragma warning(disable:4838)
#endif
#endif

// leda namespace

#define LEDA_BEGIN_NAMESPACE namespace leda {
#define LEDA_END_NAMESPACE   } 



//-----------------------------------------------------------------------------
// LEDA Evaluation	
//-----------------------------------------------------------------------------

//#define LEDA_EVAL
//#define LEDA_CHECK_LICENSE_BY_DATE

#if defined(LEDA_EVAL)
#define LEDA_CHECK_LICENSE
#endif

#include <LEDA/internal/config.h>

#endif

