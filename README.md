# NSURLConnection

NSURLConnection

``` objective-c
NSURL *url = [NSURL URLWithString: @"https://github.com/santiagocruzcarlos/RestaurantApp/blob/master/1.png"];
        NSURLRequest *request = [NSURLRequest requestWithURL:url];
        NSError *error = nil;
        NSData *data = [NSURLConnection sendSynchronousRequest:request
                                             returningResponse:NULL
                                                         error:&error];
        if(!data) {
            NSLog(@"fetching the image fail: %@", [error localizedDescription]);
            return 1;
        }
        
        NSLog(@"The file is %lu bytes", [data length]);
        
        BOOL wasWritten = [data writeToFile:@"/tmp/1.png"
                                    options:NSDataWritingAtomic
                                      error:&error];
        if(wasWritten) {
            NSLog(@"write failed, it give us: %@", [error localizedDescription]);
            return 1;
        }
        NSLog(@"Success!");
        
        NSData *readData = [NSData dataWithContentsOfFile:@"/tmp/google.png"];
        NSLog(@"The file read from the disk has %lu bytes", [readData length]);
```

