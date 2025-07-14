#include "flutter_custom_media_stream.h"

#include <iostream>
#include <ostream>

namespace flutter_webrtc_plugin {

void FlutterCustomMediaStream::RegisterCustomMediaStreamProvider(
    const std::string& name,
    scoped_refptr<FlutterCustomMediaStreamProvider> provider) {
  if (custom_media_stream_providers_.find(name) !=
      custom_media_stream_providers_.end()) {
    std::cout
        << "RegisterCustomMediaStreamProvider: already registered provider: "
        << name << std::endl;

    return;
  }

  custom_media_stream_providers_.insert({name, provider});
}

void FlutterCustomMediaStream::GetMedia(
    const std::string& providerName,
    const EncodableMap& constraints,
    std::unique_ptr<MethodResultProxy> result) {
  const auto provider_it = custom_media_stream_providers_.find(providerName);

  if (custom_media_stream_providers_.find(providerName) ==
      custom_media_stream_providers_.end()) {
    result->Error("GetCustomMediaFailed", "provider not found");
    return;
  }

  const auto& provider = provider_it->second;
  provider->GetMedia(constraints, base_->factory_, std::move(result));
}

}  // namespace flutter_webrtc_plugin