/* 
 * ctrl_logger.cpp
 * 
 * Created on: Oct 6, 2016
 * Description: 
 * 
 * Copyright (c) 2018 Ruixiang Du (rdu)
 */

#include "logging/ctrl_logger.hpp"

#include <iostream>
#include <sstream>
#include <iomanip>
#include <ctime>

namespace xmotion {
CtrlLogger::CtrlLogger(const std::string &logfile_prefix,
                       const std::string &logfile_path)
    : SpecializedLogger(logfile_prefix, logfile_path),
      head_added_(false),
      item_counter_(0) {}

CtrlLogger &CtrlLogger::GetLogger(const std::string &logfile_prefix,
                                  const std::string &logfile_path) {
  static CtrlLogger instance(logfile_prefix, logfile_path);
  return instance;
}

void CtrlLogger::AddItemNameToEntryHead(const std::string &name) {
  auto it = entry_ids_.find(name);

  if (it == entry_ids_.end()) {
    entry_names_[item_counter_] = name;
    entry_ids_[name] = item_counter_++;
  }
}

void CtrlLogger::AddItemDataToEntry(const std::string &item_name,
                                    const std::string &data_str) {
  if (!head_added_) {
    std::cerr << "No heading for log entries has been added, data ignored!"
              << std::endl;
    return;
  }

  auto it = entry_ids_.find(item_name);

  if (it != entry_ids_.end())
    item_data_[(*it).second] = data_str;
  else
    std::cerr << "Failed to find data entry!" << std::endl;
}

// adding data using id is faster than using the name
void CtrlLogger::AddItemDataToEntry(uint64_t item_id,
                                    const std::string &data_str) {
  if (!head_added_)
    return;

  if (item_id >= item_counter_) {
    std::cerr << "Invalid item ID: " << item_id << " (max: " << item_counter_ - 1 << ")" << std::endl;
    return;
  }

  item_data_[item_id] = data_str;
}

void CtrlLogger::AddItemDataToEntry(const std::string &item_name, double data) {
  std::ostringstream oss;
  oss << std::setprecision(15) << data;
  AddItemDataToEntry(item_name, oss.str());
}

void CtrlLogger::AddItemDataToEntry(uint64_t item_id, double data) {
  std::ostringstream oss;
  oss << std::setprecision(15) << data;
  AddItemDataToEntry(item_id, oss.str());
}

void CtrlLogger::PassEntryHeaderToLogger() {
  if (item_counter_ == 0)
    return;

  std::string head_str;
  for (const auto &item : entry_names_)
    head_str += item.second + " , ";

  std::size_t found = head_str.rfind(" , ");
  if (found != std::string::npos)
    head_str.erase(found);

#ifdef ENABLE_LOGGING
  logger_->info(head_str);
#endif

  item_data_.resize(item_counter_);
  head_added_ = true;
}

void CtrlLogger::PassEntryDataToLogger() {
  std::string log_entry;

  for (auto it = item_data_.begin(); it != item_data_.end(); it++) {
    std::string str;

    if ((*it).empty())
      str = "0";
    else
      str = *it;

    if (it != item_data_.end() - 1)
      log_entry += str + " , ";
    else
      log_entry += str;
  }

#ifdef ENABLE_LOGGING
  if (!log_entry.empty())
    logger_->info(log_entry);
#endif
}
} // namespace xmotion