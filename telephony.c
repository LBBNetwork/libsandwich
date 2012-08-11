/*++

Copyright (C) 2011-2012, The Little Beige Box, http://www.beige-box.com
Licensed under the GNU General Public License v2.

File name:

    telephony.c

Abstract:

    Override CoreTelephony's functions.

--*/

#include <voodoo.h>

CT_SERVER_COPY_FIRMWARE_VERSION pCTServerConnectionCopyFirmwareVersion;
CT_SERVER_COPY_MOBILE_EQUIPMENT_INFO  pCTServerConnectionCopyMobileEquipmentInfo;
CT_SERVER_COPY_MOBILE_IDENTITY pCTServerConnectionCopyMobileIdentity;

CFNumberRef kCTIndicatorsGradedSignalStrength;
CFNumberRef kCTIndicatorsSignalStrength;
CFNumberRef kCTIndicatorsRawSignalStrength;

//
// Sparsely documented functions follow.
//

CFStringRef
_CTRegistrationCopyLocalizedOperatorName(
    VOID
    )
{
    return CFSTR(CARRIER);
}
DYLD_INTERPOSE(_CTRegistrationCopyLocalizedOperatorName, CTRegistrationCopyLocalizedOperatorName)

CFStringRef
_CTRegistrationCopyOperatorName(
    VOID
    )
{
    return CFSTR(CARRIER);
}
DYLD_INTERPOSE(_CTRegistrationCopyOperatorName, CTRegistrationCopyOperatorName)

CFStringRef
_CTRegistrationCopyAbbreviatedOperatorName(
    VOID
    )
{
    return CFSTR(CARRIER);
}
DYLD_INTERPOSE(_CTRegistrationCopyAbbreviatedOperatorName, CTRegistrationCopyAbbreviatedOperatorName)

CFNumberRef
_CTGetSignalStrength(
    VOID
    )
{
    INT SignalStrength[3] = {2, -100, 20};
    INT Parameter2 = 20;
    
    return CFNumberCreate(kCFAllocatorDefault, kCFNumberSInt32Type, &Parameter2);
}
DYLD_INTERPOSE(_CTGetSignalStrength, CTGetSignalStrength)

CFStringRef
_CTRegistrationGetStatus(
    VOID
    )
{
    return CFSTR("kCTRegistrationStatusRegisteredHome");
}
DYLD_INTERPOSE(_CTRegistrationGetStatus, CTRegistrationGetStatus)

CFStringRef
_CTRegistrationGetDataIndicator(
    VOID
    )
{
    return CFSTR("kCTRegistrationDataIndicator" DATA_TYPE);
}
DYLD_INTERPOSE(_CTRegistrationGetDataIndicator, CTRegistrationGetDataIndicator)

CFStringRef
_CTSettingCopyMyPhoneNumber(
    VOID
    )
{
    return CFSTR("972-364-4415");
}
DYLD_INTERPOSE(_CTSettingCopyMyPhoneNumber, CTSettingCopyMyPhoneNumber)

CFNumberRef
_CTIndicatorsGetSignalStrength(
    __in INT Parameter1,
    __in INT Parameter2,
    __in INT Parameter3
    )
{
    INT SignalStrength[3] = {2, -100, 20};
    Parameter2 = 20;
    
    kCTIndicatorsGradedSignalStrength = CFNumberCreate(kCFAllocatorDefault, kCFNumberSInt32Type, &SignalStrength[0]);
    kCTIndicatorsSignalStrength = CFNumberCreate(kCFAllocatorDefault, kCFNumberSInt32Type, &SignalStrength[1]);
    kCTIndicatorsRawSignalStrength = CFNumberCreate(kCFAllocatorDefault, kCFNumberSInt32Type, &SignalStrength[2]);
    
    return CFNumberCreate(kCFAllocatorDefault, kCFNumberSInt32Type, &Parameter2);
}
DYLD_INTERPOSE(_CTIndicatorsGetSignalStrength, CTIndicatorsGetSignalStrength)

CFStringRef
_CTSIMSupportGetSIMStatus(
    VOID
    )
{
    return CFSTR("kCTSIMSupportSIMStatusReady");
}
DYLD_INTERPOSE(_CTSIMSupportGetSIMStatus, CTSIMSupportGetSIMStatus)

CFStringRef
_CTSIMSupportGetSIMTrayStatus(
    VOID
    )
{
    return CFSTR("kCTSIMSupportSIMTrayInsertedWithSIM");
}
DYLD_INTERPOSE(_CTSIMSupportGetSIMTrayStatus, CTSIMSupportGetSIMTrayStatus)

PINT
__CTServerConnectionCopyFirmwareVersion(
    PCORE_TELEPHONY_ERROR_STATUS Status,
    PVOID Connection,
    CFStringRef *FirmwareVersion
    )
{
    PINT Data;

    Data = _CTServerConnectionCopyFirmwareVersion(Status, Connection, FirmwareVersion);
    *FirmwareVersion = CFStringCreateWithCString(0, FIRMWARE_VERSION, kCFStringEncodingMacRoman);
    return Data;
}
DYLD_INTERPOSE(__CTServerConnectionCopyFirmwareVersion, _CTServerConnectionCopyFirmwareVersion)

extern CFStringRef kCTMobileEquipmentInfoIMEI, kCTMobileEquipmentInfoICCID, kCTMobileEquipmentInfoIMSI, kCTMobileEquipmentInfoMEID;
extern CFStringRef kCTMobileEquipmentInfoCurrentSubscriberId, kCTMobileEquipmentInfoCurrentMobileId, kCTMobileEquipmentInfoMIN;

PINT
__CTServerConnectionCopyMobileEquipmentInfo(
    PCORE_TELEPHONY_ERROR_STATUS Status,
    PVOID Connection,
    CFMutableDictionaryRef *Dictionary
    )
{
    PINT Data;
    INT i;
    CFStringRef Keys[7];
    CFStringRef Values[7];
    CFStringRef FirmwareVersion;
    
    Keys[0] = kCTMobileEquipmentInfoIMEI;
    Keys[1] = kCTMobileEquipmentInfoICCID;
    Keys[2] = kCTMobileEquipmentInfoIMSI;
    Keys[3] = kCTMobileEquipmentInfoMEID;
    Keys[4] = kCTMobileEquipmentInfoCurrentMobileId;
    Keys[5] = kCTMobileEquipmentInfoMIN;
    Keys[6] = kCTMobileEquipmentInfoCurrentSubscriberId;
    
    Values[0] = CFSTR(IMEI);
    Values[1] = CFSTR(ICCID);
    Values[2] = CFSTR(IMSI);
    Values[3] = CFSTR(MEID);
    Values[4] = CFSTR(MEID);
    Values[5] = CFSTR(SubscriberId);
    Values[6] = CFSTR(SubscriberId);
     
    Data = _CTServerConnectionCopyMobileEquipmentInfo(Status, Connection, Dictionary);

    //
    // evil hack
    //

    Data = _CTServerConnectionCopyFirmwareVersion(Status, Connection, &FirmwareVersion);

    *Dictionary = CFDictionaryCreateMutable(NULL, 0, &kCFTypeDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks);
    
    for(i = 0; i < 7; i++)
        CFDictionaryAddValue(*Dictionary, Keys[i], Values[i]); 

    return Data;
}
DYLD_INTERPOSE(__CTServerConnectionCopyMobileEquipmentInfo, _CTServerConnectionCopyMobileEquipmentInfo)

PINT
__CTServerConnectionCopyMobileIdentity(
    PCORE_TELEPHONY_ERROR_STATUS Status,
    PVOID Connection,
    CFStringRef *Imei
    )
{
    PINT Data;

    Data = _CTServerConnectionCopyMobileIdentity(Status, Connection, Imei);

    *Imei = CFStringCreateWithCString(0, IMEI, kCFStringEncodingMacRoman);
    return Data;
}
DYLD_INTERPOSE(__CTServerConnectionCopyMobileIdentity, _CTServerConnectionCopyMobileIdentity)
