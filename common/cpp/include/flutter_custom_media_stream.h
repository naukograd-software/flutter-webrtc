#ifndef FLUTTER_CUSTOM_MEDIA_STREAM_H
#define FLUTTER_CUSTOM_MEDIA_STREAM_H

#include <string>

#include "flutter_webrtc_base.h"

namespace flutter_webrtc_plugin {

class FlutterCustomMediaStreamProvider : public RefCountInterface {
 public:
  int GetMedia(const EncodableMap& constraints,
               scoped_refptr<RTCPeerConnectionFactory> factory,
               std::unique_ptr<MethodResultProxy> result);
};

class FlutterCustomMediaStream {
 public:
  explicit FlutterCustomMediaStream(FlutterWebRTCBase* base) : base_(base) {}

  void RegisterCustomMediaStreamProvider(
      const std::string& name,
      scoped_refptr<FlutterCustomMediaStreamProvider> provider);

  void GetMedia(const std::string& providerName,
                const EncodableMap& constraints,
                std::unique_ptr<MethodResultProxy> result);

 private:
  FlutterWebRTCBase* base_;

  std::unordered_multimap<std::string,
                          scoped_refptr<FlutterCustomMediaStreamProvider>>
      custom_media_stream_providers_;
};

}  // namespace flutter_webrtc_plugin

#endif  // FLUTTER_CUSTOM_MEDIA_STREAM_H
