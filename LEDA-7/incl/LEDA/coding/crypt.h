/*******************************************************************************
+
+  LEDA 7.0  
+
+
+  crypt.h
+
+
+  Copyright (c) 1995-2023
+  by Algorithmic Solutions Software GmbH
+  All rights reserved.
+ 
*******************************************************************************/


#ifndef _LEDA_CRYPT_H
#define _LEDA_CRYPT_H

// includes all header files of the cryptography module

#if !defined(LEDA_ROOT_INCL_ID)
#define LEDA_ROOT_INCL_ID 700188
#include <LEDA/internal/PREAMBLE.h>
#endif

#include <LEDA/coding/compress.h>

#include <LEDA/coding/stream_ciphers.h>
#include <LEDA/coding/authentication.h>
#include <LEDA/coding/crypt_auto_decoder.h>
#include <LEDA/coding/secure_socket_streambuf.h>

#if LEDA_ROOT_INCL_ID == 700188
#undef LEDA_ROOT_INCL_ID
#include <LEDA/internal/POSTAMBLE.h>
#endif

#endif
