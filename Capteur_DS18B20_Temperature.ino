#include <OneWire.h>
OneWire ds(7); // Broche DATA du capteur DS18B20


byte addr[8]; // Contient les adresses du capteur
byte data[9]; // Contient les valeurs du capteur (scratchpad)
float temp;

void setup() {
  Serial.begin(9600);
}


void Temperature() {
  delay(100);

  /* Vérifie qu'un capteur soit trouvé, et vérifie qu'il s'agit d'un DS18B20 
     La fonction "ds.search()" remplie le tableau "addr" avec les addresses trouvées du capteur */
  if (ds.search(addr) && addr[0] == 0x28) {
    Serial.print("Capteur DS18B20 trouve");
    ds.reset_search();
  }

  // Sinon, on affiche un msg d'erreur
  else {
    Serial.println("Capteur non trouve, ou mauvais capteur ! (DS18B20 seulement)");
    return;
  }


  ds.reset();         // Reset les data du bus
  ds.select(addr);    // Selectionne l'addresse du capteur
  ds.write(0x44, 1);  // Envoie une demande de prise de temperature


  ds.reset();         // Reset les data du bus
  ds.select(addr);    // Selectionne l'addresse du capteur
  ds.write(0xBE);     // Envoie une demande de lecture des valeurs (scratchpad)


  /* Ecrit dans le tableau "data" les 9 valeurs du scratchpad */
  for (byte i = 0; i < 9; i++) {
    data[i] = ds.read();
  }


  /* Calcul la temperature en utilisant les données "data[1]" et "data[0]"
   * " << " Ajoute 8 "0" a l'écriture binaire du nombre
   * " | " Fait un "OU Logique", en binaire, entre la valeur "data[1]" et "data[0]" */
  temp = (int16_t) ((data[1] << 8) | data[0]) * 0.0625;
  
  Serial.print(", la temperature est de : ");
  Serial.println(temp);
  
}


void loop() {
  Temperature();
}
