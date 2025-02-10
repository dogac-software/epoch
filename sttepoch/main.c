#include <stdio.h>
#include <time.h>

// satýþ süresi takibi.

// Tarih ve saat bilgisini tutan yapý
struct TarihZaman {
    int yil;
    int ay;
    int gun;
    int saat;
    int dakika;
    int saniye;
};

// Tarih ve saat bilgisini epoch zamanýna çeviren birleþtirme
union EpochZaman {
    struct TarihZaman tarihZaman;
    time_t epoch;
};

// Tarih ve saat bilgisini epoch zamanýna dönüþtüren fonksiyon
time_t cevirEpoch(struct TarihZaman tz) {
    struct tm t = {0};
    t.tm_year = tz.yil - 1900;
    t.tm_mon = tz.ay - 1;
    t.tm_mday = tz.gun;
    t.tm_hour = tz.saat;
    t.tm_min = tz.dakika;
    t.tm_sec = tz.saniye;
    t.tm_isdst = -1; // Gün ýþýðýndan yararlanma hesaplamasýný otomatik yap
    return mktime(&t);
}

int main() {
    struct TarihZaman tz1, tz2;
    union EpochZaman ez1, ez2;

    // Kullanýcýdan ilk tarih ve saat bilgisini alýn
    printf("simdiki tarih ve saati girin (YIL(YYYY) AY(AA) GUN(GG) SAAT(SS) DAKIKA(DD) SANIYE(Ss): ");
    scanf("%d %d %d %d %d %d", &tz1.yil, &tz1.ay, &tz1.gun, &tz1.saat, &tz1.dakika, &tz1.saniye);

    // Kullanýcýdan ikinci tarih ve saat bilgisini alýn
    printf("STT(son tuketim tarihi ) tarih ve saatini girin (YIL(YYYY) AY(AA) GUN(GG) SAAT(SS) DAKIKA(DD) SANIYE(Ss): ");
    scanf("%d %d %d %d %d %d", &tz2.yil, &tz2.ay, &tz2.gun, &tz2.saat, &tz2.dakika, &tz2.saniye);

    ez1.tarihZaman = tz1;
    ez2.tarihZaman = tz2;

    ez1.epoch = cevirEpoch(ez1.tarihZaman);
    ez2.epoch = cevirEpoch(ez2.tarihZaman);

    // Epoch zaman farkýný hesaplayýn
    time_t fark = difftime(ez2.epoch, ez1.epoch);

    int yillar, aylar, gunler, saatler, dakikalar, saniyeler;

    saniyeler = fark % 60;
    dakikalar = (fark / 60) % 60;
    saatler = (fark / 3600) % 24;
    gunler = (fark / 86400) % 30; 
    aylar = (fark / 2592000) % 12; 
    yillar = fark / 31104000; 

    printf("Epoch zaman farki: %ld saniye\n", fark);
    printf("urunun kullanabilirlilik suresi: yil = %d, ay = %d, gun = %d, saat = %d, dakika = %d, saniye = %d\n", 
            yillar, aylar, gunler, saatler, dakikalar, saniyeler);
            
         if(fark <= 0){
         	printf("urunun son tuketim tarihi sona erdi, urunu satisten kaldir.");
		  } else if(fark<864000){
            	printf("urunun son tuketim tarihi yaklasti,satisini hizlandirmek icin kasa onune al.");
			}
    return 0;
}

