#include <SPI.h>
#include <Controllino.h> /* Usage of CONTROLLINO library allows you to use CONTROLLINO_xx aliases in your sketch. */

void setup() {
 /* Here we initialize USB serial at 9600 baudrate for reporting */
 Serial.begin(4800);
 /* Here we initialize RS485 serial at 9600 baudrate for communication */
 Serial3.begin(4800);
  
  /* Initialize CONTROLLINO RS485 direction control DE/RE pins and Serial3 */
  Controllino_RS485Init(4800);
  Controllino_RS485TxEnable();
  
}

int slaveid = 2;
int slave;
int b_rate = 4800;
bool read = false;
bool sent = false;

void write_rs(const char* payload){
  Serial3.begin(b_rate);
  Controllino_RS485TxEnable();
  Serial3.write(payload);
  Serial3.flush();
  sent = true;
}

String read_rs(){
  String payload, payload_;
  Controllino_RS485RxEnable();
  if(Serial3.available()>0){
    payload = Serial3.readStringUntil('}');
    int br1 = payload.indexOf('{');
    int br2 = payload.indexOf('}');
    payload_ = payload.substring(br1,br2+1);
    Serial3.flush();
    read = true;
  }
  return payload_;
}


void loop() {
write_rs("{\"id\":2,\"sp\":60}");
delay(1000);

String msg = read_rs();

Serial.println(msg);

delay(500);

}
