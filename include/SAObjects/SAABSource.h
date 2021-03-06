/**
 * This header is generated by class-dump-z 0.2a.
 * class-dump-z is Copyright (C) 2009 by KennyTM~, licensed under GPLv3.
 *
 * Source: /System/Library/PrivateFrameworks/SAObjects.framework/SAObjects
 */

#import "SADomainObject.h"

@class NSNumber, NSString;

@interface SAABSource : SADomainObject {
}
@property(retain, nonatomic) NSNumber* remote;
@property(copy, nonatomic) NSString* accountName;
@property(copy, nonatomic) NSString* accountIdentifier;
+ (id)sourceWithDictionary:(id)dictionary context:(id)context;
+ (id)source;
- (void)updateUsingSet:(id)set add:(id)add remove:(id)remove;
- (id)encodedClassName;
- (id)groupIdentifier;
@end

