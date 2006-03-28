/*
  Copyright (C) 2005, 2004 Erik Eliasson, Johan Bilien
  
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

/*
 * Authors: Erik Eliasson <eliasson@it.kth.se>
 *          Johan Bilien <jobi@via.ecp.fr>
*/


/* Name
 * 	SipHeaderValueRAck.cxx
 * Author
 * 	Erik Eliasson, eliasson@it.kth.se
 * Purpose
 * 
*/

#include<config.h>


#include<libmsip/SipHeaderRAck.h>

#include<libmutil/itoa.h>
#include<libmutil/trim.h>

MRef<SipHeaderValue *> rackFactory(const string &build_from){
	                return new SipHeaderValueRAck(build_from);
}

SipHeaderFactoryFuncPtr sipHeaderRAckFactory=rackFactory;



const string sipHeaderValueRAckTypeStr = "RAck";

SipHeaderValueRAck::SipHeaderValueRAck(const string &build_from):SipHeaderValue(SIP_HEADER_TYPE_RACK,sipHeaderValueRAckTypeStr){
	unsigned i=0;
	unsigned maxi=build_from.size()-1;
	while (build_from[i]==' ')
		i++;
	
	string respnumstr;
	while (i<=maxi && ( (build_from[i]>='0' && build_from[i]<='9') || build_from[i]=='-')){
		respnumstr+=build_from[i];
		i++;
	}
	
	while (i<=maxi && build_from[i]==' ')
		i++;
	
	string cseqnumstr;
	while (i<=maxi && ((build_from[i]>='0' && build_from[i]<='9') || build_from[i]=='-')){
		cseqnumstr+=build_from[i];
		i++;
	}
	
	
	method="";
	while (!(i>=build_from.length())){
		method+=build_from[i];
		i++;
	}
	respnum = atoi((trim(respnumstr)).c_str());
	cseqnum = atoi((trim(cseqnumstr)).c_str());
}

SipHeaderValueRAck::SipHeaderValueRAck(const string &meth, int rnum, int cseq) : SipHeaderValue(SIP_HEADER_TYPE_RACK,sipHeaderValueRAckTypeStr), method(meth),cseqnum(cseq),respnum(rnum) {
}

SipHeaderValueRAck::~SipHeaderValueRAck(){
}

string SipHeaderValueRAck::getString(){
	return itoa(respnum)+" "+itoa(cseqnum)+" "+method;
}

string SipHeaderValueRAck::getMethod(){
	return method;
}
		
int32_t SipHeaderValueRAck::getResponseNum(){
	return respnum;
}

int32_t SipHeaderValueRAck::getCSeqNum(){
	return cseqnum;
}

