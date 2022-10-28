#define TRANSMIT_LED 23
#define SAMPLING_TIME 1

char* text = "10101010\n";

bool led_state = false;
bool transmit_data = true;
int bytes_counter = 20;
int total_bytes;

void setup() {
  pinMode(TRANSMIT_LED,OUTPUT);
  total_bytes = strlen(text);
  Serial.begin(9600);
}

void loop() {
   while(transmit_data)
   {
    transmit_byte(text[total_bytes - bytes_counter]);
    bytes_counter--;
      if(bytes_counter == 0)
      {
        transmit_data = false;
      }
   }
   transmit_data = true;
   bytes_counter = total_bytes;
 }

void transmit_byte(char data_byte)
{
  digitalWrite(TRANSMIT_LED,LOW); 
  delay(SAMPLING_TIME);
  for(int i = 0; i < 8; i++)
  {
    digitalWrite(TRANSMIT_LED,(data_byte >> i) & 0x01); 
    delay(SAMPLING_TIME);
  }
 dig
 italWrite(TRANSMIT_LED,HIGH); //Return to IDLE state
 delay(SAMPLING_TIME);
}

void serialEvent() {
  char inLocation = Serial.read();
  if (Serial.available()) {

    if (inLocation == '1') {
      text = "10101010\n";
      Serial.println("Location changed to 1");
    } else if (inLocation == '2') {
      text = "20202020\n";
      Serial.println("Location changed to 2");
    } else if (inLocation == '3') {
      text = "30303030\n";
      Serial.println("Location changed to 3");
    } else {
      Serial.println("No allowed location.");
    }
  }
}
