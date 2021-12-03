#include "Animation.h"

extern s_myanimation myanimation;
extern String myanimationslist[MAXANIMATION+1];
extern uint32_t anipalette[];
extern ESP8266WebServer webServer;

// Animationsliste
void getAnimationList()
{
  int aidx = 0;
  int sidx = 0;
  String Aname;
  uint8_t lidx = 0;
  for ( uint8_t z = 0;z <= MAXANIMATION;z++) myanimationslist[z] = "";
  Dir dir = SPIFFS.openDir("/");
  while (dir.next()) {    
    aidx = dir.fileName().indexOf("/ani_");
    if ( aidx >= 0 ) 
    {
      sidx = dir.fileName().lastIndexOf(".json");
      if ( sidx >= 0)
      {
        Aname = dir.fileName().substring(aidx+5,sidx);
        if ( Aname != "NEU" ) 
        {
//        Serial.println ( myanimationslist[lidx] );
          myanimationslist[lidx] = Aname;
          lidx++;
        }
      }
    }
  }

// sortieren
  for (int i = 0; i < lidx; i++) {
    for (int j = i + 1; j < lidx; j++) {
      if (myanimationslist[j] < myanimationslist[i]) {
        std::swap(myanimationslist[i], myanimationslist[j]);
      }
    }
  }
  saveAnimationsListe();
}

void saveAnimationsListe()
{ 
//  String filename = "
  String anioutput;
  int bytesWritten = 0;
  bool fk = false;
  
  File file = SPIFFS.open(ANIMATIONSLISTE, "w");
  if (!file) {
    Serial.println(F("Save Animation: Failed to create file"));
  }
   anioutput = F("{\n \"Animationsliste\" : [ "); 
   for ( uint8_t z = 0;z <= MAXANIMATION;z++) 
   {
     
     if ( myanimationslist[z].length() > 2 ) {
      if ( fk ) anioutput += F(",");
      anioutput+= "\"" + myanimationslist[z] + "\"";
     }
     fk = true;
   }
   anioutput+= F(" ]\n}\n");
   bytesWritten = file.print(anioutput);
#ifdef DEBUG_ANIMATION
   if (bytesWritten > 0) 
   {
    Serial.println(F("File " ANIMATIONSLISTE " was written"));
    Serial.println(bytesWritten);
   } else {
    Serial.println(F("File " ANIMATIONSLISTE " write failed"));
   }
#endif
  // Close the file
  file.close();
}





// Lade die Animation
bool loadAnimation(String aniname )
{
#ifdef DEBUG_ANIMATION
  Serial.print(F("Loading Animation "));
  Serial.println (aniname);
#endif
  String filename = "/ani_" + aniname + ".json";
  String zeile;
  String typ;
  String wert;
  uint32_t farbwert;
  uint8_t frame = -1;
  String jsonBuffer;
  
  File file = SPIFFS.open(filename,"r");
  if(!file)
  {
   Serial.print(F("There was an error opening the file "));
   Serial.print(aniname);
   Serial.println(F(" for reading"));
   return false;
  }
  while (file.available()) 
  {
    zeile = file.readStringUntil('\n');
    typ = zeile.substring(0,zeile.indexOf(":"));
    wert = zeile.substring(zeile.indexOf(":")+1);
    typ.trim();
    typ.replace("\"","");
//    Serial.printf("typ: %s = %s\n" , typ.c_str(), wert.c_str());
  
    if ( typ.substring(0,5) == "Frame" ) 
    { 
      frame = typ.substring(typ.indexOf("_")+1).toInt();

      if ( frame == 0 ) 
      {
        jsonBuffer.replace("],","]");
        jsonBuffer = jsonBuffer + "}";
//        Serial.print( "jsonBuffer: " );
//        Serial.println (jsonBuffer);
// Animationskopf
        JSONVar myObject = JSON.parse(jsonBuffer);
        if (JSON.typeof(myObject) == "undefined") { Serial.println(F("Load Aniamtion: Parsing the Animationsfile failed")); return false;}
//        aniname = myObject["Name"];
        wert = aniname;
        wert.toCharArray(myanimation.name,wert.length()+1);
        
        myanimation.loops = (int)myObject["Loops"];
        myanimation.laufmode = (int)myObject["Laufmode"];;
        for ( uint8_t palidx = 0;palidx <= 9;palidx++)
        {
          wert = (const char*)myObject["Palette"][palidx];
          anipalette[palidx]=string_to_num(wert);
        }
        // animation leer initialisieren
        for ( uint8_t f = 0;f < MAXFRAMES;f++)
        {
           myanimation.frame[f].delay = 0;
           for ( uint8_t zeile = 0;zeile <= 9;zeile++)
           {
              for ( uint8_t x = 0;x <= 10;x++)
              {
                 myanimation.frame[f].color[x][zeile] = num_to_color(0);
              }
           }          
        }
      }
// AnimationFrames
      if ( frame > 0 ) 
      {
        jsonBuffer = "{ " + jsonBuffer;
        jsonBuffer.replace("},","}");
        if ( ! loadFrames(frame-1,jsonBuffer)) return false;
      }
      jsonBuffer = "";
    }
    else
    {
      jsonBuffer = jsonBuffer + zeile;
    }
  }
// AnimationFrames (letzter Frame)
  jsonBuffer = "{ " + jsonBuffer;
  jsonBuffer.replace("}}","}");
//  Serial.print( "frame: " );
//  Serial.println (frame );
//  Serial.print( "jsonBuffer: " );
//  Serial.println (jsonBuffer); 
  if ( ! loadFrames(frame,jsonBuffer)) return false;
  file.close();
  return true;
}

bool loadFrames(uint8_t frame, String jsonBuffer)
{
  uint16_t delayval;
  String zeile_json;
  String farbwert;
  
  JSONVar myObject = JSON.parse(jsonBuffer);
  if (JSON.typeof(myObject) == "undefined") { Serial.println(F("Load Frames: Parsing the Animationsfile failed")); return false;}
  delayval = (int)myObject["Delay"];
  myanimation.frame[frame].delay = delayval;
  for ( uint8_t zeile = 0;zeile <= 9;zeile++)
  {
    zeile_json = "Zeile_" + String(zeile);
    for ( uint8_t x = 0;x < myObject[zeile_json].length();x++)
    {
      farbwert = (const char*)myObject[zeile_json][x];
//      Serial.printf ("pixel x/y %i/%i = %s ",x,zeile,farbwert.c_str());
      myanimation.frame[frame].color[x][zeile] = string_to_color(farbwert);
    }
  }

  return true; 
}


// Sichere die Animation
bool saveAnimation(String aniname ) {

  aniname.toUpperCase();
#ifdef DEBUG_ANIMATION
  Serial.print(F("Saving Animation "));
  Serial.println (aniname);
#endif  
  String filename = "/ani_" + aniname + ".json";
  String anioutput;
  int bytesWritten = 0;
  bool fk = false;
  bool retval = true;

  SPIFFS.remove(filename);

  // Open file for writing

  File file = SPIFFS.open(filename, "a");
  if (!file) {
    Serial.println(F("Save Animation: Failed to create file"));
    return false;
  }
  strcpy ( myanimation.name, aniname.c_str());
  anioutput = F("{\n \"Name\" : \""); 
  anioutput += String(myanimation.name);
  anioutput += F("\",\n");
  anioutput += F(" \"Loops\" : ");
  anioutput += String(myanimation.loops) + ",\n";
  anioutput += F(" \"Laufmode\" : ");
  anioutput += String(myanimation.laufmode) + ",\n";
  anioutput += F(" \"Palette\" : [ ");
  for ( uint8_t palidx = 0;palidx < 10;palidx++)
  {
    if ( fk ) anioutput += F(",");
    anioutput += F("\"");
    anioutput += num_to_string(anipalette[palidx]);
    anioutput += F("\"");
    fk = true;
  }
  anioutput += F(" ],\n");

  bytesWritten = file.print(anioutput);
  if (bytesWritten > 0) {
    anioutput = "";
    for ( uint8_t f = 0;f < MAXFRAMES;f++)
    {
      if ( f > 0 && myanimation.frame[f].delay == 0 ) break;
      anioutput += F(" \"Frame_");  anioutput += String(f); anioutput += F("\" : {\n");
      anioutput += F("  \"Delay\" : "); anioutput += String(myanimation.frame[f].delay); anioutput += F(",\n");
      for ( uint8_t z = 0;z <= 9;z++)
      {
         fk = false;
         anioutput += F("  \"Zeile_"); anioutput += String(z); anioutput += F("\" : [ ");
         for ( uint8_t x = 0;x <= 10;x++)
         {
           if ( fk ) anioutput += F(",");
           anioutput += F("\""); anioutput += color_to_string(myanimation.frame[f].color[x][z]);anioutput += F("\"");
           fk = true;
         } 
         delay(0);
         if ( z < 9 ) { anioutput += F(" ],\n");} else {anioutput += F(" ]\n");}
      }
      if ( f < MAXFRAMES-1 ) 
      { 
        if ( f > 0 && myanimation.frame[f+1].delay == 0 )
        {
          anioutput += F(" }\n");
        }
        else
        {
          anioutput += F(" },\n");
        }
      } 
      else 
      {
        anioutput += F(" }\n");
      }

      bytesWritten = bytesWritten + file.print(anioutput);
      anioutput = "";
    }
    anioutput = "}\n";
    bytesWritten = bytesWritten + file.print(anioutput);
  }
  if (bytesWritten > 0) 
  {
#ifdef DEBUG_ANIMATION
    Serial.println(F("Save Animation: File was written"));
    Serial.print(bytesWritten);
    Serial.println(F(" bytes"));
#endif
    retval = true;
  } else {
    Serial.println(F("File write failed"));
    retval = false;
  }
  // Close the file
  file.close();
  return retval;
}

//###########################################################################
// Animationsmenü
//###########################################################################
void makeAnimationmenue()
{
  webServer.setContentLength(CONTENT_LENGTH_UNKNOWN);
  String checked = "checked";
  uint8_t anzani = 0;
  
  String message = F("<!doctype html>"
  "<html>"
  "<head>"
  "<title>");
  message += String(HOSTNAME);
  message += F(" Animationen</title>"
  "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">"
  "<meta charset=\"UTF-8\">"
  "<link rel=\"icon\" type=\"image/png\" sizes=\"192x192\"  href=\"/android-icon-192x192.png\">"
  "<link rel=\"icon\" type=\"image/png\" sizes=\"32x32\"  href=\"/favicon-32x32.png\">"
  "<script src=\"jquery-3.1.1.min.js\"></script>"
  "<link rel=\"stylesheet\" href=\"/animenue.css\" >"
  "</head><body>"
  "<h2>Animationsmen&uuml</h2>"
  "<form name=\"animenue\" action=\"/\" method=\"POST\">"
  "<div class=\"background-color\"></div>"
  "<div class=\"section over-hide z-bigger\">"
    "<div class=\"row justify-content-center pb-5\">"
      "<div class=\"checkboxcontainer\">\n");
// ################################################# sende html Teil 1
    webServer.send(200, "text/html", message);
    message = "";
    delay(0);
// ###################################################################
  for ( int aninr=0; aninr <= MAXANIMATION; aninr++ )
  {
    if ( myanimationslist[aninr].length() == 0 || myanimationslist[aninr] == "neu" ) continue;
    anzani++;
    message += "<input class=\"checkbox-tools\" type=\"radio\" name=\"myselect\" id=\"" + String(myanimationslist[aninr]) + "\" " + checked +" value=\"" + String(myanimationslist[aninr]) + "\">\n"
    "<label class=\"for-checkbox-tools\" for=\"" + String(myanimationslist[aninr]) + "\">\n";
    message += "<i class='uil'>" + String(anzani) + "</i>" + String(myanimationslist[aninr]) + "</label>\n";
    checked = "";
// ########################################################################### sende Liste html
webServer.sendContent(message);
message = "";
delay(0);
// ########################################################################### 
  }
  if ( anzani < MAXANIMATION ) 
  {
    message += "<input class=\"checkbox-tools\" type=\"radio\" name=\"myselect\" id=\"NEU\" " + checked +" value=\"neu\">\n"
    "<label class=\"for-checkbox-tools\" for=\"NEU\">neu</label>\n";
  }
  message += F("</div>"
        "</div>"
    "<br>"
    "<hr>"
    "<div class=\"buttonscontainer\">"
    "<button class=\"buttons\" type=\"submit\" formaction=\"/back\">&#128281; zur&uumlck</button>"
    "<button class=\"buttons\" type=\"submit\" formaction=\"/makeanimation\">&#127912; &auml;ndern</button>"
    "</div>"
    "</div>"
    "</form>"
    
    "<script>"
    "var urlBase = \"/\";"
    "$(\".checkbox-tools\").click(function() {"
    "newvalue = $(\"input[class='checkbox-tools']:checked\").val();"
    "$.post(urlBase + \"myaniselect\" + \"?value=\" + newvalue );" 
    "});"
    "document.addEventListener('DOMContentLoaded', function() { "
     "$.post(urlBase + \"myaniselect\" + \"?value=BACK\" );"
   "});"
    "</script>"
    "</body></html>");
//##################### sende letzen html Teil
  webServer.sendContent(message);
  webServer.sendContent("");
//    return message;
}
//###########################################################################
// Animationsmenü Ende
//###########################################################################


// Farbwert (z.B. #FF00DD ) von HEX nach int wandeln
uint32_t string_to_num(String in_color)
{
  char buffer[9];
  in_color.substring(1, 7).toCharArray(buffer,7);
  return strtol(buffer, 0, 16);
}

// Farbwert (z.B. #FF00DD ) von HEX nach String wandeln
String num_to_string(uint32_t in_color)
{
  String farbe;
  farbe = "000000" + String(in_color,HEX);
  farbe = "#" + farbe.substring( farbe.length()-6,farbe.length());
  farbe.toUpperCase();
  return farbe;
}

// Farbwert (z.B. red, green, blue ) nach String wandeln
String color_to_string(color_s in_color)
{
  String farbe;
  uint32_t colbuf = 0;
  colbuf = in_color.red<<16;
  colbuf = colbuf | in_color.green<<8;
  colbuf = colbuf | in_color.blue;
  return num_to_string(colbuf);
}

// Farbwert string -> s_color
color_s string_to_color(String in_color)
{
  return num_to_color(string_to_num(in_color));
}
// Farbwert num -> s_color (z.B. 0xFF00DD) nach red, green, blue
color_s num_to_color(uint32_t in_color)
{
  color_s s_color;
  s_color.red = in_color >> 16 & 0xFF;
  s_color.green = in_color >> 8 & 0xFF;
  s_color.blue = in_color & 0xFF;
  return s_color;
}
