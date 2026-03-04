// circuitforge_improved.ino

// Include necessary libraries
#include <ArduinoJson.h>

// Define constants and global variables
const int MAX_ATTEMPTS = 5;
const unsigned long TIMEOUT = 5000;

// Function to handle connections with exponential backoff
void connectWithExponentialBackoff() {
    int attempts = 0;
    unsigned long waitTime;
    while (attempts < MAX_ATTEMPTS) {
        if (connect()) {
            // Connection successful
            return;
        }
        // Calculate wait time with exponential backoff
        waitTime = pow(2, attempts) * 1000; // seconds
        delay(waitTime);
        attempts++;
    }
}

// Function to parse JSON safely
void parseJson(const String& jsonString) {
    StaticJsonDocument<200> doc; // Adjust size as necessary for your application
    DeserializationError error = deserializeJson(doc, jsonString);
    if (error) {
        Serial.print("Failed to parse JSON: ");
        Serial.println(error.c_str());
        return;
    }
    // Process JSON data
}

// Function to prevent buffer overflow
void safeCopy(char* destination, const char* source, size_t destSize) {
    strncpy(destination, source, destSize - 1);
    destination[destSize - 1] = '\0'; // Ensure null termination
}

// Function to check for NaN safely
float safeCheckNaN(float value) {
    if (isnan(value)) {
        Serial.println("Value is NaN. Setting to 0.");
        return 0;
    }
    return value;
}

// Main setup function
void setup() {
    Serial.begin(115200);
    connectWithExponentialBackoff(); // Handle connection with improved robustness
}

// Main loop function
void loop() {
    // Your main loop code here, utilizing non-blocking delays as needed
}
