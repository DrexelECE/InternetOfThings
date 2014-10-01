Step 1: Flash the BLEMini using a Windows PC (no mac or linux support) with the HCI_USB.bin firmware.
        Hold the push button on the BLEMini, then connect it to the PC via USB.
        It should show up as a removable storage device.
        Remove any .bin files on the device. It may disconnect after files are deleted/uploaded.
        If so, just disconnect and start the process over.

Step 2: Copy the folders in the Arduino Libraries folder into the actual arduino libraries folder
        It's probably in your Documents folder
        In the RBL_BLEShidld, run the SimpleChat example on your Arduino with the BLEShield attached.
        Setting up the serial monitor should be straight forward.

Step 3: Now that the Arduino is set up and the BLEMini has the HCI firmware, connect the BLEMini
        to the computer WITHOUT holding the push button.  If you used a Windows VM earlier to flash,
        you must SHUT DOWN the virtual machine, otherwise there will be issues.

Step 4: Once the BLEMini is connected:
        If you are on OS X, first disconnect the Arduino, then run Terminal and type:

        ls /dev/tty.*

        There should be a device with 'usbmodem' in its name.
        Copy this filename

        If you're on Windows, you should find out with Serial port the BLEMini is on, which can be found
        in the system devices.

Step 5: Once you have your serial port, open the python script in a text editor and modify the serial port.

Step 6: You must have python installed (default on OS X). Otherwise, install a version of python2.

Step 7: Power on the arduino and open the serial monitor, it should now be advertising.

Step 7: Now you can run the script and follow the instructions at this blog post.
        https://redbearlab.zendesk.com/entries/50650463-ble-mini-connect-to-ble-shield

        On the third 'd' key, there will be a delay, but then eventually it should show "address found"

        Then, press 'e' to establish a connection, followed by 'n' to "subscribe" to the BLEShield

        After that, you can look through the script to see how to actually send data to the arduino.

        Data can be sent via the serial monitor to the python script.
