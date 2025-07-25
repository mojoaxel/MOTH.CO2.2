#ifndef ModuleWifi_h
#define ModuleWifi_h

#include <Arduino.h>
#include <WiFi.h>

#include "modules/ModuleHttp.h"
#include "types/Config.h"
#include "types/Define.h"

const String WIFI_CONFIG_JSON = "/config/wifi.json";
const String WIFI_CONFIG__DAT = "/config/wifi.dat";
const String WIFI_AP_KEY = "mothbox";
const String WIFI_AP_PWD = "CO2@420PPM";

const uint8_t NETWORKS_BUFFER_SIZE = 10;

const int32_t NETWORK_RSSI_INVALID = -10000;

typedef struct {
    int32_t rssi;
    char key[64];
    char pwd[64];
} network_t;

class ModuleWifi {
   private:
    static String networkName;
    static uint32_t secondstimeExpiry;
    static uint8_t expiryMinutes;
    static void updateSecondstimeExpiry(void* parameter);
    static bool connectToNetwork(config_t& config, network_t& network);
    static bool enableSoftAP(config_t& config);
    static int compareByRssi(const void* a, const void* b);
    static void handleStationDisconnected(WiFiEvent_t event);
    static std::function<void(std::function<bool(config_t& config)>)> actionCompleteCallback;  // callback to main
    static bool configureWifiValPower(config_t& config);

   public:
    static network_t discoveredNetworks[NETWORKS_BUFFER_SIZE];
    static void begin(std::function<void(std::function<bool(config_t& config)>)> actionCompleteCallback);
    static void configure(config_t& config);  // loads json configuration and creates a dat version for faster future accessibility
    static void createDat(config_t& config);
    static bool powerup(config_t& config, bool isManualActivation);
    static bool isPowered();
    static void depower(config_t& config);
    static void access();
    static void expire();
    static uint32_t getSecondstimeExpiry();
    static String getRootUrl();
    static String getAddress();
    static String getNetworkName();
    static String getNetworkPass();
};

#endif