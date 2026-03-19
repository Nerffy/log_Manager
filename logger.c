#include "logger.h"
#include <time.h>
#include <stdio.h>

void logMesaage(Logtype type, const char *message)
{
    FILE *fp = fopen("system.log", "a");
    if (!fp)
    {
        return;
    }
    time_t now = time(NULL); //bu şu anki zamanı alır ama insan formatına 00:00 çevirmek lazım
    struct tm *t = localtime(&now);  //localtime ile her zaman parçalara bölünür + localtime fonk. pointer döndürür yani karşısı *t olmalıydı
    // DİKKAT time.h dosyasında zaten struct tm var ama typedefsizdir direkt burada kullandım.

    fprintf(fp,
            "[%04d-%02d-%02d %02d:%02d:%02d] %s\n", 
            t->tm_year +1900,
            t->tm_mon+1, // Ocak = 0 !!!  (0-11 arası aylar)
            t->tm_mday,
            t->tm_hour,  // t pointerının gösterdiği struct içindeki hour alanı bu şudur: (t*).tm_hour
            t->tm_min,
            t->tm_sec,  // t bir pointer *t ise structın kendisi
            message);

    fclose(fp);
}