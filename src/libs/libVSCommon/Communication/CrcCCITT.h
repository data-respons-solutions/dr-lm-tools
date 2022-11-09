//! @class  CrcCCITT
//! @brief  This class is responsible for CRC calculations according to the CRC-16 CCITT standard
//! @author Geir Inge Tellnes
//! @date   16.05.2006
//!

#ifndef _CRC_CCITT_H_
#define _CRC_CCITT_H_

#include "vs2_global.h"
#include <stdint.h>
#include <cstddef>

namespace Communication
{
    class VSCOMMON_EXPORT CrcCCITT
    {

    public:
        static const uint8_t CRC_LEN = sizeof(uint16_t);
        static uint16_t calcCrc(uint8_t *pBuf, size_t len);

    private:
        static void crcUpdate(uint16_t& crc, uint8_t val);

        static const uint16_t CRC_INIT = 0xFFFFu;
    };

}

#endif //_CRC_CCITT_H_

