//
// Utility.h
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef Settings_Utility_INCLUDED
#define Settings_Utility_INCLUDED


#include "Poco/Poco.h"
#include "Poco/OSP/BundleContext.h"
#include "Poco/OSP/Web/WebSession.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Util/AbstractConfiguration.h"
#include "Poco/Mutex.h"
#include <set>


namespace IoT {
namespace Web {
namespace Settings {


class Utility
	/// This class contains various utility functions used by request handlers.
{
public:
	static bool isAuthenticated(Poco::OSP::Web::WebSession::Ptr pSession, const Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
		/// Checks if there is a valid session.
		///
		/// Returns true if the session is valid.
		/// Returns false and sends the HTTP response with a 401 status if not.

	static bool isMutating(const Poco::Net::HTTPServerRequest& request);
		/// Returns true if the request is a mutating request.
		///
		/// Any request other than GET and HEAD is considered a mutating request.

	static std::string jsonize(const std::string& str);
		/// Creates a copy of str properly quoted and escaped for use in JSON.

	static void copyProperties(const Poco::Util::AbstractConfiguration& source, Poco::Util::AbstractConfiguration& target, const std::set<std::string>& excludeSet, const std::string& root = "");
		/// Copies all configuration properties from the source to the target configuration, starting with
		/// the given root key, which can be empty.

	static void copyDeltaProperties(const Poco::Util::AbstractConfiguration& ref, const Poco::Util::AbstractConfiguration& source, Poco::Util::AbstractConfiguration& target, const std::set<std::string>& excludeSet, const std::string& root = "");
		/// Copies all configuration properties that are different from those in ref
		/// from the source to the target configuration starting with
		/// the given root key, which can be empty.

	static Poco::FastMutex mutex;
};


//
// inlines
//
inline bool Utility::isMutating(const Poco::Net::HTTPServerRequest& request)
{
	const std::string& method = request.getMethod();
	return method != Poco::Net::HTTPRequest::HTTP_GET && method != Poco::Net::HTTPRequest::HTTP_HEAD;
}


} } } // namespace IoT::Web::Settings


#endif // Settings_Utility_INCLUDED
