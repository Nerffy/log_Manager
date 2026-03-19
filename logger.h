#ifndef LOGGER_H
#define LOGGER_H

typedef enum{
    LOG_INFO,
    LOG_ERROR,
    LOG_WARN
}Logtype;


void logMesaage(Logtype type, const char* message); 

#endif

/*
const char*message, değişmeyecek bir stringin adresi (char*) bir string pointer
Logtype type ise bir enum değeri gelecek enum a göre bir messaj basılacak log dosyasına ve bu mesaj sabit
*/