#import "VTPCompressionSession.h"

#define VTPCompressionPropertyKeyNumberOfPendingFrames ((__bridge NSString *)kVTCompressionPropertyKey_NumberOfPendingFrames)

// kVTCompressionPropertyKey_PixelBufferPoolIsShared Read-only, Boolean
	
// kVTCompressionPropertyKey_VideoEncoderPixelBufferAttributes Read-only, CFDictionary

#define VTPCompressionPropertyKeyMaxKeyFrameInterval ((__bridge NSString *)kVTCompressionPropertyKey_MaxKeyFrameInterval)

#define VTPCompressionPropertyKeyMaxKeyFrameIntervalDuration ((__bridge NSString *)kVTCompressionPropertyKey_MaxKeyFrameIntervalDuration)

#define VTPCompressionPropertyKeyAllowTemporalCompression ((__bridge NSString *)kVTCompressionPropertyKey_AllowTemporalCompression)

#define VTPCompressionPropertyKeyAllowFrameReordering ((__bridge NSString *)kVTCompressionPropertyKey_AllowFrameReordering)


//	VT_EXPORT const CFStringRef kVTCompressionPropertyKey_AverageBitRate VT_AVAILABLE_STARTING(10_8); // Read/write, CFNumber<SInt32>, Optional
	
// VT_EXPORT const CFStringRef kVTCompressionPropertyKey_DataRateLimits VT_AVAILABLE_STARTING(10_8); // Read/write, CFArray[CFNumber], [bytes, seconds, bytes, seconds...], Optional

#define VTPCompressionPropertyKeyQuality ((__bridge NSString *)kVTCompressionPropertyKey_Quality)

// VT_EXPORT const CFStringRef kVTCompressionPropertyKey_MoreFramesBeforeStart VT_AVAILABLE_STARTING(10_8); // Read/write, CFBoolean, Optional
	
// VT_EXPORT const CFStringRef kVTCompressionPropertyKey_MoreFramesAfterEnd VT_AVAILABLE_STARTING(10_8); // Read/write, CFBoolean, Optional
	
#if 0
	VT_EXPORT const CFStringRef kVTCompressionPropertyKey_ProfileLevel VT_AVAILABLE_STARTING(10_8); // Read/write, CFString (enumeration), Optional
	
	VT_EXPORT const CFStringRef kVTProfileLevel_H264_Baseline_1_3 VT_AVAILABLE_STARTING(10_8);
	VT_EXPORT const CFStringRef kVTProfileLevel_H264_Baseline_3_0 VT_AVAILABLE_STARTING(10_8);
	VT_EXPORT const CFStringRef kVTProfileLevel_H264_Baseline_3_1 VT_AVAILABLE_STARTING(10_8);
	VT_EXPORT const CFStringRef kVTProfileLevel_H264_Baseline_3_2 VT_AVAILABLE_STARTING(10_8);
	VT_EXPORT const CFStringRef kVTProfileLevel_H264_Baseline_4_0 VT_AVAILABLE_STARTING(10_9);
	VT_EXPORT const CFStringRef kVTProfileLevel_H264_Baseline_4_1 VT_AVAILABLE_STARTING(10_8);
	VT_EXPORT const CFStringRef kVTProfileLevel_H264_Baseline_4_2 VT_AVAILABLE_STARTING(10_9);
	VT_EXPORT const CFStringRef kVTProfileLevel_H264_Baseline_5_0 VT_AVAILABLE_STARTING(10_9);
	VT_EXPORT const CFStringRef kVTProfileLevel_H264_Baseline_5_1 VT_AVAILABLE_STARTING(10_9);
	VT_EXPORT const CFStringRef kVTProfileLevel_H264_Baseline_5_2 VT_AVAILABLE_STARTING(10_9);
	VT_EXPORT const CFStringRef kVTProfileLevel_H264_Baseline_AutoLevel VT_AVAILABLE_STARTING(10_9);
	VT_EXPORT const CFStringRef kVTProfileLevel_H264_Main_3_0 VT_AVAILABLE_STARTING(10_8);
	VT_EXPORT const CFStringRef kVTProfileLevel_H264_Main_3_1 VT_AVAILABLE_STARTING(10_8);
	VT_EXPORT const CFStringRef kVTProfileLevel_H264_Main_3_2 VT_AVAILABLE_STARTING(10_8);
	VT_EXPORT const CFStringRef kVTProfileLevel_H264_Main_4_0 VT_AVAILABLE_STARTING(10_8);
	VT_EXPORT const CFStringRef kVTProfileLevel_H264_Main_4_1 VT_AVAILABLE_STARTING(10_8);
	VT_EXPORT const CFStringRef kVTProfileLevel_H264_Main_4_2 VT_AVAILABLE_STARTING(10_9);
	VT_EXPORT const CFStringRef kVTProfileLevel_H264_Main_5_0 VT_AVAILABLE_STARTING(10_8);
	VT_EXPORT const CFStringRef kVTProfileLevel_H264_Main_5_1 VT_AVAILABLE_STARTING(10_9);
	VT_EXPORT const CFStringRef kVTProfileLevel_H264_Main_5_2 VT_AVAILABLE_STARTING(10_9);
	VT_EXPORT const CFStringRef kVTProfileLevel_H264_Main_AutoLevel VT_AVAILABLE_STARTING(10_9);
	VT_EXPORT const CFStringRef kVTProfileLevel_H264_Extended_5_0 VT_AVAILABLE_STARTING(10_8);
	VT_EXPORT const CFStringRef kVTProfileLevel_H264_Extended_AutoLevel VT_AVAILABLE_STARTING(10_9);
	VT_EXPORT const CFStringRef kVTProfileLevel_H264_High_3_0 VT_AVAILABLE_STARTING(10_9);
	VT_EXPORT const CFStringRef kVTProfileLevel_H264_High_3_1 VT_AVAILABLE_STARTING(10_9);
	VT_EXPORT const CFStringRef kVTProfileLevel_H264_High_3_2 VT_AVAILABLE_STARTING(10_9);
	VT_EXPORT const CFStringRef kVTProfileLevel_H264_High_4_0 VT_AVAILABLE_STARTING(10_9);
	VT_EXPORT const CFStringRef kVTProfileLevel_H264_High_4_1 VT_AVAILABLE_STARTING(10_9);
	VT_EXPORT const CFStringRef kVTProfileLevel_H264_High_4_2 VT_AVAILABLE_STARTING(10_9);
	VT_EXPORT const CFStringRef kVTProfileLevel_H264_High_5_0 VT_AVAILABLE_STARTING(10_8);
	VT_EXPORT const CFStringRef kVTProfileLevel_H264_High_5_1 VT_AVAILABLE_STARTING(10_9);
	VT_EXPORT const CFStringRef kVTProfileLevel_H264_High_5_2 VT_AVAILABLE_STARTING(10_9);
	VT_EXPORT const CFStringRef kVTProfileLevel_H264_High_AutoLevel VT_AVAILABLE_STARTING(10_9);
	
	VT_EXPORT const CFStringRef kVTProfileLevel_MP4V_Simple_L0 VT_AVAILABLE_STARTING(10_8);
	VT_EXPORT const CFStringRef kVTProfileLevel_MP4V_Simple_L1 VT_AVAILABLE_STARTING(10_8);
	VT_EXPORT const CFStringRef kVTProfileLevel_MP4V_Simple_L2 VT_AVAILABLE_STARTING(10_8);
	VT_EXPORT const CFStringRef kVTProfileLevel_MP4V_Simple_L3 VT_AVAILABLE_STARTING(10_8);
	VT_EXPORT const CFStringRef kVTProfileLevel_MP4V_Main_L2 VT_AVAILABLE_STARTING(10_8);
	VT_EXPORT const CFStringRef kVTProfileLevel_MP4V_Main_L3 VT_AVAILABLE_STARTING(10_8);
	VT_EXPORT const CFStringRef kVTProfileLevel_MP4V_Main_L4 VT_AVAILABLE_STARTING(10_8);
	VT_EXPORT const CFStringRef kVTProfileLevel_MP4V_AdvancedSimple_L0 VT_AVAILABLE_STARTING(10_8);
	VT_EXPORT const CFStringRef kVTProfileLevel_MP4V_AdvancedSimple_L1 VT_AVAILABLE_STARTING(10_8);
	VT_EXPORT const CFStringRef kVTProfileLevel_MP4V_AdvancedSimple_L2 VT_AVAILABLE_STARTING(10_8);
	VT_EXPORT const CFStringRef kVTProfileLevel_MP4V_AdvancedSimple_L3 VT_AVAILABLE_STARTING(10_8);
	VT_EXPORT const CFStringRef kVTProfileLevel_MP4V_AdvancedSimple_L4 VT_AVAILABLE_STARTING(10_8);
	
	VT_EXPORT const CFStringRef kVTProfileLevel_H263_Profile0_Level10 VT_AVAILABLE_STARTING(10_8);
	VT_EXPORT const CFStringRef kVTProfileLevel_H263_Profile0_Level45 VT_AVAILABLE_STARTING(10_8);
	VT_EXPORT const CFStringRef kVTProfileLevel_H263_Profile3_Level45 VT_AVAILABLE_STARTING(10_8);
#endif

#if 0
	VT_EXPORT const CFStringRef kVTCompressionPropertyKey_H264EntropyMode VT_AVAILABLE_STARTING(10_9);	// Read/write, CFString, optional
	VT_EXPORT const CFStringRef kVTH264EntropyMode_CAVLC VT_AVAILABLE_STARTING(10_9);
	VT_EXPORT const CFStringRef kVTH264EntropyMode_CABAC VT_AVAILABLE_STARTING(10_9);
#endif
	
// VT_EXPORT const CFStringRef kVTCompressionPropertyKey_Depth VT_AVAILABLE_STARTING(10_8); // Read/write, CFNumber (CMPixelFormatType), Optional
	
// VT_EXPORT const CFStringRef kVTCompressionPropertyKey_MaxFrameDelayCount VT_AVAILABLE_STARTING(10_8); // Read/write, CFNumber, Optional
//	enum { kVTUnlimitedFrameDelayCount = -1 };
	
// VT_EXPORT const CFStringRef kVTCompressionPropertyKey_MaxH264SliceBytes VT_AVAILABLE_STARTING(10_8); // Read/write, CFNumber<SInt32>, Optional
	
#define VTPCompressionPropertyKeyRealTime ((__bridge NSString *)kVTCompressionPropertyKey_RealTime)
	
// VT_EXPORT const CFStringRef kVTCompressionPropertyKey_SourceFrameCount VT_AVAILABLE_STARTING(10_8); // Read/write, CFNumber, Optional
	
// VT_EXPORT const CFStringRef kVTCompressionPropertyKey_ExpectedFrameRate VT_AVAILABLE_STARTING(10_8); // Read/write, CFNumber, Optional
	
// VT_EXPORT const CFStringRef kVTCompressionPropertyKey_ExpectedDuration VT_AVAILABLE_STARTING(10_8); // Read/write, CFNumber(seconds), Optional
	
#define VTPVideoEncoderSpecificationEnableHardwareAcceleratedVideoEncoder ((__bridge NSString *)kVTVideoEncoderSpecification_EnableHardwareAcceleratedVideoEncoder)

#define VTPVideoEncoderSpecificationRequireHardwareAcceleratedVideoEncoder ((__bridge NSString *)kVTVideoEncoderSpecification_RequireHardwareAcceleratedVideoEncoder)

#define VTPCompressionPropertyKeyUsingHardwareAcceleratedVideoEncoder ((__bridge NSString *)kVTCompressionPropertyKey_UsingHardwareAcceleratedVideoEncoder)

// VT_EXPORT const CFStringRef kVTEncodeFrameOptionKey_ForceKeyFrame VT_AVAILABLE_STARTING(10_8); //  CFBoolean
	
// VT_EXPORT const CFStringRef kVTCompressionPropertyKey_CleanAperture VT_AVAILABLE_STARTING(10_8); // Read/write, CFDictionary (see CMFormatDescription.h), Optional
	
// VT_EXPORT const CFStringRef kVTCompressionPropertyKey_PixelAspectRatio VT_AVAILABLE_STARTING(10_8); // Read/write, CFDictionary (see CMFormatDescription.h), Optional
	
// VT_EXPORT const CFStringRef kVTCompressionPropertyKey_FieldCount VT_AVAILABLE_STARTING(10_8); // Read/write, CFNumber (see kCMFormatDescriptionExtension_FieldCount), Optional
	
// VT_EXPORT const CFStringRef kVTCompressionPropertyKey_FieldDetail VT_AVAILABLE_STARTING(10_8); // Read/write, CFString (see kCMFormatDescriptionExtension_FieldDetail), Optional
	
// VT_EXPORT const CFStringRef kVTCompressionPropertyKey_AspectRatio16x9 VT_AVAILABLE_STARTING(10_8); // Read/write, CFBoolean, Optional
	
// VT_EXPORT const CFStringRef kVTCompressionPropertyKey_ProgressiveScan VT_AVAILABLE_STARTING(10_8); // Read/write, CFBoolean, Optional
	
// VT_EXPORT const CFStringRef kVTCompressionPropertyKey_ColorPrimaries VT_AVAILABLE_STARTING(10_8); // Read/write, CFString (see kCMFormatDescriptionExtension_ColorPrimaries), Optional
	
// VT_EXPORT const CFStringRef kVTCompressionPropertyKey_TransferFunction VT_AVAILABLE_STARTING(10_8); // Read/write, CFString (see kCMFormatDescriptionExtension_TransferFunction), Optional
	
// VT_EXPORT const CFStringRef kVTCompressionPropertyKey_YCbCrMatrix VT_AVAILABLE_STARTING(10_8); // Read/write, CFString (see kCMFormatDescriptionExtension_YCbCrMatrix), Optional
	
// VT_EXPORT const CFStringRef kVTCompressionPropertyKey_ICCProfile VT_AVAILABLE_STARTING(10_8); // Read/write, CFData (see kCMFormatDescriptionExtension_ICCProfile), Optional
	
// VT_EXPORT const CFStringRef kVTCompressionPropertyKey_PixelTransferProperties VT_AVAILABLE_STARTING(10_8); // Read/Write, CFDictionary containing properties from VTPixelTransferProperties.h.


@interface VTPCompressionSession (Properties)

- (NSUInteger)numberOfPendingFrames;

- (NSUInteger)maxKeyframeInterval;
- (BOOL)setMaxKeyframeInterval:(NSUInteger)maxKeyFrameInterval error:(NSError **)error;

- (NSTimeInterval)maxKeyframeIntervalDuration;
- (BOOL)setMaxKeyframeIntervalDuration:(NSTimeInterval)maxKeyFrameIntervalDuration error:(NSError **)error;

- (BOOL)allowTemporalCompression;
- (BOOL)setAllowTemporalCompression:(BOOL)allowTemporalCompression error:(NSError **)error;

- (BOOL)allowFrameReordering;
- (BOOL)setAllowFrameReordering:(BOOL)allowFrameReordering error:(NSError **)error;

- (BOOL)realtime;
- (BOOL)setRealtime:(BOOL)realtime error:(NSError **)error;

- (BOOL)usingHardwareAcceleratedVideoEncoder;

@end
