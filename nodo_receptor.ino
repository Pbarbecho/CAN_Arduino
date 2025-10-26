# Nodo RX
#include <SPI.h>
#include <mcp_can.h>

const int PIN_CS  = 10;
const int PIN_INT = 2;
MCP_CAN CAN(PIN_CS);

const unsigned long CAN_ID_TEMP = 0x100;

void setup() {
  Serial.begin(115200);

  //  Con 3 parametros
  if (CAN.begin(MCP_ANY, CAN_500KBPS, MCP_8MHZ) == CAN_OK) {
    Serial.println("CAN RX OK @500k");
  } else {
    Serial.println("CAN RX FAIL");
    while (1) {}
  }

  CAN.setMode(MCP_NORMAL);
  pinMode(PIN_INT, INPUT);
}

void loop() {
  if (!digitalRead(PIN_INT)) {
    long unsigned int rxId;
    unsigned char len = 0;
    unsigned char buf[8];
    if (CAN.readMsgBuf(&rxId, &len, buf) == CAN_OK) {
      if (rxId == CAN_ID_TEMP && len >= 2) {
        int16_t t10 = (int16_t)((buf[0] << 8) | buf[1]);
        float tempC = t10 / 10.0;
        Serial.print("RX C: ");
        Serial.println(tempC, 1);
      }
    }
  }
}
