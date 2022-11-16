#include <iostream>

class myc{
public:
private:
    myc()=default;  // yazilan default ctor artik public degil private olacak.
};
// cpp20 standartlari ile yeni bir operator daha eklendi dile. Bunun ismi "uc yollu karsilastirma
// operatoru". Artik derleyici tarafindan default edilebiliyor.

// temporary object. Ismi temp olan object demek degil!!!
// temporary object ayri bir statu.
// temporary object oyle bir nesne ki valu olarak sag taraf degeri niteliginde fakat
// kodda direkt olarak bir ismi yok. Ismı olmayan pRValue kategorisinde.

class myc1{
public:
    myc1() = default;
    myc1(int, int);
    void foo();
    void func()const;
};

int asd(){
    //
    myc1{12,24};    // PRValue Kategori, bu bir gecici nesnedir.
    myc1{12,10}.foo();  // gecici nesnelerle bu sekilde sinif fonksiyonlarina erisebilirim.

    /*
        bir gecici nesne prValue exp olduguna gore parametresi
        a) sinif turundan olan
        b) parametresi const Class& olan --> const myclass&
        c) parametresi rValue& olan fonksiyonlara arguman olarak dogrudan bir gecici nesne
        gonderebilirim.
     */
/*
 gecici nesnelerle neler yapabiliriz? dogrudan ornegin sinifin uye fonksiyonlarından birisini
 cagirabiliriz.
 */
}


void f1(myc1);
void f2(const myc1&);
void f3(myc1&&);
// FAKAT bir sol tarafi olan fonksiyon olsaydi
void f4(myc1&);

int asdf(){
    f1(myc1{}); // nden bu cagrilar gecerli? Cunku bu cagrilar Call by Value
    f2(myc1{});
    f3(myc1{});
    f4(myc1{}); //  hatali durum. Cunku lValue expression ile temp object olmaz.
}


//////////////////////////////////////////////////////////////////////////////////////////////

class Date{
public:
    Date(int day, int mon, int year);
};

void func(const Date&);

int asdg(){
    Date mydate{16,05,2022};
    func(mydate);
    // bu kod problemli bir kod. Scope leakage. Her ne kadar benim niyetim bu nesneyi
    // sadece bu fonksiyon cagrisinda kullanmak olsa da kod o anlama gelmiyor. mydate nesnesi
    // hala fonksiyon cagrisindan sonra kullanilabilir durumda. Scope leakage
    // Bizim bu kaynakla isimiz bittiginde kaynagin geri verilmesini bekliyoruz.
    // Fiilen nesneyle isim bitti ama destructor cagirilmadigi icin hala kullanimda olcak.
    // Eger bu bir RAII sinifiysa kaynagini geri verecek.
    // RAII kaynagin destructor tarafindan geri verilmesi.

    // 2. kotu etkisi yanlislikla bu ismi de kullanabilirim.

    // 3. kotu etkisi : okuyana niyeti belli etmemesi.
    // bu kotu etkiyi gidermenin yollarindan birisi suni bir blok olusturmak.

    // yani asagidaki gibi.
    {
        Date mydate{16,05,2022};
        func(mydate);
        // Asagida scope sonlanacagi icin destructor cagirilacak. Ama buna da hic gerek yok.
    }

    // madem bu nesneye sadece bu fonksiyon caigirisnda ihtiyacim var, gecici nesne cagrisi
    // yapabilirim.

    func(Date{23,05,2022}); // gecici nesnelerin en sik kullanilma bicimlerinden
    // bir tanesi de bu.

    // gecici nesnenin icinde bulundugu ifadenin yurutulmesi tamamlandiktan sonra gecici
    // nesne icin destructor caigiriliyor gereksiz yere kaynak tuketmedigi gibi ortada bir
    // isim de olmadigi icin bir scope leakage'a da ihtimal kalmamis oluyor.

}

class kdr_001{
public:
    kdr_001(){
        std::cout << "kdr cagirildi" << this << " \n";
    }
    ~kdr_001(){
        std::cout << "kdr deallocate edildi" << this << " \n";
    }

};

int fcn_001(){
    kdr_001 x;
    std::cout << "main [1]\n";
    x = kdr_001{};
    (void)getchar();    // programin beklemesi icin konuldu.
    std::cout << "main [2]\n";
    // bu fonksiyon cagirildiginda goruldu ki!!!
    // basta olusturulan x nesnesi main fonksiyonu bitene kadar deallocate edilmezken
    // sonradan temporary olarak cagirilan kisimda islemler yapildi ve hemen sonrasinda
    // deallocate edildi. Bu sayede hem memory tasarrufu, hem de scope leakage gibi
    // sorunlardan kacilmis olundu.
}

int fcn_001_a(){
    // bir referansi bir gecici nesneye baglarsak bu durumda gecici nesnenin hayati
    // referansin scope'una endeksleniyor. Buna life extension deniyor.
    std::cout << "main [1]\n";
    const kdr_001& n = kdr_001{};
    std::cout << "main [2]\n";
    (void)getchar();    // programin beklemesi icin konuldu.
}

int fcn_001_b(){
    // bir referansi bir gecici nesneye baglarsak bu durumda gecici nesnenin hayati
    // referansin scope'una endeksleniyor. Buna life extension deniyor.
    std::cout << "main [1]\n";
    {
        kdr_001 &&k = kdr_001{};    // Gecici nesne referansa bagli oldugu icin ve
                                    // scope'a da bagli oldugundan dolayi, gecici obje
                                    // cagirildiktan sonra degil, scope bittiginde
                                    // gecici nesne icin destructor cagirilacak.
        std::cout << "main [2]\n";
    }
    (void)getchar();    // programin beklemesi icin konuldu.
}

void func_001()
{
    static kdr_001 mykdr;
    // static nesneler eger cagirilmazlarsa hic olusturulmazlar.
    // cagirilmadigini da constructor'a hic girmediginden anlayabiliriz.
    // func fonksiyonu 150 kere cagirilsa bile nesne static oldugundan dolayi
    // yalnizca 1 kez constructor'i ve yalnizca  bir kez destructor'i cagirilacak.
}




//////////////////////////////////////////////////////////////////////////////////////////////

class kdr_002{
public:
    kdr_002(){
        std::cout << "kdr_002 default ctor\n";
    }

    ~kdr_002(){
        std::cout << "kdr_002 destructor\n";
    }

    //kdr_002(const kdr_002&){
   //     std::cout << "kdr_002 default copy ctor\n";
    //}
};

void foo_002(kdr_002 x){

}

void func_002_a()
{
    kdr_002 y;          // burada default ctor cagirilirken
    foo_002(y);      // burada copy ctor cagirilir.
}

void func_002_b()
{
    foo_002(kdr_002{}); // burada gecici nesne foo fonksiyonuna gonderilmistir.
    // bu calistirildiginda copy ctor cagirilmaz, default ctor ve destructor cagirilir.
    // beklenenin disinda bir davranis sergilenir burada.
    // Bu konu "copy elision" ile ilgili. ya da copy elimination
    // birde "mandotory copy elision" var. C++17 ile dile eklendi.
    // bu fonksiyon mandotory'dir cunku
}

/*
 * oyle durumlar varki derleyici koda bakarak bir kopyalamayı devre dışı bırakıyor
 * derleyici gereksiz kopyalama isleminden kacinmak icin bir optimizasyon islemi
 * yapıyor. Bu kurallar 17 ile degistirildi. Copy elision yani, kopyalamanın
 * devre dışı bırakılmasıdır.
 */

/*
 * copy elision olan 3 yer vardır. Bir tanesi bir sınıf nesnesini bir geçici nesne
 * ile hayata geçirmek, bir prValue ile hayata geçirmek. Burada bir nesne oluşturup
 * onu kopyalamak yerine sadece ve sadece bir kere nesne oluşturulur.
 */

int copy_ellison_ex_002(){
    kdr_002 x = kdr_002{};
    // burada yine copy ctor cagirilmaz. Constructor ve destructor cagirilir.

    kdr_002 y = kdr_002{ kdr_002{ kdr_002{ } } };   // burada da yalnizca 1 kez copy ctor
    // ve bir kez destructor cagirilir.
}

kdr_002 ex_func_b()
{
    return kdr_002{};
}

int ex_func_a(){
    // buraya return value optimization deniyor. RVO
    //  bir fonksiyon bir sag taraf degerini nesne dondururse ve bu nesneyle baska bir
    // nesneyi hayata getirirseniz derleyicinin burada yaptigi optimizasyona RVO denir.
    // Debug mode'da da olsa, Release mode'da da olsa burada copy ctor cagirilmaz.
    kdr_002 x = ex_func_b();
}

//////////////////////////////////////////////////////////////////////////////////////////////

kdr_002 ex_func_003(){
    kdr_002 x;
    //code here
    return x;
}

int ex_func_003_a(){
    kdr_002 x = ex_func_003();
    // burada yapilan optimizasyona Named Returned Value Optimization
    //NRVO
    // Yine copy ctor cagirilmaz. Yalnizca ctor ve destructor
    // AMA
    // release mode'dan debug mode'a alirsam derleyicimi bu sefer copy ctor
    // cagirilir.
}

// Mandotorion copy elision'in normal copy elision'dan farki debug mode'da dahi
// ayni davranisi sergilemesi yani default ctor cagirmamasi. Eger Mandotori olan bir
// elision'da default copy ctor silinirse error vermez ama copy elision'da verecektir.
// Yani NRVO'da default ctor delete ise hata verecektir.

// Mandotori olan prValue ile bir nesneyi hayata geçirmek
// ama mandatori olmayan NRVO

// C++11 ve c++17 arasinda Myclass{} bir nesne olarak tanimlanmaktaydi.
// Ama C++17 sonrasinda bunu bir nesne olarak tanimamakta. Onun bir nesne haline
// gelmesi icin bir surec gerekiyor. Bu standarta Temporary materialization denir.
// bir prvalue expression olan ifade karsiligi fiilen bir nesnenin olusturulmasi
// demek. belli yerlerde temporary materialization olmak zorunda.

//////////////////////////////////////////////////////////////////////////////////////////////
// prValue expression'lar bir nesne sayilmadigi icin aslinda bir kopyalama da mevcut degil.
// prValue expression karsiliginda dogrudan bir nesne olusturulmuyor. prValue expression
// bir nesneyi init etmek icin kullanilan bir ifade. Boyle bir ifadeyle bir nesneyi hayata
// getirebiliriz bu durumda ortada fiilen oluşmuş bir nesne olmadığıiçin bir kopyalama
// da söz konusu değil. Bu durumda copy elision'da yok cunku ortada bir kopyalama da yok.
// Ne zaman bir temporary materialization olusuyor??
// Eger prValue'yu  yani ornegin Myclass{}; ifadesini bir referansa bind edersek derleyicinin
// bunun icin bir nesne olusturmak zorunda.

kdr_002 foo(){
    kdr_002 m;
    return m;
}

int main_001(){
    kdr_002 &&x = foo();
}

int main_002(){
    kdr_002 x = foo();
}

/*
 * paramatresi bir sinif turunden olan fonksiyona bir prValue expression ile cagri
 * yaparsaniz bir kopyalama soz konusu olmaz ve bu bir optimizasyon degildir ve bu durumda
 * copy constructor delete edilmis olsa bile gecerlidir.
 *
 * Diyelimki copy ctor icinde bir side effect olusturdunuz, diyelim copy ctor gitti bir
 * sayacı arttırdı ya da diyelim gitti bir dosyaya bir yazi yazdi bir loglama yapti.
 * Siz o yan etkinin gerceklesecegine guvenerek o kodu yazmissaniz o kod dogru degil
 * Cunku copy ctor cagirilmasini tahmin ettiginiz yerlerde eger bu mandatory copy ellision
 * soz konusu ise cagirilacak bir copy ctor olmadigi icin o yan etki de gerceklesmeyecek.
 * AMA son tekrarımız olsun. Return Value Optimization, Mandotory ama NRVO mandatory değil.
 * Yani NRVO olmasi icin bir kere sinifin cagirilabilir bir copy ctor'unun bulunmasi gerekiyor.
 *
*/
//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////
//MULAKAT SORUSU//
//////////////////

myc1 foox(){
    myc1 x;
    // code here
    return x;
}

int foox_f() {
    myc1 ma = foox();
    // en iyi ihtimalle NRVO olacak yani ne copy ctor ne move ctor cagirilacak.
    // sadece ve sadece default ctor cagirilacak ama bu mecburi degil. Ve aradaki
    // kodlarin ne olduguna bagli olarak derleyici bu optimizasyonu yapabilir ya da
    // yapamayabilir. Bu detaylar ileri C++ kursunda anlatiliyor.
    // 3 ihtimal var
    // 1 sadece def ctor'un cagirilmasi
    // 2 move ctor varsa move ctor'un cagirilmasi, move ctor delete edilmisse syntax hatasi olacak
    // 3 move ctor yoksa copy ctor'un cagirilmasi
}

//////////////////
//MULAKAT SORUSU//
//////////////////

//////////////////////////////////////////////////////////////////////////////////////////////

class kdr_003{
public:
    kdr_003() = default;
};

int f_kdr_003(){
    kdr_003 m;
    m = 10;

}

class kdr_004{
public:
    kdr_004() {
        std::cout << "default ctor cagirildi\n";
    }
    kdr_004(int x){
        std::cout << "int parametreli ctor cagirildi"<< x << "this: "<< this << "\n";
    }
    kdr_004& operator=(const kdr_004& r){
        // Bu bir copy assingment'tir. Gelen deger prValue olmasina ragmen
        // const class& prValue ile islem yapabilir eger rValue ifadesi yoksa. AMA
        // move assignment konursa!!! (ASAGIDA KOYUYORUM) bunun yerine move assingment
        // cagirilacaktir.
        std::cout << "kdr_004::operator=() &r =" << &r << "\n";
    }

    kdr_004& operator=(kdr_004&& r){
        std::cout << "move assignment " << &r << "\n";
    }

    ~kdr_004() {
        std::cout << "destructor cagirildi\n";
    }
};

int f_kdr_004(){
    // CONVERSION CONSTRUCTOR : donusturen kurucu islev. Special member function degil!!!


    kdr_004 m;
    m = 10; // su an bir syntax hatasi yok!!!Nasil oldu da sinifa 10 degeri atandi???
    // derleyici bu ifadeyi gordugunda bu atama normal degil deyip suna bakacak. Acaba
    // int turunden bir ifadeyi kdr_004 turune donusturebilecek bir fonksiyon var mi?
    // sinifin taniminda int parametreli boyle bir ctor'un oldugunu gordugunda derleyici
    // soyle bir kod uretecek.

      /*
        derleyici durumdan vazife cikararak!!!
        m = kdr_004{10};   // derleyici boyle bir kod uretecek!!!
     */

      /*
         Yani isi ozetleyecek olursak, m = 10 atamasinin yapilabilmesi icin derleyici
         sinifin int parametreli constructor'ina bir cagri yapti, boylece bir gecici
         nesne olusturdu bir prValue expression olusturdu ve olusturdugu gecici
         nesneyi de aslinda sinifin atama operator fonksiyonuna arguman olarak gonderdi.
         Gecici nesnelerin hayati onlarin bulundugu ifadenin yurutulmesinden sonra
         biter. Ve geçici nesnenin gerçekten destructorunun cagirildigini goruyoruz.
       */
}

/*
 sinifin tek parametreli constructori aynı zamanda bir tur donusumu icin de kullanilabilir.
 derleyici tek parametreli ctor parametresi turunden bir ifadenin bir sinif turune
 donusturulmesi soz konusu olan durumlarda( ayni tur sinif) bu ctor'a cagri yaparak
 bir prValue expression'i olan sinif nesnesi olusturuyor.
 */

// Onceki ornekte m = 10 ile bir int deger gondermistik. Eger 10 yerine double ifade olarak
// 1.5 gonderseydik ayni durumda kod calisir miydi?

// eger bir conversion normal olarak yok ise yani ortada conversion soz konusu degilse
// fakat bizim yazdigimiz bir fonksiyonun kullanilmasiyla bu donusum yapilabiliyorsa
// boyle donusumlere user-defined conversion deniyor.

// eger bir donusum ortulu olarak şunlardan biriyse derleyici bu donusumu yapmak zorunda!!!
// a) once standart conversion fakat bundan sonra user defined conversionla donusum gercek-
// lestirilebiliyorsa derleyici bunu ortulu olarak yapmak zorunda. Ya da tam tersi
// b) Once user defined conv ardindan standart conversion ile bu donusumu yapabiliyorsa
// derleyici bu donusumu yapmak zorunda.
// bir user defined conversion'i bir user defined conversion'la tamamliycaksa yani donusumun
// ortulu olarak yapilabilmesi icin iki tane arka arkaya user defined conversion kullaniliyorsa
// derleyici bu donusumu otomatik olarak yapmaz.

// double turunden int turune yapilan donusum standard conversion'dır.
// Int'ten de kdr_004'e yapilan donusum user-defined conversion olduguna gore derleyici
// bu donusumu yapmak zorunda.
// YANI
/*
  kdr_004 x;
  x = 1.5;
  // yaptigimiz anda derleyici once double'i inte donusturdu, sonrasinda class'imiza YANI

  kdr_004{(int)1.5}; // Derleyici otomatik olarak bunu yapar.
 */

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}































