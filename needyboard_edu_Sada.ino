// SADA와 함께하는 아두이노 매크로패드 프로젝트
// 해당 장치 : needyboard v0.4 (for edu)
// PCB 개발자 @oreothecream, 오류 혹은 질문 사항은 연락주세요.

// 주의사항 :
// PCB는 needyboard "educational version"으로 ghost key, chattering 등에 대한 방지는 생략한 버전입니다.
// 다이오드 및 저항을 사용하고 코드가 복잡하여 제외하였습니다.
// 따라서 키 몇가지를 동시에 누를 경우 제대로 동작하지 않을 수 있습니다.


// !! 본인이 무엇을 수정하는지 모른다면 이 부분은 절대 수정하지 마세요.
#include <HID-Project.h>

#define key1 2
#define key2 3
#define key3 4
#define key4 6
#define key5 7
#define key6 8
#define SW A3
#define CLK A1
#define DT 5

int pins[] = {key1, key2, key3, key4, key5, key6};

int currentStateCLK;       // CLK의 현재 신호상태 저장용 변수
int lastStateCLK;          // 직전 CLK의 신호상태 저장용 변수 
unsigned long lastButtonPress = 0;

void setup()
{
  for(int i=0; i<5; i++)  {
    pinMode(pins[i], INPUT);  // Set the button as an input
    digitalWrite(pins[i], HIGH);  // Pull the button high
  }
  pinMode(SW, INPUT_PULLUP);     // 스위치핀은 내부 풀업저항 사용
  pinMode(CLK,INPUT);
	pinMode(DT,INPUT);
  lastStateCLK = digitalRead(CLK);

  Keyboard.begin();
  Mouse.begin();
  Consumer.begin();
}

// 특별한 고지가 없으면 여기서부터는 수정해도 됩니다.

void loop()
{
  // Keyboard Inputs ---------------------------
  // 키 기본 입력 : Keyboard.write();
  // 키 누름 유지 : Keyboard.press();
  // 키 떼기 : Keyboard.release();
  // 키 전체 떼기 : Keyboard.releaseAll();
  // 키 문자열 출력 : Keyboard.print();, Keyboard.println();

  // Key 1이 눌렸을 때:
  if (digitalRead(key1) == 0)
  {
    Keyboard.write(KEY_1);
    delay(100);
  }

  // Key 2가 눌렸을 때 :
  if (digitalRead(key2) == 0)
  {
    Keyboard.write(KEY_2);
    delay(100);
  }

  // Key 3이 눌렸을 때 :
  if (digitalRead(key3) == 0)
  {
    Keyboard.write(KEY_3);
    delay(100);
  }

  // Key 4가 눌렸을 때 :
  if (digitalRead(key4) == 0)
  {
    Keyboard.print("Hello This is SADA!");
    delay(100);
  }

  // Key 5가 눌렸을 때 :
  if (digitalRead(key5) == 0)
  {
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_C);
    Keyboard.releaseAll();
    delay(100);
  }

  // Key 6이 눌렸을 때 :
  if (digitalRead(key6) == 0)
  {
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_V);
    Keyboard.releaseAll();
    delay(100);
  }


  currentStateCLK = digitalRead(CLK);

	if (currentStateCLK != lastStateCLK  && currentStateCLK == 1){
		if (digitalRead(DT) != currentStateCLK) {  // 신호가 다르다면 시계방향 회전
      // **********노브 시계방향 회전 시 코드를 작성해주세요.
      Keyboard.write(MEDIA_VOLUME_UP);
  
		} else {                                 // 신호가 같다면 반시계방향 회전
      // **********노브 반시계방향 회전 시 코드를 작성해주세요.
      Keyboard.write(MEDIA_VOLUME_DOWN);
		}
    delay(15);
	}

	// 현재의 CLK상태를 저장
	lastStateCLK = currentStateCLK;

  int btnState = digitalRead(SW);
  if (btnState == LOW) {
		//버튼이 눌린지 50ms가 지났는지 확인, 즉 버튼이 한번 눌린 후 최소 50 ms는 지나야 버튼이 다시 눌린것으로 감지
		if (millis() - lastButtonPress > 50) {  // 50ms 이상 지났다면 
      // ********* 여기에 노브 버튼 눌렸을 때 코드를 작성해주세요. 
			Keyboard.write(MEDIA_VOLUME_MUTE);
		}

		// 마자막 버튼이 눌린 시간 저장
		lastButtonPress = millis();
	}
}