#ifndef IOCONTROLLER_UPDATE_THREAD_H
#define IOCONTROLLER_UPDATE_THREAD_H

#include <qextserialport.h>
#include <QVector>
#include <QFile>
#include <QDir>
#include <QCoreApplication>
#include <QThread>
#include <QTimer>
#include <QSettings>
#include <QSharedPointer>
#include <gpio.h>

struct FlashData_t
{
    QByteArray m_startAddress;
    QByteArray m_data;
};


class IoControllerUpdateThread : public QThread
{
    Q_OBJECT

    public:
        //! \brief ctor
        IoControllerUpdateThread();

        //! \brief dtor
        ~IoControllerUpdateThread();

        //! \brief The starting point for the thread
        void run();

        //! \brief IO Controller bootloader ACK signal def
        static const quint8 BOOT_ACK = 0x79;

        //! \brief IO Controller bootloader NACK signal def
        static const quint8 BOOT_NACK = 0x1F;

        //! \brief IO Controller bootloader cmds def
        enum BootCMD_t {eGet = 0x00, eGetVerAndReadProtStat = 0x01, eGetID = 0x02, eReadMem = 0x11, eGo = 0x21,
                        eWriteMem = 0x31, eErase = 0x43, eExtErase = 0x44, eWriteProt = 0x63, eWriteUnprot = 0x73,
                        eAutoBaudSig = 0x7f, eReadoutProt = 0x82, eReadoutUnprot = 0x92, eNoCMD = 0xff};
        Q_ENUM(BootCMD_t)

        //! \brief The update state machine states
        enum BootStatus_t {eBootInit = 0x00, eBootEnter, eBootGetCommands, eBootEraseCMD, eBootEraseData,
                           eBootFlashCMD, eBootFlashAddr, eBootFlashData,
                           eBootExit};
        Q_ENUM(BootStatus_t)

        //! \brief Error states
        enum Error_t {eNoError = 0x00, eErrorSimFile, eErrorSimFileBadRecord, eErrorSimFileChSum, eErrorFlashFailed};
        Q_ENUM(Error_t)

        //! \brief Receive status for the IO Controller communication
        enum ReceiveStatus_t {eMessageInit, eMessageSyncronizing, eMessageReceiving, eMessageError, eMessageReceived, eMessageTimeout};
        Q_ENUM(ReceiveStatus_t)

       //! \brief Enum describing IO controller boot mode
        enum IOCtrlBootMode_t
        {
            IOCTRLBOOT_NORMAL,
            IOCTRLBOOT_REPROGRAM
        };
        Q_ENUM(IOCtrlBootMode_t);

    private:
        //! \brief Send a command to the IO Controller bootloader
        //! \param a_CMD - I.E. eGet
        void sendCMD(BootCMD_t a_CMD);

        //! \brief Send data to the IO Controller bootloader
        //! \param a_bytesToSend - byte array with data
        void sendData(QByteArray a_bytesToSend);

        //! \brief Get IO Controller in boot strap mode
        void enterBoot(void);

        //! \brief Get IO Controller out of boot strap mode. Will start user program
        void exitBoot(void);

        //! \brief Terminate IO Controller update. Will start user program
        void terminateBoot(void);

        //! \brief Convert binary sim file data to a format thet will fit the IO Controller bootloader
        //! \param a_SimFileData - byte array from a binary file read
        bool SimpleCodeProcessFile(QByteArray a_FileData);

        //! \brief Read a single byte (uint8) from the sim file byte array
        //! \param a_SimFile - byte array from a binary file read
        //! \param a_pCurrIdx - reference to the current read index
        quint8 SimFileReadByte(QByteArray a_SimFile, qint32 *a_pCurrIdx);

        //! \brief Read up to a uint32 from the sim file byte array. Will convert bytes written to correct size
        //! \param a_SimFile - byte array from a binary file read
        //! \param a_pCurrIdx - reference to the current read index
        //! \param a_Size - number of bytes to read and convert
        quint32 SimFileReadUint(QByteArray a_SimFile, qint32 *a_pCurrIdx, qint16 a_Size);

        bool configureSerial(QString a_SerialPort, BaudRateType a_BaudRate);

        //! \brief Serialport object used to communicate with IO Controller
        QextSerialPort *m_SerialPort;

        //! \brief Recieve status for the communication with IO Controller
        ReceiveStatus_t m_ReceiveStatus;

        //! \brief IO Controller bootloader current command set
        QList<quint8> m_IOcontrBootloaderCommandSet;

        //! \brief Current command
        BootCMD_t m_BootCMDpending;

        //! \brief Timer used to control the state mashine for the update process
        QTimer *m_IOcontrUpdateTimer;

        qint8 m_RetryCounter;

        //! \brief The update state machine current state
        BootStatus_t m_IOcontrUpdateStatus;

        //! \brief Flashdata ready for transmit to IO Controller
        QList<FlashData_t *> m_FlashData;

        //! \brief Flashdata curr index ready for transmit to IO Controller
        qint32 m_FlashData_idx;

        //! \brief Checksum used to validate the binary sim file data
        quint32 m_checksum;

        //! \brief Error
        Error_t m_error;

        //! \brief IOController MCU boot 0 GPIO Pin
        Gpio m_iocGPIOmcuBoot0;

        //! \brief IOController MCU boot 1 GPIO Pin
        Gpio m_iocGPIOmcuBoot1;

        //! \brief IOController MCU reset GPIO Pin
        Gpio m_iocGPIOmcuReset;

        //! \brief No of databytes for each write of IO Controller flash (max 256)
        static const quint16 FLASH_MEM_WR_BLOCK_SIZE = 256; //Bytes

        void setBootMode(IOCtrlBootMode_t a_BootMode);

        void ioControllerReset(bool a_Reset);

private slots:
        //! \brief Start update
        void updateIOcontroller(QString a_SerialPort, QByteArray a_SimFileData);

        //! \brief Received data event from serial port object
        void receivedData(void);

        //! \brief State machine for updating IO Processor
        void IOcontrUpdateProc(void);

    signals:
        //! \brief For signal parent that we are finished updating
        //! \param Result - false if failed, true if succeed
        void updateFinished(bool);

};

#endif // IOCtrlCommController_H
