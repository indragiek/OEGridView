### OEGridView (from the [OpenEmu project](https://github.com/OpenEmu/OpenEmu/))
#### Sonora 2.0 Fork

This is the unofficial repo for my fork of OEGridView, the high performance Core Animation based grid view used in [OpenEmu](http://openemu.org) (which is a fantastic app, by the way).

OEGridView doesn't have its own repository, so I copied the required source files and am hosting it in this repository with my own additions that I put in for use in the upcoming [Sonora 2.0](http://indragie.com).

**The original source code was written mainly by [Enrique Osuna](https://github.com/riquedafreak) along with contributions from other members of the OpenEmu project**

I'm also putting in some documentation in here to help other people use it in their projects. 

#### Requirements

OEGridView requires ARC. If your project doesn't use ARC, simply add the `-fobjc-arc` flag to all of the files except for `NSColor+OEAdditions.m`, which can not be compiled with ARC enabled. 

#### Additions for Sonora 2

This project has a few additions that were made due to the needs of Sonora 2:

- Support for OS X 10.8 Mountain Lion and the Retina display
- Support for receiving mouse entered, exited, and moved events inside layers


#### How to use

Basic usage of OEGridView is super simple:

- Place the OEGridView inside an NSScrollView
- Set the `dataSource` and `delegate` properties to your controller object
- Set the `itemSize` property of the `OEGridView` to the size of each content cell
- Implement the following two methods:

```
- (OEGridViewCell *)gridView:(OEGridView *)gridView cellForItemAtIndex:(NSUInteger)index;
- (NSUInteger)numberOfItemsInGridView:(OEGridView *)gridView;
```

The `gridView:cellForItemAtIndex:` method is where you would return an instance of your `OEGridViewCell` subclass. A basic implementation of this method would look like this (from Sonora):

```
- (OEGridViewCell *)gridView:(OEGridView *)gridView cellForItemAtIndex:(NSUInteger)index
{
	SNRAlbumGridViewCell *item = (SNRAlbumGridViewCell *)[gridView cellForItemAtIndex:index makeIfNecessary:NO];
	if (!item) {
		item = (SNRAlbumGridViewCell *)[gridView dequeueReusableCell];
	}
	if (!item) {
		item = [[SNRAlbumGridViewCell alloc] init];
	}
	id object = [self.fetchedResultsController objectAtIndex:index];
    item.representedObject = object;
    item.albumName = [object valueForKey:@"name"];
}
```
The key point here is to call OEGridView's `-cellForItemAtIndex:makeIfNecessary:` method first to see if the cell already exists, then call `-dequeueReusableCell`, and only then create a new cell if the previous two methods returned nil for maximum performance.

Creating an `OEGridViewCell` subclass is also fairly simple. First of all, a few tips:

- `OEGridViewCell` inherits from `OEGridLayer`, which is a `CALayer` subclass. Therefore, `OEGridViewCell`'s are to be treated like any other `CALayer`.
- Avoid drawing directly into the layer, and utilize sublayers as much as possible. Use plain `CALayer` and `CATextLayer` sublayers for displaying images and text and use your own `CALayer` subclasses for custom drawn content.
- If you want to use interactive controls, you must create a subclass of `OEGridLayer` with the `interactive` property set to `YES` in order to receive mouse events (check `OEGridLayer.h` for all the mouse event methods).
- Set the `tracking` property of the `OEGridLayer` to `YES` when the `mouseDownAtPointInLayer:` method is called if you want to continue receiving additional events for mouseUp, etc.
- `OEGridLayer`'s can also receive hover events (mouse entered, exited, and moved) when the `receivesHoverEvents` property is set to `YES`. 

A basic `OEGridViewCell` subclass might look like this:

```
- (id)init
{
    if ((self = [super init])) {
    	// Set the layer attributes
        self.receivesHoverEvents = YES;
        self.backgroundColor = [][NSColor redColor] CGColor];
        // Create and configure any sublayers
        _imageLayer = [OEGridLayer layer];
        _imageLayer.contentsGravity = kCAGravityResize;
         _textLayer = [CATextLayer layer];
        // Add sublayers
        [self addSublayer:_imageLayer];
        [self addSublayer:_textLayer];
    }
    return self;
}

- (void)layoutSublayers
{
    [super layoutSublayers];
    // Do any sublayer layout
    [_imageLayer setFrame:[self bounds]];
}

- (void)prepareForReuse
{
    [super prepareForReuse];
    // Clear any cached attributes
    self.image = nil;
    self.text = nil;
}

#pragma mark - Accessors

- (void)setImage:(NSImage*)image
{
	if (_image != image) {
		_image = image;
		[_imageLayer setImage:image];
	}
}

- (void)setText:(NSString*)text
{
	if (_text != text) {
		_text = text;
		[_textLayer setString:text];
	}
}
```

#### License

OpenEmu is distributed under the following license, which also applies to OEGridView:

```
Copyright (c) 2012, OpenEmu Team

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:
     * Redistributions of source code must retain the above copyright
       notice, this list of conditions and the following disclaimer.
     * Redistributions in binary form must reproduce the above copyright
       notice, this list of conditions and the following disclaimer in the
       documentation and/or other materials provided with the distribution.
     * Neither the name of the OpenEmu Team nor the
       names of its contributors may be used to endorse or promote products
       derived from this software without specific prior written permission.

 THIS SOFTWARE IS PROVIDED BY OpenEmu Team ''AS IS'' AND ANY
 EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL OpenEmu Team BE LIABLE FOR ANY
 DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  ```