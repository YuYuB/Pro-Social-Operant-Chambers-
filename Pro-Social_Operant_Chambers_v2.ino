#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);       


int lcd_key     = 0;
int adc_key_in  = 0;

#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

int read_LCD_buttons(){               
    adc_key_in = analogRead(0);      

    if (adc_key_in > 1000) return btnNONE; 

   
    if (adc_key_in < 50)   return btnRIGHT;  
    if (adc_key_in < 250)  return btnUP; 
    if (adc_key_in < 450)  return btnDOWN; 
    if (adc_key_in < 650)  return btnLEFT; 
    if (adc_key_in < 850)  return btnSELECT;  

    return btnNONE;                // when all others fail, return this.
}



#include <ServoTimer2.h>
#define servod1  2
ServoTimer2 Door1;
#define servod2  3
ServoTimer2 Door2;
#define servoA  12
ServoTimer2 ALever;
#define servoI  13
ServoTimer2 ILever;

long int Start;
long int StartTime;
long int APress ;
long int IPress ;
int S = 0;
int L = 0;




// Levier actif     

const int pinSTART = A5;
const boolean PRESSEstart = true;
const boolean RELACHEstart = false;
boolean etatBoutonSTART = RELACHEstart;
const byte AUCUN_EVENEMENTstart = 3;
const byte EVENEMENT_PRESSEstart = 4;
const byte EVENEMENT_RELACHEstart = 5;

boolean lirePoussoirSTART(){
    boolean resultatSTART = RELACHEstart;
    if (digitalRead(pinSTART) == HIGH) {
        resultatSTART = PRESSEstart;          
    }
    return resultatSTART;
    
}

byte lireEvenementSTART(){
    byte evenementSTART;
    boolean nouvelEtatSTART = lirePoussoirSTART();
    if (nouvelEtatSTART == etatBoutonSTART)
        evenementSTART = AUCUN_EVENEMENTstart;
    if (nouvelEtatSTART == PRESSEstart && etatBoutonSTART == RELACHEstart)
        evenementSTART = EVENEMENT_PRESSEstart;
    if (nouvelEtatSTART == RELACHEstart && etatBoutonSTART == PRESSEstart)
        evenementSTART = EVENEMENT_RELACHEstart;
    etatBoutonSTART = nouvelEtatSTART;
    return evenementSTART;
    
}


// Levier inactif

const int piniSTART = 10;
const boolean PRESSEistart = true;
const boolean RELACHEistart = false;
boolean etatBoutoniSTART = RELACHEistart;
const byte AUCUN_EVENEMENTistart = 3;
const byte EVENEMENT_PRESSEistart = 4;
const byte EVENEMENT_RELACHEistart = 5;

boolean lirePoussoiriSTART(){
    boolean resultatiSTART = RELACHEistart;
    if (digitalRead(piniSTART) == HIGH) {
        resultatiSTART = PRESSEistart;          
    }
    return resultatiSTART;
    
}

byte lireEvenementiSTART(){
    byte evenementiSTART;
    boolean nouvelEtatiSTART = lirePoussoiriSTART();
    if (nouvelEtatiSTART == etatBoutoniSTART)
        evenementiSTART = AUCUN_EVENEMENTistart;
    if (nouvelEtatiSTART == PRESSEistart && etatBoutoniSTART == RELACHEistart)
        evenementiSTART = EVENEMENT_PRESSEistart;
    if (nouvelEtatiSTART == RELACHEistart && etatBoutoniSTART == PRESSEistart)
        evenementiSTART = EVENEMENT_RELACHEistart;
    etatBoutoniSTART = nouvelEtatiSTART;
    return evenementiSTART;
    

}
void setup() {
  // put your setup code here, to run once:
  Door1.attach(servod1);
  Door1.write(2300);
  delay(100);
  Door2.attach(servod2);
  Door2.write(1500);
  delay(100);
  ALever.attach(servoA);
  ALever.write(2450);
  delay(80);
  ILever.attach(servoI);
  ILever.write(1600);
  delay(80);
  
  pinMode(10, INPUT);
  pinMode(A5, INPUT);

  //pinMode(A3, OUTPUT);
  
  Start = millis();
  Serial.begin(115200);
   lcd.begin(16, 2);           
   lcd.setCursor(1,0);             
   lcd.print("OPERANT-RESCUE");  
   lcd.setCursor(1           ,1);             
   lcd.print("DOUBLE CHAMBERS");  
delay(1500);
   lcd.begin(16, 2);           
   lcd.setCursor(1,0);             
   lcd.print("S. Watanabe &");  
   lcd.setCursor(1,1);             
   lcd.print("Y. Bouchekioua");  
delay(1500);  

}



void loop() {
lcd.setCursor(0,0);
lcd_key = read_LCD_buttons();

if (S == 0){
switch (lcd_key){               // depending on which button was pushed, we perform an action
       case btnDOWN:{
             //S = 1;
             L = 1;
             
            lcd.print("                ");
               lcd.setCursor(0,1);             // move to the begining of the second line
   lcd.print("                      ");
            
             break;
       }


       case btnUP:{
             //S = 1;
             L = 2;
             
            lcd.print("                ");
               lcd.setCursor(0,1);             // move to the begining of the second line
   lcd.print("                      ");
            
             break;
       }
       
       case btnNONE:{
                  lcd.setCursor(0,0);             // move cursor to second line "1" and 9 spaces over
     lcd.print("Capture a Mouse");
//   lcd.print(millis()/100);       // display seconds elapsed since power-up
Serial.println("Waiting for a START");
   lcd.setCursor(0,1);             // move to the begining of the second line
   lcd.print("& press a button");
//   lcd_key = read_LCD_buttons();   // read the buttons
             break;
       }
   }
}


    
 

if (L == 1) { 
    Door1.write(2300);
    delay(100);
    Door2.write(2300);
    delay(100);
    ALever.write(1700);
    delay(100);
    ILever.write(1150);
    delay(100);
    StartTime = millis() - Start;
    lcd.setCursor(2,0);
    lcd.print("LATENCY(ms):");
    lcd.setCursor(0,1);
    lcd.print("                 ");
    delay(100);
    L = 3;
    S = 1;
  }


if (L == 2) { 
    Door1.write(2300);
    delay(100);
    Door2.write(2300);
    delay(100);
    ALever.write(1700);
    delay(100);
    ILever.write(1150);
    delay(100);
    StartTime = millis() - Start;
    lcd.setCursor(2,0);
    lcd.print("LATENCY(ms):");
    lcd.setCursor(0,1);
    lcd.print("                 ");
    delay(100);
    L = 3;
    S = 3;
  }  

if (S == 1) {

         
      byte evenementiSTART = lireEvenementiSTART();
  
if (evenementiSTART == EVENEMENT_PRESSEistart ) {
    IPress = millis() - StartTime; 
    S = 2;
        lcd.setCursor(0,1);             // move to the begining of the second line
   lcd.print("A");
    lcd.setCursor(6,1);             // move to the begining of the second line
   lcd.print(IPress);
    Serial.print(IPress);
    Serial.print(";");
    Serial.println();
    ILever.write(1600);
    ALever.write(2450);
    delay(100);
 //   ILever.write(1700);
 //   delay(100);
                  Door2.write(1300);
                  delay(1000);
//    Door1.write(2200);
//    delay(1000);

    }

    byte evenementSTART = lireEvenementSTART();
if (evenementSTART == EVENEMENT_PRESSEstart ) {
  
    APress = millis() - StartTime;
    S = 2;
    lcd.setCursor(0,1);             // move to the begining of the second line
   lcd.print("S");
    lcd.setCursor(6,1);             // move to the begining of the second line
   lcd.print(APress);
    Serial.print(APress);
    Serial.print(";");
    Serial.println();
    ALever.write(2450);
    ILever.write(1600);
    delay(100);
//    ALever.write(1700);
//    delay(100);
    Door1.write(1300);
    delay(1000);
//    Door2.write(500);
//    delay(1000);

    }

}


if (S == 3) {

         
      byte evenementiSTART = lireEvenementiSTART();
  
if (evenementiSTART == EVENEMENT_PRESSEistart ) {
     APress = millis() - StartTime;
    S = 2;
    lcd.setCursor(0,1);             // move to the begining of the second line
   lcd.print("S");
    lcd.setCursor(6,1);             // move to the begining of the second line
   lcd.print(APress);
    Serial.print(APress);
    Serial.print(";");
    Serial.println();
    ALever.write(2450);
    ILever.write(1600);
    delay(100);
//    ALever.write(1700);
//    delay(100);
    Door1.write(1300);
    delay(1000);
//    Door2.write(500);
//    delay(1000);

    }

    byte evenementSTART = lireEvenementSTART();
if (evenementSTART == EVENEMENT_PRESSEstart ) {
       IPress = millis() - StartTime; 
    S = 2;
        lcd.setCursor(0,1);             // move to the begining of the second line
   lcd.print("A");
    lcd.setCursor(6,1);             // move to the begining of the second line
   lcd.print(IPress);
    Serial.print(IPress);
    Serial.print(";");
    Serial.println();
    ILever.write(1600);
    ALever.write(2450);
    delay(100);
 //   ILever.write(1700);
 //   delay(100);
                  Door2.write(1300);
                  delay(1000);
//    Door1.write(2200);
//    delay(1000);


    }

}



}

