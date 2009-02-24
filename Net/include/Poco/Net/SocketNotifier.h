//
// SocketNotifier.h
//
// $Id: //poco/1.3/Net/include/Poco/Net/SocketNotifier.h#2 $
//
// Library: Net
// Package: Reactor
// Module:  SocketNotifier
//
// Definition of the SocketNotifier class.
//
// Copyright (c) 2005-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//


#ifndef Net_SocketNotifier_INCLUDED
#define Net_SocketNotifier_INCLUDED


#include "Poco/Net/Net.h"
#include "Poco/Net/Socket.h"
#include "Poco/RefCountedObject.h"
#include "Poco/NotificationCenter.h"
#include "Poco/Observer.h"
#include <set>


namespace Poco {
namespace Net {


class Socket;
class SocketReactor;
class SocketNotification;


class Net_API SocketNotifier: public Poco::RefCountedObject
	/// This class is used internally by SocketReactor
	/// to notify registered event handlers of socket events.
{
public:
	explicit SocketNotifier(const Socket& socket);
		/// Creates the SocketNotifier for the given socket.
		
	void addObserver(SocketReactor* pReactor, const Poco::AbstractObserver& observer);
		/// Adds the given observer. 
		
	void removeObserver(SocketReactor* pReactor, const Poco::AbstractObserver& observer);
		/// Removes the given observer.
		
	bool accepts(SocketNotification* pNotification);
		/// Returns true if there is at least one observer for the given notification.
		
	void dispatch(SocketNotification* pNotification);
		/// Dispatches the notification to all observers.
		
	bool hasObservers() const;
		/// Returns true if there are subscribers.

protected:
	~SocketNotifier();
		/// Destroys the SocketNotifier.

private:
	typedef std::multiset<SocketNotification*> EventSet;

	EventSet                 _events;
	Poco::NotificationCenter _nc;
	Socket                   _socket;
};


//
// inlines
//
inline bool SocketNotifier::accepts(SocketNotification* pNotification)
{
	return _events.find(pNotification) != _events.end();
}


inline bool SocketNotifier::hasObservers() const
{
	return _nc.hasObservers();
}


} } // namespace Poco::Net


#endif // Net_SocketNotifier_INCLUDED
