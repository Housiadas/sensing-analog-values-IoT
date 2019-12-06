import paho.mqtt.client as mqtt
import time
import serial
import json
import RPi.GPIO as GPIO

ser = serial.Serial(
    port = "/dev/ttyS0",
    baudrate = 9600,
    parity = serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS,
    timeout=1
    )

# Logger function, it logs the connection with MQTT broker (server)
def on_log(client, userdata, level, buf):
    print("Log: " + buf)

def on_connect(client, userdata, flags, rc):
    if(rc==0):
       print("Connected ok")
    else:
       print("Bad connection, return code=", rc)

def on_disconnect(client, userdata, flags, rc=0):
    print("DisCoNNected: result code = " + str(rc))

def on_message(client, userdata, msg):
        global send
        topic = msg.topic
        m_dec = str(msg.payload.decode("utf-8", "ignore"))
        print("Message received", m_dec)

#The broker's wifi IP differs.
broker = "192.168.1.2"

client = mqtt.Client()

client.on_connect=on_connect
client.on_message=on_message
client.on_disconnect=on_disconnect
#client.on_log=on_log

print("Connecting to broker", broker)
client.connect(broker)
client.subscribe("home/sensor1")

client.loop_start()
time.sleep(4)
try:
    while True:
        if(send = "SEND"):
            d = ser.readline()
            d = d.decode().split("#")   ##to seperate the measured values.
            if(len(d)==2):
                client.publish("home/sensor1", str(d))
except KeyboardInterrupt:
    pass

client.loop_stop()
client.disconnect()

