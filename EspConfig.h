#ifndef _ESP_CONFIG_H
#define _ESP_CONFIG_H

#include <Arduino.h>

#if defined(ESP8266) || defined(ESP32)

#include <FS.h>

#if defined(ESP32)  || defined(ESP8266)
  #include <LittleFS.h>
#endif

class EspDeviceConfig;

class EspConfig {
public:
  EspConfig(String appName);
  ~EspConfig();

  void    setup();
  String  getValue(String name);
  String  getValue(String name, String def);
  void    setValue(String name, String value);
  void    unsetValue(String name);
  void    unsetAll();
  bool    saveToFile();
  bool    hasChanged() { return configChanged; };
  bool    littlefsMounted() { return mLittlefsMounted; };

  File    getConfigFile();
  
  EspDeviceConfig   getDeviceConfig(String deviceName);
  
protected:
  struct ConfigList
  {
    String      name, value;
    ConfigList  *next;
  };

  bool          configChanged = false, mLittlefsMounted=false;
  ConfigList    *first = NULL;
  String        mAppName;

  File configFile;

  String fileName() { return "/config/" + mAppName + ".cfg"; };
  bool openRead();
  bool openWrite();
  bool loadData();
};

class EspDeviceConfig : public EspConfig {
public:
  EspDeviceConfig(String deviceName);
};

extern EspConfig espConfig;

#endif  // ESP8266 || ESP32

#endif	// _ESP_CONFIG_H
