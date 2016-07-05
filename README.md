#VideoToolboxPlus
Objective-C wrapper for and additions to VideoToolbox

###usage
```objectivec
    [[VTPCompressionSession alloc] initWithWidth:1280 height:720 pix_fmt:kCVPixelFormatType_420YpCbCr8Planar<br> codec:kCMVideoCodecType_H264 error:&verror];

parameter setting:
    [mVideoEncode setRealtime:TRUE error:&seterr]; // zero delay
    [mVideoEncode setProfileLevel:(__bridge NSString*)kVTProfileLevel_H264_Baseline_AutoLevel error:&seterr];// profile
    [mVideoEncode setMaxKeyframeInterval:25 error:&seterr];// fps but I frame interval need use encodeXXX funcation assign
    [mVideoEncode setH264EntropyMode:(__bridge NSString*)kVTH264EntropyMode_CAVLC error:&seterr];// CAVLC CABAC
    [mVideoEncode setAverageBitrate:500000 error:&seterr]; // average bitrate 
    dispatch_queue_t encode_queue = dispatch_queue_create("encode.video.h264", NULL);
    [mVideoEncode setDelegate:mVideoEncodeDelegate queue:encode_queue]; // encode delegate assign
init
    [mVideoEncode prepare];

encode funcations:
    encodeYuv420pBytes  encodePixelBuffer  encodeSampleBuffer
custom data fillmode:
    PixelBufferPoolCreatePixelBuffer; // create CVPixelBufferRef from BufferPool
    encodePixelBufferFromPool; // encode
uninit
    [mVideoEncode finish];
