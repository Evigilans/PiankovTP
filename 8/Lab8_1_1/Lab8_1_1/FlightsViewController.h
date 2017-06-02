//
//  FlightsViewController.h
//  Lab8_1_1
//
//  Created by Admin on 07.05.17.
//  Copyright (c) 2017 Egor. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "Record.h"
#import "AppDelegate.h"

@interface FlightsViewController : UIViewController <UITableViewDataSource, UITableViewDelegate>

-(id)initWithCities:(NSString*)cityFrom cityTo: (NSString*)cityTo;
@end
