/*
 * File:   main.c
 *
 * Copyright (C) 2014 pic32mcu@gmail.com
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not
 * use this file except in compliance with the License. You may obtain a copy of
 * the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations under
 * the License.
 */

// Include files
#include "USB/usb.h"
#include "USB/usb_host_android.h"
#include "Compiler.h"
#include "HardwareProfile.h"
#include "led.h"
#include "button.h"
#include "command.h"

// If a maximum current rating hasn't been defined, then define 500mA by default
#ifndef MAX_ALLOWED_CURRENT
    #define MAX_ALLOWED_CURRENT             (500)         // Maximum power we can supply in mA
#endif

// Configuration bits for the device.  Please refer to the device datasheet for each device
//   to determine the correct configuration bit settings
#if defined __C30__ || defined __XC16__
    #if defined(__PIC24FJ256GB110__)
        _CONFIG2(FNOSC_PRIPLL & POSCMOD_HS & PLL_96MHZ_ON & PLLDIV_DIV2) // Primary HS OSC with PLL, USBPLL /2
        _CONFIG1(JTAGEN_OFF & FWDTEN_OFF & ICS_PGx2)   // JTAG off, watchdog timer off
    #elif defined(__PIC24FJ64GB004__)
        _CONFIG1(WDTPS_PS1 & FWPSA_PR32 & WINDIS_OFF & FWDTEN_OFF & ICS_PGx1 & GWRP_OFF & GCP_OFF & JTAGEN_OFF)
        _CONFIG2(POSCMOD_HS & I2C1SEL_PRI & IOL1WAY_OFF & OSCIOFNC_ON & FCKSM_CSDCMD & FNOSC_PRIPLL & PLL96MHZ_ON & PLLDIV_DIV2 & IESO_ON)
        _CONFIG3(WPFP_WPFP0 & SOSCSEL_SOSC & WUTSEL_LEG & WPDIS_WPDIS & WPCFG_WPCFGDIS & WPEND_WPENDMEM)
        _CONFIG4(DSWDTPS_DSWDTPS3 & DSWDTOSC_LPRC & RTCOSC_SOSC & DSBOREN_OFF & DSWDTEN_OFF)
    #elif defined(__PIC24FJ64GB502__)
        _CONFIG1(WDTPS_PS1 & FWPSA_PR32 & WINDIS_OFF & FWDTEN_OFF & ICS_PGx1 & GWRP_OFF & GCP_OFF & JTAGEN_OFF)
        _CONFIG2(I2C1SEL_PRI & IOL1WAY_OFF & FCKSM_CSDCMD & FNOSC_PRIPLL & PLL96MHZ_ON & PLLDIV_DIV2 & IESO_OFF)
        _CONFIG3(WPFP_WPFP0 & SOSCSEL_SOSC & WUTSEL_LEG & WPDIS_WPDIS & WPCFG_WPCFGDIS & WPEND_WPENDMEM)
        _CONFIG4(DSWDTPS_DSWDTPS3 & DSWDTOSC_LPRC & RTCOSC_SOSC & DSBOREN_OFF & DSWDTEN_OFF)
    #elif defined(__PIC24FJ256GB106__)
        _CONFIG1( JTAGEN_OFF & GCP_OFF & GWRP_OFF & COE_OFF & FWDTEN_OFF & ICS_PGx2) 
        _CONFIG2( 0xF7FF & IESO_OFF & FCKSM_CSDCMD & OSCIOFNC_OFF & POSCMOD_HS & FNOSC_PRIPLL & PLLDIV_DIV3 & IOL1WAY_ON)
    #elif defined(__PIC24FJ256DA210__) || defined(__PIC24FJ256GB210__)
        _CONFIG1(FWDTEN_OFF & ICS_PGx2 & GWRP_OFF & GCP_OFF & JTAGEN_OFF)
        _CONFIG2(POSCMOD_HS & IOL1WAY_ON & OSCIOFNC_ON & FCKSM_CSDCMD & FNOSC_PRIPLL & PLL96MHZ_ON & PLLDIV_DIV2 & IESO_OFF)
    #elif defined(IOIO)
        _CONFIG1(FWDTEN_OFF & ICS_PGx2 & GWRP_OFF & GCP_OFF & JTAGEN_OFF)
        _CONFIG2(POSCMOD_NONE & IOL1WAY_ON & OSCIOFNC_ON & FCKSM_CSDCMD & FNOSC_FRCPLL & PLL96MHZ_ON & PLLDIV_NODIV & IESO_OFF)
    #elif defined(__dsPIC33EP512MU810__) || defined(PIC24EP512GU810_PIM)
        _FOSCSEL(FNOSC_FRC);
        _FOSC(FCKSM_CSECMD & OSCIOFNC_OFF & POSCMD_XT);
        _FWDT(FWDTEN_OFF);    
    #endif
#elif defined( __PIC32MX__ )
    #pragma config UPLLEN   = ON            // USB PLL Enabled
    #pragma config FPLLMUL  = MUL_15        // PLL Multiplier
    #pragma config UPLLIDIV = DIV_2         // USB PLL Input Divider
    #pragma config FPLLIDIV = DIV_2         // PLL Input Divider
    #pragma config FPLLODIV = DIV_1         // PLL Output Divider
    #pragma config FPBDIV   = DIV_1         // Peripheral Clock divisor
    #pragma config FWDTEN   = OFF           // Watchdog Timer
    #pragma config WDTPS    = PS1           // Watchdog Timer Postscale
    //#pragma config FCKSM    = CSDCMD        // Clock Switching & Fail Safe Clock Monitor
    #pragma config OSCIOFNC = OFF           // CLKO Enable
    #pragma config POSCMOD  = HS            // Primary Oscillator
    #pragma config IESO     = OFF           // Internal/External Switch-over
    #pragma config FSOSCEN  = OFF           // Secondary Oscillator Enable (KLO was off)
    #pragma config FNOSC    = PRIPLL        // Oscillator Selection
    #pragma config CP       = OFF           // Code Protect
    #pragma config BWP      = OFF           // Boot Flash Write Protect
    #pragma config PWP      = OFF           // Program Flash Write Protect
    #pragma config ICESEL   = ICS_PGx2      // ICE/ICD Comm Channel Select
    //#pragma config DEBUG    = ON            // Background Debugger Enable

#else
    #error Cannot define configuration bits.
#endif

// C30 and C32 Exception Handlers
// If your code gets here, you either tried to read or write
// a NULL pointer, or your application overflowed the stack
// by having too many local variables or parameters declared.
#if defined(__C30__) || defined __XC16__
	void _ISR __attribute__((__no_auto_psv__)) _AddressError(void)
	{
        while(1){}
	}
	void _ISR __attribute__((__no_auto_psv__)) _StackError(void)
	{
        while(1){}
	}
	
#elif defined(__C32__)
	void _general_exception_handler(unsigned cause, unsigned status)
	{
        #if defined(DEBUG_MODE)
            unsigned long address = _CP0_GET_EPC();
        #endif

        while(1){}
	}
#endif

//Local prototypes
#if defined(__C32__)
static void InitPIC32(void);
#endif

//local variables
static BYTE _readBuffer[16384];
static void* _deviceHandle = NULL;
static BOOL _deviceAttached = FALSE;

static char manufacturer[] = "pic32mcu@gmail.com";
static char model[] = "PIC32 Accessory Kit";
static char description[] = DEMO_BOARD_NAME_STRING;
static char version[] = "1.0";
static char uri[] = "https://pic32mcu.blogspot.com";
static char serial[] = "N/A";

ANDROID_ACCESSORY_INFORMATION myDeviceInfo =
{
    manufacturer,
    sizeof(manufacturer),
    model,
    sizeof(model),
    description,
    sizeof(description),
    version,
    sizeof(version),
    uri,
    sizeof(uri),
    serial,
    sizeof(serial)
};

static void actionUserButton(BYTE id, BYTE state) {
    if (state == BUTTON_STATE_UP) {
        switch (id) {
            case 1:
                state = (getLedState(1) == LED_STATE_OFF) ? LED_STATE_ON : LED_STATE_OFF;
                setLedState(1, state);
                break;
            case 2:
                sendCommand(COMMAND_SELECT_CITY, SELECT_CITY_PREV, 0x00);
                break;
            case 3:
                sendCommand(COMMAND_SELECT_CITY, SELECT_CITY_NEXT, 0x00);
                break;
        }
    }
}

static void UserActionTask(void) {
    BYTE id;
    BYTE state;
    beginSendCommand();
    while ((id = getStateChangedButtonID()) != BUTTON_UNDEFINE_ID) {
        state = (BYTE)getButtonState(id);
        sendCommand(COMMAND_UPDATE_BUTTON, id, state);
        actionUserButton(id, state);
    }
    while ((id = getEmulateStateChangedButtonID()) != BUTTON_UNDEFINE_ID) {
        state = (BYTE)getButtonEmulateState(id);
        sendCommand(COMMAND_UPDATE_BUTTON, id, state);
        actionUserButton(id, state);
    }
    while ((id = getStateChangedLedID()) != LED_UNDEFINE_ID) {
        state = (BYTE)getLedState(id);
        sendCommand(COMMAND_UPDATE_LED, id, state);
    }
    while ((id = getEmulateStateChangedLedID()) != LED_UNDEFINE_ID) {
        state = (BYTE)getLedEmulateState(id);
        sendCommand(COMMAND_UPDATE_LED, id, state);
    }
    endSendCommand(_deviceHandle);
}

static void sendLedButtonStatus(void) {
    beginSendCommand();
    sendCommand(COMMAND_UPDATE_LED, 1, getLedState(1));
    sendCommand(COMMAND_UPDATE_LED, 2, getLedState(2));
    sendCommand(COMMAND_UPDATE_LED, 3, getLedState(3));
    sendCommand(COMMAND_UPDATE_BUTTON, 1, getButtonState(1));
    sendCommand(COMMAND_UPDATE_BUTTON, 2, getButtonState(2));
    sendCommand(COMMAND_UPDATE_BUTTON, 3, getButtonState(3));
    endSendCommand(_deviceHandle);
}

static void processCommand(PIC32KIT_APP_PACKET* command_packet) {
    switch (command_packet->command) {
        case COMMAND_UPDATE_LED:
            setLedEmulateState(command_packet->data0, command_packet->data1);
            break;

        case COMMAND_UPDATE_BUTTON:
            setButtonEmulateState(command_packet->data0, command_packet->data1);
            break;

        default:
            //Error, unknown command
            DEBUG_PrintString("Error: unknown command received");
            break;
    }
}

static void ReceiverTask(void) {
    DWORD size = 0;
    BYTE errorCode;
    PIC32KIT_APP_PACKET* command_packet = NULL;

    errorCode = AndroidAppRead(_deviceHandle, (BYTE*) & _readBuffer, (DWORD)sizeof (_readBuffer));
    //If the device is attached, then lets wait for a command from the application
    if (errorCode != USB_SUCCESS) {
        DEBUG_PrintString("Error trying to start read");
    }

    if (AndroidAppIsReadComplete(_deviceHandle, &errorCode, &size) == TRUE) {
        //We've received a command over the USB from the Android device.
        if (errorCode == USB_SUCCESS) {
            //Maybe process the data here.  Maybe process it somewhere else.
            command_packet = (PIC32KIT_APP_PACKET*) & _readBuffer[0];
        } else {
            DEBUG_PrintString("Error trying to complete read request");
        }
    }

    while (size > 0) {
        processCommand(command_packet);

        //All commands in this example are two bytes, so remove that from the queue
        size -= sizeof (PIC32KIT_APP_PACKET);

        //And move the pointer to the next packet (this works because
        //  all command packets are 2 bytes.  If variable packet size
        //  then need to handle moving the pointer by the size of the
        //  command type that arrived.
        command_packet++;
    }
}

/****************************************************************************
  Function:
    int main(void)

  Summary:
    main function

  Description:
    main function

  Precondition:
    None

  Parameters:
    None

  Return Values:
    int - exit code for main function

  Remarks:
    None
  ***************************************************************************/
int main(void)
{
    BOOL bPrevDeviceState = _deviceAttached;

    #if defined(__PIC32MX__)
        InitPIC32();
    #endif

  #if defined(__dsPIC33EP512MU810__) || defined (__PIC24EP512GU810__)

    // Configure the device PLL to obtain 60 MIPS operation. The crystal
    // frequency is 8MHz. Divide 8MHz by 2, multiply by 60 and divide by
    // 2. This results in Fosc of 120MHz. The CPU clock frequency is
    // Fcy = Fosc/2 = 60MHz. Wait for the Primary PLL to lock and then
    // configure the auxilliary PLL to provide 48MHz needed for USB 
    // Operation.

	PLLFBD = 38;				/* M  = 60	*/
	CLKDIVbits.PLLPOST = 0;		/* N1 = 2	*/
	CLKDIVbits.PLLPRE = 0;		/* N2 = 2	*/
	OSCTUN = 0;			

    /*	Initiate Clock Switch to Primary
     *	Oscillator with PLL (NOSC= 0x3)*/
	
    __builtin_write_OSCCONH(0x03);		
	__builtin_write_OSCCONL(0x01);
	while (OSCCONbits.COSC != 0x3);       

    // Configuring the auxiliary PLL, since the primary
    // oscillator provides the source clock to the auxiliary
    // PLL, the auxiliary oscillator is disabled. Note that
    // the AUX PLL is enabled. The input 8MHz clock is divided
    // by 2, multiplied by 24 and then divided by 2. Wait till 
    // the AUX PLL locks.

    ACLKCON3 = 0x24C1;   
    ACLKDIV3 = 0x7;
    ACLKCON3bits.ENAPLL = 1;
    while(ACLKCON3bits.APLLCK != 1); 

    TRISBbits.TRISB5 = 0;
    LATBbits.LATB5 = 1;

    #endif

    USBInitialize(0);
    AndroidAppStart(&myDeviceInfo);

    initLed();
    initButton();

    DEBUG_Init(0);

    while(1)
    {
        //Keep the USB stack running
        USBTasks();

        if(bPrevDeviceState != _deviceAttached) {
            // device attach state is changed
            DEBUG_PrintString(_deviceAttached? "Device attached event" : "Device detached event");
            if(_deviceAttached) {
                if(isReadyToSendCommand(_deviceHandle)) {
                    sendLedButtonStatus();
                    bPrevDeviceState = _deviceAttached;
                }
            } else {
                bPrevDeviceState = _deviceAttached;
            }
        }

        //If the device isn't attached yet,
        if(_deviceAttached == FALSE)
        {
            //Continue to the top of the while loop to start the check over again.
            continue;
        }

        //If the accessory is ready, then this is where we run all of the demo code

        ReceiverTask();

        // update the current pushbutton status
        pollButtonState();

        //If there is a write already in progress, we need to check its status
        if(isReadyToSendCommand(_deviceHandle)) {
            UserActionTask();
        }

    } //while(1) main loop
}


/****************************************************************************
  Function:
    BOOL USB_ApplicationDataEventHandler( BYTE address, USB_EVENT event, void *data, DWORD size )

  Summary:
    Handles USB data application events

  Description:
    Handles USB data application events

  Precondition:
    None

  Parameters:
    BYTE address - address of the device causing the event
    USB_EVENT event - the event that has occurred
    void* data - data associated with the event
    DWORD size - the size of the data in the data field

  Return Values:
    BOOL - Return TRUE of the event was processed.  Return FALSE if the event
           wasn't handled.

  Remarks:
    None
  ***************************************************************************/
BOOL USB_ApplicationDataEventHandler( BYTE address, USB_EVENT event, void *data, DWORD size )
{
    return FALSE;
}


/****************************************************************************
  Function:
    BOOL USB_ApplicationEventHandler( BYTE address, USB_EVENT event, void *data, DWORD size )

  Summary:
    Handles USB application events

  Description:
    Handles USB application events

  Precondition:
    None

  Parameters:
    BYTE address - address of the device causing the event
    USB_EVENT event - the event that has occurred
    void* data - data associated with the event
    DWORD size - the size of the data in the data field

  Return Values:
    BOOL - Return TRUE of the event was processed.  Return FALSE if the event
           wasn't handled.

  Remarks:
    None
  ***************************************************************************/
BOOL USB_ApplicationEventHandler( BYTE address, USB_EVENT event, void *data, DWORD size )
{
    switch( (INT)event )
    {
        case EVENT_VBUS_REQUEST_POWER:
            // The data pointer points to a byte that represents the amount of power
            // requested in mA, divided by two.  If the device wants too much power,
            // we reject it.
            if (((USB_VBUS_POWER_EVENT_DATA*)data)->current <= (MAX_ALLOWED_CURRENT / 2))
            {
                return TRUE;
            }
            else
            {
                DEBUG_PrintString( "\r\n***** USB Error - device requires too much current *****\r\n" );
            }
            break;

        case EVENT_VBUS_RELEASE_POWER:
        case EVENT_HUB_ATTACH:
        case EVENT_UNSUPPORTED_DEVICE:
        case EVENT_CANNOT_ENUMERATE:
        case EVENT_CLIENT_INIT_ERROR:
        case EVENT_OUT_OF_MEMORY:
        case EVENT_UNSPECIFIED_ERROR:   // This should never be generated.
        case EVENT_DETACH:                   // USB cable has been detached (data: BYTE, address of device)
        case EVENT_ANDROID_DETACH:
            _deviceAttached = FALSE;
            return TRUE;
            break;

        // Android Specific events
        case EVENT_ANDROID_ATTACH:
            _deviceAttached = TRUE;
            _deviceHandle = data;
            return TRUE;

        default :
            break;
    }
    return FALSE;
}


/****************************************************************************
  Function:
    void InitPIC32(void)

  Summary:
    Initialize the PIC32 core to the correct modes and clock speeds

  Description:
    Initialize the PIC32 core to the correct modes and clock speeds

  Precondition:
    Only runs on PIC32

  Parameters:
    None

  Return Values:
    None

  Remarks:
    None
  ***************************************************************************/
#if defined(__PIC32MX__)
static void InitPIC32(void)
{
    int  value;
    
    #if defined(RUN_AT_60MHZ)
        // Use OSCCON default
    #else
        OSCCONCLR = 0x38000000; //PLLODIV
        #if defined(RUN_AT_48MHZ)
            OSCCONSET = 0x08000000; //PLLODIV /2
        #elif defined(RUN_AT_24MHZ)
            OSCCONSET = 0x10000000; //PLLODIV /4
        #else
            #error Cannot set OSCCON
        #endif
    #endif
    
    value = SYSTEMConfigWaitStatesAndPB( GetSystemClock() );
    
    // Enable the cache for the best performance
    CheKseg0CacheOn();
    
    INTEnableSystemMultiVectoredInt();
    
//    DDPCONbits.JTAGEN = 0;

    value = OSCCON;
    while (!(value & 0x00000020))
    {
        value = OSCCON;    // Wait for PLL lock to stabilize
    }
    
    INTEnableInterrupts();
}
#endif
