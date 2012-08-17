/*
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
 */

#import <Cocoa/Cocoa.h>
#import "OEGridViewCell.h"
#import "OEGridViewLayoutManager.h"
#import "OEGridViewFieldEditor.h"

@class OEGridView;

@protocol OEGridViewDelegate <NSObject>

@optional
- (void)selectionChangedInGridView:(OEGridView *)gridView;
- (void)gridView:(OEGridView *)gridView doubleClickedCellForItemAtIndex:(NSUInteger)index;
- (NSDragOperation)gridView:(OEGridView *)gridView validateDrop:(id<NSDraggingInfo>)sender;
- (NSDragOperation)gridView:(OEGridView *)gridView draggingUpdated:(id<NSDraggingInfo>)sender;
- (BOOL)gridView:(OEGridView *)gridView acceptDrop:(id<NSDraggingInfo>)sender;
- (void)gridView:(OEGridView *)gridView magnifiedWithEvent:(NSEvent*)event;
- (void)gridView:(OEGridView *)gridView magnifyEndedWithEvent:(NSEvent*)event;
@end

#pragma mark -
@protocol OEGridViewDataSource <NSObject>

@required
- (OEGridViewCell *)gridView:(OEGridView *)gridView cellForItemAtIndex:(NSUInteger)index;
- (NSUInteger)numberOfItemsInGridView:(OEGridView *)gridView;

@optional
- (NSView *)viewForNoItemsInGridView:(OEGridView *)gridView;
- (void)gridView:(OEGridView *)gridView willBeginEditingCellForItemAtIndex:(NSUInteger)index;
- (void)gridView:(OEGridView *)gridView didEndEditingCellForItemAtIndex:(NSUInteger)index;
- (id<NSPasteboardWriting>)gridView:(OEGridView *)gridView pasteboardWriterForIndex:(NSInteger)index;
- (NSMenu *)gridView:(OEGridView *)gridView menuForItemsAtIndexes:(NSIndexSet *)indexes;

@end

#pragma mark -
@interface OEGridView : NSView <OEGridViewLayoutManagerProtocol, NSDraggingSource, NSDraggingDestination>
#pragma mark -
#pragma mark Query Data Sources

- (id)dequeueReusableCell;
- (NSUInteger)numberOfItems;
- (OEGridViewCell *)cellForItemAtIndex:(NSUInteger)index makeIfNecessary:(BOOL)necessary;

#pragma mark -
#pragma mark Query Cells

- (NSUInteger)indexForCell:(OEGridViewCell *)cell;
- (NSUInteger)indexForCellAtPoint:(NSPoint)point;
- (NSIndexSet *)indexesForCellsInRect:(NSRect)rect;
- (NSArray *)visibleCells;
- (NSIndexSet *)indexesForVisibleCells;
- (NSRect)rectForCellAtIndex:(NSUInteger)index;

#pragma mark -
#pragma mark Selection

- (NSUInteger)indexForSelectedCell;
- (NSIndexSet *)indexesForSelectedCells;
- (void)selectCellAtIndex:(NSUInteger)index;
- (void)deselectCellAtIndex:(NSUInteger)index;
- (void)selectAll:(id)sender;
- (void)deselectAll:(id)sender;

#pragma mark -
#pragma mark Data Reload

- (void)noteNumberOfCellsChanged;
- (void)reloadData;
- (void)reloadCellsAtIndexes:(NSIndexSet *)indexes;

#pragma mark -
#pragma mark Properties

@property(nonatomic, strong) CALayer    *foregroundLayer;      // A decorative background layer, the layer should return nil for -hitTest
@property(nonatomic, strong) CALayer    *backgroundLayer;      // A decorative foreground layer, the layer should return nil for -hitTest
@property(nonatomic, assign) CGFloat     minimumColumnSpacing; // Minimum spacing between columns
@property(nonatomic, assign) CGFloat     rowSpacing;           // Minimum spacing between rows
@property(nonatomic, assign) CGSize      itemSize;             // User defined cell size (defaults to 250 x 250)
@property(nonatomic, copy)   NSIndexSet *selectionIndexes;     // NSIndexSet of selected indexes

@property(nonatomic, assign) id<OEGridViewDataSource> dataSource; // Responsible for supplying the cells of each object represented in the grid
@property(nonatomic, assign) id<OEGridViewDelegate>   delegate;   // Receives information regarding the user interaction of the grid and it's cells

@end
