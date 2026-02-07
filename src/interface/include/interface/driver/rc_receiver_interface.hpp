/*
 * @file rc_interface.hpp
 * @date 11/23/24
 * @brief
 *
 * @copyright Copyright (c) 2024 Ruixiang Du (rdu)
 */
#ifndef RC_RECEIVER_INTERFACE_HPP
#define RC_RECEIVER_INTERFACE_HPP

#include "interface/type/base_types.hpp"

#include <array>

namespace xmotion {
struct RcMessage {
  std::array<float, 24> channels = {0};
  bool frame_loss = false;
  bool fault_protection = false;
};

class RcReceiverInterface {
 public:
  virtual ~RcReceiverInterface() = default;

  // Public API
  virtual bool Open() = 0;
  virtual void Close() = 0;
  virtual bool IsOpened() const = 0;

  /// @brief Scale the channel value to [-1, 1]
  /// @param value The raw channel value
  /// @param min The minimum calibration value
  /// @param neutral The neutral/center calibration value
  /// @param max The maximum calibration value
  /// @return Scaled value in range [-1, 1], or 0 if calibration is invalid
  static float ScaleChannelValue(float value, float min, float neutral,
                                 float max) {
    if (value < neutral) {
      float divisor = neutral - min;
      if (divisor == 0.0f) return 0.0f;
      return (value - neutral) / divisor;
    } else {
      float divisor = max - neutral;
      if (divisor == 0.0f) return 0.0f;
      return (value - neutral) / divisor;
    }
  }

  using OnRcMessageReceivedCallback = std::function<void(const RcMessage&)>;
  virtual void SetOnRcMessageReceivedCallback(
      OnRcMessageReceivedCallback cb) = 0;
};
}  // namespace xmotion

#endif  // RC_RECEIVER_INTERFACE_HPP
