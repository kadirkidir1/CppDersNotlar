#include <iostream>
// override ne demek!!!
// modern c++ ile dile eklendi.
// belirli bir baglamda ozel islevini yapiyor ama diger yerlerde normal bir id gibi kullanilabiliyor.
#include <string>
#include <random>

#include "Car.h"

void f_0()
{
    int k = 32;
    void* l = &k;

    std::cout << *static_cast<int*>(l) << std::endl;

    std::string hl = "kadirkidir";
    l = &hl;
    std::cout << *static_cast<std::string*>(l) << std::endl;
    // burada bir void pointer orneginin kullanimi gosterilmistir.
}

// override anahtar sozcugu sunu anlatiyor aslinda. bu fonksiyon taban siniftaki bir fonksiyonun override'i. Ve derleyiciye
// bir kontrol yukumlulugu veriyor. Eger override anahtar sozcugunu yazarak override etmisseniz derleyici taban sinifta boyle bir
// sanal fonksiyonun varligini sorgulamak kontrol etmek zorunda.

class Base {
public:
    void func(int);
};

class Der : public Base{
public:
   // void func(int)override; //bu kullanimda derleyici hemen syntax htasi verecektir cunku override oldugundan base
   // sinifa gidip arama yapiyor ama bulamiyor.
   // cunku yukaridaki sinifta virtual anahtar sozcugu kullanilmamis.
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Base1 {
public:
    virtual void func(unsigned int);
};

class Der1 : public Base1{
public:
    //  void func(int)override; bu kullanimda derleyici hemen syntax htasi verecektir cunku override oldugundan base
    // sinifa gidip arama yapiyor AMA imzalar farkli. Bakilirsa yukaridaki fonksiyon  unsigned int parametreli ve
    // bu sekilde override edebilmesinin imkani yok!!!
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Ne demek statik tur dinamik tur?
// statik tur derleyicinin bakis acisiyla derleyicinin koda bakarak anladigi tur. Ve belirli kontroller statik ture
// gore yapiliyor.

class car3{
public:
    virtual void start(){
        std::cout << " car3 start cagirildi \n";
    }
    virtual void run(){
        std::cout << " car3 run cagirildi \n";
    }
    virtual void stop(){
        std::cout << " car3 stop cagirildi \n";
    }
};

class Bmw2 : public car3{
public:
    void start(){
        std::cout << " bmw2 start cagirildi \n";
    }
    void run(){
        std::cout << " bmw2 run cagirildi \n";
    }
    void stop(){
        std::cout << " bmw2 stop cagirildi \n";
    }
};

class Fiat2 : public car3{
public:
    void start(){
        std::cout << " fiat2 start cagirildi \n";
    }
    void run(){
        std::cout << " fiat2 run cagirildi \n";
    }
    void stop(){
        std::cout << " fiat2 stop cagirildi \n";
    }
};

class Volvo2 : public car3{
public:
    void open_sunroof(){

    }
    void start(){
        std::cout << " volvo2 start cagirildi \n";
    }
    void run(){
        std::cout << " volvo2 run cagirildi \n";
    }
    void stop(){
        std::cout << " volvo2 stop cagirildi \n";
    }
};

class VolvoS60 : public Volvo2{
public:
    void start(){
        std::cout << " volvoS60 start cagirildi \n";
    }
    void run(){
        std::cout << " volvoS60 run cagirildi \n";
    }
    void stop(){
        std::cout << " volvoS60 stop cagirildi \n";
    }
};

class Toyota2 : public car3{
public:
    void start(){
        std::cout << " Toyota2 start cagirildi \n";
    }
    void run(){
        std::cout << " Toyota2 run cagirildi \n";
    }
    void stop(){
        std::cout << " Toyota2 stop cagirildi \n";
    }
};

class Dacia2 : public car3{
public:
    void start(){
        std::cout << " Dacia1 start cagirildi \n";
    }
    void run(){
        std::cout << " Dacia1 run cagirildi \n";
    }
    void stop(){
        std::cout << " Dacia1 stop cagirildi \n";
    }
};

void car3_game(car3& cr){
    cr.start();
    cr.run();
    cr.stop();
}

car3* create_random_car2()
{
    static std::mt19937 eng{std::random_device{}()};
    static std::uniform_int_distribution dist{1,6};

    switch (dist(eng)){
        case 1: std::cout << " BMW olusturuldu\n"; return new Bmw2;
        case 2: std::cout << " Fiat olusturuldu\n"; return new Fiat2;
        case 3: std::cout << " Volvo olusturuldu\n"; return new Volvo2;
        case 4: std::cout << " Toyota olusturuldu\n"; return new Toyota2;
        case 5: std::cout << " Dacia olusturuldu\n"; return new Dacia2;
        case 6: std::cout << " VolvoS60 olusturuldu\n"; return new VolvoS60;
    }
}

// Dinamik turden bahsedebilmemiz icin polimorfik bir sinif olmasi gerekiyor. Eger bir sinif polimorfik degilse
// dinamik tur kavramindan bahsetmek mumkun degil.
void f_1(){
    for(;;){
        auto p = create_random_car2();
        car3_game(*p);
        (void)getchar();
    }
}

// MULAKAT'larda sorulan cok temel, klasik sorular var. Ogrenci tur dinamik tur kavramini ve statik tur kavramini anla-
// mis mi? Virtual dismatch mekanizmasini tam olarak anlamis mi?

// RTTI : Run time type information. Calisma zamaninda tur belirlenmesi.
// En onemli alt basliklardan bir tanesi RTTI olacak.


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// void f_gokalp() {
//     void *p;
//     int j;
//     char z;
//     char z1;

//     printf("deger gir : ");
//     scanf("%d", &j);
//     p = (int *) j;
//     printf("%d\n", j);

//     printf("Char gir : ");
//     scanf_s(" %c", &z);

//     p = (char *) z;
//     printf("%c", p);
// }
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class base2{
private:
    virtual void vfunc();
};

class Der2 : public base2{
public:
    void vfunc()override;   // Cok cok sik kullanilan bir arac.
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class base3{
public:
    virtual void vfunc();
};

class Der3 : public base3{
private:
    void vfunc()override;   // Cok cok sik kullanilan bir arac.
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class base4{
public:
    virtual void vfunc()
    {
        std::cout << "base4::vfunc \n";
    }
};

class Der4 : public base4{
private:
    void vfunc()override   // Cok cok sik kullanilan bir arac.
    {
        std::cout << "der4::vfunc \n";
    }
};

void g(base4 &base4ref)
{
    base4ref.vfunc();
}

void f_2(){
    Der4 myder;
    g(myder);   // ilgili class base olmasina ragmen virtual dismatch mekanizmasi devreye girer ve yazilacak
    // olan deger derr4 sinifinin yazisi olur.
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class base5{
public:
    virtual void vfunc(int x = 10)
    {
        std::cout << "base5::vfunc \n";
    }
};

class Der5 : public base5{
private:
    void vfunc(int x = 77)override   // goruldugu uzere varsayilan arguman yukarida 10 iken burada 77 girilmis ve
    // degistirilmis. Tavsiye edilmeyen bir yontem.
    // Varsayilan arguman tamamen compile time ile alakali bir durum runtime ile bir alakasi yok!
    //
    {
        std::cout << "der5::vfunc "<< x << " \n";
    }
};

void g1(base5 &base5ref)
{
    base5ref.vfunc();
}

void f_3(){
    Der5 myder;
    g1(myder);   // ilgili class base olmasina ragmen virtual dismatch mekanizmasi devreye girer ve yazilacak
    // olan deger der5 sinifinin yazisi olur.
    // ilgili kisim calistirildiginda gorulur ki, varsayilan arguman compile time'da alindigi icin ve polimorfik virtual
    // secim runtime'da yapildigi icin bu fonksiyon calistiginde gorulur ki der'in outputu verilir ama x degeri olarak
    // der'in degeri degil, base2in degeri girilir. Cunku g1 fonksiyonunda baz alinan class base class'tir.
    // myder.vfunc() calistirilsaydi x 10 degil 77 olurdu.
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Sanal olmayan bir fonksiyon, sanal bir fonksiyonu cagirabilir. genel olarak uretimde virtual function'lar private
// bolume alinip public bolumdeki fonksiyon vasitasiyla cagirilir.
class base6{
public:
    void foo(){
        vfunc();
    }

private:
    virtual void vfunc(){
        std::cout << " base vfunc olusturuldu\n";

    }
};

class Der6 : public base6{
public:
    void vfunc()override
    {
        std::cout << " Der vfunc olusturuldu\n";
    }
};

void f_4(){
    Der6 myder;
    myder.foo();
}
// bu ornek en cok kullanilan orneklerden bir tanesi.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class base7{
public:
base7()
{
    vfunc();
}
private:
    virtual void vfunc(){
        std::cout << " base vfunc olusturuldu\n";

    }
};

class Der7 : public base7{
public:
    void vfunc()override
    {
        std::cout << " Der vfunc olusturuldu\n";
    }
};

void f_5(){
    Der7 myder;
}
// taban sinifin constructor'i icinde bir sanal fonksiyona cagri yapildiginde virtual dismatch mekanizmasi devreye
// girmez. Bu dilin kurali. Neden dilin kurali? Cunku bu noktada turemis sinif nesnesi hayata gelmiyor ki...

// Peki bir diger soru. Constructor degil destructor cagirildigi zaman vfunc() cagirilirsa virtual dismatch mekanizmasi
// devreye girer mi? Cevap, yine girmez. Girseydi yine felaket olurdu. Cunku base'in destructor'i der'in destructor'indan
// sonra cagiriliyor. Der kullandigi kaynaklari geri vermistir. Sanallik mekanizmasi devreye girmezdi. Syntax error de
// vermezdi.
// Virtual dismatch mekanizmasi ne zaman devreye girmez
//  1 cagri base nesnesiyle yapilmissa,
//      base_object.vfunc(); // dogrudan cagri nesne yoluyla yapilmissa yani pointer ya da ref mekanizmasi kullanilmamissa
//      burada sanallik mekanizmasi devreye girmez.
//  2   Cagriyi taban sinifin ismini niteleyerek yaparsam virtual dismatch mekanizmasi devreye girmeyecek
//      Base::vfunc seklinde base sinifta tanimlama yapmamak gerekiyor.
//      Sanal fonksiyon cagrisi taban sinif ismi ile nitelenerek yapilmis ise
//  3   Taban sinif constructor'i icerisinde yapilan sanal fonksiyon cagrilari.
//  4   Taban sinif destructor'i icerisinde yapilan sanal fonksiyon cagrilari.

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class base8{
public:
    void foo()  // bu fonksiyon ile
    {
        vfunc();
    }

    void foo_copy(base8 *ptr)
    {
        this->vfunc();   // yukaridaki fonksiyon ile asagidaki fonksiyon arasinda esasinda herhangi bir fark yoktur.
                        // parantez icerisi bos kalsa da aslinda bunu soylemektedir ve bu yuzden sanallik mekanizmasi
                        // calisabiliyor.
    }
private:
    virtual void vfunc(){
        std::cout << " base vfunc olusturuldu\n";

    }
};

class Der8 : public base8{
public:
    void vfunc()override
    {
        std::cout << " Der vfunc olusturuldu\n";
    }
};

void f_6(){
    Der8 myder;
    base8 mybase;
    myder.foo();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class base9 {
public:
    void f1();
    void f2();
    void f3();  // sinifin uye nesnelerinin sinifla hicbir ilgisi yok. Sizeof'u herhangi bir sekilde arttirmazlar.
    virtual void f4() {}    // sizeof degeri artti Sanal fonksiyon ekleyince!!!
    virtual void f5() {}    // ikinci bir sanal fonksiyon ekledim ama 2. fonksiyon sizeof'u arttirmadi.

    // Sinifa bir tane sanal fonksiyon ekledigimde o sinif artik polimorfik bir sinif oluyor. Ve polimorfik bir class'tan
    // kalitim yoluyla elde ettigimiz tum class'lar da polimorfik.
    // Derleyici, polimorfik her sinifin icerisine bir tane pointer gomuyor. Bu pointer'a sanal fonkiyon tablo
    // gostericisi deniyor vPointer daha populer bir kullanim.

private:
    int x,y;
};

// Virtual function table for class Toyota - Her adres satirinda bu fonksiyonun override'larinin adresi var!!!
/*
 0

 1  &Toyota::Start

 2  &Toyota::run

 3  &Toyota::stop

 ----------------------------------------------

 // Virtual function table for class Dacia - Her adres satirinda bu fonksiyonun override'larinin adresi var!!!

 0

 1  &Dacia::Start

 2  &Dacia::run

 3  &Dacia::stop

    Fark edilirse ayni override'larin index'leri de ayni!!!

 ----------------------------------------------

    Car *carptr;
    carptr->run();  // run bir virtual fonksiyon ise derleyici soyle davraniyor.
    // carptr'nin icerisinde bir vPointer oldugunu biliyor. Hangi fonksiyon cagirildiysa da gidip o indeksin
    // function pointer'ina isaret ediyor yani!!!

    carptr->vptr[1] --> Bu bir function pointer'dir.
    carptr->vptr[1]();  // islemini gerceklestiriyor. Bu sekilde virtual dismatch mekanizmasini calistiriyor.

 */

/*
     * Polimorfizm islem maliyetleri
     * 1) her polimorfik nesne icin vptr'nin init edilmesi
     * 2) her virtual function cagrisi icin  2 X derefencing (derleyici bir optimizasyon yapmiyorsa)
     * 3) Runtime'in basinda biz gormesek de Heap'de table'lar olusturuluyor. Her polimorfik sinif icin
     *    sanal fonksiyon tablosu veri yapisi olusturuluyor.
     * 4) Her polimorfik nesne icin bir pointer! Bu da bellek maliyeti demek.
     * 5) her polimorfik sinif icin ise bir tablo! Bu da bellek maliyeti demek!
 */

// concrete sinif olmasi icin yani sinifin tanimlanamabilmesi icin taban sinifin tum pure virtual fonksiyonlari
// tanimlaniyor olmali.

class deneme1{
public:
    virtual void a1() = 0;
    virtual void a2() = 0;
    virtual void a3() = 0;
};

class deneme2{
public:
    virtual void a1() = 0;
    virtual void a2(){}
    virtual void a3(){}
};

class deneme3 : public deneme2{
public:
    void a1(){}
    void a2(){}
    void a3(){}
};

void f_deneme1(){
    // denem
    //deneme1 x; // yorum kaldirilirsa hata gorulur. Cunku bu bir abstract class'tir. Icerisinde pure virtual
    // function barindirir

    // deneme2 x; // yorum kaldirilirsa hata gorulur. Hatanin sebebi, bir tane pure virtual olmasi yeterlidir
    // abstract olabilmesi icin.

    deneme3 x;  // turemis class'ta pure virtual function icerisi dolduruldugu icin hata ortadan kalkmistir.
}

void car_game(car4* p)
{
    p->start();
    p->run();
    p->stop();
}

void f_7(){
    while(1)
    {
        car4* p = create_random_car3();
        car_game(p);

    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Constructor virtual olabilir mi?
// C++ dilinde constructor fonksiyonlar sanal fonksiyon olamaz. Dlin kurallari bunu engelliyor.
// Clone idiomu: bir pointerla taban sinifin sanal fonksiyonuna cagri yaptigimda virtusal dismatvh mekanizmasi devreye
// giriyor. O zaman ilgili sinifin bir baska virtual fonksiyonu olsa ve ismi clone olsa, bu noktada clone fonksiyonun
// overrride'i cagirilacak. Yani audi referans etmissem audi cagirilacak. mercedes ise mercedes cagirilmis olacak.
// Ve bu cagirilan override'lar kendi turunden nesne olustursalar. yani mercedes'in klonu mercedes'in turunden bir
// dinamik nesne olustursa! Bunu yapmanin yolu ilgili fonksiyon icerisinde bir clone fonksiyonu yazip return degeri
// olarak T* almak.

void car_game2(car4* p){
    car4* car4ptr = p->clone();  //
    car4ptr->start();
    p->start();
    p->run();
    p->stop();
}

void f_8(){
    while(1)
    {
        car4* p = create_random_car3();
        car_game(p);
        (void)getchar();
    }
}

// Toplarsak C++ dilinde virtual constructor yok ama virtual constructor idiom ya da clone idiom diye bilinen
// idiomatik bir yapi var.

// destructor virtual olabilir mi? Olmak zorunda Cogu zaman!
// Dinamik omurlu butun nesneleri delete etmeliyiz bu sebeple destructor'larini cagirmis oluyoruz.
// New ile allocate edilen bellek alani da geri verilmis olur!!

/////////////////////////////////////////////////////////////////////////////
class bs{
public:
    bs()
    {
        std::cout << "bs constructor \n";
    }
    ~bs()
    {
        std::cout << "bs destructor \n";
    }
    virtual void vfnc()
    {
        std::cout << "bsvfnc\n";
    }

};

class Dr : public bs{
public:
    Dr()
    {
        std::cout << "Dr constructor \n";
    }
    ~Dr()
    {
        std::cout << "dr destructor \n";
    }
    virtual void vfnc()override
    {
        std::cout << "Drvfnc\n";
    }
};

void f_9()
{
    bs* ptr = new Dr;
    ptr->vfnc();

    delete ptr; // Undefined behaviour.
    // eger taban sinifin destroctoru birazdan gorecegimiz sekilde virtual degilse, virtual destructor
    //  degilse bir taban sinif pointeriyla bir turesmi sinif nesnesini delete ettiginizde tanimsiz davranis
    // olusuyor. ama runtime'a bakarsaniz en azindan sunu golemleyebilrsiniz. burada vagirilacak destructor
    // turemis sinifin destructori degil taban sinifin destructor'i.

    // taban snifin destructoru polimorfik siniflarda virtual olmali. eger taban sinifin destructorunda
    // virtual anahtar sozcugunu kullanirsaniz bu sekilde  yazilmis destructor'a virtual destructor deniyor.
}

// f_9 fonksiyonunda bir UB soz konusu. Bunun nedeni ise ptr'nin delete edilmesi. Bunun onune gecmek icin asagidaki
// gibi base class'in destructor'i protected sinifa almaliyiz.

/////////////////////////////////////////////////////////////////////////////

class bs1{
public:
    virtual void vfnc()
    {
        std::cout << "bsvfnc\n";
    }
protected:

    ~bs1()
    {
        std::cout << "bs destructor \n";
    }

};

class Dr1 : public bs1{
public:
    ~Dr1()
    {
        std::cout << "dr destructor \n";
    }
    virtual void vfnc()override
    {
        std::cout << "Drvfnc\n";
    }
};

void f_10()
{
    bs1* ptr = new Dr1;
    ptr->vfnc();

    // delete ptr; // Yorum kaldirilirsa gorulecektir ki bir sikinti mevcut. Bunun nedeni base class'in dtor'unun
    // protected alanda olmasi.

    // Der class, base class'in protected alanina erisebiliyor. O zaman der class turu olusturup, der class'i
    // delete etmeyi deneyelim.
    Dr1* dptr = new Dr1;
    delete dptr;    // Goruldugu gibi burada bir sorun yok, cunku der clas base class'in protected alandaki
    // destructor fonksiyonuna erisebiliyor
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// polimorfik siniflarin destructor'lari virtual olmali.
// polimorfik siniflarin dtor'lari ya public virtual ya da protected non-virtual olmalı

// Herb Sutter -- Cok onemli bir Cpp'ci. Microsoft compiler ekibinin basindaki kisi. Kitaplari da var.

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// using keywoard'u cpp'de en cok overload edilen keywoard.

class base15{
    public:
    void func(int){}
};

class der15 : public base15{
    public:
    void func(int x)    // SE1 -- SE etiketi, sonradan buraya eklendigini belirtir. Asagidaki SE etiketi takip edilebilir.
    {
        base15::func(x);
    }

    void func(double){}

};

// yukaridaki iki fonksiyon overload degildir cunku scope'lari farklidir! Bunu anlamak cok onemli.

void f11()
{
    der15 myder15;
    // bunlari overload nasil yapabilirim?
    // yani 
    myder15.func(10);  // --> Burada int parametreli fonksiyon cagiriliyorken
    myder15.func(1.1); // --> burada double parametreli fonksiyonu nasil cagirabilirim!
    // bunu yapabilmek icin turemis sinifin icerisinde bir int parametreli fonksiyon yazip base class'in fonksiyonunu cagirabilirim.
    // SE1
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 
// eger turemis isnif icinde using anahtar sozcugunu kullanarak taban sinifla nitelenmis bir isim kullanirsaniz ornegin using Base::func
// tipki namespace'lerdeki using bildirimlerinde oldugu gibi taban sinif icindeki ismi turemis sinifin scope'una ejekte etmis oluyorsunuz. 

class base16{
public:
    void func(int x)
    {
        std::cout << "base::func(int x) = " << x << "\n";
    }
};

class der16 : public base16{
public:
    using base16::func; // bu sekilde base class'in fonksiyonlarini kullanabilirim.
    void func(double x)
    {
        std::cout << "der::func(double x) = " << x << "\n";
    }
};

void f12(){
    der16 myder;
    myder.func(19);
    myder.func(104.43);
}

////////////////////////////////////////////////////////////

int main() {
    f12();
    return 0;
}



// inherited constructor!!!








































