#import "VTPCompressionSession+Properties.h"

#import <VideoToolbox/VideoToolbox.h>


@implementation VTPCompressionSession (Properties)

- (NSUInteger)numberOfPendingFrames
{
	NSNumber *value = [self valueForProperty:VTPCompressionPropertyKeyNumberOfPendingFrames error:nil];
	return value.unsignedIntegerValue;
}

- (NSUInteger)maxKeyframeInterval
{
	NSNumber *value = [self valueForProperty:VTPCompressionPropertyKeyMaxKeyFrameInterval error:nil];
	return value.unsignedIntegerValue;
}

- (BOOL)setMaxKeyframeInterval:(NSUInteger)maxKeyFrameInterval error:(NSError **)error
{
	return [self setValue:@(maxKeyFrameInterval) forProperty:VTPCompressionPropertyKeyMaxKeyFrameInterval error:error];
}

- (NSTimeInterval)maxKeyframeIntervalDuration
{
	NSNumber *value = [self valueForProperty:VTPCompressionPropertyKeyMaxKeyFrameIntervalDuration error:nil];
	return value.doubleValue;
}

- (BOOL)setMaxKeyframeIntervalDuration:(NSTimeInterval)maxKeyFrameIntervalDuration error:(NSError **)error
{
	return [self setValue:@(maxKeyFrameIntervalDuration) forProperty:VTPCompressionPropertyKeyMaxKeyFrameIntervalDuration error:error];
}

- (BOOL)allowTemporalCompression
{
	NSNumber *value = [self valueForProperty:VTPCompressionPropertyKeyAllowTemporalCompression error:nil];
	return value.boolValue;
}

- (BOOL)setAllowTemporalCompression:(BOOL)allowTemporalCompression error:(NSError **)error
{
	return [self setValue:@(allowTemporalCompression) forProperty:VTPCompressionPropertyKeyAllowTemporalCompression error:error];
}

- (BOOL)allowFrameReordering
{
	NSNumber *value = [self valueForProperty:VTPCompressionPropertyKeyAllowFrameReordering error:nil];
	return value.boolValue;
}

- (BOOL)setAllowFrameReordering:(BOOL)allowFrameReordering error:(NSError **)error
{
	return [self setValue:@(allowFrameReordering) forProperty:VTPCompressionPropertyKeyAllowFrameReordering error:error];
}

- (BOOL)realtime
{
	NSNumber *value = [self valueForProperty:VTPCompressionPropertyKeyRealTime error:nil];
	return value.boolValue;
}

- (BOOL)setRealtime:(BOOL)realtime error:(NSError **)error
{
	return [self setValue:@(realtime) forProperty:VTPCompressionPropertyKeyRealTime error:nil];
}

- (BOOL)usingHardwareAcceleratedVideoEncoder
{
	NSNumber *value = [self valueForProperty:VTPCompressionPropertyKeyUsingHardwareAcceleratedVideoEncoder error:nil];
	return value.boolValue;
}

@end
