# IOT-watter_level
Wireless Communication between two node MCU with display and some sensors like IR and ultrasonic to measure water depth.

*problem: In my home, drinking water has to be reserved manually (human interaction) by turning on and off the water pump. This process wastes water, as sometimes there is no one to turn off the pump while the water tank is full. Sometimes tank gets empty at some unusual time. So, to tackle those issues, I designed an automated system with minimal cost and modification of the existing process.

 * Hardwares
  a. ESP32
  b. ESP8266
  c. HC-SR04
  d. Standard LC 16x2 display
  
 * Idea: There are two water tanks, a reserve tank, and a filtration tank. Each tank has one Ultrasonic sensor connected with it. Those two sensors are connected with an ESP8266, which acts as a wireless Acess-point(AP) and server. This part stays on water tanks on our rooftop.  
    
   On the other hand, another ESP32 is connected with a 16x2 LC display and the AP of the rooftop wirelessly. This part stays on inside the home and acts as a client. The client makes an HTTP request (REST API) to the server every 30 seconds. The server responds with the reading of both ultrasonic sensors connected to it. Client Node MCU(ESP32) calculates the existing water quantity and necessary quantity to fill up the tanks, then displays it accordingly. The home part is connected with a relay, which can turn on and off the water pump. After crossing a certain threshold quantity, Node MCU from home part turns on the pump and fills up the tanks, also turns the pump off before overflowing.
   
*As the process is automated, displaying the information is unnecessary, but I did it for my mom's satisfaction as she wants to visualize real-time updates of those tanks.
