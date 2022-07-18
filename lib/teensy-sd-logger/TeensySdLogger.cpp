#include "TeensySdLogger.hpp"

TeensySdLogger::TeensySdLogger(
    const ParamController& param_controller,
    const EnvironmentController& environment_controller)
    : Logger(param_controller, environment_controller) {
  if (!SD.begin(BUILTIN_SDCARD)) {
    Serial.println("SD card begin() failed");
    sd_init_ = false;
    return;
  }
  Serial.println("SD card begin() success");
  sd_init_ = true;

  const size_t name_size = 100;
  char name[name_size] = "";
  int n = -1;
  for (n = 0; n < 1000; n++) {
    int ret = snprintf(name, name_size, "colordance_log_%d.csv", n);
    if (ret < 0 || ret >= (int)name_size) {
      Serial.printf("Error formatting log file name: %d\n", ret);
      sd_init_ = false;
      return;
    }
    if (!SD.exists(name)) {
      break;
    }
  }
  if (n < 0) {
    Serial.println("All log files occupied, not logging");
    sd_init_ = false;
    return;
  }

  Serial.printf("Logging to '%s'\n", name);
  log_file_ = SD.open(name, FILE_WRITE);
  if (!log_file_) {
    Serial.println("Error opening log file");
  }
}

void TeensySdLogger::Log(const char* message) {
  if (!sd_init_ || !log_file_) {
    return;
  }
  log_file_.println(message);
}
