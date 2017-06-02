//
//  ViewController.m
//  7-1
//
//  Created by Admin on 19.05.17.
//  Copyright (c) 2017 Egor. All rights reserved.
//

#import "ViewController.h"

@interface ViewController ()
@property (weak, nonatomic) IBOutlet UIImageView *imageView;
@property (weak, nonatomic) IBOutlet UITextField *widthField;
@property (weak, nonatomic) IBOutlet UITextField *redField;
@property (weak, nonatomic) IBOutlet UITextField *greenField;
@property (weak, nonatomic) IBOutlet UITextField *blueField;
@property (weak, nonatomic) IBOutlet UITextField *alphaField;
@property (weak, nonatomic) IBOutlet UITextField *fileField;
@property CGPoint lastPoint;

@end

@implementation ViewController
- (IBAction)saveImage:(id)sender {
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    NSString *basePath = ([paths count] > 0) ? [paths objectAtIndex:0] : nil;
    
    UIImage *imageToSave = [[self imageView] image];
    NSData *binaryImageData = UIImagePNGRepresentation(imageToSave);
    
    [binaryImageData writeToFile:[basePath stringByAppendingPathComponent:[[self fileField] text]] atomically:YES];
    
}

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

-(void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
    UITouch *touch = [touches anyObject];
    [self setLastPoint:[touch locationInView:self.imageView]];
}

-(void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
    UITouch *touch = [touches anyObject];
    CGPoint currentPoint = [touch locationInView:self.imageView];
    UIGraphicsBeginImageContext(self.imageView.frame.size);
    CGRect drawRect = CGRectMake(0.0f, 0.0f, self.imageView.frame.size.width, self.imageView.frame.size.height);
    [[[self imageView] image] drawInRect:drawRect];
    CGContextSetLineCap(UIGraphicsGetCurrentContext(), kCGLineCapRound);
    CGContextSetLineWidth(UIGraphicsGetCurrentContext(), [[_widthField text] floatValue]);
    CGContextSetRGBStrokeColor(UIGraphicsGetCurrentContext(), [[_redField text] floatValue], [[_greenField text] floatValue], [[_blueField text] floatValue], [[_alphaField text] floatValue]);
    CGContextBeginPath(UIGraphicsGetCurrentContext());
    CGContextMoveToPoint(UIGraphicsGetCurrentContext(), _lastPoint.x, _lastPoint.y);
    CGContextAddLineToPoint(UIGraphicsGetCurrentContext(), currentPoint.x, currentPoint.y);
    CGContextStrokePath(UIGraphicsGetCurrentContext());
    [[self imageView] setImage:UIGraphicsGetImageFromCurrentImageContext()];
    UIGraphicsEndImageContext();
    _lastPoint = currentPoint;
}

@end
