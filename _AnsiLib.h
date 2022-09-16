
#ifndef _ANSILIB_H_
#define _ANSILIB_H_

//#include <stdarg.h>
// Es la libreria mas dificil de evitar, porque depende mucho del proceda
typedef unsigned char *va_list;
#define va_start(list, param) (list = (((va_list)&param) + sizeof(param)))
#define va_arg(list, type)    (*(type *)((list += sizeof(type)) - sizeof(type)))
#define va_end(ap)  (void)0
//<stdarg.h>

//#include <stddef.h>
typedef unsigned int size_t;
typedef int ptrdiff_t;
//<stddef.h>



//********************* FUNCIONES xxxprtinf *******************************//

// HAY QUE DEFINIRLA AFUERA, PARA QUE ANDE m_printf
extern void _putchar(char character);


#define m_printf printf_
int printf_(const char* format, ...);
#define m_sprintf sprintf_
int sprintf_(char* buffer, const char* format, ...);
#define m_snprintf  snprintf_
int  snprintf_(char* buffer, size_t count, const char* format, ...);
#define m_vsnprintf vsnprintf_
int  vsnprintf_(char* buffer, size_t count, const char* format, va_list va);
#define m_vprintf vprintf_
int vprintf_(const char* format, va_list va);
#define m_fctprintf fctprintf
int fctprintf(void (*out)(char character, void* arg), void* arg, const char* format, ...);


//********************* FIN FUNCIONES xxxprtinf *******************************//


//********************* FUNCIONES DE CARACTARES *******************************//
int c_isupper(unsigned char c);
int c_islower(unsigned char c);
int c_isalpha(unsigned char c);
int c_isdigit(unsigned char c);
int c_isalnum(unsigned char c);
int c_isblank(unsigned char c);
int c_isprint(unsigned char c);
int c_iscntrl(unsigned char c);
int c_isgraph(unsigned char c);
int c_isspace(unsigned char c);
int c_ispunct(unsigned char c);
int c_isxdigit(unsigned char c);
int c_tolower(unsigned char c);
int c_toupper(unsigned char c);
//********************* FIN FUNCIONES DE CARACTARES *******************************//

//*********************    FUNCIONES DE STRING *******************************//
char * m_strcpy(char *str2,char *str1);
char * m_strcat(char *str1, char *str2);
int m_strcmp(char *str2,char *str1);
char * m_strncpy(char *str2,char *str1,int n);
char * m_strncat(char *str1,char *str2,int n);
int m_strncmp(char *str2,char *str1,int n);
//********************* FIN FUNCIONES DE STRING *******************************//


#endif  // ANSILIB
