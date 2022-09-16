


#ifdef WINDOWS
#define _MEM_SIZE 65536 /* main MMProc.memory size in bytes */
#define _getchar getchar
#define _EOF EOF
#endif // WINDOWS

#ifdef ESP8266
#define _MEM_SIZE 16384 /* main MMProc.memory size in bytes */
#define _EOF -1
#endif

#ifdef ESP32
#define _MEM_SIZE 65536 /* main MMProc.memory size in bytes */
#define _EOF -1
#endif



#define T_I_CTE 0x01

#define T_VOID_VOID   0x11
#define T_INT_VOID    0x12      // DEVUELVE INT
#define T_UINT_VOID   0x13      // DEVUELVE UNSIGNED INT
#define T_LONG_VOID   0x15      // DEVUELVE LONG
#define T_ULONG_VOID  0x16      // DEVUELVE UNSIGNED LONG

#define T_INT_INT    0x20      // DEVUELVE INT RECIBE INT
#define T_INT_UCHAR  0x21


#define T_I_CTE 0x01

#define T_VOID_VOID   0x11
#define T_INT_VOID    0x12      // DEVUELVE INT
#define T_UINT_VOID   0x13      // DEVUELVE UNSIGNED INT
#define T_LONG_VOID   0x15      // DEVUELVE LONG
#define T_ULONG_VOID  0x16      // DEVUELVE UNSIGNED LONG

#define T_INT_INT    0x20      // DEVUELVE INT RECIBE INT
#define T_INT_UCHAR  0x21


#define T_LONG_LONG  0x30
#define T_VOID_ULONG  0x31

#define T_VOID_UCHAR_UCHAR 0x40

/* Base cell data types. Use short/long on most systems for 16 bit cells. */
/* Experiment here if necessary. */
#define CELL_BASE_TYPE int
#define DOUBLE_CELL_BASE_TYPE long long

/* Basic MMProc.memory configuration */

#define STACK_SIZE 192 /* cells reserved for the stack */
#define RSTACK_SIZE 64 /* cells reserved for the return stack */
#define INPUT_LINE_SIZE 128 /* bytes reserved for the _word buffer */

#define N_ENTRADAS 16
#define N_SALIDAS 16


/******************************************************************************/

/* Our basic data types */
typedef CELL_BASE_TYPE scell;
typedef DOUBLE_CELL_BASE_TYPE dscell;
typedef unsigned CELL_BASE_TYPE cell;
typedef unsigned DOUBLE_CELL_BASE_TYPE dcell;
typedef unsigned char byte;
#define CELL_SIZE sizeof(cell)
#define DCELL_SIZE sizeof(dcell)

/* A few constants that describe the MMProc.memory layout of this implementation */
#define LATEST_POSITION INPUT_LINE_SIZE
#define HERE_POSITION (LATEST_POSITION + CELL_SIZE)
#define BASE_POSITION (HERE_POSITION + CELL_SIZE)
#define STATE_POSITION (BASE_POSITION + CELL_SIZE)
#define STACK_POSITION (STATE_POSITION + CELL_SIZE)
#define RSTACK_POSITION (STACK_POSITION + STACK_SIZE * CELL_SIZE)
#define HERE_START (RSTACK_POSITION + RSTACK_SIZE * CELL_SIZE)

/* Flags and masks for the dictionary */
#define FLAG_IMMEDIATE 0x80
#define FLAG_HIDDEN 0x40
#define MASK__name_length 0x1F

#define LINE_SIZE 256


//#define BUILTIN(id, _name, c__name, flags) const int c__name##_id=id; const char* c__name##__name=_name; const byte c__name##_flags=flags; void c__name()




// ES EL ORDEN QUE TIENEN EN LA LISTA DE COMANDOS ...se podra sacar...reemplazar por un #define?
#define DOCOL_ID 0
#define DOEXIT_ID 7
#define LIT_ID 37
#define QUIT_ID 38


typedef struct
{
/* Pointers to Forth variables stored inside the main memory array */
cell *latest, *here, *base, *state, *sp, *stack, *rsp, *rstack;

/* This is the main memory to be used by this Forth. There will be no malloc
* in this file. */
byte memory[_MEM_SIZE];

// I/O digitales
cell ENTRADAS[N_ENTRADAS];
cell SALIDAS[N_SALIDAS];

/* A few helper variables for the compiler */
int exitReq;   // 0=no salir //1=salir //-1=AutoExit
int errorFlag;
cell next;
cell lastIp;
cell quit_address;
cell commandAddress;
cell maxBuiltinAddress;

/* The TIB, stored outside the main memory array for now */
char lineBuffer[LINE_SIZE];
int charsInLineBuffer;
int positionInLineBuffer;
/* quizas se pueda usar el mismo buffer */
char  ScriptPrueba[LINE_SIZE];
int   IndiceScript;
char *Script_pos;


}tMiniProc;

/* A basic setup for defining builtins. This Forth uses impossibly low
* adresses as IDs for the builtins so we can define builtins as
* standard C functions. Slower but easier to port. */


// PARA SACAR EL WARNING ... definidas mas abajo
int EjecutarComando (cell command);
int MAX_BUILTIN_ID ();



typedef union  {
                   int i_cte;
                   void (*t_v_v)();     // T_VOID_VOID
                   int  (*t_i_v)();     // T_INT_VOID
          unsigned int  (*t_ui_v)();     // T_UINT_VOID
                   long (*t_l_v)();     // T_LONG_VOID
          unsigned long (*t_ul_v)();     // T_ULONG_VOID

                   char (*t_c_c)();
                   int  (*t_i_i)(int);   // T_INT_INT
                   long  (*t_l_l)(long);   // T_LONG_LONG
                   void  (*t_v_ul)(unsigned long);   // T_VOID_ULONG
                   int  (*t_i_uc)(unsigned char); // T_INT_UCHAR
                   void (*t_v_uc_uc)(unsigned char,unsigned char); // T_VOID_UCHAR_UCHAR

                  // Agregar nuevo tipo de fucion
} t_proto_f;




typedef struct t_builtin_f
{
//const int id; // ...es la posicion en la lista.
const char* _name;
t_proto_f f;
const byte flags;
const unsigned char tipo;
};






void docol();
void doCellSize();
void memRead();
void memReadByte();
void key();
void emit();
void drop();
void doExit();
void bye();
void doLatest();
void doHere();
void doBase ();
void doState();
void gotoInterpreter();
void gotoCompiler();
void hide();
void rtos();
void stor();
void key_p ();
void branch ();
void zbranch ();
void toggleImmediate ();
void doFree();
void s0_r();
void dsp_r();
void _not ();
void dup();
void memWrite();
void memWriteByte();
void _swap();
void over();
void comma();
void commaByte() ;
void _word();
void _find ();
void cfa ();
void number ();
void lit ();
void quit ();
void plus () ;
void minus () ;
void mul () ;
void divmod ();
void rot();
void doCreate();
void colon();
void semicolon();
void rget ();
void doJ ();
void tick();
void _equals();
void smaller();
void larger();
void doAnd ();
void doOr ();
void p_dup();
void litstring ();
void _xor ();
void timesDivide();
void timesDivideMod ();
void d_equals();
void dsmaller();
void dlarger();
void dusmaller();
void dplus();
void dminus();
void dmul();
void ddiv();
void d_swap();
void dover();
void drot();
void _words();
//********************* FUCIONES DE ENTRADA/SALIDA ****************************//
void get_entrada();
void put_salida();
void get_salida();


int setup_forth (tMiniProc* _pMMProc, struct t_builtin_f  *LBE, const char* initScriptSp );
void quit_forth (tMiniProc* _pMMProc);
void tell(const char *str);
void tellln(const char *str);
