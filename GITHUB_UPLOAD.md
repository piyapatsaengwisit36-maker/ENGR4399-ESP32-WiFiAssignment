# GitHub upload — Jacob Kebbel

1. Extract `ENGR4399-ESP32-WiFiAssignment.zip`.
2. In GitHub, create a repository named exactly **ENGR4399-ESP32-WiFiAssignment**.
3. Select **Public** visibility, as required by the assignment.
4. Upload the **contents** of the extracted `ENGR4399-ESP32-WiFiAssignment` folder to the repository root:
   - `sketch.ino`
   - `diagram.json`
   - `libraries.txt`
   - `README.md`
   - `GITHUB_UPLOAD.md`
   - the entire `evidence` folder
5. Commit with the message `Add ESP32 WiFi weather display project`.
6. Copy the actual repository URL into report Section 4.
7. Finish Wokwi sign-in, save the prepared simulation, and copy its permanent project URL into the report metadata and Section 4. Also replace the pending Wokwi link in README.md with that actual URL.
8. Upload **Jacob_Kebbel_SAR3_Report.docx** to the Canvas SAR 3 portal.

## Understanding your project
- **Input:** the Refresh button and the API's weather data.
- **Processing:** the ESP32 joins WiFi, makes an HTTP GET request, and parses JSON.
- **Outputs:** SSD1306 OLED and Serial Monitor.
- **Button:** GPIO18 with INPUT_PULLUP; LOW means pressed.
- **Display:** SDA on GPIO21, SCL on GPIO22, address 0x3C.
- **Refresh:** 40 ms debounce; manual requests at least 10 seconds apart; automatic request timer is 60 seconds.
- **API:** Open-Meteo for San Antonio, returning temperature in Fahrenheit and relative humidity.
- **Observed results:** WiFi connected, HTTP 200, JSON parsed, OLED displayed weather, early request was limited, and a later button press made one successful refresh.

The report identifies automatic-refresh and fault-injection tests that have not been observed. Do not change those outcomes to Pass without running the tests.
