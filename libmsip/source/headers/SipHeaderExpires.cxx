/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Library General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

/* Copyright (C) 2004 
 *
 * Authors: Erik Eliasson <eliasson@it.kth.se>
 *          Johan Bilien <jobi@via.ecp.fr>
*/

/* Name
 * 	SipHeaderValueExpires.cxx
 * Author
 * 	Erik Eliasson, eliasson@it.kth.se
 * Purpose
 * 
*/

#include<config.h>


#include<libmsip/SipHeaderExpires.h>

#include<libmutil/itoa.h>

const string sipHeaderValueExpiresTypeStr = "Expires";

SipHeaderValueExpires::SipHeaderValueExpires(const string &build_from)
		: SipHeaderValue(SIP_HEADER_TYPE_EXPIRES,sipHeaderValueExpiresTypeStr)
{
	timeout=300;			//TODO: XXX
}

SipHeaderValueExpires::SipHeaderValueExpires()
		: SipHeaderValue(SIP_HEADER_TYPE_EXPIRES,sipHeaderValueExpiresTypeStr)
{
	timeout=300;
}

SipHeaderValueExpires::~SipHeaderValueExpires(){
}

string SipHeaderValueExpires::getString(){
	return /*"Expires: "+*/ itoa(timeout);
}

int32_t SipHeaderValueExpires::getTimeout(){
	return timeout;
}
		
void SipHeaderValueExpires::setTimeout(int32_t timeout){
	this->timeout=timeout;
}

