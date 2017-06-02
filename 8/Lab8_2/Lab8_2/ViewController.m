//
//  ViewController.m
//  Lab8_2
//
//  Created by Admin on 07.05.17.
//  Copyright (c) 2017 Egor. All rights reserved.
//

#import "ViewController.h"

@interface ViewController ()
@property (weak, nonatomic) IBOutlet UIView *regView;
@property (weak, nonatomic) IBOutlet UITextField *login;
@property (weak, nonatomic) IBOutlet UITextField *mail;
@property (weak, nonatomic) IBOutlet UITextField *pass;
@property (weak, nonatomic) IBOutlet UITextField *repPass;
@property (weak, nonatomic) IBOutlet UISwitch *accept;
@property (weak, nonatomic) IBOutlet UITextField *enterLogin;
@property (weak, nonatomic) IBOutlet UITextField *enterPass;
@property (weak, nonatomic) IBOutlet UIView *enterView;

@end

@implementation ViewController
- (IBAction)signUp:(id)sender {
    if (![_login.text isEqualToString:@""] && ![_pass.text isEqualToString:@""] && ![_mail.text isEqualToString:@""] && [_pass.text isEqualToString:_repPass.text] && [_accept isOn])
    {
        NSUserDefaults *user = [NSUserDefaults standardUserDefaults];
        [user setObject:_login.text forKey:@"login"];
        [user setObject:_pass.text forKey:@"pass"];
        //[self performSegueWithIdentifier:@"ClosedZone" sender:self];
    }

}
- (IBAction)enter:(id)sender {
    NSUserDefaults *user = [NSUserDefaults standardUserDefaults];
    if ([_enterLogin.text isEqualToString:(NSString*)[user objectForKey:@"login"]] && [_enterPass.text isEqualToString:(NSString*)[user objectForKey:@"pass"]])
    {
        [self performSegueWithIdentifier:@"ClosedZone" sender:self];
    }

}
- (IBAction)segment:(id)sender {
    UISegmentedControl *seg = (UISegmentedControl*)sender;
    if (seg.selectedSegmentIndex == 0)
    {
        _enterView.hidden = YES;
    }
    else
    {
        _enterView.hidden = NO;
    }
}

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    _enterView.hidden = YES;
    NSUserDefaults *user = [NSUserDefaults standardUserDefaults];
    if ([user objectForKey:@"login"] != nil && [user objectForKey:@"pass"] != nil)
    {
        [self performSegueWithIdentifier:@"ClosedZone" sender:self];
    }
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
