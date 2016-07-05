#import "VTPCompressionSession.h"

#import "NSError+VTPError.h"
#import "VTPCompressionSession+Properties.h"

#if defined(MAC_OS_X_VERSION_MAX_ALLOWED) && MAC_OS_X_VERSION_MAX_ALLOWED < 1090
const CFStringRef
kVTVideoEncoderSpecification_EnableHardwareAcceleratedVideoEncoder =
CFSTR ("EnableHardwareAcceleratedVideoEncoder");
#endif

@interface VTPCompressionSession ()
{
@protected
	VTCompressionSessionRef compressionSession;
    CVPixelBufferPoolRef    pixelbufferpool;
    CGSize                  size;
}

@property (nonatomic, weak) id<VTPCompressionSessionDelegate> delegate;
@property (nonatomic, strong) dispatch_queue_t delegateQueue;

@end


@implementation VTPCompressionSession

+ (BOOL)hasHardwareSupportForCodec:(CMVideoCodecType)codec
{
    VTPCompressionSession *compressionSession = [[self alloc] initWithWidth:1280 height:720 pix_fmt:kCVPixelFormatType_420YpCbCr8BiPlanarVideoRange codec:codec error:nil];
	return [compressionSession usingHardwareAcceleratedVideoEncoder];
}

- (instancetype)initWithWidth:(NSInteger)width height:(NSInteger)height pix_fmt:(OSType)fmt codec:(CMVideoCodecType)codec error:(NSError **)outError
{
	self = [super init];
	if(self != nil)
	{
		NSDictionary *encoderSpecification = @{
#if !TARGET_OS_IPHONE
			(__bridge NSString *)kVTVideoEncoderSpecification_EnableHardwareAcceleratedVideoEncoder: @YES
#endif
		};
        //OSType pixfmt = kCVPixelFormatType_32ARGB;//kCVPixelFormatType_420YpCbCr8Planar;//kCVPixelFormatType_420YpCbCr8BiPlanarVideoRange
        NSDictionary *sourceSpecification = @{
            (__bridge NSString*)kCVPixelBufferPixelFormatTypeKey: [NSNumber numberWithInt:fmt],
            (__bridge NSString*)kCVPixelBufferOpenGLESCompatibilityKey:@TRUE
        };

		OSStatus status = VTCompressionSessionCreate(NULL, (int32_t)width, (int32_t)height, codec, (__bridge CFDictionaryRef)encoderSpecification, (__bridge CFDictionaryRef _Nullable)(sourceSpecification), NULL, VideoCompressonOutputCallback, (__bridge void *)self, &compressionSession);
		if(status != noErr)
		{
			NSError *error = [NSError videoToolboxErrorWithStatus:status];
			if(outError != nil)
			{
				*outError = error;
			}
			else
			{
				NSLog(@"%s:%d: %@", __FUNCTION__, __LINE__, error);
			}
			return nil;
		}
        size = CGSizeMake(width, height);
	}
	return self;
}

- (void)dealloc
{
	if(compressionSession != NULL)
	{
		VTCompressionSessionInvalidate(compressionSession);
	}
}

- (void)setDelegate:(id<VTPCompressionSessionDelegate>)delegate queue:(dispatch_queue_t)queue
{
	if(queue == NULL)
	{
		queue = dispatch_get_main_queue();
	}
	
	self.delegate = delegate;
	self.delegateQueue = queue;
}

- (id)valueForProperty:(NSString *)property error:(NSError **)outError
{
	CFTypeRef value = NULL;
	OSStatus status = VTSessionCopyProperty(compressionSession, (__bridge CFStringRef)property, NULL, &value);
	if(status != noErr)
	{
		NSError *error = [NSError videoToolboxErrorWithStatus:status];
		if(outError != nil)
		{
			*outError = error;
		}
		else
		{
			NSLog(@"%s:%d: %@", __FUNCTION__, __LINE__, error);
		}
		
		return nil;
	}
	
	return CFBridgingRelease(value);
}

- (BOOL)setValue:(id)value forProperty:(NSString *)property error:(NSError **)outError
{
	OSStatus status = VTSessionSetProperty(compressionSession, (__bridge CFStringRef)property, (__bridge CFTypeRef)value);
	if(status != noErr)
	{
		NSError *error = [NSError videoToolboxErrorWithStatus:status];
		if(outError != nil)
		{
			*outError = error;
		}
		else
		{
			NSLog(@"%s:%d: %@", __FUNCTION__, __LINE__, error);
		}
		
		return NO;
	}

	return YES;
}

- (void)prepare
{
	VTCompressionSessionPrepareToEncodeFrames(compressionSession);
    pixelbufferpool = NULL;
}

- (BOOL)encodeSampleBuffer:(CMSampleBufferRef)sampleBuffer forceKeyframe:(BOOL)forceKeyframe
{
	CVPixelBufferRef pixelBuffer = CMSampleBufferGetImageBuffer(sampleBuffer);
	
	CMTime presentationTimeStamp = CMSampleBufferGetOutputPresentationTimeStamp(sampleBuffer);
	CMTime duration = CMSampleBufferGetOutputDuration(sampleBuffer);
	
	return [self encodePixelBuffer:pixelBuffer presentationTimeStamp:presentationTimeStamp duration:duration forceKeyframe:forceKeyframe];
}

- (BOOL)encodePixelBuffer:(CVPixelBufferRef)pixelBuffer presentationTimeStamp:(CMTime)presentationTimeStamp duration:(CMTime)duration forceKeyframe:(BOOL)forceKeyframe
{
	NSDictionary *properties = nil;
	
	if(forceKeyframe)
	{
		properties = @{
			(__bridge NSString *)kVTEncodeFrameOptionKey_ForceKeyFrame: @YES
		};
	}
	
	OSStatus status = VTCompressionSessionEncodeFrame(compressionSession, pixelBuffer, presentationTimeStamp, duration, (__bridge CFDictionaryRef)properties, pixelBuffer, NULL);
//    status = VTCompressionSessionCompleteFrames(compressionSession, CMTimeMake(0, 0));
    if( status != noErr )
        NSLog(@"encode error:%ld", status);
	return status == noErr;
}
- (BOOL)encodeYuv420pBytes:(GLbyte*)bytes presentationTimeStamp:(CMTime)presentationTimeStamp duration:(CMTime)duration forceKeyframe:(BOOL)forceKeyframe;
{
    CVPixelBufferRef pixel_buf = NULL;
    if( pixelbufferpool == NULL ){
        pixelbufferpool = VTCompressionSessionGetPixelBufferPool(compressionSession);
        pixelbufferpool = CVPixelBufferPoolRetain(pixelbufferpool);
    }
    CVReturn nret = CVPixelBufferPoolCreatePixelBuffer(kCFAllocatorDefault, pixelbufferpool, &pixel_buf);
    if( nret != kCVReturnSuccess ){
        NSLog(@"Create PixelBuffer error:%d", nret);
        return FALSE;
    }
    void*  planedatas[3] = {bytes, bytes+(int)(size.width*size.height), bytes+(int)(size.width*size.height*5/4)};
    size_t planewidths[3] = {size.width,size.width/2, size.width/2};
    size_t planeheights[3] = {size.height,size.height/2, size.height/2};
    size_t planestrides[3] = {size.width,size.width/2, size.width/2};
    
    OSStatus status = CVPixelBufferLockBaseAddress(pixel_buf, 0);
    if (kCVReturnSuccess != status) {
        CVPixelBufferUnlockBaseAddress(pixel_buf, 0);
        CVPixelBufferRelease(pixel_buf);
        pixel_buf=nil;
        return FALSE;
    }
    void* baseAddr = CVPixelBufferGetBaseAddress(pixel_buf);
    size_t plane_width = CVPixelBufferGetWidthOfPlane(pixel_buf, 0);
    size_t plane_height = CVPixelBufferGetHeightOfPlane(pixel_buf, 0);
    //sanity check
    size_t y_bytePer_row = CVPixelBufferGetBytesPerRowOfPlane(pixel_buf, 0);
    size_t y_plane_height = CVPixelBufferGetHeightOfPlane(pixel_buf, 0);
    size_t y_plane_width = CVPixelBufferGetWidthOfPlane(pixel_buf, 0);
    
    size_t u_bytePer_row = CVPixelBufferGetBytesPerRowOfPlane(pixel_buf, 1);
    size_t u_plane_height = CVPixelBufferGetHeightOfPlane(pixel_buf, 1);
    size_t u_plane_width = CVPixelBufferGetWidthOfPlane(pixel_buf, 1);
    
    size_t v_bytePer_row = CVPixelBufferGetBytesPerRowOfPlane(pixel_buf, 2);
    size_t v_plane_height = CVPixelBufferGetHeightOfPlane(pixel_buf, 2);
    size_t v_plane_width = CVPixelBufferGetWidthOfPlane(pixel_buf, 2);
    
    uint8_t* y_src= (uint8_t*)CVPixelBufferGetBaseAddressOfPlane(pixel_buf, 0);
    memcpy(y_src, planedatas[0], planestrides[0]*planeheights[0]);
    uint8_t* u_src= (uint8_t*)CVPixelBufferGetBaseAddressOfPlane(pixel_buf, 1);
    memcpy(u_src, planedatas[1], planestrides[1]*planeheights[1]);
    uint8_t* v_src= (uint8_t*)CVPixelBufferGetBaseAddressOfPlane(pixel_buf, 2);
    memcpy(v_src, planedatas[2], planestrides[2]*planeheights[2]);
    int ntmplen = y_bytePer_row*y_plane_height + u_bytePer_row*u_plane_height + v_bytePer_row*v_plane_height;
    CVPixelBufferUnlockBaseAddress(pixel_buf, 0);
    BOOL bret = [self encodePixelBuffer:pixel_buf presentationTimeStamp:presentationTimeStamp duration:duration forceKeyframe:forceKeyframe];
    CVPixelBufferRelease(pixel_buf);
    return bret;
}

- (BOOL)finish
{
	BOOL bret = [self finishUntilPresentationTimeStamp:kCMTimeIndefinite];
    if( pixelbufferpool != NULL ){
        CVPixelBufferPoolFlush(pixelbufferpool, 0);
        CVPixelBufferPoolRelease(pixelbufferpool);
        pixelbufferpool = NULL;
    }
    return bret;
}

- (BOOL)finishUntilPresentationTimeStamp:(CMTime)presentationTimeStamp
{
	OSStatus status = VTCompressionSessionCompleteFrames(compressionSession, presentationTimeStamp);

	return status == noErr;
}

- (void)encodePixelBufferCallbackWithSampleBuffer:(CMSampleBufferRef)sampleBuffer infoFlags:(VTEncodeInfoFlags)infoFlags
{
    if( !sampleBuffer )
        return;
	id<VTPCompressionSessionDelegate> delegate = self.delegate;
	dispatch_queue_t delegateQueue = self.delegateQueue;
	
	if(infoFlags & kVTEncodeInfo_FrameDropped)
	{
		if([delegate respondsToSelector:@selector(videoCompressionSession:didDropSampleBuffer:)])
		{
			CFRetain(sampleBuffer);
			dispatch_async(delegateQueue, ^{
				[delegate videoCompressionSession:self didDropSampleBuffer:sampleBuffer];
				
				CFRelease(sampleBuffer);
			});
		}
	}
	else
	{
		if([delegate respondsToSelector:@selector(videoCompressionSession:didEncodeSampleBuffer:)])
		{
			CFRetain(sampleBuffer);
			dispatch_async(delegateQueue, ^{
				[delegate videoCompressionSession:self didEncodeSampleBuffer:sampleBuffer];
			
				CFRelease(sampleBuffer);
			});
		}
	}
}

static void VideoCompressonOutputCallback(void *VTref, void *VTFrameRef, OSStatus status, VTEncodeInfoFlags infoFlags, CMSampleBufferRef sampleBuffer)
{
	//	CVPixelBufferRef pixelBuffer = (CVPixelBufferRef)VTFrameRef;
	//	CVPixelBufferRelease(pixelBuffer); // see encodeFrame:
	//	pixelBuffer = NULL;
	
	VTPCompressionSession *compressionSession = (__bridge VTPCompressionSession *)VTref;
	[compressionSession encodePixelBufferCallbackWithSampleBuffer:sampleBuffer infoFlags:infoFlags];
}

@end
