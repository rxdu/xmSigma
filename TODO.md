# TODO - xmotion-core Code Quality Improvements

## Critical Issues

- [x] Add missing `#include <vector>` to `motor_controller_array_interface.hpp`
- [x] Fix null pointer dereference in `src/logging/src/logging_utils.hpp:22-25`
- [x] Fix null pointer dereference in `src/logging/include/logging/details/logging_utils.hpp`
- [x] Remove unreachable code after throws in `motor_controller_interface.hpp:39-51`
- [x] Remove unreachable code after throws in `motor_controller_array_interface.hpp:59-105`

## High Severity

- [x] Add bounds check in `ctrl_logger.cpp:54-58` for `AddItemDataToEntry(uint64_t item_id, ...)`
- [x] Fix data precision loss in `ctrl_logger.cpp:61-66` - use std::setprecision(15) instead of std::to_string
- [~] Consolidate duplicated `logging_utils.hpp` files - kept separate (public vs private), fixed both
- [x] Fix buffer overflow risk in `logging_utils.hpp` strftime calls - added null checks and const buffer size

## Medium Severity

- [x] Add divide-by-zero validation in `rc_receiver_interface.hpp:32-39` `ScaleChannelValue`
- [x] Document thread-safety limitations of `CtrlLogger` singleton pattern
- [x] Document thread-safety for `callback_` member in `imu_interface.hpp` and `sensor_interface.hpp`
- [~] Improve error handling in `ctrl_logger.cpp:38-50` - documented, keeping stderr for backwards compat

## Low Severity / Style

- [x] Change `std::string` parameters to `const std::string&` in interface files
- [x] Change `std::string` parameters to `const std::string&` in logging files
- [x] Remove non-standard semicolons after method bodies in interface files
- [x] Rename generic include guard `TYPES_HPP` to `XMOTION_BASE_TYPES_HPP` in `base_types.hpp`
- [x] Rename generic include guard `LOGGING_UTILS_HPP` to `XMOTION_LOGGING_UTILS_HPP`
- [ ] Add proper GoogleTest unit tests for logging utilities

## Summary of Changes

### Files Modified:
1. `src/interface/include/interface/driver/motor_controller_array_interface.hpp`
   - Added `#include <vector>`
   - Removed unreachable return statements after throws
   - Removed trailing semicolons after method bodies

2. `src/interface/include/interface/driver/motor_controller_interface.hpp`
   - Removed unreachable return statements after throws
   - Removed trailing semicolons after method bodies

3. `src/interface/include/interface/driver/rc_receiver_interface.hpp`
   - Added divide-by-zero protection in `ScaleChannelValue`

4. `src/interface/include/interface/driver/imu_interface.hpp`
   - Changed `std::string` to `const std::string&`
   - Added thread-safety documentation

5. `src/interface/include/interface/driver/sensor_interface.hpp`
   - Changed `std::string` to `const std::string&`
   - Removed unreachable return statements
   - Removed trailing semicolons
   - Added thread-safety documentation

6. `src/interface/include/interface/type/base_types.hpp`
   - Renamed include guard to `XMOTION_BASE_TYPES_HPP`

7. `src/logging/include/logging/details/logging_utils.hpp`
   - Renamed include guard to `XMOTION_LOGGING_UTILS_HPP`
   - Fixed null pointer check for `std::getenv("HOME")`
   - Added null check for `localtime()` return
   - Changed `std::string` to `const std::string&`
   - Used constexpr for buffer size

8. `src/logging/src/logging_utils.hpp`
   - Fixed null pointer check for `std::getenv("HOME")`
   - Added null check for `localtime()` return
   - Changed `std::string` to `const std::string&`
   - Used constexpr for buffer size

9. `src/logging/include/logging/ctrl_logger.hpp`
   - Changed `std::string` to `const std::string&`
   - Added thread-safety documentation

10. `src/logging/src/ctrl_logger.cpp`
    - Changed `std::string` to `const std::string&`
    - Added bounds check for `item_id`
    - Fixed precision loss using `std::setprecision(15)`

11. `src/logging/include/logging/details/specialized_logger.hpp`
    - Changed `std::string` to `const std::string&`

12. `src/logging/include/logging/details/logger_interface.hpp`
    - Changed `std::string` to `const std::string&`
    - Removed trailing semicolon after method body

13. `src/logging/include/logging/details/logger_vendor_spdlog.hpp`
    - Changed `std::string` to `const std::string&`

14. `src/logging/src/logger_vendor_spdlog.cpp`
    - Changed `std::string` to `const std::string&`
