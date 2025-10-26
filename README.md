# Laboratorio: Implementación de una Red CAN con Arduino y MCP2515

En esta primera parte del laboratorio se implementará una red **CAN de 2 nodos** (ver Figura 2.1).  
Un nodo **Tx** transmite un mensaje tipo CAN de temperatura, que lee del potenciómetro conectado al Arduino, y el segundo nodo **Rx** lo recibe y lo imprime por el monitor serial.  

A continuación, se listan las instrucciones generales para la implementación.

---

## Conexión del módulo MCP2515 con Arduino UNO

| MCP2515 | ARDUINO UNO | Descripción          |
|----------|--------------|----------------------|
| **VCC**  | 5V           | Alimentación         |
| **GND**  | GND          | Tierra               |
| **SCK**  | D13          | Reloj SPI            |
| **MISO** | D12          | Datos hacia Arduino  |
| **MOSI** | D11          | Datos hacia MCP      |
| **CS**   | D10          | Chip Select          |
| **INT**  | D2           | Interrupción         |

**Tabla 2.1:** Pinout MCP2515 - Arduino UNO

---

## Descripción general

- El **nodo transmisor (Tx)** leerá una señal analógica del potenciómetro y la enviará como mensaje CAN.
- El **nodo receptor (Rx)** recibirá el mensaje y lo mostrará en el **Serial Monitor**.
- Ambos nodos deben configurarse a la misma tasa de bits (**bitrate**) para una correcta comunicación.

---

> 💡 **Nota:** El módulo MCP2515 se comunica con el Arduino mediante la interfaz **SPI**, por lo que es importante respetar el pinout indicado.
