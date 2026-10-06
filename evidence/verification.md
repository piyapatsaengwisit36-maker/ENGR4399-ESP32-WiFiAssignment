# Observed Wokwi verification

Date: October 5, 2026. API timestamp: 2026-10-05T19:15 America/Chicago.

| Check | Observed result | Status |
| --- | --- | --- |
| Build / boot | Wokwi compiled firmware and printed ESP32 boot log | Pass |
| WiFi | Wokwi-GUEST connected; IP 10.10.0.2 | Pass |
| HTTP API | HTTP status 200 and raw Open-Meteo JSON | Pass |
| JSON / OLED | Parsed 83.2 F, 53% humidity, timestamp; OLED displayed these values | Pass |
| Early manual refresh | Debounced sticky button press before 10 simulated seconds printed rate-limit message | Pass |
| Manual refresh after limit | Held press at approximately 12.6 simulated seconds triggered one new HTTP 200 response and updated outputs | Pass |
| Automatic 60-second refresh | Still to be exercised | Pending |
| Fault injection | Error handling reviewed; WiFi/HTTP/JSON faults not injected | Pending |

The browser ran the simulation at about 3% of real time. For reliable button testing in a slow simulator, Cmd-click (Mac) or Ctrl-click (Windows/Linux) to hold the button, then click again to release. The simulator's effective speed can make a brief mouse click shorter than the 40 ms debounce interval.

Public publication has been approved. Wokwi requires account sign-in before saving; Google passkey verification remains incomplete. The student will create the required public GitHub repository and upload the supplied files. Neither permanent URL is available yet.

A later live browser observation reported that the Wokwi public IoT gateway unexpectedly closed its connection. Earlier HTTP 200 results and screenshots remain valid evidence of successful operation; restarting the simulation may be needed to restore the gateway.
