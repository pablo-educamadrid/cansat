<img width="500" height="auto" alt="image" src="https://github.com/user-attachments/assets/b7596ab2-6d64-43e9-86b2-817f90bbea5f" />


# Práctica: Monitorización de Temperatura, Control de LEDs y Análisis de Señal Analógica

## Objetivos
- Diseñar y simular en Tinkercad un circuito con protoboard que integre un sensor de temperatura (TMP36) y 3 LEDs.
- Comprender la relación entre la lectura analógica (ADC), la tensión eléctrica (Voltios) y la temperatura en grados Celsius (°C).
- Deducir las fórmulas de conversión matemáticas del código a partir de los valores leídos en el Monitor Serie.
- Programar la conversión de valores para activar los LEDs de forma progresiva y transmitir los datos por la consola serie.

---

## Materiales Requeridos
- **Plataforma:** Tinkercad Circuits
- **Componentes:**
  - 1x Placa Arduino UNO
  - 1x Protoboard (placa de pruebas)
  - 1x Sensor de temperatura TMP36
  - 3x LEDs
  - 3x Resistencias de $220\ \Omega$
  - Cables de conexión (*jumpers*)

---

## PARTE 1: Montaje en Tinkercad y Deducción de Fórmulas

### 1.1. Montaje del Circuito
1. Crea un nuevo diseño en Tinkercad Circuits.
2. Coloca la placa Arduino UNO y la protoboard.
3. Conecta las líneas de alimentación de la protoboard a los pines de **5V** y **GND** de Arduino.
4. Conecta el sensor **TMP36**:
   - Pin VCC (izquierda) a la línea de **5V**.
   - Pin Vout (centro) a la entrada analógica **A0**.
   - Pin GND (derecha) a la línea de **GND**.
5. Conecta los **3 LEDs** en los pines digitales **2, 3 y 4**, colocando una resistencia de $220\ \Omega$ entre el cátodo de cada LED y la línea de GND.

### 1.2. Tabla de Toma de Datos
Ejecuta la simulación con un código básico de lectura del pin analógico. Haz clic sobre el sensor TMP36 para desplazar el regulador de temperatura y completa la siguiente tabla con los valores obtenidos:

| Temperatura en Tinkercad (°C) | Valor de Lectura ADC (`analogRead(A0)`) | Voltaje Calculado ($V$) | Temperatura Calculada (°C) |
| :---: | :---: | :---: | :---: |
| **$-40\ ^\circ\text{C}$** | | | |
| **$0\ ^\circ\text{C}$** | | | |
| **$20\ ^\circ\text{C}$** | | | |
| **$25\ ^\circ\text{C}$** | | | |
| **$30\ ^\circ\text{C}$** | | | |
| **$125\ ^\circ\text{C}$** | | | |

### 1.3. Deducción del Código desde el Monitor Serie
A partir de los valores leídos en el Monitor Serie y los datos de tu tabla, deduce las expresiones matemáticas necesarias para responder a las siguientes preguntas:

1. **Paso de ADC a Voltios:** ¿Qué fórmula permite transformar la lectura entera del ADC (rango de $0$ a $1023$) en su equivalente de voltaje (rango de $0\text{ V}$ a $5\text{ V}$)?
2. **Paso de Voltios a °C:** ¿Cómo se convierte el voltaje obtenido a grados Celsius? Explica el motivo de restar $0.5\text{ V}$ (*offset*) y multiplicar por $100$.

---

## PARTE 2: Programación, Control de LEDs y Salida Serie

### 2.1. Conversión de Valores para el Control de LEDs
Escribe la lógica del programa para que los LEDs respondan en función de la temperatura calculada, utilizando una temperatura base de referencia ($\text{TEMP\_BASE} = 20.0\ ^\circ\text{C}$):

- **Si $\text{Temp} < 22.0\ ^\circ\text{C}$:** Apagar todos los LEDs (0 LEDs).
- **Si $22.0\ ^\circ\text{C} \le \text{Temp} < 24.0\ ^\circ\text{C}$:** Encender **1 LED** (Pin 2 en `HIGH`).
- **Si $24.0\ ^\circ\text{C} \le \text{Temp} < 26.0\ ^\circ\text{C}$:** Encender **2 LEDs** (Pines 2 y 3 en `HIGH`).
- **Si $\text{Temp} \ge 26.0\ ^\circ\text{C}$:** Encender **3 LEDs** (Pines 2, 3 y 4 en `HIGH`).

### 2.2. Envío de Datos por el Puerto Serie
Configura la comunicación serie a $9600\text{ baudios}$ para transmitir los datos procesados con el siguiente formato:

```text
Lectura ADC: [valor] | Voltaje: [valor] V | Temp: [valor] °C
