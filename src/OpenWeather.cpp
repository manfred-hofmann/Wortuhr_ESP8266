//******************************************************************************
// OpenWeather.cpp - Get weather data from OpenWeather
//******************************************************************************

#include "OpenWeather.h"

OpenWeather::OpenWeather()
{
}

OpenWeather::~OpenWeather()
{
}

uint16_t OpenWeather::getOutdoorConditions(String location, String apiKey)
{
  
  String response;
  String sdescription;
  String dout;
  uint8_t retcode;
  int timezoneshift;
  retcode = 0;
  owfehler = "Alles OK!!";
  if ( apiKey.length() > 25 ) 
  {
    WiFiClient client;
   
#ifdef DEBUG_OW
  Serial.println("Call Open Weather" );
#endif    
    if (client.connect("api.openweathermap.org", 80))
    {
        String url = "/data/2.5/weather?q=" + String(location) + "&lang=de&units=metric&appid=" + String(apiKey);
#ifdef DEBUG_OW
  Serial.printf("Open Weather url: %s\n",url.c_str() );
#endif       
        client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: api.openweathermap.org" + "\r\n" + "Connection: close\r\n\r\n");
        unsigned long timeout = millis();
        while (client.available() == 0)
        {
            if (millis() - timeout > 5000)
            {
                client.stop();
                return 1;
            }
        }
        client.setTimeout(2000);
        while (client.available())
            response = client.readStringUntil('\r'); 

        response.trim();
#ifdef DEBUG_OW
  Serial.printf("Open Weather Response: %s\n",response.c_str() );
#endif

        JSONVar weatherArray = JSON.parse(response);
        description = "";
        weathericon2 = "";   
        weathericon1 = "";
        weatherid1 = 0;
        weatherid2 = 0;
        for ( uint8_t z = 0;z < weatherArray["weather"].length() ;z++)
        {
          sdescription = (const char*)weatherArray["weather"][z]["description"];
          description += sdescription;
          if ( z+1 < weatherArray["weather"].length()) description += ", ";
          if ( z == 0 ) 
          {
            weathericon1 = (const char*)weatherArray["weather"][z]["icon"];
            weatherid1   = (int)weatherArray["weather"][z]["id"];
          }
          if ( z == 1 ) 
          {
            weathericon2 = (const char*)weatherArray["weather"][z]["icon"];
            weatherid2   = (int)weatherArray["weather"][z]["id"];
          }
#ifdef DEBUG_OW
  Serial.printf("Open Weather description: %i ",z );
  Serial.print( weatherArray["weather"][z]["description"]);
  Serial.print (" ID: ");
  Serial.print ( weatherArray["weather"][z]["id"]);
  Serial.print (" Icon: ");
  Serial.println( weatherArray["weather"][z]["icon"]);
#endif    
        }
        description.trim();
#ifdef DEBUG_OW
  Serial.print("Open Weather description:");
  Serial.println(description);
#endif        
        if(! isnan((double)weatherArray["main"]["temp"]) ) 
        {
          temperature = (double)weatherArray["main"]["temp"];
#ifdef DEBUG_OW
  Serial.print("Open Weather temperature:");
  Serial.println(temperature);
#endif  
        }
        else
        {
          retcode = retcode + 2;
          owfehler = "Fehler bei Temperatur!!";
        }
        if(! isnan((int)weatherArray["main"]["humidity"]))
        {
          humidity = (int)weatherArray["main"]["humidity"];
#ifdef DEBUG_OW
  Serial.print("Open Weather humidity:");
  Serial.println(humidity);
#endif  
        }
        else
        {
          retcode = retcode + 4;
          owfehler = "Fehler bei Luftfeuchte!!";
        }
        if(! isnan((int)(int)weatherArray["main"]["pressure"]))
        {
          pressure = (int)weatherArray["main"]["pressure"];
#ifdef DEBUG_OW
  Serial.print("Open Weather pressure:");
  Serial.println(pressure);
#endif  
        }
        else
        {
          retcode = retcode + 8;
          owfehler = "Fehler bei Luftdruck!!";
        }
//Clouds
        if(! isnan((int)(int)weatherArray["clouds"]["all"]))
        {
          clouds = (int)weatherArray["clouds"]["all"];
        }
// Sonnenaufgang
        if(! isnan((int)(int)weatherArray["sys"]["sunrise"]))
        {
          sunrise = (int)weatherArray["sys"]["sunrise"] + (int)weatherArray["timezone"];
#ifdef DEBUG_OW
  Serial.print("Open Weather sunrise:");
  Serial.println(sunrise);
  dout = "Sonnenaufgang: " + String(hour(sunrise)) + ":";
  if (minute(sunrise) < 10) dout += "0";
  dout += String(minute(sunrise));
  dout += ":";
  if (second(sunrise) < 10) dout += "0";
  dout += String(second(sunrise));
  Serial.println(dout);
#endif  
        }
        else
        {
          retcode = retcode + 16;
          owfehler = "Keine Sonnenaufgangsinfo!!";
        }
// Sonnenuntergang
        if(! isnan((int)(int)weatherArray["sys"]["sunset"]))
        {
          sunset = (int)weatherArray["sys"]["sunset"] + (int)weatherArray["timezone"];
#ifdef DEBUG_OW
  Serial.print("Open Weather sunset:");
  Serial.println(sunset);
  dout = "Sonnenuntergang: " + String(hour(sunset)) + ":";
  if (minute(sunset) < 10) dout += "0";
  dout += String(minute(sunset));
  dout += ":";
  if (second(sunset) < 10) dout += "0";
  dout += String(second(sunset));
  Serial.println(dout);
#endif  
        }
        else
        {
          retcode = retcode + 32;
          owfehler = "Keine Sonnenuntergangsinfo!!";
        }
        if(! isnan((double)weatherArray["wind"]["speed"]) ) 
        {
          windspeed = (double)weatherArray["wind"]["speed"];
#ifdef DEBUG_OW
  Serial.print("Wind Speed:");
  Serial.println(windspeed);
#endif  
        }
      client.stop();
    }
    else
    {
#ifdef DEBUG_OW
      Serial.println("Keine Connect zu Open Weather!!" );
#endif
      retcode = 64;
      owfehler = "Keine Connect zu Open Weather!!";
    }
  }
  else
  {
    retcode = 1;
    owfehler = "API-Key zu kurz!!";
    description = "";
    weathericon1 = "";
    weathericon2 = "";
    weatherid1 = 0;
    weatherid2 = 0;
    temperature = 0;
    windspeed = 0;
    humidity = 0;
    clouds = 0;
    pressure = 0;
  }
  return retcode;
}
