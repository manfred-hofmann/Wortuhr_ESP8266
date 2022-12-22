#include <list>

void setupFS() {
  initFS();

  webServer.on("/fs", handleFSExplorer);
  webServer.on(F("/fsstyle.css"),handleFSExplorerCSS);

  webServer.on(F("/sanduhr"), []() {sendPcontent(p_bluespinner,sizeof(p_bluespinner),IMAGE_GIF);});
  webServer.on(F("/sunrise"), []() {sendPcontent(p_sunrise,sizeof(p_sunrise),IMAGE_PNG);});
  webServer.on(F("/sunset"), []() {sendPcontent(p_sunset,sizeof(p_sunset),IMAGE_PNG);});

  webServer.on(F("/format"), formatFS);
  webServer.on(F("/upload"), HTTP_POST, sendResponce, handleUpload);

  webServer.onNotFound([]() {
    if (!handleFile(webServer.urlDecode(webServer.uri())))
      webServer.send(404, TEXT_PLAIN, F("FileNotFound"));
  });
 
}


void initFS() {
  if ( !LittleFS.begin() ) 
  {
    Serial.println(F("LittleFS Mount fehlgeschlagen"));
    if ( !LittleFS.format() )
    {
      Serial.println(F("Formatierung nicht möglich"));
    }
    else
    {
      Serial.println(F("Formatierung erfolgreich"));
      if ( !LittleFS.begin() )
      {
        Serial.println(F("LittleFS Mount trotzdem fehlgeschlagen"));
      }
      else 
      {
        Serial.println(F("LittleFS Dateisystems erfolgreich gemounted!")); 
      }
    }
  }  
  else
  {
    Serial.println(F("LittleFS erfolgreich gemounted!"));
  }
  
  if ( !LittleFS.exists("/web"))
  {
    if ( LittleFS.mkdir("/web") )
    {
      Serial.println(F("Verzeichnis /web erstellt"));
    }
    else
    {
      Serial.println(F("Verzeichnis /web konnte nicht erstellt werden"));
    }
  } 
}

bool handleList() {                                                                    // Senden aller Daten an den Client
  FSInfo fs_info;  LittleFS.info(fs_info);                                             // Füllt FSInfo Struktur mit Informationen über das Dateisystem
  Dir dir = LittleFS.openDir("/");
#ifdef DEBUG_WEB
  Serial.printf("LittleFS.handleList: %i Codezeile: %u\n", ESP.getMaxFreeBlockSize(),  __LINE__);
#endif
  using namespace std;
  using records = tuple<String, String, int>;
  list<records> dirList;
  while (dir.next()) {                                                                 // Ordner und Dateien zur Liste hinzufügen
    if (dir.isDirectory()) {
      uint8_t ran {0};
      Dir fold = LittleFS.openDir(dir.fileName());
      while (fold.next())  {
        ran++;
        dirList.emplace_back(dir.fileName(), fold.fileName(), fold.fileSize());
      }
      if (!ran) dirList.emplace_back(dir.fileName(), "", 0);
    }
    else {
      dirList.emplace_back("", dir.fileName(), dir.fileSize());
    }
  }
#ifdef DEBUG_WEB
  Serial.printf("LittleFS.handleList: %i Codezeile: %u\n", ESP.getMaxFreeBlockSize(),  __LINE__);
#endif  
  dirList.sort([](const records & f, const records & l) {                              // Dateien sortieren
    if (webServer.arg(0) == "1") {
      return get<2>(f) > get<2>(l);
    } else {
      for (uint8_t i = 0; i < 31; i++) {
        if (tolower(get<1>(f)[i]) < tolower(get<1>(l)[i])) return true;
        else if (tolower(get<1>(f)[i]) > tolower(get<1>(l)[i])) return false;
      }
      return false;
    }
  });
  dirList.sort([](const records & f, const records & l) {                              // Ordner sortieren
    if (get<0>(f)[0] != 0x00 || get<0>(l)[0] != 0x00) {
      for (uint8_t i = 0; i < 31; i++) {
          if (tolower(get<0>(f)[i]) < tolower(get<0>(l)[i])) return true;
          else if (tolower(get<0>(f)[i]) > tolower(get<0>(l)[i])) return false;
      }
    }
    return false;
  });
#ifdef DEBUG_WEB
  Serial.printf("LittleFS: %i Codezeile: %u\n", ESP.getMaxFreeBlockSize(),  __LINE__);
#endif
  webServer.setContentLength(CONTENT_LENGTH_UNKNOWN);
  uint8_t jsonoutteil = 0;
  bool jsonoutfirst = true;
  String temp = F("[");
  for (auto& t : dirList) {
    if ( ESP.getMaxFreeBlockSize() < 1000) delay(10);
    if (temp != "[") temp += ',';
    temp += F("{\"folder\":\"");
    temp += get<0>(t);
    temp += F("\",\"name\":\"");
    temp += get<1>(t);
    temp += F("\",\"size\":\"");
    temp += formatBytes(get<2>(t));
    temp += F("\"}");
    jsonoutteil++;
    if ( jsonoutteil > 2 ) 
    {
      jsonoutteil = 0;
      if ( jsonoutfirst )
      {
        jsonoutfirst = false;
        webServer.send(200, F("application/json"), temp);
      }
      else
      {
        webServer.sendContent(temp);
      }

      if ( ESP.getMaxFreeBlockSize() < minFreeBlockSize )
      {
        minFreeBlockSize = ESP.getMaxFreeBlockSize();
        codeline = __LINE__;
        codetab = __NAME__;
#ifdef DEBUG_WEB
        Serial.printf("minFreeBlockSize: %i Tab: %s Codezeile: %u\n", minFreeBlockSize, codetab.c_str(), codezeile);
#endif
      }
#ifdef DEBUG_WEB
      Serial.printf("LittleFS.handleList.MaxFreeBlockSize: %i Codezeile: %u\n", ESP.getMaxFreeBlockSize(),  __LINE__);
      Serial.println(temp);
#endif

      temp = "";
      delay(0);
    } 
  }
  temp += F(",{\"usedBytes\":\"");
  temp += formatBytes(fs_info.usedBytes);                      // Berechnet den verwendeten Speicherplatz
  temp += F("\",\"totalBytes\":\"");
  temp += formatBytes(fs_info.totalBytes);                     // Zeigt die Größe des Speichers
  temp += F("\",\"freeBytes\":\""); 
  temp += (fs_info.totalBytes - fs_info.usedBytes);            // Berechnet den freien Speicherplatz
  temp += F("\"}]");   

  webServer.sendContent(temp);
  webServer.sendContent("");
#ifdef DEBUG_WEB
  Serial.println(temp);
#endif
  temp = "";

  return true;
}

void deleteRecursive(const String &path) {
  if (LittleFS.remove(path)) {
    LittleFS.open(path.substring(0, path.lastIndexOf('/')) + "/", "w");
    return;
  }
  Dir dir = LittleFS.openDir(path);
  while (dir.next()) {
    deleteRecursive(path + '/' + dir.fileName());
  }
  LittleFS.rmdir(path);
}

bool handleFile(String &&path) {
#ifdef DEBUG_WEB
  Serial.print (F("LittleFS handleFile: "));
  Serial.println(path);
#endif

  if (path.endsWith("/")) path += F("index.html");
  if (path.endsWith(F("player"))) path=F("/web/spieler.html");
  if (path.endsWith(F("spieler"))) path=F("/web/spieler.html");
  if (path.endsWith(F("favicon.ico"))) path=F("/web/favicon.ico");
  if ( LittleFS.exists(path) )
  {
    File f = LittleFS.open(path, "r");
    if(!f)
    {
      Serial.print(F("Fehler beim lesen des Files: "));
      Serial.println(path);
      return false;
    }
    else
    {
#ifdef DEBUG_WEB
      Serial.println(mime::getContentType(path));
#endif
      webServer.streamFile(f, mime::getContentType(path));
      f.close(); 
      return true;
    }
  }
  else
  {
    return false;
  }
}

void handleUpload() {                                                                  // Dateien ins Filesystem schreiben
  static File fsUploadFile;
  HTTPUpload& upload = webServer.upload();
  if (upload.status == UPLOAD_FILE_START) {
    if (upload.filename.length() > 31) {  // Dateinamen kürzen
      upload.filename = upload.filename.substring(upload.filename.length() - 31, upload.filename.length());
    }
    Serial.print(F("handleFileUpload Name: "));
    Serial.println (upload.filename);
    fsUploadFile = LittleFS.open(webServer.arg(0) + "/" + webServer.urlDecode(upload.filename), "w");
  } else if (upload.status == UPLOAD_FILE_WRITE) {
    Serial.print(F("handleFileUpload Data: "));
    Serial.println (upload.currentSize);
    fsUploadFile.write(upload.buf, upload.currentSize);
  } else if (upload.status == UPLOAD_FILE_END) {
    Serial.print(F("handleFileUpload Size: "));
    Serial.println (upload.totalSize);
    fsUploadFile.close();
  }
}

void formatFS() {                                                                      // Formatiert das Filesystem
  LittleFS.format();
  initFS();
  sendResponce();
}

void sendResponce() {
  webServer.sendHeader("Location", "fs");
  webServer.send(303, "message/http");
}

const String formatBytes(size_t const& bytes) {                                        // lesbare Anzeige der Speichergrößen
  return bytes < 1024 ? static_cast<String>(bytes) + " Byte" : bytes < 1048576 ? static_cast<String>(bytes / 1024.0) + "KB" : static_cast<String>(bytes / 1048576.0) + "MB";
}

// #####################################################################################################################
// FS Webseite
// Teil 1
const char fshtml1[] PROGMEM =  R"=====(
    document.addEventListener('DOMContentLoaded', () => {
    list(JSON.parse(localStorage.getItem('sortBy')));
    btn.addEventListener('click', () => {
      if (!confirm(LANG_FORMATCONF + "\n" )) event.preventDefault();
    });
    });
    function list(to){
    let myList = document.querySelector('main'), noted = '';
    fetch(`?sort=${to}`).then( (response) => {
          return response.json();
        }).then((json) => {
      myList.innerHTML = '<nav><input type="radio" id="/" name="group" checked="checked"><label for="/"> &#128193;</label><span id="cr">+&#128193;</nav></span><span id="si"></span>';
      document.querySelector('form').setAttribute('action', '/upload?f=');
      for (var i = 0; i < json.length - 1; i++) {
        let dir = '', f = json[i].folder, n = json[i].name;
        if (f != noted) {
        noted = f;
        dir = `<nav><input type="radio" id="${f}" name="group"><label for="${f}"></label> &#128193; ${f} <a href="?delete=/${f}">&#x1f5d1;&#xfe0f;</a></nav>`;
        }
        if (n != '') dir += `<li><a href="${f}/${n}">${n}</a><small> ${json[i].size}</small><a href="${f}/${n}"download="${n}"> Download</a> or<a href="?delete=${f}/${n}"> Delete</a>`;
        myList.insertAdjacentHTML('beforeend', dir);
      }
      myList.insertAdjacentHTML('beforeend', `<li><b id="so">${to ? '&#9660;' : '&#9650;'} LittleFS</b><small> ` + LANG_FSUSED + `: ${json[i].usedBytes.replace(".00", "")}/` + LANG_FSTOTAL + `: ${json[i].totalBytes.replace(".00", "")}</small>`);
      var free = json[i].freeBytes;
      cr.addEventListener('click', () => {
      document.getElementById('no').classList.toggle('no');
      });
      so.addEventListener('click', () => {
      list(to=++to%2);
      localStorage.setItem('sortBy', JSON.stringify(to));
      });
      document.addEventListener('change', (e) => {
        if (e.target.id == 'fs') { 
          for (var bytes = 0, i = 0; i < event.target.files.length; i++) bytes += event.target.files[i].size;
              for (var output = `${bytes} Byte`, i = 0, circa = bytes / 1024; circa > 1; circa /= 1024) output = circa.toFixed(2) + ['KB', 'MB', 'GB'][i++];
              if (bytes > free) {
                si.innerHTML = `<li><b> ${output}</b><strong> ` + LANG_NOSPACE + `</strong></li>`;
                up.setAttribute('disabled', 'disabled');
              } 
              else {
                si.innerHTML = `<li><b>` + LANG_FILESIZE + `:</b> ${output}</li>`;
                up.removeAttribute('disabled');
              }
       }
       document.querySelectorAll(`input[type=radio]`).forEach(el => { if (el.checked) document.querySelector('form').setAttribute('action', '/upload?f=' + el.id)});
     });
     document.querySelectorAll('[href^="?delete=/"]').forEach(node => {
       node.addEventListener('click', () => {
            if (!confirm(LANG_SURE)) event.preventDefault();
       });
     });
   });
 }
    
</script>
</head>
<body>
)=====";

// Teil 2
const char fshtml2[] PROGMEM =  R"=====(
  <form method="post" enctype="multipart/form-data">
    <input id="fs" type="file" name="up[]" multiple>
    <button id="up" disabled>Upload</button>
  </form>
  <div class="sanduhrcontainer" id="sanduhrcontainer" style="display: none">
  <img class="sanduhr" id="sanduhr" style="width: 150px" src="/sanduhr" alt="Sanduhr">
  </div>
  <script>
    const upbut = document.getElementById("up");
    upbut.addEventListener("click", function() {
    document.getElementById("sanduhrcontainer").style.display = "block";
  });
  </script>
  
  <form id="no" class="no" method="POST">
)=====";

//################################################################
// FS Webseite CSS
// Teil 1

const char fsstyle1[] PROGMEM =  R"=====(
body {
  font-family: sans-serif;
  background-color: #aaaaaa;
  display: flex;
  max-width : 500px;
  flex-flow: column;
  align-items: center;
}
h1,h2 {
  color: #e1e1e1;
  text-shadow: 2px 2px 2px black;
}
li {
  background-color: #feb1e2;
  list-style-type: none;
  margin-bottom: 10px;
  padding: 2px 5px 1px 0;
  box-shadow: 5px 5px 5px rgba(0,0,0,0.7);
}
li a:first-child, li b {
  background-color: #8f05a5;
  font-weight: bold;
  color: white;
  text-decoration:none;
  padding: 2px 5px;
  text-shadow: 2px 2px 1px black;
  cursor:pointer;
}
li strong {
  color: red;
}
input {
  height:35px;
  font-size:14px;
}
label + a {
  text-decoration: none;
}
h1 + main {
  display: flex;
}  
aside {
  display: flex;
  flex-direction: column;
  padding: 0.2em;
}
#left {
  align-items:flex-end;
  text-shadow: 0.5px 0.5px 1px #757474;
}
.note {
  background-color: #fecdee;
  padding: 0.5em;
  margin-top: 1em;
  text-align: center;
  max-width: 320px;
  border-radius: 0.5em;
}
[type=submit] {
  height:40px; 
  font-size: 14px;
}
.buttons {
  background-color: #353746;
  text-align:center;
  line-height: 22px;
  color:#FFFFFF;
  width:200px;
  height: 32px;
  padding:1px;
  border:2px solid #FFFFFF;
  font-size:14px;
  border-radius:15px;
  cursor: pointer;
}
form [title] {
  background-color: #353746;
  font-size: 14px;
  width: 150px;
}
)=====";

 // Teil 2
const char fsstyle2[] PROGMEM =  R"=====(
nav {
  display: flex;
  align-items: baseline;
  justify-content: space-between;
}
#left {
  align-items:flex-end;
  text-shadow: 0.5px 0.5px 1px #757474;
}
#cr {
  font-weight: bold;
  cursor:pointer;
  font-size: 1.5em;
}
#up {
  width: auto; 
}
.note {
  background-color: #fecdee;
  padding: 0.5em;
  margin-top: 1em;
  text-align: center;
  max-width: 320px;
  border-radius: 0.5em;
}
.no {
  display: none;
}

[value*=Format] {
  margin-top: 1em;
  box-shadow: 5px 5px 5px rgba(0,0,0,0.7);
}
[name="group"] {
  display: none;
}
[name="group"] + label {
  font-size: 1.5em;
  margin-right: 5px;
}
[name="group"] + label::before {
  content: "\002610";
} 
[name="group"]:checked + label::before {
  content: '\002611\0027A5';
}
.sanduhrcontainer {
  position: absolute;
    top: 130px;
    left: 180px;
}
.sanduhr {
    position: absolute;
      margin: 0px auto;   
}
)=====";
// #####################################################################################################################

void handleFSExplorer() {
  String message;
  if (webServer.hasArg("new")) 
  {
    String folderName {webServer.arg("new")};
    for (auto& c : {34, 37, 38, 47, 58, 59, 92}) for (auto& e : folderName) if (e == c) e = 95;    // Ersetzen der nicht erlaubten Zeichen
    LittleFS.mkdir(folderName);
    sendResponce();
  }
  else if (webServer.hasArg("sort")) 
  {
    bool x=handleList();
  }
  else if (webServer.hasArg("delete")) 
  {
    deleteRecursive(webServer.arg("delete"));
    sendResponce();
  }
  else
  {
    webServer.setContentLength(CONTENT_LENGTH_UNKNOWN);
    message =  F("<!DOCTYPE HTML>");
    message += F("<html lang=\"");
    message += LANG_HTMLLANG;
    message += F("\">\n");
    message += F("<head>");
    message += F("<meta charset=\"UTF-8\">");
    message += F("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
    message += F("<link rel=\"stylesheet\" href=\"fsstyle.css\">");
    message += F("<title>");
    message += LANG_EXPLORER;
    message += F("</title>\n");
    message += F("<script>");
    message += F("const LANG_FORMATCONF = \"" LANG_FORMATCONF "\";\n");
    message += F("const LANG_NOSPACE = \"" LANG_NOSPACE "\";\n");
    message += F("const LANG_FILESIZE= \"" LANG_FILESIZE "\";\n");
    message += F("const LANG_SURE= \"" LANG_SURE "\";\n");
    message += F("const LANG_FSUSED= \"" LANG_FSUSED "\";\n");
    message += F("const LANG_FSTOTAL= \"" LANG_FSTOTAL "\";\n");
    
    webServer.send(200, F(TEXT_HTML), message);
    delay(0);
    webServer.sendContent_P(fshtml1);
    delay(0);
    message = F("<h2>" LANG_EXPLORER "</h2>");
    webServer.sendContent(message);
    webServer.sendContent_P(fshtml2);
    delay(0);
    message = F("<input name=\"new\" placeholder=\"" LANG_FOLDER "\"");    
    message += F(" pattern=\"[^\x22/%&\\:;]{1,31}\" title=\"");
    message += F(LANG_CHAR_NOT_ALLOW);
    message += F("\" required=\"\">");
    message += F("<button>Create</button>\n");
    message += F("</form>");
    message += F("<main></main>\n");
    message += F("<form action=\"/format\" method=\"POST\">\n");            
    message += F("<button class=\"buttons\" title=\"" LANG_BACK "\" id=\"back\" type=\"button\" onclick=\"window.location.href=\'\\/\'\">&#128281; " LANG_BACK "</button>\n");
    message += F("<button class=\"buttons\" title=\"Format LittleFS\" id=\"btn\" type=\"submit\" value=\"Format LittleFS\">&#10060;Format LittleFS</button>\n");
    message += F("</form>\n");
    message += F("</body>\n");
    message += F("</html>\n");
    webServer.sendContent(message);
    message = "";
    delay(0);
    webServer.sendContent("");
    delay(0);
  }
}

void handleFSExplorerCSS() {
  webServer.setContentLength(CONTENT_LENGTH_UNKNOWN);
  delay(0);
  webServer.send_P(200, TEXT_CSS, fsstyle1);
  delay(0);
  webServer.sendContent_P(fsstyle2);
  delay(0);
  webServer.sendContent("");  
  delay(0);
}


void sendPcontent(const char * p_cont, size_t size, char* ctype)
{
  const uint16_t maxbuff = 512;
  uint16_t aktsize = 0;
  uint16_t akt_index = 0;
  uint16_t sz;
  char tmp_buffer[maxbuff]; 
  bool f = true;

  webServer.setContentLength(size);
  while ( akt_index < size)
  {
    for (sz = 0; sz < maxbuff; sz++)
    {
      if ( sz+akt_index < size)
      {
        tmp_buffer[sz] = pgm_read_byte(&p_cont[sz+akt_index]);
        aktsize++;
      }
    }
    akt_index = akt_index + maxbuff;

    if ( f ) {
      webServer.send(200, ctype, tmp_buffer,aktsize);
      f = false;
    }
    else
    {
      webServer.sendContent(tmp_buffer,aktsize);
    }
//    Serial.printf("sendPcontent ESP.getMaxFreeBlockSize: %i Codezeile: %u\n", ESP.getMaxFreeBlockSize(),  __LINE__);
    delay(0);
    aktsize = 0;
  }
  delay(0); 
}
