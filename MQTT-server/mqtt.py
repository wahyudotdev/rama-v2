import paho.mqtt.client as mqtt
import time
import numpy as np
import mysql.connector
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from matplotlib import style

HOST = '127.0.0.1'

db = mysql.connector.connect(
    host = HOST,
    user = "root",
    passwd = "kenari123",
    database = "sensor"
)
cursor = db.cursor()

def on_connect(client, userdata, flags, rc):
    try:
        if db.is_connected():
            print("Berhasil terhubung ke database")
        client.subscribe("esp")
        print("Connected")
    except:
        print('gagal')
        pass

def on_message(client, userdata, msg):
    payload = msg.payload.decode('utf-8')
    timestamp = int(time.time()*1000)
    sql = 'insert into encoder (pos, timestamp) values (%s, %s)'
    val = (int(payload), timestamp)
    cursor.execute(sql,val)
    db.commit()

def start():
    client.loop_forever()

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message
client.connect(HOST, 1883, 60)

start()