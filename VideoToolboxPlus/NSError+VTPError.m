#import "NSError+VTPError.h"

#import <VideoToolbox/VTErrors.h>


NSString * const VTPErrorDomain = @"VideoToolboxPlusError";

static NSString * DescriptionWithStatus(OSStatus status)
{
	switch(status)
	{
		case kVTPropertyNotSupportedErr:
			return @"Property Not Supported";
			
		default:
			return [NSString stringWithFormat:@"Video Toolbox Error: %d", (int)status];
	}
}


@implementation NSError (VTPError)

+ (instancetype)videoToolboxErrorWithStatus:(OSStatus)status
{
	NSDictionary *userInfo = @{
		NSLocalizedDescriptionKey: DescriptionWithStatus(status),
	};
	
	return [NSError errorWithDomain:VTPErrorDomain code:(NSInteger)status userInfo:userInfo];
}

@end
