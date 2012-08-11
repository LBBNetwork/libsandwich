libsandwich 1.0.0.0
===================

Previously known as libvoodoogestalt, libsandwich allows you to modify
lower level details of your iDevice using dyld function interposition.
The dylib is sandwiched between any executable, overriding functions as
necessary.

Compiling
---------

    make

Just as easy as that. Make sure to have your iOS 5 SDK installed in /Developer
and in the usual location in that folder, and make sure to have the iPhone4S
dyld cache binaries (dumped using dyld_decache) in binaries/. Also make sure
to compile ldid.

A ldid mach-o x86_64 binary is available in the repo, copy it to /usr/bin/
if you wish.

Usage
-----

Make sure to have the dylib on the root filesystem of the target iDevice,
then export the following environment variables for the target process:

    DYLD_INSERT_LIBRARIES=/usr/lib/libsandwich.dylib
    DYLD_FORCE_FLAT_NAMESPACE=1

Some applications will crash, some will not. You will get interesting results
based on whatever you do!

What's done and not done
------------------------

Done:

* Serial number hooking (MLB/Real)
* Model identifier hooking
* Telephony carrier hooks
* Telephony modem service hooks
* Lockdownd hacktivation
* Siri activation (somewhat done actually)

Not done:

* Telephony IMEI/ICCID/IMSI dictionary hooks

License
-------

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

Please read LICENCE.txt to read the full GPL-4.0 licence. 

