// Eight pots to MIDI control data
// Code by James Henderson (slightly edited by Sebastian Tomczak)

// command bytes
byte status_byte = 176; // control change on channel 1
byte cc_number = 0; // value for control number

// init transfer and operation values
byte data_send = 0; // stores outgoing byte for spi bus

//to store pot valuse to filter output
byte filter[8];

// init looping and working values
int workPort = 0; // working value for outgoing port
int workAn = 5; // reading from analog in 0

// setup begins here
void setup() {
  Serial.begin(31250); // open serial port
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
}

// main program begins here
void loop() {

  for (int i = 0; i < 8; i ++) // loop the following code 8 times
  {
    cc_number = 20 + i; // set control number to between 20 and 25 depending on loop iteration
    PORTD = i << 2; // get pot 1 to 8 ignoring bits 0 and 1 of a 5 bit value
    data_send = analogRead(workAn) / 8; //read analog pin into variable... with 10 bit -> 7 bit


    if (filter[i] != data_send) { //if filter and data_send not equal then in theory this will only send midi data when a value is changes an not constantly.
      Serial.print("The MIDI Data was: ");
      Serial.print(status_byte, HEX); // send status byte
      Serial.print(cc_number, HEX); // send CC number
      Serial.print(data_send, HEX); // send data value
      // loop back...
    }

    filter[i] = data_send; // Value of filter become same as data_send

    // loop back...
  }
  // loop back...
}
