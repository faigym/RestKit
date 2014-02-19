//
//  RKRoute.h
//  RestKit
//
//  Created by Blake Watters on 5/31/12.
//  Copyright (c) 2012 RestKit. All rights reserved.
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//  http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.
//

#import "RKHTTPUtilities.h"
#import "CSURITemplate.h"

/**
 The `RKRoute` class models a single routable path pattern in use by the application. A route can be combined with an `NSURL` base URL and interpolated with an object to produce a new fully hydrated URL object. Routes are always instantiated with a path pattern and metadata to provide for the subsequent identification of the defined route.

 There are three types of routes modeled by the RKRoute class:

 1. **Named Routes**: A named route represents a single path and optional request method within the application. The route is not affiliated with any particular class. For example, one might define a route with the name `@"airlines_list"` as a GET to the path '/airlines.json'.
 1. **Class Routes**: An class route represents a single path that is identified by object class and request method for which it is appropriate. For example, one might define a route for the class `RKArticle` for a POST to the path '/articles.json'.
 1. **Relationship Routes**: A relationship route represents a single path through which the relationship of a parent object can be manipulated. For example, given an `RKArticle` and `RKComment` class, one might define a relationship route for the `RKArticle` class's `@"comments"` relationship as pointing to a GET to the path `@"/articles/:articleID/comments".

 The RKRoute class is internally implemented as a class cluster and is not to be directly instantiated via alloc and init.

 @see RKRouter
 @see RKRouteSet
 */
@interface RKRoute : NSObject

///---------------------------
/// @name Instantiating Routes
///---------------------------

/**
 Creates and returns a new named route object with the given name, path pattern and method.

 @param name A unique identifying name for the route.
 @param URITemplateString A URI Template string describing the format of URL paths generated from the route.
 @param method The request method of the route. The method given must specify a single HTTP method to be used for requests using the route.
 @return A new named route object with the given name, path pattern and request method.
 @raise NSInvalidArgumentException Raised if the given HTTP request method is not an exact match of the RKHTTPMethod enum
 */
+ (instancetype)routeWithName:(NSString *)name URITemplateString:(NSString *)URITemplateString method:(RKHTTPMethodOptions)method;

/**
 Creates and returns a new class route object with the given object class, path pattern and method.

 @param objectClass The class that is represented by the route.
 @param URITemplateString A URI Template string describing the format of URL paths generated from the route.
 @param method The request method of the route. More than one method may be specified via a bitwise OR.
 @return A new class route object with the given object class, path pattern and request method.
 */
+ (instancetype)routeWithClass:(Class)objectClass URITemplateString:(NSString *)URITemplateString method:(RKHTTPMethodOptions)method;

/**
 Creates and returns a new relationship route object with the given relationship name, object class, path pattern and method.

 @param name The name of the relationship represented by the route.
 @param objectClass The class containing the relationship represented by the route.
 @param URITemplateString A URI Template string describing the format of URL paths generated from the route.
 @param method The request method of the route. More than one method may be specified via a bitwise OR.
 @return A new class route object with the given object class, path pattern and request method.
 */
+ (instancetype)routeWithRelationshipName:(NSString *)name objectClass:(Class)objectClass URITemplateString:(NSString *)URITemplateString method:(RKHTTPMethodOptions)method;

///---------------------------------
/// @name Accessing Route Attributes
///---------------------------------

/**
 The name of the receiver.

 The name is used to identify named and relationship routes and is always `nil` for object routes.
 */
@property (nonatomic, strong, readonly) NSString *name;

/**
 The object class of the receiver.

 Defines the class for which the route is appropriate. Always returns `nil` for named routes.
 */
@property (nonatomic, strong, readonly) Class objectClass;

/**
 The request method of the receiver.

 Appropriate for all route types. If the route is appropriate for any HTTP request method, then the `RKHTTPMethodAny` value is used.
 */
@property (nonatomic, assign, readonly) RKHTTPMethodOptions method;

/**
 The URI Template of the receiver.

 A URI Template that is expanded to construct a complete URL. Required and used by all route types.

 @see `SOCPattern`
 */
@property (nonatomic, strong, readonly) CSURITemplate *URITemplate;

/**
 A Boolean value that determines if the path pattern should be escaped when evaluated.

 *Default*: `NO`
 */
@property (nonatomic, assign) BOOL shouldEscapePath;

///-----------------------------
/// @name Inspecting Route Types
///-----------------------------

/**
 Determines if the receiver is a named route.

 @return YES if the receiver is a named route, else NO.
 */
- (BOOL)isNamedRoute;

/**
 Determines if the receiver is a class route.

 @return YES if the receiver is a class route, else NO.
 */
- (BOOL)isClassRoute;

/**
 Determines if the receiver is a relationship route.

 @return YES if the receiver is a relationship route, else NO.
 */
- (BOOL)isRelationshipRoute;

@end
