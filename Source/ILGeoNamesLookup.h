//
//  ILGeoNamesLookup.h
//
//  Created by Claus Broch on 20/06/10.
//  Copyright 2010-2011 Infinite Loop. All rights reserved.
//
//  Redistribution and use in source and binary forms, with or without modification, are permitted
//  provided that the following conditions are met:
//
//  - Redistributions of source code must retain the above copyright notice, this list of conditions 
//    and the following disclaimer.
//  - Redistributions in binary form must reproduce the above copyright notice, this list of 
//    conditions and the following disclaimer in the documentation and/or other materials provided 
//    with the distribution.
//  - Neither the name of Infinite Loop nor the names of its contributors may be used to endorse or 
//    promote products derived from this software without specific prior written permission.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR 
//  IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND 
//  FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
//  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL 
//  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, 
//  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
//  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY 
//  WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//  
//
//  Use of the data is subject to the terms detailed on http://www.geonames.org/export/#terms
//

#import <Foundation/Foundation.h>

typedef enum {
	kILGeoNamesAuthorizationExceptionError = 10,
	kILGeoNamesRecordDoesNotExistError = 11,
	kILGeoNamesOtherError = 12,
	kILGeoNamesDatabaseTimeoutError = 13,
	kILGeoNamesInvalidParameterError = 14,
	kILGeoNamesNoResultsFoundError = 15,
	kILGeoNamesDuplicateExceptionError = 16,
	kILGeoNamesPostalCodeNotFoundError = 17,
	kILGeoNamesDailyCreditLimitExceededError = 18,
	kILGeoNamesHourlyCreditLimitExceededError = 19,
	kILGeoNamesWeeklyCreditLimitExceededError = 20,
	kILGeoNamesServerOverload = 22
} GeoNamesError;

extern NSString *const kILGeoNamesErrorDomain;

@protocol ILGeoNamesLookupDelegate;

@interface ILGeoNamesLookup : NSObject {
	@private
    NSURLConnection		*dataConnection;
    BOOL				done;
    NSMutableData		*dataBuffer;
	NSString			*userID;
    id <ILGeoNamesLookupDelegate> delegate;
	
}

@property (nonatomic, assign) id <ILGeoNamesLookupDelegate> delegate;

// Initialize a new instance with the user ID obtained from Geonames.org
- (id)initWithUserID:(NSString*)userID;

// Query the geonames.org service for the name of the place near the given position (WGS84)
- (void)findNearbyPlaceNameForLatitude:(double)latitude longitude:(double)longitude;

// Query the geonames.org service for a number of entries matching the query
- (void)search:(NSString*)query maxRows:(NSInteger)maxRows startRow:(NSUInteger)startRow language:(NSString*)langCode;

// Cancel any outstanding request;
- (void)cancel;

@end

// Protocol for the parser to communicate with its delegate.
@protocol ILGeoNamesLookupDelegate <NSObject>

@optional

// Called by the parser when starting and stopping network activity
- (void)geoNamesLookup:(ILGeoNamesLookup *)handler networkIsActive:(BOOL)isActive;
// Called by the parser in the case of an error.
- (void)geoNamesLookup:(ILGeoNamesLookup *)handler didFailWithError:(NSError *)error;
// Called by the parser when parsing is finished parsing current weather.
- (void)geoNamesLookup:(ILGeoNamesLookup *)handler didFindGeoNames:(NSArray *)geoNames totalFound:(NSUInteger)total;

@end