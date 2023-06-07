#include "TeensySdLogger.hpp"

#include <TimeLib.h>

TeensySdLogger::TeensySdLogger(
    const ParamController& param_controller,
    const EnvironmentController& environment_controller)
    : Logger(param_controller, environment_controller) {}

bool TeensySdLogger::Begin() {
  if (!SD.begin(BUILTIN_SDCARD)) {
    Serial.println("SD card begin() failed");
    sd_init_ = false;
    return false;
  }
  Serial.println("SD card begin() success");
  sd_init_ = true;

  const size_t name_size = 100;
  char name[name_size] = "";
  int n = -1;
  for (n = 0; n < 10000; n++) {
    int ret = snprintf(name, name_size, "colordance_log_%d.csv", n);
    if (ret < 0 || ret >= (int)name_size) {
      Serial.print("Error formatting log file name: ");
      Serial.println(ret);
      sd_init_ = false;
      return false;
    }
    if (!SD.exists(name)) {
      break;
    }
  }
  if (n < 0) {
    Serial.println("All log files occupied, not logging");
    sd_init_ = false;
    return false;
  }

  Serial.print("Logging to: ");
  Serial.println(name);
  log_file_ = SD.open(name, FILE_WRITE);
  if (!log_file_) {
    Serial.println("Error opening log file");
    return false;
  }
  sd_flush_timer_.Reset();
  return true;
}

void TeensySdLogger::Log(const char* message) {
  if (!sd_init_ || !log_file_) {
    return;
  }
  log_file_.println(message);

  // Flush the cache periodically. According to the documentation, the SD
  // library has a 512-byte buffer, and should flush once that's full, but
  // experimentally, without this, nothing is ever written to the file.
  if (sd_flush_timer_.Expired()) {
    log_file_.flush();
    sd_flush_timer_.Reset();
  }
}

char* TeensySdLogger::GetTimestamp() {
  static constexpr uint32_t kBufferSize = 30;
  static char buffer[kBufferSize];

  time_t time = now();
  snprintf(buffer, kBufferSize, "%u-%u-%u %u:%u:%u", year(time), month(time),
           day(time), hour(time), minute(time), second(time));

  return buffer;
}
