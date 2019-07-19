//
//  NasaObject.h
//  NSNotificationCenter
//
//  Created by Carlos Santiago Cruz on 7/15/19.
//  Copyright © 2019 Carlos Santiago Cruz. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface NasaObject : NSObject

@property (strong, nonatomic) NSString *copyright;
@property (strong, nonatomic) NSString *date;
@property (strong, nonatomic) NSString *explanation;
@property (strong, nonatomic) NSString *hdurl;
@property (strong, nonatomic) NSString *media_type;
@property (strong, nonatomic) NSString *service_version;
@property (strong, nonatomic) NSString *title;
@property (strong, nonatomic) NSString *urlImage;

@end

NS_ASSUME_NONNULL_END
