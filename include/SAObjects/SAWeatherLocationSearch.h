/**
 * This header is generated by class-dump-z 0.2a.
 * class-dump-z is Copyright (C) 2009 by KennyTM~, licensed under GPLv3.
 *
 * Source: /System/Library/PrivateFrameworks/SAObjects.framework/SAObjects
 */

#import "SABaseClientBoundCommand.h"

@class NSURL, NSString;

@interface SAWeatherLocationSearch : SABaseClientBoundCommand {
}
@property(copy, nonatomic) NSString* locationId;
@property(copy, nonatomic) NSURL* identifier;
@property(copy, nonatomic) NSURL* targetAppId;
+ (id)locationSearch;
+ (id)locationSearchWithDictionary:(id)dictionary context:(id)context;
- (id)encodedClassName;
- (BOOL)requiresResponse;
- (id)groupIdentifier;
@end
