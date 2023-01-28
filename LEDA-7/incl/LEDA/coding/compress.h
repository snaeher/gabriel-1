/***************************************************************************
+
+  LEDA 7.0  
+
+
+  compress.h
+
+
+  Copyright (c) 1995-2023
+  by Algorithmic Solutions Software GmbH
+  All rights reserved.
+ 
*******************************************************************************/


#ifndef _LEDA_COMPRESS_H
#define _LEDA_COMPRESS_H

// includes all header files of the compression module

#if !defined(LEDA_ROOT_INCL_ID)
#define LEDA_ROOT_INCL_ID 700192
#include <LEDA/internal/PREAMBLE.h>
#endif

#include <LEDA/coding/arithmetic_coding.h>
#include <LEDA/coding/auto_decoder.h>
#include <LEDA/coding/block_coder.h>
#include <LEDA/coding/BWT.h>
#include <LEDA/coding/checksum.h>
#include <LEDA/coding/coder_util.h>
#include <LEDA/coding/count_streambuf.h>
#include <LEDA/coding/deflate.h>
#include <LEDA/coding/dict_coder.h>
#include <LEDA/coding/huffman.h>
#include <LEDA/coding/MTF.h>
#include <LEDA/coding/MTF2.h>
#include <LEDA/coding/PPMII.h>
#include <LEDA/coding/RLE.h>
#include <LEDA/coding/RLE0.h>

#if LEDA_ROOT_INCL_ID == 700192
#undef LEDA_ROOT_INCL_ID
#include <LEDA/internal/POSTAMBLE.h>
#endif

#endif
