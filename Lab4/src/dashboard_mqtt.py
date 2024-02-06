import paho.mqtt.client as mqtt
import json
import time
import random
import requests



# Callback para manejar la conexión al broker MQTT
def on_connect(client, userdata, flags, rc):
    if rc == 0:
        print("Conexión establecida con el broker MQTT")
    else:
        print("No se pudo establecer la conexión. Código de retorno:", rc)

# Callback para manejar la publicación de mensajes
def on_publish(client, userdata, mid):
    print("Mensaje publicado en el topic")

# Configuración del cliente MQTT
client = mqtt.Client("microcontrolador")
client.on_connect = on_connect
client.on_publish = on_publish

# Configuración del broker y token de autenticación
broker_address = "iot.eie.ucr.ac.cr"
port = 1883
token = "aknw9qgidmkg8t5radyi"  

# Conexión al broker MQTT
client.username_pw_set(token)
client.connect(broker_address, port)

# Bucle principal
try:
    while True:
        # Lectura de datos del microcontrolador
        temperature = round(random.uniform(1, 50), 4)
        battery_data = round(random.uniform(1, 9), 4)
        Eje_X = random.uniform(-100, 100)
        Eje_Y = random.uniform(-100, 100)
        Eje_Z = random.uniform(-100, 100)
    
        if battery_data < 7:
            battery_level = "Batería Baja"
    
        else:
            battery_level = "Batería Alta"
        
        # Construcción del mensaje JSON
        data = {
            "Eje X": Eje_X,
            "Eje Y": Eje_Y,
            "Eje Z": Eje_Z,
            "Batería": battery_data,
            "Nivel de batería": battery_level,
            "Temperatura": temperature,
        }
        payload = json.dumps(data)
    
        # Publicación del mensaje en el topic del dashboard
        topic = "v1/devices/me/telemetry"
        client.publish(topic, payload)
    
        # Espera antes de enviar el siguiente mensaje
        time.sleep(1)  # Envía datos cada 1 segundo

except KeyboardInterrupt:
    print("Conexión al dashboard finalizada.")
