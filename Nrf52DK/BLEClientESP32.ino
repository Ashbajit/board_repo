#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEClient.h>
#include <BLEAdvertisedDevice.h>

#define LED_CHARACTERISTIC_UUID "00001525-1212-efde-1523-785feabcd123"  // LED characteristic UUID
#define SERVICE_UUID "00001523-1212-efde-1523-785feabcd123"             // Service UUID on the nRF board

BLEAdvertisedDevice* myDevice; // Creating pointer to instance of object(device)
bool doConnect = false; // flag set up
bool connected = false; // flag set up
BLEClient* pClient; // Creating pointer to instance of an object(BLE Client)
BLERemoteCharacteristic* pRemoteCharacteristic; // Creating pointer to instance of an object(BLE Characteristic)

// Class to handle advertised BLE devices
class MyAdvertisedDeviceCallbacks : public BLEAdvertisedDeviceCallbacks {
  void onResult(BLEAdvertisedDevice advertisedDevice) {
    Serial.print("BLE Advertised Device found: ");
    Serial.println(advertisedDevice.toString().c_str());

    // Check if the device advertises the service we are looking for
    if (advertisedDevice.haveServiceUUID() && advertisedDevice.isAdvertisingService(BLEUUID(SERVICE_UUID))) {
      Serial.println("Found our device!");
      BLEDevice::getScan()->stop();
      myDevice = new BLEAdvertisedDevice(advertisedDevice);
      doConnect = true;
    }
  }
};

void setup() {
  Serial.begin(115200);

  // Initialize BLE
  BLEDevice::init("");

  // Start scanning for BLE devices
  BLEScan* pBLEScan = BLEDevice::getScan();
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks()); // Use the callback to find the desired BLE device
  pBLEScan->setActiveScan(true);
  pBLEScan->start(30); // Scan for 30 seconds
}

void loop() {
  if (doConnect == true) {
    if (connectToServer()) {
      Serial.println("We are now connected to the BLE Server.");
      // After connecting, writing to the characteristic to control the LED
      while(1){
      toggleLED(true);  // Turn on the LED
      delay(2000);      // Wait for 2 seconds
      toggleLED(false); // Turn off the LED
      delay(2000);      // Wait for 2 seconds
      }
    } else {
      Serial.println("Failed to connect.");
    }
    doConnect = false;
  }
}

// Function to connect to the nRF server
bool connectToServer() {
  pClient = BLEDevice::createClient();
  Serial.println("Created client");

  pClient->connect(myDevice);  // Connect to the server
  Serial.println("Connected to server");

  // Obtain the service of the remote BLE server
  BLERemoteService* pRemoteService = pClient->getService(BLEUUID(SERVICE_UUID));
  if (pRemoteService == nullptr) {
    Serial.print("Failed to find our service UUID: ");
    return false;
  }

  // Obtain a reference to the characteristic where we will write to control the LED
  pRemoteCharacteristic = pRemoteService->getCharacteristic(BLEUUID(LED_CHARACTERISTIC_UUID));
  if (pRemoteCharacteristic == nullptr) {
    Serial.println("Failed to find the LED characteristic.");
    return false;
  }

  return true;
}

// Function to toggle the LED
void toggleLED(bool turnOn) {
  if (pRemoteCharacteristic == nullptr) return;

  uint8_t ledState = turnOn ? 1 : 0;
  pRemoteCharacteristic->writeValue(&ledState, 1);  // Write 1 to turn LED on, 0 to turn it off
  Serial.println(turnOn ? "LED ON" : "LED OFF");
}
