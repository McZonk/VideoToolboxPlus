#import <Foundation/Foundation.h>
#import <VideoToolbox/VideoToolbox.h>

@class VTPCompressionSession;


@protocol VTPCompressionSessionDelegate <NSObject>
@required

- (void)videoCompressionSession:(VTPCompressionSession *)compressionSession didEncodeSampleBuffer:(CMSampleBufferRef)sampleBuffer;

@optional

- (void)videoCompressionSession:(VTPCompressionSession *)compressionSession didDropSampleBuffer:(CMSampleBufferRef)sampleBuffer;

@end


@interface VTPCompressionSession : NSObject

#if !TARGET_OS_IPHONE
+ (BOOL)hasHardwareSupportForCodec:(CMVideoCodecType)codec;
#endif

/**
 * Creates a VTPCompressionSession with kVTVideoEncoderSpecification_EnableHardwareAcceleratedVideoEncoder.
 * Calls the designated initializer.
 */
- (instancetype)initWithWidth:(NSInteger)width height:(NSInteger)height codec:(CMVideoCodecType)codec error:(NSError **)error;

/**
 * Creates a VTPCompressionSession
 * @param width The width of frames, in pixels.
 * @param height The height of frames in pixels.
 * @param codec The codec type.
 * @param encoderSpecification Specifies a particular video encoder that must be used.
 * @param sourceImageBufferAttributes Required attributes for source pixel buffers, used when creating a pixel buffer pool for source frames. (Using pixel buffers not allocated by the Video Toolbox may increase the chance that it will be necessary to copy image data.)
 * @param error Output error.
 */
- (instancetype)initWithWidth:(NSInteger)width height:(NSInteger)height codec:(CMVideoCodecType)codec encoderSpecification:(NSDictionary<NSString *, id> *)encoderSpecification sourceImageBufferAttributes:(NSDictionary<NSString *, id> *)sourceImageBufferAttributes error:(NSError **)error NS_DESIGNATED_INITIALIZER;

- (instancetype)init NS_UNAVAILABLE;

@property (nonatomic, weak, readonly) id<VTPCompressionSessionDelegate> delegate;
@property (nonatomic, strong, readonly) dispatch_queue_t delegateQueue;

- (void)setDelegate:(id<VTPCompressionSessionDelegate>)delegate queue:(dispatch_queue_t)queue;

- (CVPixelBufferPoolRef)pixelBufferPool;

- (id)valueForProperty:(NSString *)property error:(NSError **)outError;
- (BOOL)setValue:(id)value forProperty:(NSString *)property error:(NSError **)outError;

- (void)prepare;

- (BOOL)encodeSampleBuffer:(CMSampleBufferRef)sampleBuffer forceKeyframe:(BOOL)forceKeyframe;
- (BOOL)encodePixelBuffer:(CVPixelBufferRef)pixelBuffer presentationTimeStamp:(CMTime)presentationTimeStamp duration:(CMTime)duration forceKeyframe:(BOOL)forceKeyframe;

- (BOOL)finish;
- (BOOL)finishUntilPresentationTimeStamp:(CMTime)presentationTimeStamp;

@end
