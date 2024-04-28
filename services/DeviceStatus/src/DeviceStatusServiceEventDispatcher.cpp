//
// DeviceStatusServiceEventDispatcher.cpp
//
// Library: IoT/DeviceStatus
// Package: Generated
// Module:  DeviceStatusServiceEventDispatcher
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2016-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/DeviceStatus/DeviceStatusServiceEventDispatcher.h"
#include "IoT/DeviceStatus/DeviceStatusChangeDeserializer.h"
#include "IoT/DeviceStatus/DeviceStatusChangeSerializer.h"
#include "Poco/Delegate.h"
#include "Poco/RemotingNG/Deserializer.h"
#include "Poco/RemotingNG/RemotingException.h"
#include "Poco/RemotingNG/Serializer.h"
#include "Poco/RemotingNG/TypeDeserializer.h"
#include "Poco/RemotingNG/TypeSerializer.h"
#include "Poco/RemotingNG/URIUtility.h"


namespace IoT {
namespace DeviceStatus {


DeviceStatusServiceEventDispatcher::DeviceStatusServiceEventDispatcher(IDeviceStatusService* pInterface, const Poco::RemotingNG::Identifiable::ObjectId& objectId, const std::string& protocol):
	Poco::RemotingNG::EventDispatcher(protocol),
	_objectId(objectId),
	_pInterface(pInterface)
{
	_pInterface->statusChanged += Poco::delegate(this, &DeviceStatusServiceEventDispatcher::event__statusChanged);
	_pInterface->statusUpdated += Poco::delegate(this, &DeviceStatusServiceEventDispatcher::event__statusUpdated);
}


DeviceStatusServiceEventDispatcher::~DeviceStatusServiceEventDispatcher()
{
	try
	{
		_pInterface->statusChanged -= Poco::delegate(this, &DeviceStatusServiceEventDispatcher::event__statusChanged);
		_pInterface->statusUpdated -= Poco::delegate(this, &DeviceStatusServiceEventDispatcher::event__statusUpdated);
	}
	catch (...)
	{
		poco_unexpected();
	}
}


void DeviceStatusServiceEventDispatcher::event__statusChanged(const void* pSender, const IoT::DeviceStatus::DeviceStatusChange& data)
{
	if (pSender)
	{
		Poco::Clock now;
		Poco::FastMutex::ScopedLock lock(_mutex);
		SubscriberMap::iterator it = _subscribers.begin();
		while (it != _subscribers.end())
		{
			if (it->second->expireTime != 0 && it->second->expireTime < now)
			{
				SubscriberMap::iterator itDel(it++);
				_subscribers.erase(itDel);
			}
			else
			{
				try
				{
					event__statusChangedImpl(it->first, data);
				}
				catch (Poco::RemotingNG::RemoteException&)
				{
					throw;
				}
				catch (Poco::Exception&)
				{
				}
				++it;
			}
		}
	}
}


void DeviceStatusServiceEventDispatcher::event__statusUpdated(const void* pSender, const IoT::DeviceStatus::DeviceStatusChange& data)
{
	if (pSender)
	{
		Poco::Clock now;
		Poco::FastMutex::ScopedLock lock(_mutex);
		SubscriberMap::iterator it = _subscribers.begin();
		while (it != _subscribers.end())
		{
			if (it->second->expireTime != 0 && it->second->expireTime < now)
			{
				SubscriberMap::iterator itDel(it++);
				_subscribers.erase(itDel);
			}
			else
			{
				try
				{
					event__statusUpdatedImpl(it->first, data);
				}
				catch (Poco::RemotingNG::RemoteException&)
				{
					throw;
				}
				catch (Poco::Exception&)
				{
				}
				++it;
			}
		}
	}
}


void DeviceStatusServiceEventDispatcher::event__statusChangedImpl(const std::string& subscriberURI, const IoT::DeviceStatus::DeviceStatusChange& data)
{
	using namespace std::string_literals;
	
	static const std::string REMOTING__NAMES[] = {"statusChanged"s,"subscriberURI"s,"data"s};
	Poco::RemotingNG::Transport& remoting__trans = transportForSubscriber(subscriberURI);
	Poco::ScopedLock<Poco::RemotingNG::Transport> remoting__lock(remoting__trans);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginMessage(_objectId, remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	Poco::RemotingNG::TypeSerializer<IoT::DeviceStatus::DeviceStatusChange>::serialize(REMOTING__NAMES[2], data, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__trans.sendMessage(_objectId, remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
}


void DeviceStatusServiceEventDispatcher::event__statusUpdatedImpl(const std::string& subscriberURI, const IoT::DeviceStatus::DeviceStatusChange& data)
{
	using namespace std::string_literals;
	
	static const std::string REMOTING__NAMES[] = {"statusUpdated"s,"subscriberURI"s,"data"s};
	Poco::RemotingNG::Transport& remoting__trans = transportForSubscriber(subscriberURI);
	Poco::ScopedLock<Poco::RemotingNG::Transport> remoting__lock(remoting__trans);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginMessage(_objectId, remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	Poco::RemotingNG::TypeSerializer<IoT::DeviceStatus::DeviceStatusChange>::serialize(REMOTING__NAMES[2], data, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__trans.sendMessage(_objectId, remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
}


const std::string DeviceStatusServiceEventDispatcher::DEFAULT_NS("");
} // namespace DeviceStatus
} // namespace IoT

