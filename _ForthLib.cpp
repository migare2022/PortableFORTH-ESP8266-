 
#include "_ForthLib.h"
#include "_ansilib.h"


extern tMiniProc* pMMProc;
extern void putkey(char c);
extern struct t_builtin_f  ListaBuiltinEsp[]; 
extern int MAX_BUILTIN_ESP ();

/* C string output */
void tell(const char *str) {  while (*str) putkey(*str++); }
void tellln(const char *str) {  while (*str) putkey(*str++); putkey('\n'); }

struct t_builtin_f  ListaBuiltin[] ={
{"RUNDOCOL",{.t_v_v =docol},0,T_VOID_VOID},                  // Ejecuta la siguiente instruccion?
{"CELL",{.t_v_v=doCellSize},0,T_VOID_VOID},                  // Tamano (bytes) que ocupa una celda
{"@",{.t_v_v=memRead},0,T_VOID_VOID},                        // Peek de una posicion de memoria? ....
{"C@",{.t_v_v=memReadByte},0,T_VOID_VOID},                   // Fetches a byte from addr ( addr -- byte )
{"KEY",{.t_v_v=key},0,T_VOID_VOID},                          // Lee un caracter de la entrada (devuelve el codigo ASCII)
{"EMIT",{.t_v_v=emit},0,T_VOID_VOID},                        // Escribe un caracter de la entrada (devuelve el codigo ASCII)
{"DROP",{.t_v_v=drop},0,T_VOID_VOID},                        // Tira el ultimo elemento del stack
{"EXIT",{.t_v_v=doExit},0,T_VOID_VOID},                      // ? UNA ESPECIE DE RETORNO DE SUBRUTINA ???
{"BYE",{.t_v_v=bye},0,T_VOID_VOID},                          // SALE DEL PROGRAM
{"LATEST",{.t_v_v=doLatest},0,T_VOID_VOID},
{"HERE",{.t_v_v=doHere},0,T_VOID_VOID},
{"BASE",{.t_v_v=doBase},0,T_VOID_VOID},                  // CAMBIA LA BASE (DECIMAL, HEXADECIMAL ...)
{"STATE",{.t_v_v=doState},0,T_VOID_VOID},
{"[",{.t_v_v=gotoInterpreter},FLAG_IMMEDIATE,T_VOID_VOID},    //Begins interpreting.      Compiles the next (immediate) word. (Recommend using postpone instead.)
{"]",{.t_v_v=gotoCompiler},0,T_VOID_VOID},                    //Ends interpreting, resumes compilation.
{"HIDE",{.t_v_v=hide},0,T_VOID_VOID},                     // Oculta del diccionario
{"R>",{.t_v_v=rtos},0,T_VOID_VOID},                       // Moves a stack item to the return stack. ( x -- ) (R: -- x )
{">R",{.t_v_v=stor},0,T_VOID_VOID},                       // Moves a return stack item to the stack. ( -- x ) ( R: x -- )
{"KEY?",{.t_v_v=key_p},0,T_VOID_VOID},                    // True if a key has been typed on the console input device.
{"BRANCH",{.t_v_v=branch},0,T_VOID_VOID},
{"0BRANCH",{.t_v_v=zbranch},0,T_VOID_VOID},
{"IMMEDIATE",{.t_v_v=toggleImmediate},FLAG_IMMEDIATE,T_VOID_VOID},      //Marks the last definition as immediate.
{"FREE",{.t_v_v=doFree},0,T_VOID_VOID},                                 // MUESTRA LA MEMORIA LIBRE.
{"S0@",{.t_v_v=s0_r},0,T_VOID_VOID},
{"DSP@",{.t_v_v=dsp_r},0,T_VOID_VOID},
{"_not",{.t_v_v=_not},0,T_VOID_VOID},
{"DUP",{.t_v_v=dup},0,T_VOID_VOID},                         //  Duplicates the top stack item. ( x -- x x )
{"!",{.t_v_v=memWrite},0,T_VOID_VOID},                      // Stores a number at a-addr . ( x a-addr -- )
{"C!",{.t_v_v=memWriteByte},0,T_VOID_VOID},                 // Stores byte at addr . ( byte addr -- )
{"SWAP",{.t_v_v=_swap},0,T_VOID_VOID},                      // Exchanges the top 2 stack items. ( x1 x2 -- x2 x1 )
{"OVER",{.t_v_v=over},0,T_VOID_VOID},                       // Copies second stack item to top of stack. ( x1 x2 -- x1 x2 x1 )
{",",{.t_v_v=comma},0,T_VOID_VOID},                         // Places a number in the dictionary.
{"C,",{.t_v_v=commaByte},0,T_VOID_VOID},                    // Places a byte in the dictionary.
{"_word",{.t_v_v=_word},0,T_VOID_VOID},                     // Devuelve 1 y la longitud de la palabra leida
{"_find",{.t_v_v=_find},0,T_VOID_VOID},
{">CFA",{.t_v_v=cfa},0,T_VOID_VOID},
{"NUMBER",{.t_v_v=number},0,T_VOID_VOID},
{"LIT",{.t_v_v=lit},0,T_VOID_VOID},
{"QUIT",{.t_v_v=quit},0,T_VOID_VOID},

// **********************************************************************************************************************************
// ****************************** Antes de esta linea no cambiar orden (por los IDs) **********************************************************/

{"+",{.t_v_v=plus},0,T_VOID_VOID},
{"-",{.t_v_v=minus},0,T_VOID_VOID},
{"*",{.t_v_v=mul},0,T_VOID_VOID},
{"/MOD",{.t_v_v=divmod},0,T_VOID_VOID},
{"ROT",{.t_v_v=rot},0,T_VOID_VOID},
{"CREATE",{.t_v_v=doCreate},0,T_VOID_VOID},
{":",{.t_v_v=colon},0,T_VOID_VOID},
{";",{.t_v_v=semicolon},FLAG_IMMEDIATE,T_VOID_VOID},
{"R@",{.t_v_v=rget},0,T_VOID_VOID},
{"J",{.t_v_v=doJ},0,T_VOID_VOID},
{"'",{.t_v_v=tick},FLAG_IMMEDIATE,T_VOID_VOID},
{"=",{.t_v_v=_equals},0,T_VOID_VOID},
{"<",{.t_v_v=smaller},0,T_VOID_VOID},
{">",{.t_v_v=larger},0,T_VOID_VOID},
{"AND",{.t_v_v=doAnd},0,T_VOID_VOID},
{"OR",{.t_v_v=doOr},0,T_VOID_VOID},
{"?DUP",{.t_v_v=p_dup},0,T_VOID_VOID},
{"LITSTRING",{.t_v_v=litstring},0,T_VOID_VOID},
{"_xor",{.t_v_v=_xor},0,T_VOID_VOID},
{"*/",{.t_v_v=timesDivide},0,T_VOID_VOID},
{"*/MOD",{.t_v_v=timesDivideMod},0,T_VOID_VOID},
{"D=",{.t_v_v=d_equals},0,T_VOID_VOID},
{"D<",{.t_v_v=dsmaller},0,T_VOID_VOID},
{"D>",{.t_v_v=dlarger},0,T_VOID_VOID},
{"DU<",{.t_v_v=dusmaller},0,T_VOID_VOID},
{"D+",{.t_v_v=dplus},0,T_VOID_VOID},
{"D-",{.t_v_v=dminus},0,T_VOID_VOID},
{"D*",{.t_v_v=dmul},0,T_VOID_VOID},
{"D/",{.t_v_v=ddiv},0,T_VOID_VOID},
{"2SWAP",{.t_v_v=d_swap},0,T_VOID_VOID},
{"2OVER",{.t_v_v=dover},0,T_VOID_VOID},
{"2ROT",{.t_v_v=drot},0,T_VOID_VOID},

{"WORDS",{.t_v_v=_words},0,T_VOID_VOID},
{";!",{.t_v_v=bye},0,T_VOID_VOID},                  // Para que salga del programa automaticamente, y dejarle el control externo.




//************************ I/O ***************************//

{"getIN",{.t_v_v=get_entrada},0,T_VOID_VOID},
{"putOUT",{.t_v_v=put_salida},0,T_VOID_VOID},
{"getOUT",{.t_v_v=get_salida},0,T_VOID_VOID},
//{"passthroughIO",{.t_v_v=passthrough_IO},0,T_VOID_VOID},

//************************ CARACTERES ***************************//
{"cUPPER?",{.t_i_uc=c_isupper},0,T_INT_UCHAR},
{"cLOWER?",{.t_i_uc=c_islower},0,T_INT_UCHAR},
{"cALPHA?",{.t_i_uc=c_isalpha},0,T_INT_UCHAR},
{"cDIGIT?",{.t_i_uc=c_isdigit},0,T_INT_UCHAR},
{"cALNUM?",{.t_i_uc=c_isalnum},0,T_INT_UCHAR},
{"cBLANK?",{.t_i_uc=c_isblank},0,T_INT_UCHAR},
{"cPRINT?",{.t_i_uc=c_isprint},0,T_INT_UCHAR},
{"cCTRL?", {.t_i_uc=c_iscntrl},0,T_INT_UCHAR},
{"cGRAPH?",{.t_i_uc=c_isgraph},0,T_INT_UCHAR},
{"cSPACE?",{.t_i_uc=c_isspace},0,T_INT_UCHAR},
{"cPUNCT?",{.t_i_uc=c_ispunct},0,T_INT_UCHAR},
{"cXDIG?",{.t_i_uc=c_isxdigit},0,T_INT_UCHAR},
{"cTOLOWER",{.t_i_uc=c_tolower},0,T_INT_UCHAR},
{"cTOUPPER",{.t_i_uc=c_toupper},0,T_INT_UCHAR}


// Ejemplo:
// : SET_LED LED_BUILTIN OUTPUT PINMODE ;
// : LED_ON LED_BUILTIN LOW DIGITALWRITE ;
// : LED_OFF LED_BUILTIN HIGH DIGITALWRITE ;
// : TILT SET_LED LED_BUILTIN OUTPUT PINMODE 10 0 DO i . LED_BUILTIN HIGH DIGITALWRITE 500 DELAY LED_BUILTIN LOW DIGITALWRITE 500 DELAY LOOP ;

 };


int MAX_BUILTIN_ID () { return (sizeof(ListaBuiltin)/sizeof(struct t_builtin_f)); }



/* This is our initialization script containing all the _words we define in
* Forth for convenience. Focus is on simplicity, _not speed. Partly copied from
* Jonesforth (see top of file). */

const char *initScript =
    ": DECIMAL 10 BASE ! ;\n"
    ": HEX 16 BASE ! ;\n"
    ": OCTAL 8 BASE ! ;\n"
    ": 2DUP OVER OVER ;\n"
    ": 2DROP DROP DROP ;\n"
    ": NIP SWAP DROP ;\n"       // NIP ( x y -- y )
    ": 2NIP 2SWAP 2DROP ;\n"
    ": TUCK SWAP OVER ;\n"    //"tuck" ( x1 x2 -- x2 x1 x2 ) Copies top stack item below second item
    ": / /MOD NIP ;\n"
    ": MOD /MOD DROP ;\n"
    ": BL 32 ;\n"
    ": CR 10 EMIT ;\n"
    ": SPACE BL EMIT ;\n"
    ": NEGATE 0 SWAP - ;\n"
    ": DNEGATE 0. 2SWAP D- ;\n"
    ": CELLS CELL * ;\n"                    // Calcula el espacion de N celdas
    ": ALLOT HERE @ + HERE ! ;\n"           // Allocates n bytes in the dictionary.
    ": TRUE -1 ;\n"
    ": FALSE 0 ;\n"
    ": 0= 0 = ;\n"
    ": 0< 0 < ;\n"
    ": 0> 0 > ;\n"
    ": <> = 0= ;\n"
    ": <= > 0= ;\n"
    ": >= < 0= ;\n"
    ": 0<= 0 <= ;\n"
    ": 0>= 0 >= ;\n"
    ": 1+ 1 + ;\n"      //"1+" Adds one.  ( nu1 -- nu2 )
    ": 1- 1 - ;\n"      //"1-" Subtracts one ( nu1 -- nu2 )
    ": 2+ 2 + ;\n"
    ": 2- 2 - ;\n"
    ": 2/ 2 / ;\n"
    ": 2* 2 * ;\n"
    ": D2/ 2. D/ ;\n"
    ": +! DUP @ ROT + SWAP ! ;\n"
    ": [COMPILE] _word _find >CFA , ; IMMEDIATE\n"
    ": [CHAR] key ' LIT , , ; IMMEDIATE\n"
    ": RECURSE LATEST @ >CFA , ; IMMEDIATE\n"
    ": DOCOL 0 ;\n"
    ": CONSTANT CREATE DOCOL , ' LIT , , ' EXIT , ;\n"
    ": 2CONSTANT SWAP CREATE DOCOL , ' LIT , , ' LIT , , ' EXIT , ;\n"
    ": VARIABLE HERE @ CELL ALLOT CREATE DOCOL , ' LIT , , ' EXIT , ;\n"  /* Creates a named variable. name returns a-addr */
                                                                          /* TODO: Allot AFTER the code, _not before */
    ": 2VARIABLE HERE @ 2 CELLS ALLOT CREATE DOCOL , ' LIT , , ' EXIT , ;\n" /* TODO: Allot AFTER the code, _not before */
    ": IF ' 0BRANCH , HERE @ 0 , ; IMMEDIATE\n"
    ": THEN DUP HERE @ SWAP - SWAP ! ; IMMEDIATE\n"
    ": ELSE ' BRANCH , HERE @ 0 , SWAP DUP HERE @ SWAP - SWAP ! ; IMMEDIATE\n"
    ": BEGIN HERE @ ; IMMEDIATE\n"
    ": UNTIL ' 0BRANCH , HERE @ - , ; IMMEDIATE\n"
    ": AGAIN ' BRANCH , HERE @ - , ; IMMEDIATE\n"
    ": WHILE ' 0BRANCH , HERE @ 0 , ; IMMEDIATE\n"
    ": REPEAT ' BRANCH , SWAP HERE @ - , DUP HERE @ SWAP - SWAP ! ; IMMEDIATE\n"
    ": UNLESS ' 0= , [COMPILE] IF ; IMMEDIATE\n"
    ": DO HERE @ ' SWAP , ' >R , ' >R , ; IMMEDIATE\n"
    ": LOOP ' R> , ' R> , ' SWAP , ' 1+ , ' 2DUP , ' = , ' 0BRANCH , HERE @ - , ' 2DROP , ; IMMEDIATE\n"
    ": +LOOP ' R> , ' R> , ' SWAP , ' ROT , ' + , ' 2DUP , ' <= , ' 0BRANCH , HERE @ - , ' 2DROP , ; IMMEDIATE\n"
    ": I ' R@ , ; IMMEDIATE\n"
    ": SPACES DUP 0> IF 0 DO SPACE LOOP ELSE DROP THEN ;\n"
    ": ABS DUP 0< IF NEGATE THEN ;\n"
    ": DABS 2DUP 0. D< IF DNEGATE THEN ;\n"
    ": .DIGIT DUP 9 > IF 55 ELSE 48 THEN + EMIT ;\n"
    ": .SIGN DUP 0< IF 45 EMIT NEGATE THEN ;\n" /* BUG: 10000000000... will be shown wrong */
    ": .POS BASE @ /MOD ?DUP IF RECURSE THEN .DIGIT ;\n"
    ": . .SIGN DUP IF .POS ELSE .DIGIT THEN ;\n"
    ": COUNTPOS SWAP 1 + SWAP BASE @ / ?DUP IF RECURSE THEN ;\n"
    ": DIGITS DUP 0< IF 1 ELSE 0 THEN SWAP COUNTPOS ;\n"
    ": .R OVER DIGITS - SPACES . ;\n"
    ": . . SPACE ;\n"
    ": ? @ . ;\n"
    ": .S DSP@ BEGIN DUP S0@ > WHILE DUP ? CELL - REPEAT DROP ;\n"    // Muestra el stack
    ": TYPE 0 DO DUP C@ EMIT 1 + LOOP DROP ;\n"
    ": ALIGN BEGIN HERE @ CELL MOD WHILE 0 C, REPEAT ;\n"
    ": s\" ' LITSTRING , HERE @ 0 , BEGIN KEY DUP 34 <> WHILE C, REPEAT DROP DUP HERE @ SWAP - CELL - SWAP ! ALIGN ; IMMEDIATE\n"  // s" STRING " Almacena un string?
   // ": .\" [COMPILE] s\" ' TYPE , ; IMMEDIATE\n"  // ." STRING "  Almacena un string?
    ": .\" STATE @ IF [COMPILE] s\" ' TYPE , ELSE BEGIN KEY DUP 34 = IF DROP EXIT THEN EMIT AGAIN THEN ; IMMEDIATE\n"
    ": ( BEGIN KEY [CHAR] ) = UNTIL ; IMMEDIATE\n"
    ": COUNT DUP 1+ SWAP C@ ;\n"
    ": MIN 2DUP < IF DROP ELSE NIP THEN ;\n"
    ": MAX 2DUP > IF DROP ELSE NIP THEN ;\n"
    ": D0= OR 0= ;\n"
    ": DMIN 2OVER 2OVER D< IF 2DROP ELSE 2NIP THEN ;\n"
    ": DMAX 2OVER 2OVER D> IF 2DROP ELSE 2NIP THEN ;\n"

    //*******************************************************************//
    // Adicionales jombloforth                                           //
    //*******************************************************************//

    ": DEEP DSP@ S0@ - CELL / ;\n"
    ": ENDIF DUP HERE @ SWAP - SWAP ! ; IMMEDIATE \n"      // ALIAS THEN
    ": WITHIN ROT  OVER  <= IF > IF TRUE ELSE FALSE THEN ELSE 2DROP FALSE THEN ;\n" //  1 8  5 WITHIN .  5 esta entre 1 y 8excl ?
    ": FORGET _WORD _FIND DUP @ LATEST ! HERE !  ;\n"  // BORRA Tooooooodo a partir de esa palabra (no anda bien)
    ": PICK  CELLS DSP@ SWAP - @  ;\n"

    //": ?HIDDEN CELL + C@ FLAG_HIDDEN AND ;\n"


    // VECTORES //

    ": ->V0  HERE @ 2DUP SWAP 1 + CELLS ALLOT CREATE DOCOL , ' LIT , , ' EXIT , ! ;\n"  /* N ->V0 Nombre  //  Crea un vector de Nombre y N elementos vacios (1..N) en la posicion 0 esta la longitud */
    ": Vput SWAP ROT SWAP CELLS + ! ;\n"      // Nombre pos val --   Todo verificar dimension
    ": Vget  CELLS + @ ;\n"                   // Nombre pos -- val
    ": Vsize  @ ;\n"                          // Nombre -- size
                                              //  V->
                                              // ->V

    // ALIAS
     ": STO  ! ;\n"
     ": RCL  @ ;\n"

 ".\" Mini Stack Procesador (Ver 0.25 - Build 10)\"\n"
 ";! \n" // (BYE) PARA QUE SALGA DESPUES DE HACER TODO
    ;

//************* EJEMPLOS *******************************************************/
// : SUM-OF-SQUARES   ( a b -- c )   DUP *   SWAP   DUP *  +  ;                 /
// : one-to-12 ( -- ) 12 0 do i . loop ;                                        /
// : DECADE  10 0 DO  I .  LOOP ;                                              /
// : ?UMBRAL  220 > IF 1 ELSE 0 THEN ;                                          /
// : EGGSIZE
//  DUP 18 < IF  ." reject "      ELSE
//  DUP 21 < IF  ." small "       ELSE
//  DUP 24 < IF  ." medium "      ELSE
//  DUP 27 < IF  ." large "       ELSE
//  DUP 30 < IF  ." extra large " ELSE
//     ." error "
//   THEN THEN THEN THEN THEN DROP ;
/******************************************************************************/
// : abs ( n1 -- +n2 ) dup 0 < if negate endif ;
// : menor ( n1 n2 -- n ) 2dup < if drop else nip endif ;


// VARIABLE PRUEBA    /* CREA LA VARIABLE */
// 5 PRUEBA !        /* GUARDA el valor 5 en PRUEBA */
// PRUEBA @ .        /* LEE (y muestra) el contenido de PRUEBA */
//
//
// VARIABLE xxx( — ) xxx: ( — addr )   Creates a variable named xxx; the word xxx returns its address when executed.
// !( n addr — )     Stores a single-length number into the address.
// @( addr — n )   Fetches that value at addr.
// ?( addr — )   Prints the contents of the address, followed by one space.
// +!( n addr — )    Adds a single-length number to the contents of the address.

//VARIABLE HECTOR  3 CELLS ALLOT   /* CREA LA VARIABLE HECTOR ... y reserva 3 celdas mas */
// ...los vectores no andan, pq cuando se crea la variable, el puntero lo manda al principio.
//http://www.jimbrooks.org/archive/programming/forth/FIG-FORTH_internals.php
// Almacena strings...o algo asi
// : foo s" hello," s" world" ;
// foo .s
// type
// type
//
//: swap  { a b } b a ; ...parece que no esta implementado
// Tampoco decompila comando: see
//
// : 2swap ( x1 x2 x3 x4 -- x3 x4 x1 x2 ) rot >r rot r> ;  ..usa el return stack
/********************************************************************************************/





//********************* FUCIONES DE CARACTARES *******************************//

char up(char c){ return (c >= 'a' && c <= 'z') ? c - 'a' + 'A' : c; }
/* A simple strlen clone so we don't have to pull in string.h */
byte slen(const char *str) { byte ret = 0; while (*str++) ret++; return ret; }

/* The primary data input function. This is where you place the code to e.g.
* read from a serial line. */
int llkey()
{
    int receivedChar = '/n';

    if (*pMMProc->Script_pos) return *(pMMProc->Script_pos++);

//    receivedChar = _getchar();

    return receivedChar;
}


/* Anything waiting in the keyboard buffer? */
int keyWaiting(){ return pMMProc->positionInLineBuffer < pMMProc->charsInLineBuffer ? -1 : 0;}

/* Line buffered character input. We're duplicating the functionality of the
* stdio library here to make the code easier to port to other input sources */
/* Lee lineas */
int getkey() {
    int c;

    if (keyWaiting())
        return pMMProc->lineBuffer[pMMProc->positionInLineBuffer++];

    pMMProc->charsInLineBuffer = 0;
    while ( (c = llkey() ) != _EOF)
    {
        if (pMMProc->charsInLineBuffer == sizeof(pMMProc->lineBuffer)) break;
        if (c != '\r') pMMProc->lineBuffer[pMMProc->charsInLineBuffer++] = c;
        if (c == '\n') { pMMProc->lineBuffer[pMMProc->charsInLineBuffer] = 0;
                        break;
                        }
    }


    pMMProc->positionInLineBuffer = 1;

    return pMMProc->lineBuffer[0];
}


cell _pop()
{
    if (*pMMProc->sp == 1)
    {
        tell("? Stack underflow\n");
        pMMProc->errorFlag = 1;
        return 0;
    }

return pMMProc->stack[--(*pMMProc->sp)];
}

cell tos()
{
    if (*pMMProc->sp == 1)
    {
        tell("? Stack underflow\n");
        pMMProc->errorFlag = 1;
        return 0;
    }
return pMMProc->stack[(*pMMProc->sp)-1];
}

void _push(cell data)
{
    if (*pMMProc->sp >= STACK_SIZE)
    {
        tell("? Stack overflow\n");
        pMMProc->errorFlag = 1;
        return;
    }
    pMMProc->stack[(*pMMProc->sp)++] = data;
}

dcell d_pop() { cell tmp[2]; tmp[1] = _pop(); tmp[0] = _pop(); return *((dcell*)tmp); }

void d_push(dcell data) { cell tmp[2]; *((dcell*)tmp) = data; _push(tmp[0]);  _push(tmp[1]); }

/* The basic return stack operations */
/* In addition to the data stack Forth also has a second stack, the return stack; most Forth
systems store the return addresses of procedure calls there (thus its name). Programmers
can also use this stack: */


cell r_pop()
{
    if (*pMMProc->rsp == 1)
    {
        tell("? RStack underflow\n");
        pMMProc->errorFlag = 1;
        return 0;
    }
return pMMProc->rstack[--(*pMMProc->rsp)];
}

void r_push(cell data)
{
    if (*pMMProc->rsp >= RSTACK_SIZE)
    {
        tell("? RStack overflow\n");
        pMMProc->errorFlag = 1;
        return;
    }
pMMProc->rstack[(*pMMProc->rsp)++] = data;
}

/* Secure memory access */

cell readMem(cell address)
{
    if (address > _MEM_SIZE)
    {
        tell("Internal error in readMem: Invalid addres\n");
        pMMProc->errorFlag = 1;
        return 0;
    }
    //printf ("Reading en %d el valor % d\n",address,*((cell*)(memory + address)));
    return *((cell*)(pMMProc->memory + address));
}

void writeMem(cell address, cell _value)
{
    if (address > _MEM_SIZE)
    {
        tell("Internal error in writeMem: Invalid address\n");
        pMMProc->errorFlag = 1;
        return;
    }
   // printf ("Writing en %d el valor %X \n",address,_value); delay (10);
    *((cell*)(pMMProc->memory + address)) = _value;
}


/* Reading a _word into the input line buffer */
/* El primer caracter es la longitud y despues los chars ...todo eso queda en line */

byte read_word()
{
    char *line = (char*)pMMProc->memory;
    byte len = 0;
    int c;

    while ((c = getkey()) != _EOF)
    {
        if (c == ' ') continue;
        if (c == '\n') continue;
        if (c != '\\') break;

        while ((c = getkey()) != _EOF)
            if (c == '\n')
                break;

    }


    while (c != ' ' && c != '\n' && c != _EOF)
    {

        if (len >= (INPUT_LINE_SIZE - 1))
            break;
        line[++len] = c;
         c = getkey();
    }

    line[0] = len;

    return len;
}


/* Dictionary lookup */
cell _find_word(cell address, cell len)
{
    cell ret = *pMMProc->latest;
    char *_name = (char*)&pMMProc->memory[address];
    cell i;
    int found;

    for (ret = *pMMProc->latest; ret; ret = readMem(ret))
    {
        if ((pMMProc->memory[ret + CELL_SIZE] & MASK__name_length) != len) continue;
        if (pMMProc->memory[ret + CELL_SIZE] & FLAG_HIDDEN) continue;

        found = 1;
        for (i = 0; i < len; i++)
        {
            if (up(pMMProc->memory[ret + i + 1 + CELL_SIZE]) != up(_name[i]))
            {
                found = 0;
                break;
            }
        }
        if (found) break;
    }
    return ret;
}


/* Imprime todas las palabras del diccionario */
void _words()
{
    cell len=0;
    cell ret = *pMMProc->latest;
    cell i;

    for (ret = *pMMProc->latest; ret; ret = readMem(ret))
    {
        len=(pMMProc->memory[ret + CELL_SIZE] & MASK__name_length);

        if (pMMProc->memory[ret + CELL_SIZE] & FLAG_HIDDEN) continue;

        else for (i = 0; i < len; i++)
        {
         putkey ((char)pMMProc->memory[ret + i + 1 + CELL_SIZE]);
        }
        tell("\n");


    }
  //  return ret;
  return;
}

/* Basic number parsing, base <= 36 only atm */
void parseNumber(byte *_word, cell len, dcell *number, cell *_notRead, byte *isDouble)
{
    int negative = 0;
    cell i;
    char c;
    cell current;

    *number = 0;
    *isDouble = 0;

    if (len == 0)
    {
        *_notRead = 0;
        return;
    }

    if (_word[0] == '-')
    {
        negative = 1;
        len--;
        _word++;
    }
    else if (_word[0] == '+')
    {
        len--;
        _word++;
    }

    for (i = 0; i < len; i++)
    {
        c = *_word;
        _word++;
        if (c == '.') { *isDouble = 1; continue; }
        else if (c >= '0' && c <= '9') current = c - '0';
        else if (c >= 'A' && c <= 'Z') current = 10 + c - 'A';
        else if (c >= 'a' && c <= 'z') current = 10 + c - 'a';
        else break;

        if (current >= *pMMProc->base) break;

        *number = *number * *pMMProc->base + current;
    }

    *_notRead = len - i;
    if (negative) *number = (-((scell)*number));
}


/* Create a _word in the dictionary */
void create_word(const char* _name, byte len, byte flags)
{
    cell newLatest = *pMMProc->here;
    _push(*pMMProc->latest);
    comma();
    _push(len | flags);
    commaByte();
    while (len--)
    {
        _push(*_name);
        commaByte();
        _name++;
    }
    while (*pMMProc->here & (CELL_SIZE-1))
    {
        _push(0);
        commaByte();
    }
    *pMMProc->latest = newLatest;
}




//************************************************************************************************************************************//
//********************************************************** BUILD IN ****************************************************************//
//************************************************************************************************************************************//


void docol() { r_push(pMMProc->lastIp); pMMProc->next = pMMProc->commandAddress + CELL_SIZE; }
/* The first few builtins are very simple, _not need to waste vertical space here */
void doCellSize() { _push(CELL_SIZE); }
void memRead ()  { _push(readMem(_pop())); }
//void memRead ()  { _push(readMem((_pop()>>2)<<2)); }  // PARA NO LEER LA MEMORIA DESALINEADA ....ver si se puede mejorar
 void memReadByte() { _push(pMMProc->memory[_pop()]); }
void key() { _push(getkey()); }
void emit() { putkey(_pop() & 255); }       // Escribe un caracter
void drop() { _pop(); }
void doExit() { pMMProc->next = r_pop(); }
void bye() { pMMProc->exitReq = 1; }
void doLatest() { _push(LATEST_POSITION); }
void doHere()  { _push(HERE_POSITION); }
void doBase () { _push(BASE_POSITION); }
void doState() { _push(STATE_POSITION); }
void gotoInterpreter() { *pMMProc->state = 0; }
void gotoCompiler() { *pMMProc->state = 1; }
void hide() { pMMProc->memory[*pMMProc->latest + CELL_SIZE] ^= FLAG_HIDDEN; }
void rtos() { _push(r_pop()); }
void stor()  { r_push(_pop()); }
void key_p () { _push(keyWaiting()); }
void branch ()  { pMMProc->next += readMem(pMMProc->next); }
void zbranch () { pMMProc->next += _pop() ? CELL_SIZE : readMem(pMMProc->next); }
void toggleImmediate () { pMMProc->memory[*pMMProc->latest + CELL_SIZE] ^= FLAG_IMMEDIATE; }
void doFree() { _push(_MEM_SIZE - *pMMProc->here); }
void s0_r() { _push(STACK_POSITION + CELL_SIZE); }
void dsp_r() { _push(STACK_POSITION + *pMMProc->sp * CELL_SIZE); }
void _not () { _push(~_pop()); }
void dup ()  { _push(tos()); }
void memWrite () { cell address = _pop(); cell _value = _pop(); writeMem(address, _value);}
//void memWrite () { cell address =(_pop()>>2)<<2; cell _value = _pop(); writeMem(address, _value);}  // PARA NO LEER LA MEMORIA DESALINEADA ....ver si se puede mejorar

void memWriteByte () { cell address = _pop(); cell _value = _pop(); pMMProc->memory[address] = _value & 255; }
void _swap () { cell a = _pop(); cell b = _pop(); _push(a); _push(b); }
void over () { cell a = _pop(); cell b = tos(); _push(a); _push(b); }
void comma () { _push(*pMMProc->here); memWrite(); *pMMProc->here += CELL_SIZE; }
void commaByte () { _push(*pMMProc->here); memWriteByte(); *pMMProc->here += sizeof(byte);}

void _word () { byte len = read_word(); _push(1); _push(len); }

void _find () { cell len = _pop(); cell address = _pop(); cell ret = _find_word(address, len); _push(ret); }

cell getCfa(cell address)
{
    byte len = (pMMProc->memory[address + CELL_SIZE] & MASK__name_length) + 1;
    while ((len & (CELL_SIZE-1)) != 0) len++;
    return address + CELL_SIZE + len;
}

void cfa ()
{
    cell address = _pop();
    cell ret = getCfa(address);
    if (ret < pMMProc->maxBuiltinAddress)
        _push(readMem(ret));
    else
        _push(ret);
}



void number ()
{
    dcell num;
    cell _notRead;
    byte isDouble;
    cell len = _pop();
    byte* address = &pMMProc->memory[_pop()];
    parseNumber(address, len, &num, &_notRead, &isDouble);
    if (isDouble) d_push(num); else _push((cell)num);
    _push(_notRead);
}

void lit () { _push(readMem(pMMProc->next)); pMMProc->next += CELL_SIZE; }

/* Outer and inner interpreter, TODO split up */
void quit ()
{
    cell address;
    dcell number;
    cell _notRead;
    cell command;
    int i;
    byte isDouble;
    cell tmp[2];

    int immediate;

    for (pMMProc->exitReq = 0; pMMProc->exitReq == 0;)
    {
        pMMProc->lastIp = pMMProc->next = pMMProc->quit_address;
        pMMProc->errorFlag = 0;



        _word();
        _find();

        address = _pop();
        if (address)
        {


            immediate = (pMMProc->memory[address + CELL_SIZE] & FLAG_IMMEDIATE);
            pMMProc->commandAddress = getCfa(address);
            command = readMem(pMMProc->commandAddress);
            if (*pMMProc->state && !immediate)
            {
                if (command < (MAX_BUILTIN_ID()+MAX_BUILTIN_ESP()) && command != DOCOL_ID)
                    _push(command);
                else
                    _push(pMMProc->commandAddress);
                comma();
            }
            else
            { 
                while (!pMMProc->errorFlag && !pMMProc->exitReq)
                {
                    if (command == QUIT_ID) break;
                    else if (command < (MAX_BUILTIN_ID()+MAX_BUILTIN_ESP()) )  EjecutarComando(command);
                    else
                    {
                        pMMProc->lastIp = pMMProc->next;
                        pMMProc->next = command;
                    }

                    pMMProc->commandAddress = pMMProc->next;
                    command = readMem(pMMProc->commandAddress);
                    pMMProc->next += CELL_SIZE;
                }
            }
        }
        else
        {
            //printf("ParseNumber %d\n",pMMProc->memory[0]);
            parseNumber(&pMMProc->memory[1], pMMProc->memory[0], &number, &_notRead, &isDouble);
            if (_notRead)
            {
                tell("Unknown _word: ");
                for (i=0; i<pMMProc->memory[0]; i++) putkey(pMMProc->memory[i+1]);
                putkey('\n');

                *pMMProc->sp = *pMMProc->rsp = 1;

                continue;
            }
            else
            {
                if (*pMMProc->state)
                {
                    *((dcell*)tmp) = number;
                    _push(LIT_ID);
                    comma();

                    if (isDouble)
                    {
                        _push(tmp[0]);
                        comma();
                        _push(LIT_ID);
                        comma();
                        _push(tmp[1]);
                        comma();
                    }
                    else
                    {
                        _push((cell)number);
                        comma();
                    }
                }
                else
                {
                    if (isDouble) d_push(number); else _push((cell)number);
                }
            }
            
        }

        if (pMMProc->errorFlag)
            *pMMProc->sp = *pMMProc->rsp = 1;
        else if (!keyWaiting() && !(*pMMProc->Script_pos))
            // if(!pMMProc->exitReq)  
              tell(" <OK>\n");   


             
    }

//printf ("Bye...\n");

}

void plus () { scell n1 = _pop(); scell n2 = _pop(); _push(n1 + n2); }
void minus () { scell n1 = _pop(); scell n2 = _pop(); _push(n2 - n1); }
void mul ()  { scell n1 = _pop(); scell n2 = _pop(); _push(n1 * n2); }
void divmod () { scell n1 = _pop(); scell n2 = _pop(); _push(n2 % n1); _push(n2 / n1); }
void rot() { cell a = _pop(); cell b = _pop(); cell c = _pop(); _push(b); _push(a); _push(c); }
void create_word(const char* _name, byte len, byte flags);




void doCreate ()
{
    byte len;
    cell address;
    _word();
    len = _pop() & 255;
    address = _pop();
    create_word((char*)&pMMProc->memory[address], len, 0);
}

void colon ()
{
    doCreate();
    _push(DOCOL_ID);
    comma();
    hide();
    *pMMProc->state = 1;
}

void semicolon()
{
    _push(DOEXIT_ID);
    comma();
    hide();
    *pMMProc->state = 0;
}

void rget ()
{
    cell tmp = r_pop();
    r_push(tmp);
    _push(tmp);
}

void doJ ()
{
    cell tmp1 = r_pop();
    cell tmp2 = r_pop();
    cell tmp3 = r_pop();
    r_push(tmp3);
    r_push(tmp2);
    r_push(tmp1);
    _push(tmp3);
}

void tick()
{
    _word();
    _find();
    cfa();

    if (*pMMProc->state)
    {
        _push(LIT_ID);
        comma();
        comma();
    }
}

void _equals() { cell a1 = _pop(); cell a2 = _pop(); _push(a2 == a1 ? -1 : 0); }
void smaller() { scell a1 = _pop(); scell a2 = _pop(); _push(a2 < a1 ? -1 : 0); }
void larger() { scell a1 = _pop(); scell a2 = _pop(); _push(a2 > a1 ? -1 : 0); }
void doAnd () { cell a1 = _pop(); cell a2 = _pop(); _push(a2 & a1); }
void doOr () { cell a1 = _pop(); cell a2 = _pop(); _push(a2 | a1); }
void p_dup() { cell a = tos(); if (a) _push(a); }

void litstring ()
{
    cell _length = readMem(pMMProc->next);
    pMMProc->next += CELL_SIZE;
    _push(pMMProc->next);
    _push(_length);
    pMMProc->next += _length;
    while (pMMProc->next & (CELL_SIZE-1))
        pMMProc->next++;
}

void _xor () { cell a = _pop(); cell b = _pop(); _push(a ^ b); }

void timesDivide ()
{
    cell n3 = _pop();
    dcell n2 = _pop();
    dcell n1 = _pop();
    dcell r = (n1 * n2) / n3;
    _push((cell)r);
    if ((cell)r != r)
    {
        tell("Arithmetic overflow\n");
        pMMProc->errorFlag = 1;
    }
}

void timesDivideMod ()
{
    cell n3 = _pop();
    dcell n2 = _pop();
    dcell n1 = _pop();
    dcell r = (n1 * n2) / n3;
    dcell m = (n1 * n2) % n3;
    _push((cell)m);
    _push((cell)r);
    if ((cell)r != r)
    {
        tell("Arithmetic overflow\n");
        pMMProc->errorFlag = 1;
    }
}

void d_equals() { dcell a1 = d_pop(); dcell a2 = d_pop(); _push(a2 == a1 ? -1 : 0); }
void dsmaller() { dscell a1 = d_pop(); dscell a2 = d_pop(); _push(a2 < a1 ? -1 : 0); }
void dlarger() { dscell a1 = d_pop(); dscell a2 = d_pop(); _push(a2 > a1 ? -1 : 0); }
void dusmaller(){ dcell a1 = d_pop(); dcell a2 = d_pop(); _push(a2 < a1 ? -1 : 0); }
void dplus() { dscell n1 = d_pop(); dscell n2 = d_pop(); d_push(n1 + n2); }
void dminus() { dscell n1 = d_pop(); dscell n2 = d_pop(); d_push(n2 - n1); }
void dmul() { dscell n1 = d_pop(); dscell n2 = d_pop(); d_push(n1 * n2); }
void ddiv() { dscell n1 = d_pop(); dscell n2 = d_pop(); d_push(n2 / n1); }
void d_swap() { dcell a = d_pop(); dcell b = d_pop(); d_push(a); d_push(b); }
void dover() { dcell a = d_pop(); dcell b = d_pop(); d_push(b); d_push(a); d_push(b);}
void drot() { dcell a = d_pop(); dcell b = d_pop(); dcell c = d_pop(); d_push(b); d_push(a);d_push(c);}

//********************* FUCIONES DE ENTRADA/SALIDA ****************************//

void get_entrada() { cell in = _pop(); if ((in>=0)&&(in<N_ENTRADAS)) _push( pMMProc->ENTRADAS[in]);  else  tell("I/O Inexistente\n");  }
void put_salida() { cell valor = _pop(); cell in = _pop();  if ((in>=0)&&(in<N_SALIDAS)) pMMProc->SALIDAS[in]=valor; else  tell("I/O Inexistente\n"); }
void get_salida() { cell in = _pop(); if ((in>=0)&&(in<N_SALIDAS)) _push(pMMProc->SALIDAS[in]);  else  tell("I/O inexistente\n");  }



// ...para poder usarlo antes de que este definido, en Blocks
int EjecutarComando (cell command) {


        struct t_builtin_f *tbfc;
        if (command<MAX_BUILTIN_ID()) tbfc= &ListaBuiltin[command]; 
        else if (command<(MAX_BUILTIN_ID()+MAX_BUILTIN_ESP())) tbfc= &ListaBuiltinEsp[command-MAX_BUILTIN_ID()]; 
        else tell ("Error en comando...\n");

        switch(tbfc->tipo) {
                                               case T_I_CTE :

                                               _push(tbfc->f.i_cte);
                                               break;

                                               case T_VOID_VOID  :
                                               tbfc->f.t_v_v();
                                               break; /* optional */

                                               case T_INT_VOID  :
                                                _push(tbfc->f.t_i_v());
                                               break;

                                               case T_UINT_VOID  :
                                                _push(tbfc->f.t_ui_v());
                                               break;

                                               case T_LONG_VOID :
                                                _push(tbfc->f.t_l_v());
                                               break; /* optional */

                                               case T_ULONG_VOID :
                                                _push(tbfc->f.t_ul_v());
                                               break; /* optional */

                                               case T_INT_INT  :
                                                _push(tbfc->f.t_i_i(_pop()));
                                               break;

                                               case T_LONG_LONG  :
                                                _push(tbfc->f.t_l_l(_pop()));
                                               break;
                                               case T_INT_UCHAR  :
                                                _push(tbfc->f.t_i_uc(_pop()));
                                               break;

                                               case T_VOID_ULONG  :
                                               tbfc->f.t_v_ul(_pop());
                                               break;

                                               case T_VOID_UCHAR_UCHAR :
                                            {
                                               unsigned char c2=(unsigned char) _pop();
                                               unsigned char c1=(unsigned char) _pop();
                                               tbfc->f.t_v_uc_uc(c1,c2) ;

                                            }

                                               break;

                                        }


   return 0;
}



//************************************************************************************************************************************//
//******************************************************* FIN BUILD IN ***************************************************************//
//************************************************************************************************************************************//


/* Add a builtin to the dictionary */
void addBuiltin(cell code, const char* _name, const byte flags)
{
    create_word(_name, slen(_name), flags);
    _push(code);
    comma();
    _push(DOEXIT_ID);
    comma();
}

    
/* Program setup and jump to outer interpreter */
int setup_forth (tMiniProc* _pMMProc, struct t_builtin_f  *LBE, const char* initScriptSp )
{
    pMMProc=_pMMProc;  

    pMMProc->errorFlag = 0;
    pMMProc->charsInLineBuffer = 0;
    pMMProc->positionInLineBuffer = 0;
    

    int i;

    if (DCELL_SIZE != 2*CELL_SIZE)
    {

        #ifdef DEBUG
        printf ("CELL_SIZE=%d , DCELL_SIZE%d\n",CELL_SIZE,DCELL_SIZE);
        #endif

        tell ("Configuration error: DCELL_SIZE != 2*CELL_SIZE\n");

        return 1;
    }

    pMMProc->state = (cell*)&pMMProc->memory[STATE_POSITION];
    pMMProc->base = (cell*)&pMMProc->memory[BASE_POSITION];
    pMMProc->latest = (cell*)&pMMProc->memory[LATEST_POSITION];
    pMMProc->here = (cell*)&pMMProc->memory[HERE_POSITION];
    pMMProc->sp = (cell*)&pMMProc->memory[STACK_POSITION];
    pMMProc->stack = (cell*)&pMMProc->memory[STACK_POSITION + CELL_SIZE];
    pMMProc->rsp = (cell*)&pMMProc->memory[RSTACK_POSITION];
    pMMProc->rstack = (cell*)&pMMProc->memory[RSTACK_POSITION + CELL_SIZE];

    *pMMProc->sp = *pMMProc->rsp = 1;
    *pMMProc->state = 0;
    *pMMProc->base = 10;
    *pMMProc->latest = 0;
    *pMMProc->here = HERE_START;


    for (i=0;i<MAX_BUILTIN_ID();i++)
              {
              addBuiltin( i , ListaBuiltin[i]._name, ListaBuiltin[i].flags);
              if (ListaBuiltin[i].f.t_v_v==quit) { pMMProc->quit_address = getCfa(*pMMProc->latest);   }
              }

    // AGREGO LAS QUE ESTAN EN LA LISTA ESPECIFICA PARA LA IMPLEMENTACION
    for (i=0;i<MAX_BUILTIN_ESP();i++) addBuiltin( i+MAX_BUILTIN_ID() , ListaBuiltinEsp[i]._name, ListaBuiltinEsp[i].flags);


    pMMProc->maxBuiltinAddress = (*pMMProc->here) - 1;

    if (pMMProc->errorFlag) return 1;

    pMMProc->IndiceScript=0;
    pMMProc->Script_pos = (char*)initScript;
    quit();

    pMMProc->IndiceScript=0;
    pMMProc->Script_pos = (char*)initScriptSp;
    quit();
    
    return 0;
}



void quit_forth (tMiniProc* _pMMProc)
{
    pMMProc=_pMMProc;  
    
  //*** LE AGREGA UN COMANDO PARA QUE SALGA DESPUES DE CADA LLAMADA ****/
  //*** HABRIA QUE CONVERTIRLO EN EL COMPORTAMIENTO ESTANDAR...y EL BYE PARA QUE SALGA ENSERIO **//
  pMMProc->ScriptPrueba[pMMProc->IndiceScript-1]=(char)' ';
  pMMProc->ScriptPrueba[pMMProc->IndiceScript]=(char)';';
  pMMProc->ScriptPrueba[pMMProc->IndiceScript+1]=(char)'!';
 // pMMProc->ScriptPrueba[pMMProc->IndiceScript+2]=(char)' ';
  pMMProc->ScriptPrueba[pMMProc->IndiceScript+2]=(char)'\n';
                      
   pMMProc->Script_pos = (char*)pMMProc->ScriptPrueba;
   
    quit();
   
   pMMProc->IndiceScript=0;
   
}
