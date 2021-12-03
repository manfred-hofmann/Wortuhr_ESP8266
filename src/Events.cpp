#include "Events.h"

extern s_event events[MAXEVENTS+1];

// Lade Events
bool loadEvents()
{
   Serial.println(F("Loading Events "));
   String filename = EVENTFILE;
   String jsonBuffer;
   uint8_t eventnr = 0;
   
  // Open file for reading
  File file = SPIFFS.open(filename,"r");
  if(!file)
  {
   Serial.println(F("There was an error opening the file " EVENTFILE " for reading"));
   return false;
  }
  // alle events deaktivieren
  for ( uint8_t z = 0;z <= MAXEVENTS;z++)
  {
    events[z].aktiv=false;
    events[z].year=0;
    events[z].month=0;
    events[z].day=0;
    events[z].text = "";
    events[z].color=0;
    events[z].audio_file=0;
    events[z].preani="";
    events[z].postani="";
    events[z].intervall=0;
  }
  while (file.available()) 
  {
    jsonBuffer = file.readStringUntil('\r');
    JSONVar myObject = JSON.parse(jsonBuffer);

    if (JSON.typeof(myObject) == "undefined") {
        Serial.println(F("Parsing the Eventfile " EVENTFILE " failed"));
        return false;
      }
    // Serial.println(myObject);
    // Serial.print("myObject[\"events\"].length() = ");
#ifdef DEBUG_EVENTS
       Serial.print("Anzahl Events: ");
       Serial.println(myObject["events"].length());
#endif
    for ( uint8_t z = 1;z <= MAXEVENTS ;z++)
    {
      if ( z <= myObject["events"].length() ) 
      {
        events[z].aktiv=true;
        events[z].year=(int)myObject["events"][z-1]["jahr"];
        events[z].month=(int)myObject["events"][z-1]["monat"];
        events[z].day=(int)myObject["events"][z-1]["tag"];
        events[z].text = (const char*)myObject["events"][z-1]["text"];
        events[z].text.trim();
        events[z].color=(int)myObject["events"][z-1]["farbe"];
        events[z].audio_file=(int)myObject["events"][z-1]["audionr"];
        events[z].preani=(const char*)myObject["events"][z-1]["preani"];
        events[z].preani.trim();
        events[z].postani=(const char*)myObject["events"][z-1]["postani"];
        events[z].postani.trim();
        events[z].intervall=(int)myObject["events"][z-1]["intervall"];
      }
    }
  }
  
  file.close();  
#ifdef DEBUG_EVENTS
  for ( uint8_t eventnr = 0;eventnr <= MAXEVENTS;eventnr++)
  {
    if ( events[eventnr].aktiv ) Serial.printf("Event: %i , Jahr: %i Monat: %i Tag: %i\n",eventnr, events[eventnr].year, events[eventnr].month,events[eventnr].day);
    if ( events[eventnr].aktiv ) Serial.println(events[eventnr].text);
    if ( events[eventnr].aktiv ) Serial.printf("Farbe: %i Audio: %i Intervall: %i Pre/Post Ani: ",events[eventnr].color, events[eventnr].audio_file, events[eventnr].intervall);
    if ( events[eventnr].aktiv ) Serial.print(events[eventnr].preani);
    if ( events[eventnr].aktiv ) Serial.print(" / ");
    if ( events[eventnr].aktiv ) Serial.println(events[eventnr].postani);
  } 
#endif
  return true;
}

// Sichere Events
bool saveEvents() 
{
  Serial.println(F("Saving Events "));
  String filename = EVENTFILE;
  String fileout;
  int bytesWritten = 0;
  bool retval = true;
  bool fk = false;
  SPIFFS.remove(filename);

  // Open file for writing
  File file = SPIFFS.open(filename, "a");
  if (!file) {
    Serial.println(F("Failed to create file " EVENTFILE));
    return false;
  }
  fileout = "{\"maxevents\": " + String(MAXEVENTS) + ",\n";
  fileout += F(" \"events\": [\n");
  bytesWritten = file.print(fileout);
  fileout = "";
  if (bytesWritten > 0) 
  {
    for ( uint8_t eventnr = 1;eventnr <= MAXEVENTS;eventnr++)
    {
      if ( events[eventnr].aktiv ) 
      {
        fileout = "";
        if ( fk ) fileout += ",\n";
        fileout += " {\n";
        fileout +=  "  \"jahr\":" + String(events[eventnr].year) + ",\n";
        fileout +=  "  \"monat\":" + String(events[eventnr].month) + ",\n";
        fileout +=  "  \"tag\":" + String(events[eventnr].day) + ",\n";
        fileout +=  "  \"text\": \"" + String(events[eventnr].text) + "\",\n";
        fileout +=  "  \"farbe\":" + String(events[eventnr].color) + ",\n";
        fileout +=  "  \"audionr\":" + String(events[eventnr].audio_file) + ",\n";
        fileout +=  "  \"preani\": \"" + String(events[eventnr].preani) + "\",\n";
        fileout +=  "  \"postani\": \"" + String(events[eventnr].postani) + "\",\n";
        fileout +=  "  \"intervall\":" + String(events[eventnr].intervall) + "\n";
        fileout +=  " }";
        fk = true;
      } 
      bytesWritten = bytesWritten + file.print(fileout); 
      fileout = "";
    }
    fileout = "\n ]\n}";
    bytesWritten = bytesWritten + file.print(fileout);
  }
  if (bytesWritten > 0) 
  {
    Serial.println("File " EVENTFILE " was written");
    Serial.println(bytesWritten);
    retval = true;
  } else 
  {
    Serial.println("File " EVENTFILE " write failed");
    retval = false;
  }
 
  // Close the file
  file.close();
  return retval;
}
