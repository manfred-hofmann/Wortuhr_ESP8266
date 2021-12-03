
// ****************************************************************
// Sketch Esp8266 Dateiverwaltung spezifisch Sortiert Modular(Tab)
// created: Jens Fleischer, 2020-08-03
// last mod: Jens Fleischer, 2020-08-03
// For more information visit: https://fipsok.de
// ****************************************************************
// Hardware: Esp8266
// Software: Esp8266 Arduino Core 2.6.0 - 2.7.4
// Geprüft: von 1MB bis 16MB Flash
// Getestet auf: Nodemcu, Wemos D1 Mini Pro, Sonoff Switch, Sonoff Dual
/******************************************************************
  Copyright (c) 2020 Jens Fleischer. All rights reserved.

  This file is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.
  This file is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.
*******************************************************************/
#include <list>

const char WARNING[] PROGMEM = R"(<h2>Der Sketch wurde mit "no SPIFFS" kompilliert!)";
const char HELPER[] PROGMEM = R"(<form method="POST" action="/upload" enctype="multipart/form-data">
<input type="file" name="[]" multiple><button>Upload</button></form>Lade die spiffs.html hoch.)";

void spiffs() {     // Funktionsaufruf "spiffs();" muss im Setup eingebunden werden
  SPIFFS.begin();
  webServer.on("/list", handleList);
  webServer.on("/format", formatSpiffs);
  webServer.on("/upload", HTTP_POST, sendResponce, handleUpload);

  webServer.onNotFound([]() {
    if (!handleFile(webServer.urlDecode(webServer.uri())))
      webServer.send(404, "text/plain", "FileNotFound");
  });
 
}

void handleList() {                           // Senden aller Daten an den Client
  FSInfo fs_info;  SPIFFS.info(fs_info);      // Füllt FSInfo Struktur mit Informationen über das Dateisystem
  Dir dir = SPIFFS.openDir("/");              // Auflistung aller im Spiffs vorhandenen Dateien
  typedef std::pair<String, int> prop;
  std::list<prop> dirList;                                                               // Liste anlegen
  while (dir.next()) 
  {
    dirList.emplace_back(dir.fileName().substring(1), dir.fileSize());                   // Liste füllen
  }
  dirList.sort([](const prop & f, const prop & l) {                                      // Liste sortieren
    if (webServer.arg(0) == "1") {
      return f.second > l.second;
    } else {
      for (uint8_t i = 0; i < 30; i++) {
        if (tolower(f.first[i]) < tolower(l.first[i])) return true;
        else if (tolower(f.first[i]) > tolower(l.first[i])) return false;
      }
      return false;
    }
  });
  
  webServer.setContentLength(CONTENT_LENGTH_UNKNOWN);

  uint8_t jsonoutteil = 0;
  bool jsonoutfirst = true;
  
  String temp = "[";
  for (auto& p : dirList) {
    
    if (temp != "[") temp += ",";
    temp += "{\"name\":\"" + p.first + "\",\"size\":\"" + formatBytes(p.second) + "\"}";
    jsonoutteil++;
    if ( jsonoutteil > 10 ) 
    {
      jsonoutteil = 0;
      if ( jsonoutfirst )
      {
        jsonoutfirst = false;
        webServer.send(200, "application/json", temp);
      }
      else
      {
        webServer.sendContent(temp);
      }
      temp = "";
      delay(0);
    }
  }
  temp += ",{\"usedBytes\":\"" + formatBytes(fs_info.usedBytes * 1.05) + "\"," +             // Berechnet den verwendeten Speicherplatz + 5% Sicherheitsaufschlag
          "\"totalBytes\":\"" + formatBytes(fs_info.totalBytes) + "\",\"freeBytes\":\"" +    // Zeigt die Größe des Speichers
          (fs_info.totalBytes - (fs_info.usedBytes * 1.05)) + "\"}]";                        // Berechnet den freien Speicherplatz + 5% Sicherheitsaufschlag
  webServer.sendContent(temp);
  webServer.sendContent("");
  temp = "";
}

bool handleFile(String&& path) {
#ifdef DEBUG_WEB
  Serial.println(path);
#endif
  if (webServer.hasArg("delete")) {
    SPIFFS.remove(webServer.arg("delete"));                   // Datei löschen
    sendResponce();
    return true;
  }
  if (!SPIFFS.exists("/spiffs.html"))webServer.send(200, "text/html", SPIFFS.begin() ? HELPER : WARNING);     // ermöglicht das hochladen der spiffs.html
  if (path.endsWith("/")) path += "index.html";
  if (path.endsWith("player")) path="/spieler.html";
  if (path.endsWith("spieler")) path="/spieler.html";
  return SPIFFS.exists(path) ? ({File f = SPIFFS.open(path, "r"); webServer.streamFile(f, spiffsgetContentType(path)); f.close(); true;}) : false;
}

void handleUpload() {                                      // Dateien ins SPIFFS schreiben
  static File fsUploadFile;                                // enthält den aktuellen Upload
  HTTPUpload& upload = webServer.upload();
  if (upload.status == UPLOAD_FILE_START) {
    if (upload.filename.length() > 30) {
      upload.filename = upload.filename.substring(upload.filename.length() - 30, upload.filename.length());  // Dateinamen auf 30 Zeichen kürzen
    }
    printf(PSTR("handleFileUpload Name: /%s\n"), upload.filename.c_str());
    fsUploadFile = SPIFFS.open("/" + webServer.urlDecode(upload.filename), "w");
  } else if (upload.status == UPLOAD_FILE_WRITE) {
    printf(PSTR("handleFileUpload Data: %u\n"), upload.currentSize);
    fsUploadFile.write(upload.buf, upload.currentSize);
  } else if (upload.status == UPLOAD_FILE_END) {
    printf(PSTR("handleFileUpload Size: %u\n"), upload.totalSize);
    fsUploadFile.close();
  }
}

void formatSpiffs() {                                      // Formatiert den Speicher
  SPIFFS.format();
  sendResponce();
}

void sendResponce() {
  webServer.sendHeader("Location", "spiffs.html");
  webServer.send(303, "message/http");
}

const String formatBytes(size_t const& bytes) {            // lesbare Anzeige der Speichergrößen
  return bytes < 1024 ? static_cast<String>(bytes) + " Byte" : bytes < 1048576 ? static_cast<String>(bytes / 1024.0) + " KB" : static_cast<String>(bytes / 1048576.0) + " MB";
}

const String spiffsgetContentType(const String& path) {          // ermittelt den Content-Typ
  using namespace mime;
  char buff[sizeof(mimeTable[0].mimeType)];
  for (size_t i = 0; i < maxType - 1; i++) {
    strcpy_P(buff, mimeTable[i].endsWith);
    if (path.endsWith(buff)) {
      strcpy_P(buff, mimeTable[i].mimeType);
      return static_cast<String>(buff);
    }
  }
  strcpy_P(buff, mimeTable[maxType - 1].mimeType);
  return static_cast<String>(buff);
}

bool freeSpace(uint16_t const& printsize) {                // Funktion um beim speichern in Logdateien zu prüfen ob noch genügend freier Platz verfügbar ist.
  FSInfo fs_info;   SPIFFS.info(fs_info);                  // Füllt FSInfo Struktur mit Informationen über das Dateisystem
  //Serial.printf("Funktion: %s meldet in Zeile: %d FreeSpace: %s\n", __PRETTY_FUNCTION__, __LINE__, formatBytes(fs_info.totalBytes - (fs_info.usedBytes * 1.05)).c_str());
  return (fs_info.totalBytes - (fs_info.usedBytes * 1.05) > printsize) ? true : false;
}
