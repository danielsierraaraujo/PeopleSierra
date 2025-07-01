from ubidots import ApiClient
from serial import Serial
import time
import re  # para trabajar con expresiones regulares

arduino = Serial(port='COM5', baudrate=9600, timeout=None)
api = ApiClient(token="BBUS-KJrDRzXyRdwHTBxXxfm48PeIIxZErX")  # Abrir una sola vez
humedad = api.get_variable('6850321824375500103eefbf')

while True:
    while arduino.inWaiting() == 0:
        pass
    try:
        linea = arduino.readline().decode('utf-8').strip()
        print(linea)
        
        # Extraer el valor de humedad usando expresiones regulares
        match = re.search(r'Humedad:\s*([\d.]+)', linea)
        if match:
            data = float(match.group(1))
            print(f"Humedad extraída: {data}")
            humedad.save_value({'value': data})
        else:
            print("No se encontró el dato de humedad en la línea.")
            
    except Exception as e:
        print(f"Error leyendo o enviando datos: {e}")
