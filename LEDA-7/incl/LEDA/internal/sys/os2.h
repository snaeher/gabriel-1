/*******************************************************************************
+
+  LEDA 7.0  
+
+
+  os2.h
+
+
+  Copyright (c) 1995-2023
+  by Algorithmic Solutions Software GmbH
+  All rights reserved.
+ 
*******************************************************************************/


#ifndef LEDA_SYS_OS2_H
#define LEDA_SYS_OS2_H

#define __os2__

#define LITTLE_ENDIAN_MACHINE

#if defined(__STDC__)
#define STRINGIZE(x) #x
#else
#define STRINGIZE(x) "x"
#endif


//------------------------------------------------------------------------------
//  DLL definitions
//------------------------------------------------------------------------------

#if defined(BUILD_DLL)
#define __exportC __export
#define __exportF __export
#define __exportD __export
#else
#define __exportC
#define __exportF
#define __exportD
#endif

#define __exportGeoW
#endif
