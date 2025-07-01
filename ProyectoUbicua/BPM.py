from ubidots import ApiClient
from serial import Serial
import time
import re

arduino = Serial(port='COM3', baudrate=9600, timeout=None)

api = ApiClient(token="BBUS-gjIq6FsboSFAROEFRGhWTmHJmHUvlE")
bpm_var = api.get_variable("6862ad39ce1381e4a92027fd")
luz_var = api.get_variable("6862acd131251fe6398dceec")


# Loop principal
while True:
    try:
        if arduino.inWaiting():
            linea = arduino.readline().decode('utf-8').strip()

            bpm = float(linea.strip())
            print("BPM:", bpm)
            bpm_var.save_value({'value': bpm})
    except Exception as e:
        print(f"[!] Error: {e}")


