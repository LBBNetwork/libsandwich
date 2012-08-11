/*++

Copyright (C) 2011-2012, The Little Beige Box, http://www.beige-box.com
Licensed under the GNU General Public License v2.

File name:

    sysctl.c

Abstract:

    Hook sysctlbyname.

--*/

#include <voodoo.h>

PSYSCTL_BY_NAME pSysctlbyname;

//
// This one has to be done like this because of header craziness...
//

int
_sysctlbyname(
    __in const char *name,
    __in void *oldp,
    __in size_t *oldlenp,
    __in void *newp,
    __in size_t newlen
    )
/*++

Routine Description:

    Return a value from the system sysctl repository nodes.

Arguments:

    name        - Oid to get.
    oldp        - Pointer to buffer to store data in.
    oldlenp     - Length of buffer.
    newp        - Pointer to buffer for new Oid data.
    newlen      - Length of buffer.

Return Value:

    0 if successful, -1 if not.
    
--*/
{
    CHAR ModelData[] = MODEL_STRING;
    CHAR MachineData[] = MACHINE_STRING;
    INT ReturnValue = 0;
    
    //
    // Do we handle these oids?
    //
    
    if(oldp && oldlenp) {
        if(!strcmp(name, "hw.model")) {
            strlcpy(oldp, ModelData, sizeof(ModelData));
        } else if(!strcmp(name, "hw.machine")) {
            strlcpy(oldp, MachineData, sizeof(ModelData));
        }
    } else if(!oldp && oldlenp) {
        if(!strcmp(name, "hw.model")) {
            *oldlenp = sizeof(ModelData);
        } else if(!strcmp(name, "hw.machine")) {
            *oldlenp = sizeof(MachineData);
        }
    } else {
        ReturnValue = sysctlbyname(name, oldp, oldlenp, newp, newlen);
    }

    return ReturnValue;
}
DYLD_INTERPOSE(_sysctlbyname, sysctlbyname)