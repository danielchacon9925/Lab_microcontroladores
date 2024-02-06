# Laboratorio 4: Daniel Chacón Mora (B72018) - Erick Sancho (B87388)

import time, json
import requests
import random
import serial

# Configura la URL y el token de acceso de ThingsBoard
#ser = serial.Serial('COMX', 115200)  # Reemplaza 'COMX' con el puerto serie correcto y la velocidad correcta
access_token = 'aknw9qgidmkg8t5radyi'
url = f'https://iot.eie.ucr.ac.cr/api/v1/{access_token}/telemetry'

# URL del servidor ThingsBoard (ajusta la URL y el token de acceso)
thingsboard_url = "https://iot.eie.ucr.ac.cr"

#puerto_serial = serial.Serial("/dev/ttyACM0", 115200, timeout = 1)
#print("Conexión al puerto serial.")

# Función para enviar los datos al dashboard
def send_data_to_thingsboard(data):
    headers = {'Content-Type': 'application/json'}
    payload = {"ts": int(time.time() * 1000), "values": data}
    url = f"{thingsboard_url}/api/v1/{access_token}/telemetry"
    response = requests.post(url, json=payload, headers=headers)

    if response.status_code == 200:
        print("Datos enviados exitosamente a ThingsBoard.")
    else:
        print("Error al enviar datos a ThingsBoard")


try:
    while True:
        # Datos simulados para el giroscopio, el nivel de batería y temperatura
        gyro_data = {
            "Eje X": random.uniform(-100, 100),
            "Eje Y": random.uniform(-100, 100),
            "Eje Z": random.uniform(-100, 100)
        }
        battery_data = {"Batería": round(random.uniform(1, 9), 4)}
        temperature = {"Temperatura": round(random.uniform(1, 50), 4)}
        battery_value = battery_data.get("Batería")

        if battery_value < 7:
            battery_level = {"Nivel batería": "Batería Baja"}

        else:
            battery_level = {"Nivel batería": "Batería Alta"}


        # Combinar datos en un solo diccionario
        combined_data = {**gyro_data, **battery_data, **temperature, **battery_level}

        # Enviar los datos a ThingsBoard
        send_data_to_thingsboard(combined_data)

        # Espera un intervalo de tiempo (puedes ajustarlo)
        time.sleep(0.5)  # Espera 10 segundos

except KeyboardInterrupt:
    print("Conexión al dashboard finalizada.")
