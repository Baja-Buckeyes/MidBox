#include <SPI.h>
#include <mcp2515.h>

struct can_frame canMsg;
MCP2515 mcp2515(10);

int pot1 = A0;
int pot2 = A1;
int pot3 = A2;
int pot4 = A3;
int val1, val2, val3, val4;

void setup() {
  Serial.begin(115200);
  mcp2515.reset();
  mcp2515.setBitrate(CAN_125KBPS);
  mcp2515.setNormalMode();
  
  Serial.println("CAN Sender Ready");
}

void loop() {
  val1 = analogRead(pot1) / 4;  // Scale down to 8-bit (0-255)
  val2 = analogRead(pot2) / 4;
  val3 = analogRead(pot3) / 4;
  val4 = analogRead(pot4) / 4;

  canMsg.can_id  = 0x100; // Standard ID
  canMsg.can_dlc = 4;     // Data Length Code (4 bytes)
  canMsg.data[0] = val1;  // Send first potentiometer value
  canMsg.data[1] = val2;  // Send second potentiometer value
  canMsg.data[2] = val3;  // Send third potentiometer value
  canMsg.data[3] = val4;  // Send fourth potentiometer value

  if (mcp2515.sendMessage(&canMsg) == MCP2515::ERROR_OK) {
    Serial.println("Message Sent");
  } else {
    Serial.println("Error Sending Message");
  }

  delay(50); // Adjust as needed
}
