
#ifdef USE_WIFI

// WIFI //

// ************************************************* //
// *************** setup_inicial   ***************** //
// ************************************************* //

// ******************************
// ****** CONEXION A WIFI *******
// ******************************

void setup_wifi( unsigned long reintentos ) 
{

  tell("Conectando a");
  tellln(mi_ssid);
  
  WiFi.begin(mi_ssid, mi_password);
  
  while ((reintentos-->0)&&(WiFi.status() != WL_CONNECTED)) 
  {
    delay(500);
    tell(".");
  
  }

  if (reintentos>0)
  {
    tellln("Conectado a red WiFI");
    estado_red_WIFI = 1;
    //EnviarSMS ("Conectado a red WiFI"); // Cambiar de lugar
    tell("IP: ");
    tellln(WiFi.localIP().toString().c_str());
   }
   
}

void scanNetworks() {
  // scan for nearby networks:
  tellln("** Scan Networks **");
  byte numSsid = WiFi.scanNetworks();

  // print the list of networks seen:
  tell("SSID List:");
  tellln(String(numSsid).c_str());
  // print the network number and name for each network found:
  for (int thisNet = 0; thisNet<numSsid; thisNet++) {
    tell(String(thisNet).c_str());
    tell(") Network: ");
    tellln(WiFi.SSID(thisNet).c_str());
  }
}

#endif 
