#include <iostream>

// Kalitimda ozel uye fonksiyonlarin durumu!

class base1{
public:
    base1()
    {
        std::cout << " base1 Ctor \n";
    }
    ~base1()
    {
        std::cout << " base1 destor \n";
    }
};

class der1 : public base1{

};

void f_1(){
    der1 myder1;    // Ben sub class'i cagirdigimda super class'in ctor'u ve destor cagirilacaktir.
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class base2{
public:
    base2(int)
    {
        std::cout << " base2 Ctor \n";
    }
    ~base2()
    {
        std::cout << " base2 destor \n";
    }
};

class der2 : public base2{

};

void f_2(){
    //der2 myder2;    // buradaki hatanin sebebi superclass'in default ctor'unun default olarak delete edilmis olmasi.
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class base3{
public:
    base3()
    {
        std::cout << " base3 Ctor \n";
    }
    ~base3()
    {
        std::cout << " base3 destor \n";
    }
};

class der3 : public base3{
public:
    der3()
    {
        std::cout << " der3 Ctor \n";
    }
    ~der3()
    {
        std::cout << " der3 destor \n";
    }
};

void f_3(){
    //der2 myder2;    // buradaki hatanin sebebi superclass'in default ctor'unun default olarak delete edilmis olmasi.
    der3 myder3;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class base4{
public:
    base4(int x){
        std::cout << " x : " << x << "\n";
    }
    ~base4(){
        std::cout << "base4 kapaniyor \n";
    }
};

class der4 : public base4{
public:
    der4() : base4(23)  // base4'u fonksiyon gibi gosterip icerisine parametre yazdik. Burasina dikkat edilmeli.
    // Modern Cpp ile artik uniform init de yapabiliriz yani base4{23} gibi.
    {
        std::cout << "der4 aciliyor \n";

    }
    ~der4()
    {
        std::cout << "der4 kapaniyor \n";
    }
};

void f_4(){
    der4 myder4;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class person{
public:
    person(const std::string& name)
    {
        std::cout << name << "\n";
    }
private:
    std::string mname;
};

class employee : public person{
public:
    employee(const std::string &name) : person(name)
    {

    }
};

void f_5()
{
    employee("kadir kidir");
}

// Yukaridaki gibi kullanim cok yaygin bir kullanimdir.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class kdr_m1{
public:
    kdr_m1(){
        std::cout << " kdr_m1 Hosgeldiniz Der \n";
    }
};

class kdr_m2 : public kdr_m1{
public:
    kdr_m2()
    {
        std::cout << " kdr_m2 Hosgeldiniz Der \n";
    }
};

class kdr_m3 : public kdr_m2{
    // Coklu kalitim ornegi gorulur. m3 m2'e, m2 ise m1'e derivative olur!!!
    // kdr_m3 class'inin constructor'i direct class'ina gore yazilir. yani asagidak gibi bir kod yazarsam hata alirim.
public:
    kdr_m3()
    {
        std::cout << " kdr_m3 Hosgeldiniz Der \n";
    }
};

void f_6()
{
    kdr_m3 asd;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copy constructorlarda Inheritance
class kdr_f1{
public:
    kdr_f1()
    {
        std::cout << " bu bir testtir. Ama Default Ctor Testi\n";
    }
    kdr_f1(const kdr_f1&)
    {
        std::cout << " bu bir testtir. Ama Copy Ctor Testi\n";
    }
};

class kdr_f2 : public kdr_f1{

};

void f_7(){
    kdr_f2 f2;      // Kod calistirilirsa gorulecekki burada def ctor cagiriliyorken
    kdr_f2 f22 = f2;// burada ise
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Eger sub class'in copy ctor'unu ben yaziyor olsaydim!!!

class kdr_f3{
public:
    kdr_f3()
    {
        std::cout << " bu bir testtir. Ama Default Ctor Testi\n";
    }
    kdr_f3(const kdr_f3&)
    {
        std::cout << " bu bir testtir. Ama Copy Ctor Testi\n";
    }
};

class kdr_f4 : public kdr_f3{
public:
    kdr_f4() = default;
    kdr_f4(const kdr_f4&)
    {

    }
};

void f_8(){
    kdr_f4 f2;      // Bu program calistirildiginda anlasilacak ki 2 defa default ctor cagirilacak.
    kdr_f4 f22 = f2;// Cunku copy ctor'u yukaridaki gibi yazamayiz. Asagidak anlatiliyor.
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class kdr_f5{
public:
    kdr_f5()
    {
        std::cout << " bu bir testtir. Ama Default Ctor Testi\n";
    }
    kdr_f5(const kdr_f5&)
    {
        std::cout << " bu bir testtir. Ama Copy Ctor Testi\n";
    }
};

class kdr_f6 : public kdr_f5{
public:
    kdr_f6() = default;
    kdr_f6(const kdr_f6&other) : kdr_f5(other)
    {

    }
};

void f_9(){
    kdr_f6 f2;      // Yukaridaki hatali durum bu sekilde uygulandigi takdirde cozulur. Aslinda kullanim boyledir.
    kdr_f6 f22 = f2;//
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Move ctor'A bakiyoruz simdi de
class kdr_f7{
public:
    kdr_f7()
    {
        std::cout << " bu bir testtir. Ama Default Ctor Testi\n";
    }
    kdr_f7(kdr_f7&&)
    {
        std::cout << " bu bir testtir. Ama move Ctor Testi\n";
    }
    // derleyicinin yazdigi move ctor taban sinif nesnesini de move construct edecek.
};

class kdr_f8 : public kdr_f7{
public:
    kdr_f8() = default;

};

void f_10(){
    kdr_f8 asd;
    kdr_f8 bsd = std::move(asd);    // Burada Move semantigi calistirilmistir.
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class kdr_f9{
public:
    kdr_f9()
    {
        std::cout << " bu bir testtir. Ama Default Ctor Testi\n";
    }
    kdr_f9(kdr_f9&&)
    {
        std::cout << " bu bir testtir. Ama move Ctor Testi\n";
    }
    // derleyicinin yazdigi move ctor taban sinif nesnesini de move construct edecek.
};

class kdr_f10 : public kdr_f9{
public:
    kdr_f10() = default;
    // Ama sub class'in move ctor'unu biz yasiyorsak taban sinif nesnesi move ctor'un cagirilmasini biz saglamaliyiz.
//    kdr_f10(kdr_f10&&)  // Burada sub class'a move ctor yaziyorum ama burada yine eksik bir seyler oldugu icin
//    {                   // iki defa default ctor cagirilacaktir. Yorumdan kaldirilip gorulebilir.
//
//    }
    kdr_f10(kdr_f10&&other) : kdr_f9{std::move(other)}  // eger bu sekilde yaparsam istedigim sekilde move ctor cagi-
    {                   // rilmis olur. Copy ctor'u biz yaziyorsak taban sinif alt nesnesinin move edilmesinden
                        // biz sorumluyuz.
    }

};

void f_11(){
    kdr_f10 asd;
    kdr_f10 bsd = std::move(asd);    // Burada Move semantigi calistirilmistir.
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Atama islemlerine bakalim!! yani assingment'lara bakalim.
class b1{
public:
    b1& operator=(const b1&){
        std::cout << " bu bir testtir. Ama copy assingment Testi\n";
        return *this;   // syntax hatasi olmasin diye *this'i return etmeyi ihmal etmeyelim.
    }
};

class s1 : public b1{

};

void f_12(){
    s1 asdf1,asdf2;
    asdf1 = asdf2;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class b2{
public:
    b2& operator=(const b2&){
        std::cout << " bu bir testtir. Ama copy assingment Testi\n";
        return *this;   // syntax hatasi olmasin diye *this'i return etmeyi ihmal etmeyelim.
    }
};

class s2 : public b2{
public:
    // ama sub class'in assnment'ini kendim yaziyor olsaydim yani derleyiciye birakmiyor olsaydim bunu eksiksiz ve
    // dogru bir sekilde yapmam gerekir.
    s2& operator=(const s2&)
    {
        return *this;
        // bunun ciktisi olarak hicbir sey almayacagiz cunku eksik yazdigimiz icin base class'in def ctor'u cagirilir.
    }
};

void f_13(){
    s2 asdf1,asdf2;
    asdf1 = asdf2;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class b3{
public:
    b3& operator=(const b3&){
        std::cout << " bu bir testtir. Ama copy assingment Testi\n";
        return *this;   // syntax hatasi olmasin diye *this'i return etmeyi ihmal etmeyelim.
    }
};

class s3 : public b3{
public:
    // ama sub class'in assnment'ini kendim yaziyor olsaydim yani derleyiciye birakmiyor olsaydim bunu eksiksiz ve
    // dogru bir sekilde yapmam gerekir.
    s3& operator=(const s3&other)
    {
        b3::operator=(other);   // bu sekilde eksiksiz olarak calisacaktir.
        // Yukaridaki kodu, upcast mantigiyla asagidaki gibi de yazabiliriz ve ayni sekilde calisir.
        *(b3*)this= other;      // ilgili func cagirildiginda durum anlasilir.
        return *this;
        // bunun ciktisi olarak hicbir sey almayacagiz cunku eksik yazdigimiz icin base class'in def ctor'u cagirilir.
    }
};

void f_14(){
    s3 asdf1,asdf2;
    asdf1 = asdf2;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// move assingment
class b4{
public:
    b4& operator=(b4&&)
    {
        std::cout << " bu bir testtir. Ama move assingment Testi\n";
        return *this;
    }
};

class s4 : public b4{

};

void f_15()
{
    s4 a,b;
    a = std::move(b);   // burada yazilmis olan move assingment cout ciktisina ulasilir.
}

// eger su 3 islevden biri bildirilmis ise derleyici sinifin move member'larini yazmaz.
// copy ctor
// move ctor
// destructor

// eger su 2 islevden biri bildirilmis ise derleyici sinifin copy member'larini delete eder.
// move ctor
// move assngmnt

////////////////////////
class b5{
public:
    b5& operator=(b5&&)
    {
        std::cout << " bu bir testtir. Ama move assingment Testi\n";
        return *this;
    }
};

class s5 : public b5{
public:
    s5& operator=(s5&& other)
    {
        b5::operator=(std::move(other));
        return *this;
    }
};

void f_16()
{
    s5 a,b;
    a = std::move(b);   // burada yazilmis olan move assingment cout ciktisina ulasilir.
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Runtime polymorphism
// 1. tip: diyelim ki airplane adinda bir sinif var. Bu sinifin fly isminde bir fonksiyonu olsun.ç
// void fly();
// Airplane sinifi kendisinden kalitim yoluyla olusan siniflara sunu soyler.
// Her ucak ucar, ve benim verdigim kodla ucar. Bu durumda airplane sinifindan kalitim yoluyla boing sinifi
// olusturugunuzda, airplane'nin verdigi kod ile ucacak. Yani hem interface hem de implamentasyon saglamis oluyor.

// 2. kategoride bu kez fly fonksiyonu icin diyor ki taban sinif, hem bir interface veriyorum hem de bir default
// implemantasyon veriyorum. Yani size bir kod veriyorum default olarak kullanabileceginiz. Isterseniz benim verdigim
// kullanirsiniz isterseniz de kendi kodunuzu olusturabilirsiniz. Subclass'in kendi kodunu saglamasina bu fonksiyonu
// override etmesi deniyor. Overload ile karsilastirilmasin.

// 3. kategoride ise fonksiyon implamentasyonundan sub class sorumlu. super class bir fonksiyon sunmuyor. Bu isleme de
// yine override diyoruz.

// eger bir sinifin C++'ta ikinci kategoride en az bir fonksiyonu varsa boyle siniflara polimorfik siniflar deniyor.
// 3. kategoride en az bir fonksiyonu varsa bunlara abstract sinif deniyor.

// concrete class(somut siniflar) : bu sinif turunden nesneler olusturulabilir
// abstract class(soyut siniflar) : nesne olusturulamayan siniflar.
// sadece pointer ya da referans semantigi ile kullanilir abstarct siniflar.

class Airplane{
public:
    void takeoff();
    // birinci tip. Yani hem interface hem de implamentasyon saglanmis olur.
    virtual void land();    // virtual function. land'in kodunu override edebilirim. Istersem override ederim istersem
                            // etmem. Bu ikinci tip.
    virtual void fly() = 0; // bu sembolik bir sentax. Bu bir atama degildir. Bu da 3. tip kullanima ornektir.
                            // pure virtual function.
};

// late binding ya da dynamic binding. Function overriding tamamen late binding.
// hangi programin cagirilacagi programin calisma zamaninda belli olacak.

class car1{
public:
    void start(){
        std::cout << " car1 start cagirildi \n";
    }
    void run(){
        std::cout << " car1 run cagirildi \n";
    }
    void stop(){
        std::cout << " car1 stop cagirildi \n";
    }
};

class Bmw : public car1{
public:
    void start(){
        std::cout << " bmw start cagirildi \n";
    }
    void run(){
        std::cout << " bmw run cagirildi \n";
    }
    void stop(){
        std::cout << " bmw stop cagirildi \n";
    }
};

class Fiat : public car1{
public:
    void start(){
        std::cout << " fiat start cagirildi \n";
    }
    void run(){
        std::cout << " fiat run cagirildi \n";
    }
    void stop(){
        std::cout << " fiat stop cagirildi \n";
    }
};

class Volvo : public car1{
public:
    void start(){
        std::cout << " volvo start cagirildi \n";
    }
    void run(){
        std::cout << " volvo run cagirildi \n";
    }
    void stop(){
        std::cout << " volvo stop cagirildi \n";
    }
};

class Toyota : public car1{
public:
    void start(){
        std::cout << " Toyota start cagirildi \n";
    }
    void run(){
        std::cout << " Toyota run cagirildi \n";
    }
    void stop(){
        std::cout << " Toyota stop cagirildi \n";
    }
};

class Dacia : public car1{
public:
    void start(){
        std::cout << " Dacia start cagirildi \n";
    }
    void run(){
        std::cout << " Dacia run cagirildi \n";
    }
    void stop(){
        std::cout << " Dacia stop cagirildi \n";
    }
};

void car1_game(car1& cr){
    cr.start();
    cr.run();
    cr.stop();
}

void f_17(){
    Bmw bmw;
    Toyota toyota;
    Dacia dacia;

    car1_game(bmw);
    car1_game(toyota);
    car1_game(dacia);
    // surekli olarak base class'in fonksiyonlari cagirildi.
    // ben bu fonksiyonlari bu sekilde cagirinca yine base class'in fonksiyonlari cagirilir cunku virtual anahtar
    // sozcugunu eklemedik!
    // Asagidaki ornekte virtual'lar eklenince ve burada eklenmemis sekilde, nasil farkliliklar olustugu gorulebilir!
}

//********************************************************************************************************************//

class car2{
public:
    virtual void start(){
        std::cout << " car2 start cagirildi \n";
    }
    virtual void run(){
        std::cout << " car2 run cagirildi \n";
    }
    virtual void stop(){
        std::cout << " car2 stop cagirildi \n";
    }
};

class Bmw1 : public car2{
public:
    void start(){
        std::cout << " bmw1 start cagirildi \n";
    }
    void run(){
        std::cout << " bmw1 run cagirildi \n";
    }
    void stop(){
        std::cout << " bmw1 stop cagirildi \n";
    }
};

class Fiat1 : public car2{
public:
    void start(){
        std::cout << " fiat1 start cagirildi \n";
    }
    void run(){
        std::cout << " fiat1 run cagirildi \n";
    }
    void stop(){
        std::cout << " fiat1 stop cagirildi \n";
    }
};

class Volvo1 : public car2{
public:
    void start(){
        std::cout << " volvo1 start cagirildi \n";
    }
    void run(){
        std::cout << " volvo1 run cagirildi \n";
    }
    void stop(){
        std::cout << " volvo1 stop cagirildi \n";
    }
};

class Toyota1 : public car2{
public:
    void start(){
        std::cout << " Toyota1 start cagirildi \n";
    }
    void run(){
        std::cout << " Toyota1 run cagirildi \n";
    }
    void stop(){
        std::cout << " Toyota1 stop cagirildi \n";
    }
};

class Dacia1 : public car2{
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

void car2_game(car2& cr){
    cr.start();
    cr.run();
    cr.stop();
}

void f_18(){
    Bmw1 bmw;
    Toyota1 toyota;
    Dacia1 dacia;

    car2_game(bmw);
    car2_game(toyota);
    car2_game(dacia);
    // ilgili ciktiya bakildiginda virtual keyword'unun eklenmesinden sonra base class'in ilgili fonksiyonlarinin degil
    // ilgili sinifin fonksiyonlarinin calistigi gorulur.
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <random>

car2* create_random_car()
{
    static std::mt19937 eng{std::random_device{}()};
    static std::uniform_int_distribution dist{1,5};

    switch (dist(eng)){
        case 1: std::cout << " BMW olusturuldu\n"; return new Bmw1;
        case 2: std::cout << " Fiat olusturuldu\n"; return new Fiat1;
        case 3: std::cout << " Volvo olusturuldu\n"; return new Volvo1;
        case 4: std::cout << " Toyota olusturuldu\n"; return new Toyota1;
        case 5: std::cout << " Dacia olusturuldu\n"; return new Dacia1;
//        case 6: std::cout << " VolvoS60 olusturuldu\n"; return new VolvoS60;

    }
}

void f_19(){
    for(;;){
        auto p = create_random_car();
        car2_game(*p);
        (void)getchar();
    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class c_kdr0{
public:
    virtual void vfunc();
};

class c_kdr1 : public c_kdr0{
public:
    // eger yukaridaki fonksiyon sanal olmasaydi turemis sinif pek ala ayni isme sahip parametresi ayni fakat geri
    // donus degeri farkli olabilirdi. Ama su an hata verecektir.
    // int vfunc();    // yorum cizgileri kaldirilirsa acikca gorulecektir.

    // eger geri donus degeri ayni fakat parametresi farkli ise burada bir hata yok ama bu overriding ya da overloading
    // degil.
    void vfunc(int);    //  burada hata vermez. Ama burada herhangi bir override fonksiyonu yoktur.
    // demekki bir taban sinifin sanal fonksiyonunu nasil override edecegim sorunun cevabi ortaya cikti
    // ayni parametre ve ayni geri donus degeri olmali. Yazdigimiz fonksiyona virtual yazip yazmamak arasinda bir fark
    // yoktur.
    void vfunc()override; // boyle sozcuklere contextual keywork deniyor. Ne demek bu?
    // belirli bir bağlamda kullanildiginda anahtar sozcuk etkisi yapiyor amabunun disinda anahtar sozcuk anlami
    // yapmiyor.
    // neden override sozcugu getirdiler? Legacy kodlar, eski kodlari yeni derleyicilerle derledigimizde override
    // sozcugu kullanilmissa sapir sapir hata vermemesi icin boyle bir kavram cikarildi.
    // Override ayri bir baslik altinda anlatilacak.

    // const da imzanin bir parcasi oldugu icin base sinifta fonksiyon const ise ve turemis sinifta const anahtar
    // sozcugu olmazsa override islemi gerceklesmemis olur.
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Fuction overloading ile function overriding bir arada da olabilirdi.

class c_kdr2{
public:
    virtual void vfunc();
    virtual void vfunc(int);
    virtual void vfunc(int,int);    // an itibariyle vfunc'in 3 tane overload'u var ve 3'u de virtual. Turemis siniflar
    // bu 3 fonksiyonun 3'unu de ayri ayri override edebilirler.
};

class c_kdr3{
public:
    void vfunc();   // override1
    void vfunc(int);   // override2
    void vfunc(int,int);   // override3

};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class c_kdr4{
public:
    virtual void vfunc(){
        std::cout << " base'in vfunc'i\n";
    }
};

class c_kdr5 : public c_kdr4{
public:
    void vfunc(){
        std::cout << " der'in vfunc'i\n";
    }
};

void f_20()
{
    c_kdr5 myder;
    c_kdr4* baseptr = &myder;
    baseptr->vfunc();
    // bu fonksiyonun cagirilmasiyla der'in vfunc'i cagirilir.
}

void f_21(){
    c_kdr5 myder;
    c_kdr4& baseptr = myder;
    baseptr.vfunc();
    // bu fonksiyonun cagirilmasiyla da der'in vfunc'i cagirilir.
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class c_kdr6{
public:
    virtual void vfunc()
    {

    }
    void foo() // non virtual bir fonksiyon
    {
        vfunc();    // virtual fonksiyon cagiriliyor.
    }
};

class c_kdr7:public c_kdr6{
public:
    void v_func()
    {
        std::cout << "der::vfunc()\n";
    }
};

void func(c_kdr6& r)
{
    r.vfunc();
}

void foo(c_kdr6* ptr)
{
    ptr->vfunc();
}

void f_22()
{
    c_kdr7 myder;
    myder.foo();    // goruldugu uzere burada non-virtual bir fonksiyon cagiriyorum.
                    // ama sonuca bakilirsa derivative class'in virtual fonksiyonu cagirilir.
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

void f_23(){
    for(;;){
        auto p = create_random_car2();
        car3_game(*p);
        (void)getchar();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    f_23();
    return 0;
}
