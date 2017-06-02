//
//  ViewController.swift
//  iShop
//
//  Created by Admin on 26.05.17.
//  Copyright (c) 2017 Egor. All rights reserved.
//

import UIKit
import MapKit

class ViewController: UIViewController {
    
    @IBOutlet weak var segmentedControl: UISegmentedControl!
    @IBOutlet weak var login: UITextField!
    @IBOutlet weak var email: UITextField!
    @IBOutlet weak var pass: UITextField!
    @IBOutlet weak var repPass: UITextField!
    @IBOutlet weak var agree: UISwitch!
    @IBOutlet var regView: UIView!
    @IBOutlet weak var enterView: UIView!
    @IBOutlet weak var enterLogin: UITextField!
    @IBOutlet weak var enterPass: UITextField!
    @IBOutlet weak var ут: UIView!
    @IBOutlet weak var regLabel: UILabel!
    @IBOutlet weak var enterLabel: UILabel!
    @IBOutlet weak var order: UIButton!
    
    @IBOutlet weak var map: MKMapView!
    override func viewDidLoad() {
        super.viewDidLoad()
        self.items = loadPlist()
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
    }
    
    @IBAction func register(sender: AnyObject) {
        if (!login.text.isEmpty && !pass.text.isEmpty && pass.text == repPass.text && !email.text.isEmpty && agree.enabled == true) {
            let users = NSUserDefaults.standardUserDefaults()
            users.setObject(login.text, forKey: "login")
            users.setObject(pass.text, forKey: "pass")
            users.setObject(email.text, forKey: "email")
            self.regLabel.text = "Успешная регистрация!";
        } else {
            self.regLabel.text = "Проверьте данные!";
        }
    }

    @IBAction func indexChanged(sender: UISegmentedControl) {
        switch segmentedControl.selectedSegmentIndex
        {
        case 0:
            enterView.hidden = false;
        case 1:
            enterView.hidden = true;

        default:
            break;
        }
    }
    
    @IBAction func enter(sender: AnyObject) {
        let users = NSUserDefaults.standardUserDefaults()
        if (users.objectForKey("login")?.isEqualToString(enterLogin.text).boolValue == true && users.objectForKey("pass")?.isEqualToString(enterPass.text).boolValue == true) {
            performSegueWithIdentifier("Catalog", sender: nil)
        } else {
            self.enterLabel.text = "Проверьте данные!";
        }
    }
    
    @IBAction func order(sender: AnyObject) {
        performSegueWithIdentifier("Map", sender:
            nil)
    }
    
    @IBAction func backToMenu(sender: AnyObject) {
        performSegueWithIdentifier("Back", sender:
            nil)
    }
    
    @IBAction func exit(sender: AnyObject) {
        exit(0);
    }
    
    @IBOutlet weak var addressField: UITextField!
    func setAnnotationToMap(title: String, coordinate : CLLocationCoordinate2D)
    {
        map.removeAnnotations(map.annotations)
        var annotatiion = MKPointAnnotation()
        annotatiion.title = title
        annotatiion.coordinate = coordinate
        map.addAnnotation(annotatiion)
        self.addressField.text = title;
    }
    
    @IBAction func handleLongPressGesture(sender: UILongPressGestureRecognizer) {
        if (sender.state == UIGestureRecognizerState.Ended)
        {
            var point = sender.locationInView(self.map)
            var geocoder = CLGeocoder()
            var coord = self.map.convertPoint(point, toCoordinateFromView: self.map)
            var location = CLLocation(latitude: coord.latitude, longitude: coord.longitude)
            geocoder.reverseGeocodeLocation(location, completionHandler:{ (placemarks, error) in
                if (error != nil) {
                    print("Geocode failed with error: \(error)");
                    return;
                }
                
                for placemark in placemarks as [CLPlacemark] {
                    self.setAnnotationToMap(placemark.locality, coordinate: coord);
                }
            })
        }
    }
    
    @IBOutlet weak var table: UITableView!
    
    @IBOutlet weak var descriptionField: UITextView!
    
    var items = [[String:String]]()
    
    func loadPlist()->[[String:String]]
    {
        let path = NSBundle.mainBundle().pathForResource("iPlist", ofType: "plist")
        return NSArray(contentsOfURL: NSURL(fileURLWithPath: path!)!) as [[String:String]]
    }
    
}

extension ViewController:UITableViewDataSource,UITableViewDelegate
{
    func tableView(tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return self.items.count
    }
    
    func tableView(tableView: UITableView, cellForRowAtIndexPath indexPath: NSIndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCellWithIdentifier("iCell") as UITableViewCell
        
        let item = items[indexPath.row]
        cell.textLabel?.text = item["title"]
        cell.detailTextLabel?.text = item["description"]
        cell.imageView?.image = UIImage(named: item["image"]!)
        
        return cell
    }
    
    func tableView(tableView: UITableView, heightForRowAtIndexPath indexPath: NSIndexPath) -> CGFloat {
        return 120
    }
    
    func tableView(tableView: UITableView, didSelectRowAtIndexPath indexPath: NSIndexPath) {
        let item = items[indexPath.row]
        descriptionField.text = item["description"]
        order.enabled = true;

    }
    
    
}


