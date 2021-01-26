## Arduino firmware
First you need to install Arduino IDE. you can see an installation guide [here][1].

Download the arduino sketch from [firmware/walkingbot](../firmware/walkingbot).
To upload an arduino sketch to the NodeMcu board you can follow [this guide][2].

The firmware on the NodeMcu subscribes to an MQTT topic `diff_speed` to get the linear and angular speed commands in a range from 0 to 100 to command the motors that drive the leags on each side of the robot.
It also subscribes to the topic `head_dir` that commands the movement of the head. Note that the current model of the head doesn't have a really wide angle of movement. This will be tackled in future versions no make for a wider vision angle.
The firmware also publishes constantly the readings from the ultrasound sensor to the topic `ultrasound`, which represents the distance in centimeters.

## Node-RED
You will require to install Node-RED in your pc. You can see an installation guide [here][3].

You will also need to install and run a MQTT broker. You can use Eclipse Mosquitto, which is an open-source MQTT message broker. You can see an installation guide [here][4].

Once you have node-RED running, download the Node-RED flow from [nodered/robot-control.json](../nodered/robot-control.json) and import it in your browser.
Then you can make sure that all nodes are set up properly and then click the 'Deploy' button.

## Android Remote XY
You can download the [Remote XY][5] app to your Android device.
Once you run it, you can go to the '+' option, then 'connect to device by IP or URL'.
In the 'Device IP or URL' field enter your local IP address, on which node-RED is running.
In the 'Port' field you can check the selected port in the node-RED configuration for the nodes using Remote XY, in general it is 6377.
Finally you should see a dashboard with a joystick and a control to move the head and see the distance reading.

You can edit the current dashboard in the [Remote XY Editor][6] and then paste the generated code in any node configuration for Remote XY in your node-RED flow.

[1]: https://www.arduino.cc/en/software
[2]: https://www.instructables.com/Quick-Start-to-Nodemcu-ESP8266-on-Arduino-IDE/
[3]: https://nodered.org/docs/getting-started/local
[4]: https://mosquitto.org/download/
[5]: https://play.google.com/store/apps/details?id=com.shevauto.remotexy.free&hl=es&gl=US
[6]: https://remotexy.com/en/editor/
