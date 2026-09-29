# 🌡️ Módulo de Lectura de Temperatura y Presión — CanSat

Este directorio contiene el código y la documentación para la medición de variables atmosféricas en el proyecto **CanSat** mediante la familia de sensores Bosch **BMP280** y **BME280**.

Ambos módulos se comunican a través del bus **I2C**, lo que permite una integración sencilla compartiendo las mismas líneas de datos.

---

## 📌 Comparativa: BMP280 vs BME280

| Característica | BMP280 | BME280 |
| :--- | :--- | :--- |
| **Magnitudes que mide** | Temperatura, Presión Atmosférica y Altitud | Temperatura, Presión Atmosférica, Altitud y **Humedad** |
| **Protocolo de comunicación** | I2C (o SPI) | I2C (o SPI) |
| **Tensión de alimentación** | **3.3 V** | **3.3 V** |
| **Dirección I2C habitual** | `0x76` o `0x77` | `0x76` o `0x77` |
| **Rol en el CanSat** | Cobertura de la misión primaria | Misión primaria + datos de humedad |

---

## 🔌 Esquema de Conexionado (Bus I2C)

> ⚠️ **Importante:** Alimenta el sensor siempre utilizando el pin de **3.3 V** de tu placa. Conectarlo a 5V puede dañar el sensor.

| Pin del Sensor | Arduino UNO / Nano | ESP32 | Descripción |
| :--- | :--- | :--- | :--- |
| **VCC** | **3V3** (Salida 3.3 V) | **3.3V** | Alimentación del módulo |
| **GND** | GND | GND | Masa común |
| **SCL / SCK** | Pin **A5** | **GPIO 22** | Línea de reloj I2C |
| **SDA** | Pin **A4** | **GPIO 21** | Línea de datos I2C |

---

## 📚 Librerías Requeridas (Arduino IDE)

Instala las bibliotecas necesarias desde el menú **Herramientas > Administrar bibliotecas** (`Ctrl + Shift + I`):

* **Para BMP280:**
  * `Adafruit BMP280 Library`
  * `Adafruit Unified Sensor`

* **Para BME280:**
  * `Adafruit BME280 Library`
  * `Adafruit Unified Sensor`

---
<!--
## ⚙️ Configuración en el Código

En el archivo principal del sensor (`.ino`), descomenta la opción según el chip montado:

```cpp
// ======================================================
// CONFIGURACIÓN DEL SENSOR
// Descomenta SOLO una de las dos líneas:
// ======================================================

#define USAR_BMP280      // Opción BMP280
//#define USAR_BME280    // Opción BME280-->
