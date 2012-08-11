/*++

Copyright (C) 2011-2012, The Little Beige Box, http://www.beige-box.com
Licensed under the GNU General Public License v2.

File name:

    voodoo.h

Abstract:

    Define core types used by libvoodoogestalt.

--*/

#ifndef _VOODOO_

#include <CoreFoundation/CoreFoundation.h>
#include <sys/types.h>
#include <sys/sysctl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <dlfcn.h>
#include <stdio.h>
#include <syslog.h>

#include <deli/ipad.h>
#include <deli/iphone.h>
#include <deli/ipod.h>

//
// Configurable portion
//

#define CARRIER         "Verizon"
#define MLB_SERIAL      "C0714156KB0DQ5MB"
#define REGION_INFO     "LL/A"
#define DATA_TYPE       "3_5G"
#define DEVICE_UDID     "4a5a5fe4eebdb5a11c6d6a7fce4795e914769802"
#define SIGNAL_STRENGTH 30
#define FIRMWARE_VERSION "3.14.01E"
#define IMEI             "010113006310121"
#define ICCID            "310090521813935"
#define IMSI             "8901090382521813935"
#define MEID             "A100001AEF8D32"
#define SubscriberId     "2062760895"


//
// Do not edit anything below.
//

#ifndef __in
#define __in
#endif

#ifndef __out
#define __out
#endif

#ifndef __optional
#define __optional
#endif

#ifndef __inout
#define __inout
#endif

#define BUFFER_SIZE     256

//
// Windowsy types follow.
//

typedef char CHAR, *PCHAR, CCHAR, *LPCHAR;
typedef void *PVOID, *LPVOID;
typedef int INT, *PINT, *LPINT;
typedef size_t SIZE_T;
#define VOID void
#define CONST const

//
// Hook API type definitions
//

extern void NSLog(CFStringRef format, ...); 

typedef struct _CORE_TELEPHONY_ERROR_STATUS {
  INT _field1;
  INT _field2;
} CORE_TELEPHONY_ERROR_STATUS, *PCORE_TELEPHONY_ERROR_STATUS;

typedef
CFTypeRef
(*PMG_COPY_ANSWER_ROUTINE)(
    __in CFStringRef KeyToCopy
    );
    
typedef
CFTypeRef
(*PIO_REGISTRY_ENTRY_CREATE_CF_PROPERTY)(
    __in PVOID Entry,
    __in CFStringRef Key,
    __in CFAllocatorRef Allocator,
    __in PVOID Options
    );

typedef
INT
(*PSYSCTL_BY_NAME)(
    __in const char *name,
    __in void *oldp,
    __in size_t *oldlenp,
    __in void *newp,
    __in size_t newlen
    );
    
typedef
CFPropertyListRef
(*PLOCKDOWN_COPY_VALUE)(
    __in PVOID LockdownConnection,
    __in CFStringRef Domain,
    __in CFStringRef Key
    );

typedef 
PINT
(*CT_SERVER_COPY_FIRMWARE_VERSION)(
    PCORE_TELEPHONY_ERROR_STATUS Status,
    PVOID Connection,
    CFStringRef *FirmwareVersion
    );
    
typedef 
PINT
(*CT_SERVER_COPY_MOBILE_EQUIPMENT_INFO)(
    PCORE_TELEPHONY_ERROR_STATUS Status,
    PVOID Connection,
    CFMutableDictionaryRef *Dictionary
    );
    
typedef 
PINT
(*CT_SERVER_COPY_MOBILE_IDENTITY)(
    PCORE_TELEPHONY_ERROR_STATUS Status,
    PVOID Connection,
    CFStringRef *Imei
    );
    
#define DYLD_INTERPOSE(_replacment,_replacee) \
   __attribute__((used)) static struct{ const void* replacment; const void* replacee; } _interpose_##_replacee \
            __attribute__ ((section ("__DATA,__interpose"))) = { (const void*)(unsigned long)&_replacment, (const void*)(unsigned long)&_replacee };
            
//
// telephony.c
//

CFStringRef
CTRegistrationCopyLocalizedOperatorName(
    VOID
    );

CFStringRef
CTRegistrationCopyOperatorName(
    VOID
    );
    
CFStringRef
CTRegistrationCopyAbbreviatedOperatorName(
    VOID
    );

CFNumberRef
CTGetSignalStrength(
    VOID
    );

CFStringRef
CTRegistrationGetStatus(
    VOID
    );
    
CFStringRef
CTRegistrationGetDataIndicator(
    VOID
    );

CFStringRef
CTSettingCopyMyPhoneNumber(
    VOID
    );

CFNumberRef
CTIndicatorsGetSignalStrength(
    __in INT Parameter1,
    __in INT Parameter2,
    __in INT Parameter3
    );

CFStringRef
CTSIMSupportGetSIMStatus(
    VOID
    );

CFStringRef
CTSIMSupportGetSIMTrayStatus(
    VOID
    );

PINT
_CTServerConnectionCopyFirmwareVersion(
    PCORE_TELEPHONY_ERROR_STATUS Status,
    PVOID Connection,
    CFStringRef *FirmwareVersion
    );

PINT
_CTServerConnectionCopyMobileEquipmentInfo(
    PCORE_TELEPHONY_ERROR_STATUS Status,
    PVOID Connection,
    CFMutableDictionaryRef *Dictionary
    );

PINT
_CTServerConnectionCopyMobileIdentity(
    PCORE_TELEPHONY_ERROR_STATUS Status,
    PVOID Connection,
    CFStringRef *Imei
    );

//
// sysctl.c
//

int
sysctlbyname(
    __in const char *name,
    __in void *oldp,
    __in size_t *oldlenp,
    __in void *newp,
    __in size_t newlen
    );

//
// lockdown.c
//

CFTypeRef
lockdown_copy_value(
    __in PVOID LockdownConnection,
    __in CFStringRef Domain,
    __in CFStringRef Key
    );

//
// iokit.c
//

CFTypeRef
IORegistryEntryCreateCFProperty(
    __in PVOID Entry,
    __in CFStringRef Key,
    __in CFAllocatorRef Allocator,
    __in PVOID Options
    );

//
// gestalt.c
//

CFTypeRef
MGCopyAnswer(
    __in CFStringRef KeyToCopy
    );
    
#endif // _VOODOO_
