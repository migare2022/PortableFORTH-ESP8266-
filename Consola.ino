

WiFiServer TelnetServer(23);
WiFiClient client;
int estado_cliente = 0;

// ************************************************* //
// *************** setup_inicial   ***************** //
// ************************************************* //



/* The primary data output function. This is the place to change if you want
* to e.g. output data on a microcontroller via a serial interface. */
void putkey(char c)
{
   // delay(10); 
    putchar(c);
    if (estado_cliente) {  if (c=='\n') { client.print ('\r');
                                          // delay(10);
                                         }
                            client.print (c);
                        }
                        
}







void setup_Consola_Serial ()
{

  // Consola USB
  Serial.begin(SERIALSPEED); 
  
}

void setup_Consola_Telnet ()
{
  TelnetServer.begin();
}



//***************************************************//
//**************** loop_asincronico *****************//
//***************************************************//


 
void loop_asinc_serial(void ) {
byte ch;

   if (Serial.available()) {
     
                 // Serial.println("Caracter...");

                 delay(1);
                 ch = Serial.read();

                  MMProc.ScriptPrueba[MMProc.IndiceScript++]= (char)ch;

              if (ch=='\n') quit_forth(&MMProc);

                    
   }
}


void loop_asinc_socket ()  {

   if (!estado_cliente) client = TelnetServer.available();
  
  if (client) {
               if(client.connected())
                     {        if (!estado_cliente) {
                              Serial.println("Cliente Telnet conectado");
                              estado_cliente =1;   }
                      }
                else {    if (estado_cliente){
                     Serial.println("Cliente Telnet deconectado");
                      estado_cliente =0; }
                      }
    
              } 

   else { if (estado_cliente){
         Serial.println("Cliente Telnet deconectado");
         estado_cliente =0; }    
         }
    
   if(client.connected()){      

      // read data from the connected client
     if (client.available()>0)   
          {

             char ch = client.read();

              MMProc.ScriptPrueba[MMProc.IndiceScript++]= (char)ch;

              if (ch=='\n') quit_forth(&MMProc);
            
          }
               
      // Send Data to connected client
      //if (Serial.available()>0) client.write(Serial.read());     
     
    ///client.stop();
    //Serial.println("Client disconnected");    
     }
    
}



void ConsolaPrint(String s)
{  

Serial.print(s);  
if (estado_cliente) client.print (s);
}

void ConsolaPrintln(String  s)
{
Serial.println(s); 
if (estado_cliente) client.println (s);
}



void ConsolaPrintDebug(String s, int D)
{  
if (D<=DEBUG) ConsolaPrint(s); 
}


void ConsolaPrintlnDebug(String s, int D)
{  
if (D<=DEBUG) ConsolaPrintln(s); 
}
