//
//  KSPhotoBrowser.h
//  KSPhotoBrowser
//
//  Created by Kyle Sun on 12/25/16.
//  Copyright © 2016 Kyle Sun. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "KSPhotoItem.h"
#import "KSImageManagerProtocol.h"

@class KSPhotoView;

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, KSPhotoBrowserInteractiveDismissalStyle) {
    KSPhotoBrowserInteractiveDismissalStyleRotation,
    KSPhotoBrowserInteractiveDismissalStyleScale,
    KSPhotoBrowserInteractiveDismissalStyleSlide,
    KSPhotoBrowserInteractiveDismissalStyleNone
};

typedef NS_ENUM(NSUInteger, KSPhotoBrowserBackgroundStyle) {
    KSPhotoBrowserBackgroundStyleBlurPhoto,
    KSPhotoBrowserBackgroundStyleBlur,
    KSPhotoBrowserBackgroundStyleBlack
};

typedef NS_ENUM(NSUInteger, KSPhotoBrowserPageIndicatorStyle) {
    KSPhotoBrowserPageIndicatorStyleNone,
    KSPhotoBrowserPageIndicatorStyleDot,
    KSPhotoBrowserPageIndicatorStyleText
};

typedef NS_ENUM(NSUInteger, KSPhotoBrowserImageLoadingStyle) {
    KSPhotoBrowserImageLoadingStyleIndeterminate,
    KSPhotoBrowserImageLoadingStyleDeterminate
};

@protocol KSPhotoBrowserDelegate, KSImageManager;
@interface KSPhotoBrowser : UIViewController

@property (nonatomic, strong, readonly) NSMutableArray *photoItems;
@property (nonatomic, assign, readonly) NSUInteger currentPage;

@property (nonatomic, assign) KSPhotoBrowserInteractiveDismissalStyle dismissalStyle;
@property (nonatomic, assign) KSPhotoBrowserBackgroundStyle backgroundStyle;
@property (nonatomic, assign) KSPhotoBrowserPageIndicatorStyle pageindicatorStyle;
@property (nonatomic, assign) KSPhotoBrowserImageLoadingStyle loadingStyle;
@property (nonatomic, assign) BOOL bounces;
@property (nonatomic, weak) id<KSPhotoBrowserDelegate> delegate;
@property (class, nonatomic, strong) Class<KSImageManager> imageManagerClass;
@property (class, nonatomic, strong) UIColor *imageViewBackgroundColor;

/// 开启转场动画
@property (nonatomic, assign) BOOL enableTransitionAnimation;
/// 允许单击Dismiss
@property (nonatomic, assign) BOOL allowsSingleTapToDismiss;
/// 允许拖拽Dismiss, 如果No, 会恢复手势开始位置
@property (nonatomic, assign) BOOL allowsDragToDismiss;
/// 开启拖拽手势拖拽
@property (nonatomic, assign) BOOL enableDrag;

+ (instancetype)browserWithPhotoItems:(NSArray<KSPhotoItem *> *)photoItems selectedIndex:(NSUInteger)selectedIndex;
- (instancetype)initWithPhotoItems:(NSArray<KSPhotoItem *> *)photoItems selectedIndex:(NSUInteger)selectedIndex;
- (void)showFromViewController:(UIViewController *)vc;
- (UIImage *)imageForItem:(KSPhotoItem *)item;
- (UIImage *)imageAtIndex:(NSUInteger)index;
- (void)removeItemAtIndex:(NSUInteger)index;

- (KSPhotoView *)photoViewForPage:(NSUInteger)page;
- (void)reloadItemWithIndex:(NSUInteger)index;

/// MARK: - Override Methods
- (void)showDismissalAnimation;
- (void)configSubviews;

@end

@protocol KSPhotoBrowserDelegate <NSObject>

@optional
- (void)ks_photoBrowser:(KSPhotoBrowser *)browser didSelectItem:(KSPhotoItem *)item atIndex:(NSUInteger)index;

- (void)ks_photoBrowser:(KSPhotoBrowser *)browser didScrollToIndex:(NSUInteger)index totalCount:(NSUInteger)totalCount;

// If you do not implement this method, there will be a default implementation which will call the system share sheet `UIActivityViewController`
- (void)ks_photoBrowser:(KSPhotoBrowser *)browser didLongPressItem:(KSPhotoItem *)item atIndex:(NSUInteger)index;

@end

NS_ASSUME_NONNULL_END
