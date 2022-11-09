#include "Communication/CrcCCITT.h"

namespace Communication
{
    inline void CrcCCITT::crcUpdate(uint16_t& crc, uint8_t val)
    {
        //lint ++fpm
        crc = (uint8_t)(crc >> 8) | (crc << 8);
        crc ^= val;
        crc ^= (uint8_t)(crc & 0xff) >> 4;
        crc ^= (crc << 12);         //was "crc ^= (crc << 8) << 4;" in MRX puck, since 8-bit cpu
        crc ^= ((crc & 0xff) << 5); //was "crc ^= ((crc & 0xff) << 4) << 1;" in MRX puck, since 8-bit cpu
        //lint --fpm
    }

    /********************************************************************* calcCrc
     * Name:    calcCrc
     *
     * Purpose: Calculates CRC from the contents of a byte array buffer
     *
     * Design reference: <SWSPEC> 7.2.3
     *
     * Input Parameters: pointer to buffer, length of buffer
     *
     * Permitted range:  any (it is up to the caller to set these up correctly)
     *
     * Return Parameter: the CRC, 16 bits unsigned
     *
     */

    uint16_t CrcCCITT::calcCrc(uint8_t *pBuf, size_t len)
    {
        uint16_t crc = CRC_INIT;
        uint8_t *pEnd = pBuf + len;

        while (pBuf < pEnd)
        {
            crcUpdate(crc, *pBuf++);
        }
        return crc;
    }

}// end namespace LittleSister

