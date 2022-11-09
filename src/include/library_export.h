#ifndef LIBRARY_EXPORT_H
#define LIBRARY_EXPORT_H

#include <QObject>
#ifndef STATICLIB
#if defined(COMMONGUI_SHAREDLIB_LIBRARY)
#  define COMMONGUI_EXPORT Q_DECL_EXPORT
#else
#  define COMMONGUI_EXPORT Q_DECL_IMPORT
#endif

#if defined(VSCOMMON_SHAREDLIB_LIBRARY)
#  define VSCOMMON_EXPORT Q_DECL_EXPORT
#else
#  define VSCOMMON_EXPORT Q_DECL_IMPORT
#endif

#if defined(VSGUI_SHAREDLIB_LIBRARY)
#  define VSGUI_EXPORT Q_DECL_EXPORT
#else
#  define VSGUI_EXPORT Q_DECL_IMPORT
#endif

#if defined(VSCOM_SHAREDLIB_LIBRARY)
#  define VSCOM_EXPORT Q_DECL_EXPORT
#else
#  define VSCOM_EXPORT Q_DECL_IMPORT
#endif
#else
#  define COMMONGUI_EXPORT
#  define VSCOMMON_EXPORT
#  define VSGUI_EXPORT
#  define VSCOM_EXPORT
#endif

#endif /* LIBRARY_EXPORT_H */
