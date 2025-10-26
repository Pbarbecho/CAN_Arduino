# Nodo TX 
#include <SPI.h>
#include <mcp_can.h>

// Pines (ajusta si cambiaste cableado)
const int PIN_CS  = 10;
const int PIN_INT = 2;
MCP_CAN CAN(PIN_CS);

// ID del frame
const unsigned long CAN_ID_TEMP = 0x100;

void setup() {
 Serial.begin(115200);
 while (!Serial) {}

 if (CAN.begin(MCP_ANY, CAN_500KBPS, MCP_8MHZ) == CAN_OK) {
   Serial.println("CAN OK @500k");
 } else {
   Serial.println("CAN FAIL");
   while (1) {}
 }

 // Modo normal (no loopback)
 CAN.setMode(MCP_NORMAL);
}

void loop() {
 // Simula lectura A0 - temperatura 0..100 C aprox
 int raw = analogRead(A0); // 0..1023
 float tempC = (raw / 1023.0) * 100.0;

 // Empaqueta en decimas (int16)
 int16_t t10 = (int16_t)round(tempC * 10.0);
 byte data[2];
 data[0] = (byte)((t10 >> 8) & 0xFF);
 data[1] = (byte)(t10 & 0xFF);

 byte rc = CAN.sendMsgBuf(CAN_ID_TEMP, 0, 2, data);
 if (rc == CAN_OK) {
   Serial.print("TX C: ");
   Serial.println(tempC, 1);
 } else {
   Serial.println("TX FAIL");
 }

 delay(500);
}
