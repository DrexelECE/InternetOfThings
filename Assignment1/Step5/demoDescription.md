#Project Proposal: Next-Generation Bicycle Computer#
James Kurtz and Greg Yeutter
ECEC 490 - Enabling the Internet of Things
Summer 2014

Many bicyclists use a bike computer as well as a phone-based fitness tracking app to monitor different aspects of their rides and health. But why are these items disconnected? The standard bike computer uses a cadence sensor on the front wheel to get an extremely precise, high-resolution speed measurement. The majority of today's fitness apps depend on location-based input for determining common measurements such as speed and distance. Cellular polling can be very energy-intensive, and as a result, many app designers have sacrificed precision for battery life. The proposed system would provide more precise information with significantly less energy. We seek to build an accurate hardware cadence sensor that communicates with smartphones via BLE, in a manner useful to many new or existing apps. The results will be uploaded to a server from the app, and additional sensors in the phone as well as data from the internet will be combined with the cadence sensor data to provide the rider with a wealth of real-time information.

Further directions for this project:
- Obtain power from bike motion for BLE sensor, eliminating inconvenience (and weight) of batteries. 
- Allow device to communicate directly to internet, without a phone (via GPRS). 
- Live monitoring of moving bicycle (important in case of theft). Obtain data via GPRS or GPS. 
- Integrate other sensors, such as temperature and heart rate, that can provide a more accurate picture of the quality and health benefits/risks of the ride. 
- Detect significant crashes and automatically call for help
