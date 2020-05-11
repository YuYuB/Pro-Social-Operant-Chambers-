#include <ServoTimer2.h>
#define servod1  2
ServoTimer2 Door1;
#define servod2  4
ServoTimer2 Door2;
#define servoA  3
ServoTimer2 ALever;
#define servoI  5
ServoTimer2 ILever;

long int Start;
long int StartTime;
long int APress ;
long int IPress ;
int S = 0;
int L = 0;

// Boutton de demarrage 

const int pinS = 7;
const boolean PRESSEs = true;
const boolean RELACHEs = false;
boolean etatBoutonS = RELACHEs;
const byte AUCUN_EVENEMENTs = 6;
const byte EVENEMENT_PRESSEs = 7;
const byte EVENEMENT_RELACHEs = 8;

boolean lirePoussoirS()
{
    boolean resultatS = RELACHEs;
    if (digitalRead(pinS) == HIGH) {
        resultatS = PRESSEs;          
    }
    return resultatS;
    
}

byte lireEvenementS()
{
    byte evenementS;
    boolean nouvelEtatS = lirePoussoirS();
    if (nouvelEtatS == etatBoutonS)
        evenementS = AUCUN_EVENEMENTs;
    if (nouvelEtatS == PRESSEs && etatBoutonS == RELACHEs)
        evenementS = EVENEMENT_PRESSEs;
    if (nouvelEtatS == RELACHEs && etatBoutonS == PRESSEs)
        evenementS = EVENEMENT_RELACHEs;
    etatBoutonS = nouvelEtatS;
    return evenementS;
}


// Levier actif     

const int pinSTART = 12;
const boolean PRESSEstart = true;
const boolean RELACHEstart = false;
boolean etatBoutonSTART = RELACHEstart;
const byte AUCUN_EVENEMENTstart = 3;
const byte EVENEMENT_PRESSEstart = 4;
const byte EVENEMENT_RELACHEstart = 5;

boolean lirePoussoirSTART()
{
    boolean resultatSTART = RELACHEstart;
    if (digitalRead(pinSTART) == HIGH) {
        resultatSTART = PRESSEstart;          
    }
    return resultatSTART;
    
}

byte lireEvenementSTART()
{
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

const int piniSTART = 6;
const boolean PRESSEistart = true;
const boolean RELACHEistart = false;
boolean etatBoutoniSTART = RELACHEistart;
const byte AUCUN_EVENEMENTistart = 3;
const byte EVENEMENT_PRESSEistart = 4;
const byte EVENEMENT_RELACHEistart = 5;

boolean lirePoussoiriSTART()
{
    boolean resultatiSTART = RELACHEistart;
    if (digitalRead(piniSTART) == HIGH) {
        resultatiSTART = PRESSEistart;          
    }
    return resultatiSTART;
    
}

byte lireEvenementiSTART()
{
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
  Door1.write(2100);
  delay(100);
  Door2.attach(servod2);
  Door2.write(2100);
  delay(100);
  ALever.attach(servoA);
  ALever.write(2200);
  delay(80);
  ILever.attach(servoI);
  ILever.write(2200);
  delay(80);
  
  pinMode(7, INPUT);
  
  Serial.begin(115200);
  
  Start = millis();

  delay(2000);
}

void loop() {
  

 byte evenementS = lireEvenementS();
  if (evenementS == EVENEMENT_PRESSEs ) { 
    S = S + 1;
    L = 1;
    Serial.println("START");


    StartTime = millis() - Start;
  }

if (L == 1) { 
    ALever.write(1700);
    delay(100);
    ILever.write(1750);
    delay(100);
    Door1.write(2100);
    delay(100);
    Door2.write(2100);
    delay(100);
    L = 2;
  }

while (S == 1) {

byte evenementS = lireEvenementS();
  
  if (evenementS == EVENEMENT_PRESSEs ) { 
    S = S + 1;}


  
      byte evenementiSTART = lireEvenementiSTART();
  
if (evenementiSTART == EVENEMENT_PRESSEistart ) {
    IPress = millis() - StartTime; 
    S = 2;
    Serial.print(IPress);
    Serial.print(";");
    Serial.println();
    ILever.write(2200);
    ALever.write(2200);
    delay(100);
 //   ILever.write(1700);
 //   delay(100);
                  Door1.write(1300);
                  delay(1000);
//    Door1.write(2200);
//    delay(1000);

    }

    byte evenementSTART = lireEvenementSTART();
if (evenementSTART == EVENEMENT_PRESSEstart ) {
    APress = millis() - StartTime;
    S = 2;
    Serial.print(APress);
    Serial.print(";");
    Serial.println();
    ALever.write(2200);
    ILever.write(2200);
    delay(100);
//    ALever.write(1700);
//    delay(100);
    Door2.write(1300);
    delay(1000);
//    Door2.write(500);
//    delay(1000);

    }

if (S == 2) { 


S = 0; Start = 0;   
  }

}
}
