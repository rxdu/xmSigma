/* 
 * ctrl_logger.hpp
 * 
 * Created on: Oct 6, 2016
 * Description: 
 * 
 * Copyright (c) 2018 Ruixiang Du (rdu)
 */

#ifndef CTRL_LOGGER_HPP
#define CTRL_LOGGER_HPP

#include <cstdint>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <atomic>
#include <sstream>

#include "logging/details/specialized_logger.hpp"

namespace xmotion {
/// @brief A specialized logger for control data logging to CSV format.
/// @note Thread-safety: This class uses a singleton pattern. The first call to
/// GetLogger() determines the log file path for the entire application lifetime.
/// Subsequent calls with different parameters will NOT change the log path.
/// The logging methods are NOT thread-safe; if multiple threads need to log,
/// external synchronization is required.
class CtrlLogger : public SpecializedLogger {
 public:
  static CtrlLogger &GetLogger(const std::string &logfile_prefix = "",
                               const std::string &logfile_path = "");

  // basic functions
  void AddItemNameToEntryHead(const std::string &name);
  void AddItemDataToEntry(const std::string &item_name,
                          const std::string &data_str);
  void AddItemDataToEntry(uint64_t item_id, const std::string &data_str);

  // extra helper functions
  void AddItemDataToEntry(const std::string &item_name, double data);
  void AddItemDataToEntry(uint64_t item_id, double data);

  // functions that invoke logger calls
  void PassEntryHeaderToLogger();
  void PassEntryDataToLogger();

 private:
  bool head_added_;
  std::map<uint64_t, std::string> entry_names_;
  std::map<std::string, uint64_t> entry_ids_;
  std::atomic<uint64_t> item_counter_;
  std::vector<std::string> item_data_;

  CtrlLogger(const std::string &log_name_prefix,
             const std::string &log_save_path);

  // non-copyable
  CtrlLogger(const CtrlLogger &) = delete;
  CtrlLogger &operator=(const CtrlLogger &) = delete;
};
} // namespace xmotion

#endif /* CTRL_LOGGER_HPP */
