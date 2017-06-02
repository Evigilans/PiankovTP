//
//  ViewController.m
//  Lab8_1_1
//
//  Created by Admin on 07.05.17.
//  Copyright (c) 2017 Egor. All rights reserved.
//

#import "ViewController.h"
#import "Record.h"
#import "AppDelegate.h"
#import "FlightsViewController.h"

@interface ViewController ()
{
    int isCity;
    MKPointAnnotation *annotationFrom;
    MKPointAnnotation *annotationTo;
}

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    
    UILongPressGestureRecognizer *longPressGesture =
    [[UILongPressGestureRecognizer alloc] initWithTarget:self
                                                  action:@selector(handleLongPressGesture:)];
    [self.map addGestureRecognizer:longPressGesture];
}

-(void)handleLongPressGesture:(UIGestureRecognizer*)sender
{
    if (sender.state == UIGestureRecognizerStateEnded)
    {
        CGPoint point = [sender locationInView:self.map];
        CLGeocoder *geocoder = [[CLGeocoder alloc] init];
        CLLocationCoordinate2D coord = [self.map convertPoint:point
                                         toCoordinateFromView:self.map];
        CLLocation *location = [[CLLocation alloc]
                                initWithLatitude:coord.latitude longitude:coord.longitude];
        [geocoder reverseGeocodeLocation:location completionHandler:^(NSArray *placemarks, NSError *error)
         {
             if (error)
             {
                 NSLog(@"Geocode failed with error: %@", error);
                 return;
             }
             for (CLPlacemark * placemark in placemarks) {
                 [self setAnnotationToMap:isCity :placemark.locality
                                         :coord];
             }
         }];
    }
}

-(void)setAnnotationToMap:(int)type :(NSString *)title
                         :(CLLocationCoordinate2D)coordinate
{
    if (type == 0) {
        [_map removeAnnotation:annotationFrom];
        annotationFrom = [[MKPointAnnotation alloc] init];
        annotationFrom.title = title;
        annotationFrom.coordinate = coordinate;
        [_map addAnnotation:annotationFrom];
        self.cityFrom.text = title;
    }
    else
    {
        [_map removeAnnotation:annotationTo];
        annotationTo = [[MKPointAnnotation alloc] init];
        annotationTo.title = title;
        annotationTo.coordinate = coordinate;
        [_map addAnnotation:annotationTo];
        self.cityTo.text = title;
    }
}

-(void)textFieldDidBeginEditing:(UITextField *)textField
{
    if (textField == self.cityFrom)
        isCity = 0;
    else if (textField == self.cityTo)
        isCity = 1;
    [textField resignFirstResponder];
}


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)showFlights:(id)sender {
    /*AppDelegate *appDelegate = [UIApplication sharedApplication].delegate;
    NSArray *flights = [appDelegate getAllFlights];
    for(Record *record in flights)
    {
        if([self.cityFrom.text isEqualToString:record.cityFrom] && [self.cityTo.text isEqualToString:record.cityTo])
        {
            FlightViewController *flightView =[[FlightViewController alloc] initWithNibName:@"FlightViewController" bundle:[NSBundle mainBundle]];
            [flightView showFlight:record];
            flightView.view.backgroundColor = [UIColor whiteColor];
            [[[[UIApplication sharedApplication] keyWindow] rootViewController] presentViewController:flightView animated:NO completion: nil];
            
        }
    }*/
    

    FlightsViewController *flightView =[[FlightsViewController alloc] initWithCities:self.cityFrom.text cityTo:self.cityTo.text];
    flightView.view.backgroundColor = [UIColor whiteColor];
    [self presentViewController:flightView animated:YES completion: nil];
    
}

- (IBAction)isCityFrom:(id)sender {
    isCity = 0;
}

- (IBAction)isCityTo:(id)sender {
    isCity = 1;
}

@end
