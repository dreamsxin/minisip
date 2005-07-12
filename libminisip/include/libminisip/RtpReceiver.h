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


/* Copyright (C) 2004, 2005 
 *
 * Authors: Erik Eliasson <eliasson@it.kth.se>
 *          Johan Bilien <jobi@via.ecp.fr>
*/

#ifndef RTPRECEIVER_H
#define RTPRECEIVER_H

#ifdef _MSC_VER
#ifdef LIBMINISIP_EXPORTS
#define LIBMINISIP_API __declspec(dllexport)
#else
#define LIBMINISIP_API __declspec(dllimport)
#endif
#else
#define LIBMINISIP_API
#endif


#include<libmutil/Mutex.h>
#include<libmutil/MemObject.h>
#include<libmutil/Thread.h>
#include<libminisip/IpProvider.h>

class UDPSocket;
class MediaStreamReceiver;
class CryptoContext;


class LIBMINISIP_API RtpReceiver : public Runnable{
	public:
		RtpReceiver( MRef<IpProvider *> ipProvider );

		void registerMediaStream( MRef<MediaStreamReceiver *> mediaStream );
		void unregisterMediaStream( MRef<MediaStreamReceiver *> );

		virtual void run();

		uint16_t getPort();

		~RtpReceiver();

		MRef<UDPSocket *> getSocket();

		virtual std::string getMemObjectType(){return "RtpReceiver";}

	private:
		MRef<UDPSocket *> socket;
		uint16_t externalPort;
		bool kill;

		std::list< MRef<MediaStreamReceiver *> > mediaStreams;

		Mutex mediaStreamsLock;

                Thread * thread;
};

#endif