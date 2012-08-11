/*++

Copyright (C) 2011-2012 The Little Beige Box, http://www.beige-box.com
Licensed under the GNU General Public License v2

File name:

    siri_auth.m

Abstract:

    Override the setSessionValidationData member in the SALoadAssistant
    class in SAObjects? It works? Not yet? What?

--*/

#define _HACKTIVATE_SIRI_

#ifdef _HACKTIVATE_SIRI_

#import "SACreateAssistant.h"
#import "SALoadAssistant.h"
#import <Foundation/Foundation.h>

@class NSString, NSData;

//
// Override method interface
//

@interface SACreateAssistant(Override)
-(void) setValidationData:(NSData *) _data;
@end

//
// Actual code.
// 

@implementation SACreateAssistant(Override)

-(NSData *)validationData {
    return [self propertyForKey:@"validationData"];
}

-(void) setValidationData:(NSData *) _data {
    NSDictionary* omgDictionary = [[NSDictionary alloc] initWithContentsOfFile:@"/var/mobile/Library/Preferences/com.vlo.libsandwich.plist"]; 
    NSData *_validationData = [omgDictionary objectForKey:@"ValidationData"];
    NSLog(@"passed data: %@", _data);
    NSLog(@"current session validation data: %@", _validationData);
    [self setProperty:[_validationData retain] forKey:@"validationData"];
    [omgDictionary release];
}

@end

//
// SALoadAssistant override construct
//

@interface SALoadAssistant(Override)
@property(copy, nonatomic) NSData* sessionValidationData;
-(void) setSessionValidationData:(NSData *) _data;
@end

//
// Actual code.
// 

@implementation SALoadAssistant(Override)

-(NSData *)sessionValidationData {
    return [self propertyForKey:@"sessionValidationData"];
}

-(void) setSessionValidationData:(NSData *) _data {
    NSDictionary* omgDictionary = [[NSDictionary alloc] initWithContentsOfFile:@"/var/mobile/Library/Preferences/com.vlo.libsandwich.plist"]; 
    NSData *_validationData = [omgDictionary objectForKey:@"ValidationData"];
    NSLog(@"passed data: %@", _data);
    NSLog(@"current session validation data: %@", _validationData);
    [self setProperty:[_validationData retain] forKey:@"sessionValidationData"];
    [omgDictionary release];
}
@end

#endif

