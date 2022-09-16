//Executable segment sizes:
//IROM   : 239380          - code in flash         (default or ICACHE_FLASH_ATTR) 
//IRAM   : 27376   / 32768 - code in IRAM          (ICACHE_RAM_ATTR, ISRs...) 
//DATA   : 2500  )         - initialized variables (global, static) in RAM/HEAP 
//RODATA : 4800  ) / 81920 - constants             (global, static) in RAM/HEAP 
//BSS    : 50288 )         - zeroed variables      (global, static) in RAM/HEAP 
//Sketch uses 274056 bytes (26%) of program storage space. Maximum is 1044464 bytes.
//Global variables use 57588 bytes (70%) of dynamic memory, leaving 24332 bytes for local variables. Maximum is 81920 bytes.

#define DEBUG 1

#define ESP8266
//#define ESP32

#define USE_WIFI   
#define OTA

#define SERIALSPEED  115200   // 115200 
//*********************************** CORTE  *************************************//

#include "_ForthLib.h"

tMiniProc* pMMProc;
tMiniProc MMProc;



#ifdef USE_WIFI
    #ifdef ESP8266    
    #include <ESP8266WiFi.h>
    #endif

    #ifdef ESP32    
    #include <WiFi.h>
    #endif

    WiFiClient espClient;
    const char* mi_ssid =  "TeleCentro-a6f1";
    const char* mi_password =  "MTFGMJMMJJDZ";
    void WiFiTellSSID () { tellln( WiFi.SSID().c_str() );  }
    void WiFiTellIP () { tellln( WiFi.localIP().toString().c_str() );  }
    void WiFiTellgateIP () { tellln( WiFi.gatewayIP().toString().c_str() ); }
    void WiFiDisconnect (){  WiFi.disconnect(); tellln ("Desconectado"); }
    
    int estado_red_WIFI = 0;
    
#endif




//*******************************************************//
const char *initScriptEsp =

  ": Aoff 14 OUTPUT PINMODE 14 HIGH DIGITALWRITE ;\n"
  ": Aon  14 OUTPUT PINMODE 14 LOW DIGITALWRITE ;\n"
  ": Boff 12 OUTPUT PINMODE 12 HIGH DIGITALWRITE ;\n"
  ": Bon 12 OUTPUT PINMODE 12 LOW DIGITALWRITE ;\n"


   //****************************************//
   
   ": SET_LED LED_BUILTIN OUTPUT PINMODE ;\n"
   ": LED_ON LED_BUILTIN LOW DIGITALWRITE ;\n"
   ": LED_OFF LED_BUILTIN HIGH DIGITALWRITE ;\n"
   ": TILT SET_LED 10 0 DO i . LED_ON 500 DELAY LED_OFF 500 DELAY LOOP ;\n"
   ": TILTn SET_LED  0 DO i . LED_ON 500 DELAY LED_OFF 500 DELAY LOOP ;\n"
   
   ".\" ESP8266 - NodeMCU \"\n"
   ";!\n" // (BYE) PARA QUE SALGA DESPUES DE HACER TODO
    ;
//********************************************************//



/*******************************************************************************
*
* Builtin definitions
*
*******************************************************************************/


//************************************************************************************************************************************//
//********************************************************** BUILD IN ****************************************************************//
//************************************************************************************************************************************//

void _delay (unsigned long n) {delay(n);}

#ifdef ESP8266    
ADC_MODE(ADC_VCC);
long ESPgetvcc () { return ESP.getVcc(); }
void ESPreset ()   { ESP.reset(); }

#endif

#ifdef ESP32    
long ESPgetvcc () { return 0; }
void ESPreset ()   { ESP.restart(); }
#endif

void ESPrestart () { ESP.restart(); }



//********************************************************//
//CONSTANTES
//********************************************************//

struct t_builtin_f  ListaBuiltinEsp[] = {
{"HIGH",{.i_cte=HIGH},0,T_I_CTE },
{"LOW",{.i_cte=LOW},0,T_I_CTE },
{"INPUT",{.i_cte=INPUT},0,T_I_CTE },
{"OUTPUT",{.i_cte=OUTPUT},0,T_I_CTE },
{"INPUT_PULLUP",{.i_cte=INPUT_PULLUP},0,T_I_CTE },
{"LED_BUILTIN",{.i_cte=LED_BUILTIN},0,T_I_CTE },

{"RESTART",{.t_v_v=ESPrestart},0,T_VOID_VOID},
{"RESET",{.t_v_v=ESPreset},0,T_VOID_VOID},

{"VCC?",{.t_l_v=ESPgetvcc},0,T_LONG_VOID},

{"DIGITALREAD",{.t_i_uc=digitalRead},0,T_INT_UCHAR},    // PIN
{"PINMODE",{.t_v_uc_uc=pinMode},0,T_VOID_UCHAR_UCHAR},  // PIN MODE
{"DIGITALWRITE",{.t_v_uc_uc=digitalWrite},0,T_VOID_UCHAR_UCHAR},  // PIN VALUE


#ifdef USE_WIFI

{"SSID?",{.t_v_v=WiFiTellSSID},0,T_VOID_VOID},
{"IP?",{.t_v_v=WiFiTellIP},0,T_VOID_VOID},
{"GATEIP?",{.t_v_v=WiFiTellgateIP},0,T_VOID_VOID},
{"DESCONECTAR",{.t_v_v= WiFiDisconnect},0,T_VOID_VOID},
{"CONECTAR",{.t_v_ul=  setup_wifi},0,T_VOID_ULONG},
{"SCAN",{.t_v_v= scanNetworks },0,T_VOID_VOID},

#endif


{"MICROS",{.t_ul_v=micros},0,T_LONG_VOID},
{"MILLIS",{.t_ul_v=millis},0,T_LONG_VOID},
{"RANDOM",{.t_l_l=random},0,T_LONG_LONG},
{"DELAY",{.t_v_ul=_delay},0,T_VOID_ULONG}
 
 };


//**************************************************************************************************************************************//
//**************************************************************** ESP8266 *************************************************************//
//**************************************************************************************************************************************//


int MAX_BUILTIN_ESP () { return (sizeof(ListaBuiltinEsp)/sizeof(struct t_builtin_f)); }


//#ifdef ESP8266

void setup() {

setup_Consola_Serial ();

setup_forth (&MMProc, ListaBuiltinEsp, initScriptEsp);

#ifdef USE_WIFI
  setup_wifi(10);
  setup_Consola_Telnet();  
#endif



#ifdef OTA
  setup_OTA();  //DEPENDE DE WIFI
#endif


}




void loop() {

 // **************************************** //
 // ************** ASINCRONICO ************* //
 // **************************************** //

  loop_asinc_serial ();
  loop_asinc_socket ();
 
   


  if (WiFi.status() != WL_CONNECTED)
    {
      tellln("WiFi no conectado...");
      setup_wifi(10);  
    }
  else {
          #ifdef OTA
          loop_asinc_OTA ();  //DEPENDE DE WIFI
          #endif  OTA 
   }




}

//#endif // ESP8266

#ifdef WINDOWS


int main() {
setup_forth (); 
}
#endif //WINDOWS
