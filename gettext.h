﻿/*
  This header should not be included in other header files,
  but included in the most bottom position of the inclusion part in the implementation (.cpp) files
  where the message internationalization (texts with _("...") form) is required.
*/


#ifdef CNOID_GETTEXT_DOMAIN_NAME
#undef CNOID_GETTEXT_DOMAIN_NAME
#endif
#define CNOID_GETTEXT_DOMAIN_NAME "CnoidOpenRTMPythonPlugin-1.6"

#ifdef _
#undef _
#endif

#include <boost/format.hpp>
namespace cnoid {
    inline boost::format fmt(const char* f_string) {
        boost::format f(f_string);
        f.exceptions(boost::io::no_error_bits);
        return f;
    }
    inline boost::format fmt(const std::string& f_string) {
        boost::format f(f_string);
        f.exceptions(boost::io::no_error_bits);
        return f;
    }

    // wrapper
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
# ifdef CnoidUtil_EXPORTS
    __declspec(dllexport) const char* getText(const char* domainname, const char* msgid);
# else
    __declspec(dllimport) const char* getText(const char* domainname, const char* msgid);
# endif
#else
    const char* getText(const char* domainname, const char* msgid);
#endif
    
}

#define CNOID_ENABLE_GETTEXT 1

#if CNOID_ENABLE_GETTEXT

#include <libintl.h>

#ifdef CNOID_USE_GETTEXT_WRAPPER
#define _(text) cnoid::getText(CNOID_GETTEXT_DOMAIN_NAME, text)
#else
#define _(text) dgettext(CNOID_GETTEXT_DOMAIN_NAME, text)
#endif

#define N_(string) string

#else

namespace cnoid {
    inline const char* bindtextdomain(const char* domainname, const char* dirname) {
        return dirname;
    }
    inline const char* dgettext(const char* domainname, const char* msgid){
        return msgid;
    }
}

#define _(string) string
#define N_(string) string

#endif
