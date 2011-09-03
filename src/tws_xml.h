/*** tws_xml.h -- conversion between IB/API structs and xml
 *
 * Copyright (C) 2011 Ruediger Meier
 *
 * Author:  Ruediger Meier <sweet_f_a@gmx.de>
 *
 * This file is part of twstools.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the author nor the names of any contributors
 *    may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ***/

#ifndef TWS_XML_H
#define TWS_XML_H


namespace IB {
	class ComboLeg;
	class UnderComp;
	class Contract;
	class ContractDetails;
	class Execution;
	class ExecutionFilter;
	class TagValue;
	class Order;
	class OrderState;
}


typedef struct _xmlNode * xmlNodePtr;
typedef struct _xmlDoc * xmlDocPtr;


void conv_ib2xml( xmlNodePtr parent, const char* name, const IB::ComboLeg& c );
void conv_ib2xml( xmlNodePtr parent, const char* name, const IB::UnderComp& c );
void conv_ib2xml( xmlNodePtr parent, const char* name, const IB::Contract& c );
void conv_ib2xml( xmlNodePtr parent, const char* name,
	const IB::ContractDetails& c );
void conv_ib2xml( xmlNodePtr parent, const char* name, const IB::Execution& );
void conv_ib2xml( xmlNodePtr parent, const char* name,
	const IB::ExecutionFilter& );
void conv_ib2xml( xmlNodePtr parent, const char* name, const IB::TagValue& );
void conv_ib2xml( xmlNodePtr parent, const char* name, const IB::Order& );
void conv_ib2xml( xmlNodePtr parent, const char* name, const IB::OrderState& );

void conv_xml2ib( IB::ComboLeg* c, const xmlNodePtr node );
void conv_xml2ib( IB::UnderComp* c, const xmlNodePtr node );
void conv_xml2ib( IB::Contract* c, const xmlNodePtr node );
void conv_xml2ib( IB::ContractDetails* c, const xmlNodePtr node );
void conv_xml2ib( IB::Execution*, const xmlNodePtr node );
void conv_xml2ib( IB::ExecutionFilter*, const xmlNodePtr node );
void conv_xml2ib( IB::TagValue*, const xmlNodePtr node );
void conv_xml2ib( IB::Order*, const xmlNodePtr node );
void conv_xml2ib( IB::OrderState*, const xmlNodePtr node );




class TwsXml
{
	public:
		TwsXml();
		virtual ~TwsXml();
		
		static void setSkipDefaults( bool );
		static xmlNodePtr newDocRoot();
		static void dumpAndFree( xmlNodePtr root );
		
		bool openFile( const char *filename );
		xmlDocPtr nextXmlDoc();
		xmlNodePtr nextXmlRoot();
		xmlNodePtr nextXmlNode();
		
		static const bool &skip_defaults;
		
	private:
		void resize_buf();
		
		static bool _skip_defaults;
		
		void *file; // FILE*
		long buf_size;
		long buf_len;
		char *buf;
		xmlDocPtr curDoc;
		xmlNodePtr curNode;
};




#endif