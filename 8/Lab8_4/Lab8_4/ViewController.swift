//
//  ViewController.swift
//  Lab8_4
//
//  Created by Admin on 09.05.17.
//  Copyright (c) 2017 Egor. All rights reserved.
//

import UIKit

class ViewController: UIViewController {

    @IBOutlet weak var table: UITableView!
    
    @IBOutlet weak var descrField: UITextView!
    
    var items = [[String:String]]()
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
        
        self.items = loadPlist()
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }

    func loadPlist()->[[String:String]]
    {
        let path = NSBundle.mainBundle().pathForResource("Property List", ofType: "plist")
        return NSArray(contentsOfURL: NSURL(fileURLWithPath: path!)!) as [[String:String]]
    }
    
}

extension ViewController:UITableViewDataSource,UITableViewDelegate
{
    func tableView(tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return self.items.count
    }
    
    func tableView(tableView: UITableView, cellForRowAtIndexPath indexPath: NSIndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCellWithIdentifier("bookCell") as UITableViewCell
        
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
        descrField.text = item["description"]
        
    }
    
    
}

