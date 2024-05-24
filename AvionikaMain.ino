//AvionikaMain - program
//----------------------
//(c) Tobiáš Mazura, 2024

//Konstanty:

//Parametry letu:
const long delkaLetu;
const int prodlevaMeziGPS = 1000; //v ms


//Použité piny:
//I2C
const byte pinSDA; //dopsat hodnoty!!!
const byte pinSCLK;
//uSD
const byte pinMISO; //SPI Lora a uSD nelze míchat - procesy na různých jádrech
const byte pinMOSI;
const byte pinSCLK;
const byte pinSS;
//LoRa
const byte LoRaMISO;
const byte LoRaMOSI;
const byte LoRaSCLK;
const byte LoRaRST;
const byte LoRaDIO0;
//Ostatní
const byte pinStart; //byteerrupt pin na adxl, start měření
const byte pinPiezo;
const byte pinPalnikGlider;
const byte pinPalnikPadak;
const byte pinRBFPGlider; //pojistka
const byte pinRBFPPadak; //pojistka

//Parametry komunikace:

const byte synchronizacniKod = 0xFA;

//groundstationPrikazyProMain = a
//groundstationPrikazyProPeripheral = b
//avionikaMainStavLetu = c
//avionikaMainMereni = d
//avionikaMainPrikazyProPeripheral = e
//avionikaPeripheralStavLetu = f
//avionikaPeripheralMereni = g

//kontrolniLastChar = x

//Další proměnné:
bool let = false; //po startu rakety
bool vymet = false; //po pokusu o výmet
bool glider = true; //true - glider, false - padák
bool signalGPS = false; //zmeni se po prvni uspesne gps.availible(), menit se na false třeba po 1000ms stejných dat
bool signalLoRa = false //signál s groundstation, změní se opět po nějakém čase
bool posilatPeripheral = false; //posílání směru a GPS souřadnic pro zatáčení
bool pojistky = false;
String mereni = "";
String gpsSouradnice;
String gpsVyska;
int vyskaZeme; //referenční výška, kterou naměří GPS na zemi

int[,] zvuk = {
  {750,250}, //Alert
  {300,250}, //Operace v pořádku provedena
  {1000,250} //Hlasitý alert
}

//Použité knihovny:

//Instance knihoven (objekty):

void setup()
{
  //Povypínání pinů
  digitalWrite(pinPalnikGlider, 0);
  digitalWrite(pinPalnikPadak, 0);
  digitalWrite(pinPiezo, 0);
  
  //Příprava a nastavení pinů
  //Inicializace VŠECH periferií (aby se na nic nečekalo)
    //LoRa
    //GPS
    //BME280
    //ADXL345
      //nastavení interruptu a jeho následná kontrola, že funguje (vypíše 1 nebo bzučák a zpráva)
    //BatMon
    //uSD
    
}
void loop()
{
  //Čekání na start (ADXL345)(začne vše měřit a čeká interval dle modelového letu ANEBO když náklon je příliš velký)
  while (digitalRead(pinStart) == 1)
  {
    if (digitalRead(pinRBFPGlider) == 1 || digitalRead(pinRBFPPadak) == 1)
    {
      pojistky = true;
    }
    else if (digitalRead(pinRBFPGlider) == 0 && digitalRead(pinRBFPPadak) == 0)
    {
     pojistky = false; 
    }
    vyskaZeme = gpsMereni();
  }
    
  //Spuštění časování
  long StartTime = millis();
  
  while(millis() <= (StartTime + delkaLetu))
  {
      //Měření dat (pouze v případě < 10ms)
  }
  //Odpálení nálože
  odpaleniVymetu(glider);

  //Měření dat, GPS
}

void loopLoRa()
{
  //Příjem dat
    //Dekódování
    
      //!!!! odpálení výmetu v případě potřeby
      if (payload[???] == '1')
      {
        odpaleniVymetu(1);
      }
      else
      {
        odpaleniVymetu(0);
      }

    
  //Odeslání specifické zprávy (3x po sobě)
    //každých 50 ms měření
    //každých 50 ms stav letu
}

//Speciální procedury a funkce (možná vysekat z některých knihoven jen to, co potřebujeme)
void odpaleniVymetu(bool primary)
{
  //V případě připojených pojistek se to ani nebude snažit - !!!testnout, jestli pojistky fungují i bez tohoto programového prvku!
  if (!pojistky)
  {
    //Odpálení požadovaného palníku
    if (primary)
    {
      digitalWrite(pinPalnikGlider, 1);
      delay (20);
      digitalWrite(pinPalnikGlider, 0);
    }
    else
    {
      digitalWrite(pinPalnikPadak, 1);
      delay (20);
      digitalWrite(pinPalnikPadak, 0);
    }
    //Přenastavení parametru vymet
    vymet = 1;
  }
}

int mereniGPS(int parametr)
{
  if (parametr == 0)
  {
    return //nadmorskavyska
  }
  if (parametr == 1)
  {
    return //souradnice, vyska
  }
}

void bzuk(int frekvence, int delka)
{
  tone(pinPiezo, frekvence, delka);
}
