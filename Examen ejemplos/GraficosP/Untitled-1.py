import pandas as pd
import matplotlib.pyplot as plt
import re

# Leer todas las líneas
with open("C:\\Users\\danie\\OneDrive\\Desktop\\Datos", "r") as file:
    lines = [line.strip() for line in file if line.strip()]

temperaturas = []
humedades = []

# Recorremos las líneas de dos en dos: una es temperatura, la siguiente humedad
for i in range(0, len(lines), 2):
    # Línea de temperatura
    temp_line = lines[i]
    temp_match = re.search(r'([\d.]+)', temp_line)
    if temp_match:
        temperaturas.append(float(temp_match.group(1)))
    else:
        print(f"⚠️ No se pudo leer temperatura en línea {i+1}: {temp_line}")

    # Verificar si hay una línea siguiente (de humedad)
    if i + 1 < len(lines):
        hum_line = lines[i + 1]
        hum_match = re.search(r'([\d.]+)', hum_line)
        if hum_match:
            humedades.append(float(hum_match.group(1)))
        else:
            print(f"⚠️ No se pudo leer humedad en línea {i+2}: {hum_line}")

# Asegurarse de que las listas tengan igual longitud
min_len = min(len(temperaturas), len(humedades))
temperaturas = temperaturas[:min_len]
humedades = humedades[:min_len]

# Crear DataFrame
df = pd.DataFrame({
    'Temperatura': temperaturas,
    'Humedad': humedades
})

print("✅ Primeros datos extraídos:")
print(df.head())

# Graficar Temperatura
plt.figure(figsize=(10, 4))
plt.plot(df['Temperatura'], color='red', label='Temperatura (°C)')
plt.title('Temperatura Registrada')
plt.xlabel('Medición')
plt.ylabel('°C')
plt.grid(True)
plt.legend()
plt.show()

# Graficar Humedad
plt.figure(figsize=(10, 4))
plt.plot(df['Humedad'], color='blue', label='Humedad (%)')
plt.title('Humedad Registrada')
plt.xlabel('Medición')
plt.ylabel('%')
plt.grid(True)
plt.legend()
plt.show()

# Gráfico combinado
plt.figure(figsize=(10, 5))
plt.plot(df['Temperatura'], label='Temperatura (°C)', color='red')
plt.plot(df['Humedad'], label='Humedad (%)', color='blue')
plt.title('Temperatura y Humedad Registradas')
plt.xlabel('Medición')
plt.ylabel('Valor')
plt.legend()
plt.grid(True)
plt.show()
