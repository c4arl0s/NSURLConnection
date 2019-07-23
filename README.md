# NSURLConnection

- An object that enables you to start and stop URL requests.
- The NSURLConnection class provides convenience class methods to load URL requests both asynchronously using a callback block and synchronously.

# Content-type

- Content-type is known as a MIME type that indicates what kind of data an HTTP response contains.

# ViewController.m

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

![Screen Shot 2019-07-19 at 12 31 52 AM](https://user-images.githubusercontent.com/24994818/61511510-9cbba600-a9bc-11e9-9b4b-85c6573de38a.png)

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





