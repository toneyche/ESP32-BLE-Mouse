#include "BleConnectionStatus.h"
#include <Arduino.h>
BleConnectionStatus::BleConnectionStatus(void) {
}

void BleConnectionStatus::onConnect(BLEServer* pServer)
{
  this->connected = true;
  BLE2902* desc = (BLE2902*)this->inputMouse->getDescriptorByUUID(BLEUUID((uint16_t)0x2902));
  desc->setNotifications(true);
}

void BleConnectionStatus::onDisconnect(BLEServer* pServer)
{
  this->connected = false;
  BLE2902* desc = (BLE2902*)this->inputMouse->getDescriptorByUUID(BLEUUID((uint16_t)0x2902));
  desc->setNotifications(false);
  uint8_t* mac = param->connect.remote_bda;
  //char macStr[18];
  //sprintf(macStr, "%02X:%02X:%02X:%02X:%02X:%02X", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
 //Serial.println(macStr);

  esp_err_t status = esp_ble_gap_read_rssi(mac);
  if (status != ESP_OK)
  {
    Serial.println("Failed to read RSSI");
  }
  for(int i = 0; i < 6; i++)
  {
    macc[i] = mac[i];
  }
}
