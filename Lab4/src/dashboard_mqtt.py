import paho.mqtt.client as mqtt
import json
import time
import random
import requests
import serial



# Callback para manejar la conexión al broker MQTT
def on_connect(client, userdata, flags, rc):
    if rc == 0:
        print("Conexión establecida con el broker MQTT")
    else:
        print("No se pudo establecer la conexión. Código de retorno:", rc)

def on_disconnect(client, userdata, rc):
    if(rc == 0):
        print("Desconexión exitosa")
    else:
        print("Sistema desconectado mediante el código: ", rc)

# Callback para manejar la publicación de mensajes
def on_publish(client, userdata, mid):
    print("Mensaje publicado en el topic", mid)

ser = serial.Serial("/dev/ttyACM0", 115200, timeout = 1)
print("Conectado al puerto serial /dev/ttyACM0")

# Configuración del cliente MQTT
client = mqtt.Client("microcontrolador")
client.connected = False
client.on_connect = on_connect
client.on_disconnect = on_disconnect
client.on_publish = on_publish

# Configuración del broker y token de autenticación
broker_address = "iot.eie.ucr.ac.cr"
port = 1883
token = "aknw9qgidmkg8t5radyi"  
username = "Lab_04_B72018_B87388"

# Conexión al broker MQTT
client.username_pw_set(token)
client.connect(broker_address, port)

# Estructura json
dictionary = dict()

#Rutina de dormir
while client.connected != True:
    client.loop()
    time.sleep(2)

# Bucle principal
    while 1:
        # Lectura de datos del microcontrolador
        # Error estas lineas
        data = ser.readline().decode('utf-8')
        data = data.replace('\r', "").replace('\n', "")
        data = data.split(',')
        if (len(data) == 4):
            dictionary["Eje X"] = data[0]
            dictionary["Eje Y"] = data[1]
            dictionary["Eje Z"] = data[2]
            dictionary["Bateria"] = data[3]

            if (float(data[3]) < 7):
                dictionary["Nivel de bateria"] = "Bateria baja"
            else:
                dictionary["Nivel de bateria"] = "Bateria alta"
            
        payload = json.dumps(dictionary)
        
        # Publicación del mensaje en el topic del dashboard
        topic = "v1/devices/me/telemetry"
        print(payload) 
        client.publish(topic, payload)
        
        # Espera antes de enviar el siguiente mensaje
        time.sleep(1)  # Envía datos cada 1 segundo

