#ifndef SW_VERSION_H
#define SW_VERSION_H


struct SWversion_t
{
    SWversion_t() : m_verMaj(0), m_verMin(0), m_verMaint(0), m_verBuild(0), m_license0(0), m_license1(0)
    {
    }

    SWversion_t(quint8 verMaj, quint8 verMin, quint8 verMaint, quint8 verBuild, quint8 license0, quint8 license1) :
        m_verMaj(verMaj), m_verMin(verMin), m_verMaint(verMaint), m_verBuild(verBuild), m_license0(license0), m_license1(license1)
    {
    }

    quint8 m_verMaj;
    quint8 m_verMin;
    quint8 m_verMaint;
    quint8 m_verBuild;
    quint8 m_license0;
    quint8 m_license1;
};

#endif // SW_VERSION_H
