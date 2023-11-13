#include <M5EPD.h>
#include <BleKeyboard.h>

M5EPD_Canvas canvas(&M5.EPD);
BleKeyboard bleKeyboard;

int point[2][2];

int btnSize = 150;
int btnPitch = 170;
int xOffset = 20;
int yOffset = 60;
int PrtOffsetx = 25;
int PrtOffsety = -13;
int btn0 = yOffset + 0 * btnPitch;
int btn1 = yOffset + 1 * btnPitch;
int btn2 = yOffset + 2 * btnPitch;
int btn3 = yOffset + 3 * btnPitch;
int btn4 = yOffset + 4 * btnPitch;

void setup() {
  // put your setup code here, to run once:
  M5.begin();
  adc_power_acquire();
  bleKeyboard.begin();
  M5.EPD.SetRotation(270);
  M5.TP.SetRotation(270);
  M5.EPD.Clear(true);
  canvas.createCanvas(540, 960);
  canvas.setTextSize(3);

  for (int i = 0; i < 3; i++) {
    canvas.drawRoundRect(xOffset + i * btnPitch, btn0, btnSize, btnSize, 10, WHITE); //
  }
  canvas.drawString("Insert", xOffset + 0 * btnPitch + PrtOffsetx, btn0 + 0.5 * btnSize + PrtOffsety);
  canvas.drawString("Home", xOffset + 1 * btnPitch + PrtOffsetx, btn0 + 0.5 * btnSize + PrtOffsety);
  canvas.drawString("Page", xOffset + 2 * btnPitch + PrtOffsetx, btn0 + 0.5 * btnSize + PrtOffsety * 1.8);
  canvas.drawString("Up", xOffset + 2 * btnPitch + PrtOffsetx, btn0 + 0.5 * btnSize + PrtOffsety * (-.6));

  for (int i = 0; i < 3; i++) {
    canvas.drawRoundRect(xOffset + i * btnPitch, btn1, btnSize, btnSize, 10, WHITE); //
  }
  canvas.drawString("Delete", xOffset + 0 * btnPitch + PrtOffsetx, btn1 + 0.5 * btnSize + PrtOffsety);
  canvas.drawString("end", xOffset + 1 * btnPitch + PrtOffsetx, btn1 + 0.5 * btnSize + PrtOffsety);
  canvas.drawString("Page", xOffset + 2 * btnPitch + PrtOffsetx, btn1 + 0.5 * btnSize + PrtOffsety * 1.8);
  canvas.drawString("Down", xOffset + 2 * btnPitch + PrtOffsetx, btn1 + 0.5 * btnSize + PrtOffsety * (-.6));

  for (int i = 0; i < 3; i++) {
    canvas.drawRoundRect(xOffset + i * btnPitch, btn2, btnSize, btnSize, 10, WHITE); //
  }
  canvas.drawString("Cut", xOffset + 0 * btnPitch + PrtOffsetx, btn2 + 0.5 * btnSize + PrtOffsety);
  canvas.drawString("Copy", xOffset + 1 * btnPitch + PrtOffsetx, btn2 + 0.5 * btnSize + PrtOffsety);
  canvas.drawString("Paste", xOffset + 2 * btnPitch + PrtOffsetx, btn2 + 0.5 * btnSize + PrtOffsety);

  for (int i = 1; i < 2; i++) {
    canvas.drawRoundRect(xOffset + i * btnPitch, btn3, btnSize, btnSize, 10, WHITE); //
  }
  canvas.drawString("^", xOffset + 1 * btnPitch + btnSize / 2 - 7, btn3 + 0.5 * btnSize + PrtOffsety);

  for (int i = 0; i < 3; i++) {
    canvas.drawRoundRect(xOffset + i * btnPitch, btn4, btnSize, btnSize, 10, WHITE); //
  }
  canvas.drawString("<", xOffset + 0 * btnPitch + btnSize / 2 - 10, btn4 + 0.5 * btnSize + PrtOffsety);
  canvas.drawString("v", xOffset + 1 * btnPitch + btnSize / 2 - 7, btn4 + 0.5 * btnSize + PrtOffsety);
  canvas.drawString(">", xOffset + 2 * btnPitch + btnSize / 2 - 10, btn4 + 0.5 * btnSize + PrtOffsety);

  canvas.pushCanvas(0, 0, UPDATE_MODE_DU4);

}

void loop() {
  // put your main code here, to run repeatedly:

  if (M5.TP.avaliable()) {
    if (!M5.TP.isFingerUp()) {
      M5.TP.update();
      for (int i = 0; i < 2; i++) {
        tp_finger_t FingerItem = M5.TP.readFinger(i);
        if ((point[i][0] != FingerItem.x) || (point[i][1] != FingerItem.y)) {
          point[i][0] = FingerItem.x;
          point[i][1] = FingerItem.y;
          Serial.printf("Finger ID:%d-->X: %d*C  Y: %d  Size: %d\r\n", FingerItem.id, FingerItem.x, FingerItem.y , FingerItem.size);

          if ((point[i][0] >= xOffset + 0 * btnPitch && point[i][0] <= xOffset + 0 * btnPitch + btnSize) && ( point[i][1] >= btn0 && point[i][1] <= btn0 + btnSize)) {
            Serial.println("Sending Insert");
            bleKeyboard.write(KEY_INSERT);
          }
          if ((point[i][0] >= xOffset + 0 * btnPitch && point[i][0] <= xOffset + 0 * btnPitch + btnSize) && ( point[i][1] >= btn1 && point[i][1] <= btn1 + btnSize)) {
            Serial.println("Sending Delete");
            bleKeyboard.write(KEY_DELETE);
          }
          if ((point[i][0] >= xOffset + 1 * btnPitch && point[i][0] <= xOffset + 1 * btnPitch + btnSize) && ( point[i][1] >= btn0 && point[i][1] <= btn0 + btnSize)) {
            Serial.println("Sending Home");
            bleKeyboard.write(KEY_HOME);
          }
          if ((point[i][0] >= xOffset + 1 * btnPitch && point[i][0] <= xOffset + 1 * btnPitch + btnSize) && ( point[i][1] >= btn1 && point[i][1] <= btn1 + btnSize)) {
            Serial.println("Sending End");
            bleKeyboard.write(KEY_END);
          }
          if ((point[i][0] >= xOffset + 2 * btnPitch && point[i][0] <= xOffset + 2 * btnPitch + btnSize) && ( point[i][1] >= btn0 && point[i][1] <= btn0 + btnSize)) {
            Serial.println("Sending PageUp");
            bleKeyboard.write(KEY_PAGE_UP);
          }
          if ((point[i][0] >= xOffset + 2 * btnPitch && point[i][0] <= xOffset + 2 * btnPitch + btnSize) && ( point[i][1] >= btn1 && point[i][1] <= btn1 + btnSize)) {
            Serial.println("Sending PageDown");
            bleKeyboard.write(KEY_PAGE_DOWN);
          }

          if ((point[i][0] >= xOffset + 0 * btnPitch && point[i][0] <= xOffset + 0 * btnPitch + btnSize) && ( point[i][1] >= btn2 && point[i][1] <= btn2 + btnSize)) {
            Serial.println("Sending Cut");
            bleKeyboard.press(KEY_LEFT_CTRL);
            bleKeyboard.write("x");
            delay(100);
            bleKeyboard.releaseAll();
          }
          if ((point[i][0] >= xOffset + 1 * btnPitch && point[i][0] <= xOffset + 1 * btnPitch + btnSize) && ( point[i][1] >= btn2 && point[i][1] <= btn2 + btnSize)) {
            Serial.println("Sending DownArrow");
            bleKeyboard.press(KEY_LEFT_CTRL);
            bleKeyboard.press("c");
            delay(100);
            bleKeyboard.releaseAll();
          }
          if ((point[i][0] >= xOffset + 2 * btnPitch && point[i][0] <= xOffset + 2 * btnPitch + btnSize) && ( point[i][1] >= btn2 && point[i][1] <= btn2 + btnSize)) {
            Serial.println("Sending RightArrow");
            bleKeyboard.press(KEY_LEFT_CTRL);
            bleKeyboard.press("v");
            delay(100);
            bleKeyboard.releaseAll();
          }

          if ((point[i][0] >= xOffset + 1 * btnPitch && point[i][0] <= xOffset + 1 * btnPitch + btnSize) && ( point[i][1] >= btn3 && point[i][1] <= btn3 + btnSize)) {
            Serial.println("Sending UpArrow");
            bleKeyboard.write(KEY_UP_ARROW);
          }

          if ((point[i][0] >= xOffset + 0 * btnPitch && point[i][0] <= xOffset + 0 * btnPitch + btnSize) && ( point[i][1] >= btn4 && point[i][1] <= btn4 + btnSize)) {
            Serial.println("Sending LeftArrow");
            bleKeyboard.write(KEY_LEFT_ARROW);
          }
          if ((point[i][0] >= xOffset + 1 * btnPitch && point[i][0] <= xOffset + 1 * btnPitch + btnSize) && ( point[i][1] >= btn4 && point[i][1] <= btn4 + btnSize)) {
            Serial.println("Sending DownArrow");
            bleKeyboard.write(KEY_DOWN_ARROW);
          }
          if ((point[i][0] >= xOffset + 2 * btnPitch && point[i][0] <= xOffset + 2 * btnPitch + btnSize) && ( point[i][1] >= btn4 && point[i][1] <= btn4 + btnSize)) {
            Serial.println("Sending RightArrow");
            bleKeyboard.write(KEY_RIGHT_ARROW);
          }
        }
      }
    }
  }
}
