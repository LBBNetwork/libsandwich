MODELID		:= _MUSCLENERD_IPHONE_4S
ARM-CC		:= arm-apple-darwin10-llvm-gcc-4.2
ARM-CFLAGS	:= -dynamiclib -isysroot /Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS5.0.sdk -Fbinaries/System/Library/PrivateFrameworks/ -c -I include/ -I include/SAObjects/ -I include/Assistant -I. -g -D$(MODELID)
ARM-LDCFLAGS	:= -fconstant-cfstrings -dynamiclib -Wall -multiply_defined suppress -isysroot /Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS5.0.sdk  /Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS5.0.sdk/usr/lib/libMobileGestalt.dylib -framework IOKit -framework CoreTelephony -framework CoreFoundation -framework SAObjects  -lobjc -Fbinaries/System/Library/PrivateFrameworks -framework Foundation -framework AppSupport /Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS5.0.sdk/usr/lib/liblockdown.dylib -g -framework GraphicsServices
OBJS		:= siri_auth.o gestalt.o iokit.o sysctl.o telephony.o lockdown.o
LDID		:= ldid
DYLIB		:= libsandwich.dylib
DYLIB_SIMPLE	:= libsandwich.siri_only.dylib

all: libsandwich.siri_only.dylib libsandwich.dylib

libsandwich.siri_only.dylib: siri_auth.o Makefile
	@echo Linking $(DYLIB_SIMPLE)...
	@$(ARM-CC) siri_auth.o $(ARM-LDCFLAGS) -o $(DYLIB_SIMPLE)
	@echo Fake-codesigning $(DYLIB_SIMPLE)...
	@$(LDID) -S $(DYLIB_SIMPLE)

libsandwich.dylib: $(OBJS) Makefile
	@echo Linking $(DYLIB)...
	@$(ARM-CC) $(OBJS) $(ARM-LDCFLAGS) -o $(DYLIB)
	@echo Fake-codesigning $(DYLIB)...
	@$(LDID) -S $(DYLIB)

%.o : %.m
	@echo Compiling $<
	@$(ARM-CC) $(ARM-CFLAGS) -c $<

%.o : %.c
	@echo Compiling $<
	@$(ARM-CC) $(ARM-CFLAGS) -c $<

clean:
	@echo Deleting "$(DYLIB) $(OBJS)"...
	@rm $(DYLIB) $(OBJS) $(DYLIB_SIMPLE)

me:
	@true

a:
	@true

sandwich:
	@[ -w /etc/master.passwd ] && echo "Okay." || echo "What? Make it yourself."

