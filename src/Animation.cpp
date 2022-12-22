#include "Animation.h"
#include "Languages.h"

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
  Dir dir = LittleFS.openDir("/");
  while (dir.next()) {    
    if (!dir.isDirectory())
    {
      aidx = dir.fileName().indexOf("ani_");
      if ( aidx >= 0 ) 
      {
        sidx = dir.fileName().lastIndexOf(".json");
        if ( sidx >= 0)
        {
          Aname = dir.fileName().substring(aidx+4,sidx);
          if ( Aname != "NEU" ) 
          {
            myanimationslist[lidx] = Aname;
//            Serial.println ( myanimationslist[lidx] );
            lidx++;
          }
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
  
  File file = LittleFS.open(ANIMATIONSLISTE, "w");
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
  String filezeile;
  String typ;
  String wert;
  uint32_t farbwert;
  uint8_t frame = 0;
  uint8_t zeile = 0;
  String jsonBuffer;

  File file = LittleFS.open(filename,"r");
  if(!file)
  {
   Serial.print(F("There was an error opening the file "));
   Serial.print(aniname);
   Serial.println(F(" for reading"));
   return false;
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
  while (file.available()) 
  {
    filezeile = file.readStringUntil('\n');
    typ = filezeile.substring(0,filezeile.indexOf(":"));
    wert = filezeile.substring(filezeile.indexOf(":")+1);
    
    typ.replace("\"","");
    typ.trim();
    
    wert.replace(",","");
    wert.replace("\"","");
    wert.trim();
    
//    Serial.printf("typ: %s = %s\n" , typ.c_str(), wert.c_str());
    
    if ( typ == "Name" ) aniname.toCharArray(myanimation.name,aniname.length()+1);
    if ( typ == "Loops" ) myanimation.loops = wert.toInt();
    if ( typ == "Laufmode" ) myanimation.laufmode = wert.toInt();
    if ( typ == "Palette") 
    {
      jsonBuffer = filezeile;
      jsonBuffer.replace("],","]");
      jsonBuffer = '{' + jsonBuffer + "}";
//      Serial.print( "jsonBuffer0: " );
//      Serial.println (jsonBuffer);
      if ( !loadjsonarry(-1,0,jsonBuffer) ) return false;  //Load Palette
      jsonBuffer="";
    }
    if ( typ.substring(0,5) == "Frame" ) frame = typ.substring(typ.indexOf("_")+1).toInt();
    if ( typ == "Delay") myanimation.frame[frame].delay = wert.toInt();
    if ( typ.substring(0,5) == "Zeile" ) 
    {
      zeile = typ.substring(typ.indexOf("_")+1).toInt();
      jsonBuffer = filezeile;
      jsonBuffer.replace("],","]");
      jsonBuffer = '{' + jsonBuffer + "}";
      
      if ( !loadjsonarry(frame,zeile,jsonBuffer) ) return false; //Load Zeilen pro Frame
      jsonBuffer="";
    }
//    Serial.printf("AnimationFrames ESP.getMaxFreeBlockSize: %i Codezeile: %u\n", ESP.getMaxFreeBlockSize(),  __LINE__);

  }
  file.close();
#ifdef DEBUG_ANIMATION
  Serial.print( "myanimation.name: " );
  Serial.println (myanimation.name);
  Serial.print( "myanimation.loops: " );
  Serial.println (myanimation.loops); 
  Serial.print( "myanimation.laufmode: " );
  Serial.println (myanimation.laufmode);    
  Serial.print( "anipalette: " );
  for ( uint8_t palidx = 0;palidx <= 9;palidx++)
  {
    Serial.print(num_to_string(anipalette[palidx]));
    Serial.print(" ");
  }
  Serial.println("");
  for ( uint8_t f = 0;f < MAXFRAMES;f++)
  {
    Serial.print ("myanimation.frame: ");
    Serial.println (f);
    Serial.print ("myanimation.frame.delay: ");
    Serial.println (myanimation.frame[f].delay);
    for ( uint8_t zeile = 0;zeile <= 9;zeile++)
    {
      Serial.print ("myanimation.frame.zeile: ");
      Serial.print (zeile);
      Serial.print (": ");
      for ( uint8_t x = 0;x <= 10;x++)
      {
        Serial.print (color_to_string(myanimation.frame[f].color[x][zeile]));
        Serial.print (" ");
      }
      Serial.println(" ");
    }          
  }
  Serial.printf("AnimationFrames ESP.getMaxFreeBlockSize: %i Codezeile: %u\n", ESP.getMaxFreeBlockSize(),  __LINE__);
#endif
  return true;
}

bool loadjsonarry( int8_t frame, uint8_t zeile, String &jsonBuffer)
{
  String farbwert;
  String zeile_json;
  JSONVar myObject = JSON.parse(jsonBuffer);

  if (JSON.typeof(myObject) == "undefined") { Serial.println(F("Load JSON_ARRAY: Parsing the Animationsfile failed")); return false;}
  delay(0);
  if ( frame == -1 && zeile == 0 ) 
  {
    for ( uint8_t palidx = 0;palidx <= 9;palidx++)
    {
       farbwert = (const char*)myObject["Palette"][palidx];
       anipalette[palidx]=string_to_num(farbwert);
    }
  }
  else
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

  LittleFS.remove(filename);

  // Open file for writing

  File file = LittleFS.open(filename, "a");
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
  String checked = F("checked");
  uint8_t anzani = 0;
  
  String message = F("<!doctype html>"
  "<html>"
  "<head>"
  "<title>");
  message += String(HOSTNAME);
  message += F(" " LANG_ANIMATIONS "</title>\n"
  "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n"
  "<meta charset=\"UTF-8\">\n"
  "<link rel=\"icon\" type=\"image/png\" sizes=\"192x192\"  href=\"/web/android-icon-192x192.png\">"
  "<link rel=\"icon\" type=\"image/png\" sizes=\"32x32\"  href=\"/web/favicon-32x32.png\">\n"
  "<script src=\"/web/jquery-3.1.1.min.js\"></script>\n"
  "<link rel=\"stylesheet\" href=\"/web/animenue.css\" >\n"
  "</head><body>\n"
  "<h2>\n"
  LANG_ANIMATIONMENU
  "</h2>"
  "<form name=\"animenue\" action=\"/\" method=\"POST\">\n"
  "<div class=\"background-color\"></div>\n"
  "<div class=\"section over-hide z-bigger\">\n"
    "<div class=\"row justify-content-center pb-5\">\n"
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
    message += F("<input class=\"checkbox-tools\" type=\"radio\" name=\"myselect\" id=\"");
    message += String(myanimationslist[aninr]);
    message += F("\" ");
    message += checked;
    message += F(" value=\"");
    message += String(myanimationslist[aninr]);
    message += F("\">\n");
    message += F("<label class=\"for-checkbox-tools\" for=\""); 
    message += String(myanimationslist[aninr]);
    message += F("\">\n");
    message += F("<i class='uil'>");
    message += String(anzani); 
    message += F("</i>");
    message += String(myanimationslist[aninr]); 
    message += F("</label>\n");
    checked = "";
//########################################################################### sende Liste html
    if ( aninr %5 == 0 )
    {
      webServer.sendContent(message);
      message = "";
      delay(0);
    }
//########################################################################### 
  }
  if ( anzani < MAXANIMATION ) 
  {
    message += F("<input class=\"checkbox-tools\" type=\"radio\" name=\"myselect\" id=\"NEU\" ");
    message += checked;
    message += F(" value=\"neu\">\n");
    message += F("<label class=\"for-checkbox-tools\" for=\"NEU\">neu</label>\n");
  }
  message += F("</div>"
    "</div>\n"
    "<br>\n"
    "<hr>\n"
    "<div class=\"buttonscontainer\">\n"
    "<button class=\"buttons\" title=\"" LANG_BACK "\" type=\"submit\" formaction=\"/back\">&#128281; " LANG_BACK "</button>\n"
    "<button class=\"buttons\" title=\"" LANG_CHANGEBUTTON "\" type=\"submit\" formaction=\"/makeanimation\">&#127912; " LANG_CHANGEBUTTON "</button>\n"
    "</div>"
    "</div>"
    "</form>\n"
    
    "<script>\n"
    "var urlBase = \"/\";\n"
    "$(\".checkbox-tools\").click(function() {\n"
    "newvalue = $(\"input[class='checkbox-tools']:checked\").val();"
    "$.post(urlBase + \"myaniselect\" + \"?value=\" + newvalue );" 
    "});\n"
    "document.addEventListener('DOMContentLoaded', function() {\n"
     "$.post(urlBase + \"myaniselect\" + \"?value=BACK\" );"
    "});\n"
    "</script>\n"
    "</body></html>\n");
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
