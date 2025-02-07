#include <SPI.h>
#include <mcp2515.h>

struct can_frame canMsg;
MCP2515 mcp2515(10);

void setup() {
  Serial.begin(115200);
  mcp2515.reset();
  mcp2515.setBitrate(CAN_125KBPS);
  mcp2515.setNormalMode();
  
  Serial.println("CAN Receiver Ready");
}

void loop() {
  if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK) {
    Serial.print("Received ID: 0x");
    Serial.print(canMsg.can_id, HEX);
    Serial.print(" | ");

    if (canMsg.can_dlc == 4) {
      Serial.print("POT1: "); Serial.print(canMsg.data[0] * 4);
      Serial.print(" | POT2: "); Serial.print(canMsg.data[1] * 4);
      Serial.print(" | POT3: "); Serial.print(canMsg.data[2] * 4);
      Serial.print(" | POT4: "); Serial.println(canMsg.data[3] * 4);
    }
  }
}
