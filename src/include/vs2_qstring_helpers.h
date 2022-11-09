#ifndef VS2_QSTRING_HELPERS_H
#define VS2_QSTRING_HELPERS_H

#include <QString>

#ifdef UNICODE
inline std::wstring QStringToStdTString(const QString& str) { return str.toStdWString();}
inline QString QStringFromStdTString(const std::wstring& str) { return QString::fromStdWString(str);}
#else
inline std::string QStringToStdTString(const QString& str) { return std::string(str.toUtf8());}
inline QString QStringFromStdTString(const std::string& str) { return QString::fromUtf8(str.data());}
#endif

#endif // VS2_QSTRING_HELPERS_H
