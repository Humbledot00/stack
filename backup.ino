#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <Wire.h>

const char *ssid = "Galaxy A129E3D";
const char *password = "bhxg8697";

// Replace with your server address
const char *serverAddress = "http://192.168.149.226:3000/data-receiver";

int value = 0;

const int MPU6050Address = 0x68; // MPU6050 I2C address


void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  Wire.begin();
  initializeMPU6050();
}

void loop() {
  // Your data to be sent


  String dataToSend = readMPU6050Data();

  // Create a WiFiClient object
  WiFiClient client;

  // Create an HTTP object with the WiFiClient
  HTTPClient http;
  http.begin(client, serverAddress);

  // Set content type header
  http.addHeader("Content-Type", "text/plain");

  // Send POST request
  int httpResponseCode = http.POST(dataToSend);

  // Check for a successful response
  if (httpResponseCode > 0) {
    Serial.println("Data sent successfully");
  } else {
    Serial.print("HTTP Error code: ");
    Serial.println(httpResponseCode);
    Serial.println("Error sending data");
  }

  // Close connection
  http.end();

  // Wait for a while before sending the next request
  delay(50);
}

String randomnumber() {
  if (value == 0) {
    value = 1;
    return "10,20,30";
  } else {
    value = 0;
    return "30,20,10";
  }
}

void initializeMPU6050() {
  Wire.beginTransmission(MPU6050Address);
  Wire.write(0x6B); // PWR_MGMT_1 register
  Wire.write(0);    // Set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
}

String readMPU6050Data() {

  int16_t gyroscopeX, gyroscopeY, gyroscopeZ;

  Wire.beginTransmission(MPU6050Address);
  Wire.write(0x3B); // Starting register address for accelerometer data
  Wire.endTransmission(false);
  Wire.requestFrom(MPU6050Address, 14, true);

  Wire.beginTransmission(MPU6050Address);
  if (Wire.endTransmission() != 0) {
    return "MPU6050 not connected";
  }

  Wire.read(); // Temperature data, not used in this example
  Wire.read();
  Wire.read();
  gyroscopeX = Wire.read() << 8 | Wire.read();
  gyroscopeY = Wire.read() << 8 | Wire.read();
  gyroscopeZ = Wire.read() << 8 | Wire.read();

  String data = String(gyroscopeX) + "," + String(gyroscopeY) + "," + String(gyroscopeZ);

  return data;
}
