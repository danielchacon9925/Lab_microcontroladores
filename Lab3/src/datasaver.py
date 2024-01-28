#!/usr/bin/env python3
# Paquete de comunicacion arduino / python
import serial

baud = 9600
samples = 29

file = open("datos.csv", 'w')
file.close()
print("Se leyó el archivo")


# Comunicacion con el arduino: puerto ttyS1
ser = serial.Serial("/tmp/ttyS1", baudrate=baud, timeout=1)
# ser = serial.Serial("/tmp/ttyS1", baudrate=baud, timeout=1)
print("Conexión exitosa")

file = open("datos.csv", 'w')  # Archivo csv
print("Se creó el archivo csv")

contador = 0

while (1):
    getData = str(ser.readline())
    print("getdata", getData)
    data = getData[2:][:-5]
    print(data)

    if contador == 4:
        file = open("datos.csv", "a")
        file.write(data + "\n")
        contador = 0
    else:
        file.write(data + ",")
        contador += 1
