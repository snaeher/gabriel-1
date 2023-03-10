/*******************************************************************************
+
+  LEDA 6.6.1  
+
+
+  RLE.h
+
+
+  Copyright (c) 1995-2020
+  by Algorithmic Solutions Software GmbH
+  All rights reserved.
+ 
*******************************************************************************/


#ifndef _LEDA_RLE_H
#define _LEDA_RLE_H

#if !defined(LEDA_ROOT_INCL_ID)
#define LEDA_ROOT_INCL_ID 661258
#include <LEDA/internal/PREAMBLE.h>
#endif

#include <LEDA/coding/coder_base.h>

LEDA_BEGIN_NAMESPACE

/// RLECoder ////////////////////////////////////////////////////////////////////////////////

/*{\Manpage {RLECoder} {} {Run-Length Coder} {C}}*/

class __exportC RLECoder : public coder_base {
/*{\Mdefinition
A Run-Length coder is used for compressing inputs which contain many long
sequences of repeating characters. 
The basic idea is as follows: A sequence |aaaaaaa| of 7 consecutive $a$'s 
is replaced by something like $a\#7$.\\
We provide two schemes for the actual encoding of the compressed sequence,
which allows the user to select between fast or high compression.
}*/
public:
	typedef coder_base base;
	enum { ID_Fast = 0x434c09, ID_High = 0x434c0a, ID = ID_Fast };
	enum { sentinel = 0xA1 };

public:
/*{\Mcreation}*/

	RLECoder(streambuf* src_stream = 0, streambuf* tgt_stream = 0, bool own_streams = false,
		     bool fast_mode = true);
	/*{\Mcreate creates an instance |\Mvar| which uses the given source 
	and target streams. If |own_streams| is set, then |\Mvar| is 
	responsible for the destruction of the streams, otherwise the pointers 
	|src_stream| and |tgt_stream| must be valid during the life-time of 
	|\Mvar|. 
	The parameter |fast_mode| allows to select fast or high compression 
	mode.}*/

	RLECoder(const char* src_file_name, const char* tgt_file_name, bool fast_mode = true);
	/*{\Mcreate creates an instance |\Mvar| which uses file-streams for 
	input and output.
	The parameter |fast_mode| allows to select fast or high compression 
	mode.}*/

/*{\Moperations}*/
/*{\Mtext \headerline{Standard Operations}}*/

/*{\Moptions nextwarning=no }*/
/*	inherited:
	void encode();
*/
	/*{\Mop encodes the source stream and writes the output to the target
	stream.}*/

/*{\Moptions nextwarning=no }*/
/*	inherited:
	void decode();
*/
	/*{\Mop decodes the source stream and writes the output to the target
	stream.}*/

/*{\Moptions nextwarning=no }*/
/*	inherited:
	uint32 encode_memory_chunk(const char* in_buf, uint32 in_len, char* out_buf, uint32 out_len);
*/
	/*{\Mop encodes the memory chunk starting at |in_buf| with size |in_len| 
	into the buffer starting at |out_buf| with size |out_len|. 
	The function returns actual length of the encoded chunk which may be 
	smaller than |out_len|. If the output buffer is too small for the encoded
	data the failure flag will be set (see below).}*/

/*{\Moptions nextwarning=no }*/
/*	inherited:
	uint32 decode_memory_chunk(const char* in_buf, uint32 in_len, char* out_buf, uint32 out_len);
*/
	/*{\Mop decodes a memory chunk. The meaning of the parameters and the 
	return value is the same as in the previous function.}*/

/*{\Moptions nextwarning=no }*/
/*	inherited:
	streambuf* get_src_stream() const;
*/
	/*{\Mop returns the current source stream.}*/

/*{\Moptions nextwarning=no }*/
/*	inherited:
	void set_src_stream(streambuf* src_stream, bool own_stream = false);
*/
	/*{\Mop sets the source stream (cf.~constructor).}*/

/*{\Moptions nextwarning=no }*/
/*	inherited:
	void set_src_file(const char* file_name);
*/
	/*{\Mop sets a file as source stream.}*/

/*{\Moptions nextwarning=no }*/
/*	inherited:
	streambuf* get_tgt_stream() const;
*/
	/*{\Mop returns the current target stream.}*/

/*{\Moptions nextwarning=no }*/
/*	inherited:
	void set_tgt_stream(streambuf* tgt_stream, bool own_Stream = false);
*/
	/*{\Mop sets the target stream (cf.~constructor).}*/

/*{\Moptions nextwarning=no }*/
/*	inherited:
	void set_tgt_file(const char* file_name);
*/
	/*{\Mop sets a file as target stream.}*/

/*{\Moptions nextwarning=no }*/
/*	inherited:
	void reset(bool keep_mode = true); 
*/
	/*{\Mop puts |\Mvar| in the same state as the default constructor.
	If |keep_mode| is false the compression mode is set to the default
	value.}*/

/*{\Moptions nextwarning=no }*/
/*	inherited:
	bool failed() const;
*/
	/*{\Mop returns |true| if an error occured.}*/

/*{\Moptions nextwarning=no }*/
/*	inherited:
	bool finished() const;
*/
	/*{\Mop returns |true| if the coding is finished.}*/

/*{\Moptions nextwarning=no }*/
	virtual string get_description() const;
	/*{\Mop provides a description for |\Mvar|.}*/

/*{\Mtext \headerline{Additional Operations}}*/

	bool is_in_fast_mode() const { return FastMode; }
	/*{\Mop returns |true| if the coder is in fast mode, and |false| if
	it is in high compression mode.}*/

	void set_fast_compression_mode();
	/*{\Mop selects fast compression mode.}*/

	void set_high_compression_mode();
	/*{\Mop selects high compression mode.}*/

protected:
	virtual const char* get_class_name() const { return "RLECoder"; }
	virtual id_type get_id() const { return FastMode ? ID_Fast : ID_High; }
	virtual void check_id(id_type id_to_check);

	virtual void init_encoding();
	virtual void encode_stream();

	virtual void init_decoding();
	virtual void decode_stream();

	virtual void do_reset(reset_type t);

private:
	void init_encoding_fast_mode();
	void init_encoding_slow_mode();

	void encode_stream_fast_mode();
	void encode_stream_slow_mode();

	void init_decoding_fast_mode();
	void init_decoding_slow_mode();

	void decode_stream_fast_mode();
	void decode_stream_slow_mode();

private:
	uint32	Count;
	byte	PreviousSymbol;
	bool    FastMode;
};


#if LEDA_ROOT_INCL_ID == 661258
#undef LEDA_ROOT_INCL_ID
#include <LEDA/internal/POSTAMBLE.h>
#endif

LEDA_END_NAMESPACE

#endif
