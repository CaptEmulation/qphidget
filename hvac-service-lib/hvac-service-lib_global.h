#ifndef HVACSERVICELIB_GLOBAL_H
#define HVACSERVICELIB_GLOBAL_H

#include <QtCore/qglobal.h>
#include "HttpDaemon.h"

#if defined(HVACSERVICELIB_LIBRARY)
#  define HVACSERVICELIBSHARED_EXPORT Q_DECL_EXPORT
#else
#  define HVACSERVICELIBSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // HVACSERVICELIB_GLOBAL_H
