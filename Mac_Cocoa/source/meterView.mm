//
//  meterView.m
//  Meter_OSX
//
//  Created by John Carlson on 10/24/19.
//

#import "../include/meterView.h"

@implementation meterView

- (void)drawRect:(NSRect)dirtyRect {
    [super drawRect:dirtyRect];
    
    // Drawing code here.
}

-(id) initWithFrame:(NSRect)frameRect {
    self = [super initWithFrame:frameRect];
    //
    if(self) {
        [[NSBundle mainBundle] loadNibNamed: @"meterViewController"
                                      owner: self
                            topLevelObjects: nil];
    }
    //
    return self;
}

@end
