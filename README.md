An object that enables you to start and stop URL requests.

# NSURLConnection

- An object that enables you to start and stop URL requests.
- The NSURLConnection class provides convenience class methods to load URL requests both asynchronously using a callback block and synchronously.

# NSURLConnection can be used to download contents from a URL syncronously

- The sendSynchronousRequest:returninghResponse:error: class method of NSURLConnection, as its name implies, deals with synchronous calls.
- A synchronous call blocks its calling thread until the method returns.

# NSURLConnection can be used to download contents from a URL asyncronously

- An asynchronous call starts accessing and downloading the contents of a URL without blocking the calling thread.

# Content-type

- Content-type is known as a MIME type that indicates what kind of data an HTTP response contains.

# ViewController.m

![Screen Shot 2019-08-10 at 9 47 30 AM](https://user-images.githubusercontent.com/24994818/62823168-e75fb680-bb53-11e9-8be8-9ec6cc6fcf81.png)

``` objective-c
//
//  ViewController.m
//  NSNotificationCenter
//
//  Created by Carlos Santiago Cruz on 7/11/19.
//  Copyright © 2019 Carlos Santiago Cruz. All rights reserved.
//

#import "ViewController.h"

@interface ViewController ()
@property (weak, nonatomic) IBOutlet UILabel *titleLabel;
@property (weak, nonatomic) IBOutlet UIImageView *imageView;
@property (weak, nonatomic) IBOutlet UILabel *dateLabel;
@property (weak, nonatomic) IBOutlet UITextView *textViewExplanation;
@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    NSString *urlString = @"https://api.nasa.gov/planetary/apod?api_key=donTYCCXyjv1z6RfdxVqOa5IiFS8b6FagqVjEJLI";
    NSURL *url = [NSURL URLWithString:urlString];
    [[NSURLSession.sharedSession dataTaskWithURL:url completionHandler:^(NSData * _Nullable data,
                                                                         NSURLResponse * _Nullable response,
                                                                         NSError * _Nullable error) {
        NSLog(@"finishing fetching data");
        NSString *dummyString = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
        NSLog(@"%@", dummyString);
        
        NSError *serializationError;
        NSDictionary *nasaJSON = [NSJSONSerialization JSONObjectWithData:data
                                                            options:NSJSONReadingAllowFragments
                                                              error:&serializationError];
        if (serializationError) {
            NSLog(@"failed to serialize into JSON: %@", serializationError.description);
            return;
        }
        
        for (NSDictionary *itemNasaJSON in nasaJSON) {
            NSLog(@"itemNasaJSON: %@", itemNasaJSON);
        }
        
        NSString *dateValue = nasaJSON[@"date"];
        NSLog(@"%@", dateValue);
        NSString *explanationValue = nasaJSON[@"explanation"];
        NSLog(@"%@", explanationValue);
        
        // Display the information
        dispatch_async(dispatch_get_main_queue(),^{
            self.titleLabel.text = nasaJSON[@"title"];
            self.dateLabel.text = nasaJSON[@"date"];
            self.textViewExplanation.text = nasaJSON[@"explanation"];
            NSString *urlString = nasaJSON[@"url"];
            NSURL *url = [NSURL URLWithString:urlString];
            NSData *data = [[NSData alloc] initWithContentsOfURL:url];
            self.imageView.image = [[UIImage alloc] initWithData:data];
        });
    } ] resume ];
}

@end
```

# Console output

``` console
2019-08-10 09:51:00.237014-0500 NSNotificationCenter[2744:142870] finishing fetching data
2019-08-10 09:51:00.237219-0500 NSNotificationCenter[2744:142870] {"copyright":"Ignacio\nDiaz Bobillo","date":"2019-08-10","explanation":"A star cluster around 2 million years young surrounded by natal clouds of dust and glowing gas, M16 is also known as The Eagle Nebula. This beautifully detailed image of the region adopts the colorful Hubble palette and includes cosmic sculptures made famous in Hubble Space Telescope close-ups of the starforming complex. Described as elephant trunks or Pillars of Creation, dense, dusty columns rising near the center are light-years in length but are gravitationally contracting to form stars. Energetic radiation from the cluster stars erodes material near the tips, eventually exposing the embedded new stars. Extending from the ridge of bright emission left of center is another dusty starforming column known as the Fairy of Eagle Nebula. M16 lies about 7,000 light-years away, an easy target for binoculars or small telescopes in a nebula rich part of the sky toward the split constellation Serpens Cauda (the tail of the snake).   Watch: Perseid Meteor Shower","hdurl":"https://apod.nasa.gov/apod/image/1908/M16_HSHO_crop2.jpg","media_type":"image","service_version":"v1","title":"M16 Close Up","url":"https://apod.nasa.gov/apod/image/1908/M16_HSHO_crop2_1024.jpg"}
2019-08-10 09:51:00.237973-0500 NSNotificationCenter[2744:142870] itemNasaJSON: media_type
2019-08-10 09:51:00.238152-0500 NSNotificationCenter[2744:142870] itemNasaJSON: copyright
2019-08-10 09:51:00.238267-0500 NSNotificationCenter[2744:142870] itemNasaJSON: date
2019-08-10 09:51:00.238387-0500 NSNotificationCenter[2744:142870] itemNasaJSON: explanation
2019-08-10 09:51:00.238521-0500 NSNotificationCenter[2744:142870] itemNasaJSON: hdurl
2019-08-10 09:51:00.238632-0500 NSNotificationCenter[2744:142870] itemNasaJSON: service_version
2019-08-10 09:51:00.238750-0500 NSNotificationCenter[2744:142870] itemNasaJSON: title
2019-08-10 09:51:00.238855-0500 NSNotificationCenter[2744:142870] itemNasaJSON: url
2019-08-10 09:51:00.238960-0500 NSNotificationCenter[2744:142870] 2019-08-10
2019-08-10 09:51:00.242537-0500 NSNotificationCenter[2744:142870] A star cluster around 2 million years young surrounded by natal clouds of dust and glowing gas, M16 is also known as The Eagle Nebula. This beautifully detailed image of the region adopts the colorful Hubble palette and includes cosmic sculptures made famous in Hubble Space Telescope close-ups of the starforming complex. Described as elephant trunks or Pillars of Creation, dense, dusty columns rising near the center are light-years in length but are gravitationally contracting to form stars. Energetic radiation from the cluster stars erodes material near the tips, eventually exposing the embedded new stars. Extending from the ridge of bright emission left of center is another dusty starforming column known as the Fairy of Eagle Nebula. M16 lies about 7,000 light-years away, an easy target for binoculars or small telescopes in a nebula rich part of the sky toward the split constellation Serpens Cauda (the tail of the snake).   Watch: Perseid Meteor Shower

```

# AppDelegate.m

``` objective-c
//
//  AppDelegate.m
//  NSNotificationCenter
//
//  Created by Carlos Santiago Cruz on 7/11/19.
//  Copyright © 2019 Carlos Santiago Cruz. All rights reserved.
//

#import "AppDelegate.h"
#import "ViewController.h"

@interface AppDelegate ()
{
    ViewController *viewController;
}
@end

@implementation AppDelegate


- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    self.window = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
    viewController = [[ViewController alloc] initWithNibName:@"ViewController" bundle:nil];
    self.window.rootViewController = viewController;
    [self.window makeKeyAndVisible];
    return YES;
}


- (void)applicationWillResignActive:(UIApplication *)application {
    // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
    // Use this method to pause ongoing tasks, disable timers, and invalidate graphics rendering callbacks. Games should use this method to pause the game.
}


- (void)applicationDidEnterBackground:(UIApplication *)application {
    // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later.
    // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
}


- (void)applicationWillEnterForeground:(UIApplication *)application {
    // Called as part of the transition from the background to the active state; here you can undo many of the changes made on entering the background.
}


- (void)applicationDidBecomeActive:(UIApplication *)application {
    // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
}


- (void)applicationWillTerminate:(UIApplication *)application {
    // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
}


@end
```





