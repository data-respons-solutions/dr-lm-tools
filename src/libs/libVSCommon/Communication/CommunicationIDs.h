namespace Communication
{
    class CommunicationIDs
    {
        public:
            //! \brief Message identifcations for communication between Base Unit Main software and IO Controller software
            //! Messages are sendt without any delimiters, but formatted as [ID][Parameter1][Parameter2] based on specified data type for parameters.
            //! Example: CMD_SET_BP 120/80 will result in 0x2178005000  [ID][P1-LSB][P1-MSB][P2-LSB][P2-MSB]
            enum MessageIDs
            {
                //Originator Base Unit Main Software
                EVENT_PULSESYNC                 = 0x01, //Sender = BU, Parameters = (uint8_t enum scale_normal=0 scale_half=1 scale_1.5=2 scale_cprpulse=3)
                
                CMD_SET_AUSCULTATIONGAP         = 0x20, //Sender = BU, Parameters = (int8_t OnOff)
                CMD_SET_BP                      = 0x21, //Sender = BU, Parameters = (int16_t Systolic, int16_t Diastolic)
                CMD_CALIBRATECUFF               = 0x22,
                CMD_SET_CUFFGAIN                = 0x23, //Sender = BU, Parameters = (uint32_t gain)
                CMD_SET_PULSESTRENGTH           = 0x24, //Sender = BU, Parameters = (int8_t PulseNumber, int8_t Strength)
                CMD_SET_PULSEDELAY              = 0x25, //Sender = BU, Parameters = (int8_t PulseNumber, int8_t ms)
                CMD_SET_HEARTRATE               = 0x26, //Sender = BU, Parameters = (int16_t HeartRate beats/minute)
                CMD_SET_PULSESTRENGTH_CENTRAL   = 0x27, //Sender = BU, Parameters = (int8_t Strength)
                CMD_SET_PULSESTRENGTH_PERIPHERAL= 0x28, //Sender = BU, Parameters = (int8_t Strength)
                CMD_SET_AIRWAY                  = 0x40, //Sender = BU, Parameters = (int8_t mode 0=closed, 1=open) Only applicable if RASim connected
                CMD_SET_CHEST_RISE              = 0x41, //Sender = BU, Parameters = (int8_t direction 0=down, 1=up) Only applicable if RASim connected
                CMD_SET_POWER_PANEL             = 0x42, //Sender = BU, Parameters = (int8_t led 0=Red LED 1=Green LED, int8_t state 0=off 1=on) Only applicable if RASim connected


                REQ_MANIKINTYPE                 = 0x50, //Sender = BU
                REQ_USER_SW_VER                 = 0x51, //Sender = BU
                REQ_NECK_TILT                   = 0x52, //Sender = BU
                REQ_MANIKIN_CONNECTED           = 0x53, //Sender = BU

                //Board test commands
                CMD_TEST_MODE                   = 0x70, //Sender = BU, Parameters = (int8_t testMode 1 = enter test mode, 2 = exit test mode)
                CMD_TEST_SET_IO                 = 0x71, //Sender = BU, Parameters = (int8_t ch 1=MCU_GPIO0, 2=MCU_GPIO1, 3=MCU_GPIO2, 4=MCU_GPO1, 5=MCU_GPO2, int8_t setOrClear 0=clear, 1=set)
                CMD_TEST_GET_IO                 = 0x72, //Sender = BU, Parameters = (int8_t ch 1=MCU_GPIO0, 2=MCU_GPIO1, 3=MCU_GPIO2, 4=MCU_GPO1, 5=MCU_GPO2)
                CMD_TEST_SET_PWM                = 0x73, //Sender = BU, Parameters = (int8_t ch 0=RCAR, 1=LCAR, 2=RAD, 3=BRA, 4=UNASS1, 5=UNASS2, uint16_t pwm)
                CMD_TEST_GET_PULSE_PALP_FREQ    = 0x74, //Sender = BU, Parameters = (int8_t ch 0=RCAR, 1=LCAR, 2=RAD, 3=BRA, 4=UNASS1, 5=UNASS2)
                CMD_TEST_GET_AD                 = 0x75, //Sender = BU, Parameters = (int8_t ch 0-15)

                
                //Originator IOController Software
                CMD_EVENT_PULSEPALPATED         = 0x80, //Sender = IO, Parameter = (int8_t PulseID)
                CMD_EVENT_SHOCKDETECTED         = 0x81, //Sender = IO
                CMD_EVENT_PACINGDETECTED        = 0x82, //Sender = IO, Parameter = (int8_t mA)
                CMD_EVENT_CUFFGAIN              = 0x83, //Sender = IO, Parameter = (uint32_t Gain)
                CMD_EVENT_BPSOUND               = 0x84, //Sender = IO, Parameter = (int8_t Volume, int8_t Phase)
                CMD_EVENT_PULSEPALPATION_STOPPED= 0x85, //Sender = IO, Paramter  = (int8_t PulseID)
                CMD_EVENT_BP_MEASURED           = 0x86, //Sender = IO, Paramter  = (None)
                CMD_EVENT_BP_CUFF_VALUE         = 0x87, //Sender = IO, Paramter  = (uint16 CuffPressure)
                CMD_EVENT_BP_CUFF_CAL_RESULT    = 0x88, //Sender = IO, Paramter  = (uint8 Result 0=fail, 1=success)
                
                CMD_EVENT_COMP_DATA             = 0x90, //Sender = IO, Parameter = (uint8_t wrHandPosBitMask 0=High 1=Low 2=Left 3=Right, uint8_t depth mm) Only applicable if RASim connected
                CMD_EVENT_VENT_DATA             = 0x91, //Sender = IO, Parameter = (uint8_t volume ml) Only applicable if RASim connected
                CMD_EVENT_NECK_TILT             = 0x92, //Sender = IO, Parameter = (uint8_t neckTiltStatus 0=closed 1=open) Only applicable if RASim connected
                CMD_EVENT_SHAKE                 = 0x93, //Sender = IO, Parameter = None Only applicable if RASim connected
                CMD_EVENT_VENT_DETECT           = 0x94, //Sender = IO, Parameter = None

                RPL_MANIKINTYPE                 = 0xB0,  //Sender = IO, Parameter = (int8_t ManikinType)
                RPL_USER_SW_VER                 = 0xB1,  //Sender = IO, Parameter = (int8_t VerMaj, int8_t verMin, int8_t verMaint, int8_t verBuild)
                RPL_MANIKIN_CONNECTED           = 0xB2,  //Sender = IO, Parameter = (uint8 Status 0=Not connected, 1=connected)

                //Board test replies
                RPL_TEST_GET_IO                 = 0xF0,  //Sender = IO, Parameter = (int8_t ch, int8_t value)
                RPL_TEST_GET_PULSE_PALP_FREQ    = 0xF1,  //Sender = IO, Parameter = (int8_t ch, int8_t value)
                RPL_TEST_GET_AD                 = 0xF2,  //Sender = IO, Parameter = (int8_t ch, int16_t value)


                //Errors:
                ERR_UNKNOWN_DATA                = 0xFE, //Sender = IO/BU, Parameter = (int8_t MessageID)
                ERR_UNKNOWN_COMMAND             = 0xFF, //Sender = IO/BU, Parameter = (int8_t MessageID)
            };
    };

}
