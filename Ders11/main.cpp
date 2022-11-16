#include <iostream>
#include <cstdlib>
#include <cstring>
/*
 * Copy member --> copy assignment, copy ctor
 * move member --> move assignment, move ctor
 */
 // Shallow copy = memberwise copy.

 class kdr_001{
 public:
     kdr_001() = default; // sinifa special bir ctor atandi.
     kdr_001(int);        // Bundan dolayi ustteki yazilmasaydi, sinifin def ctor'u olmayacakti.

 };

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class  Sentence {
public:
    Sentence(const char *p) : m_len{std::strlen(p)}, m_p{ static_cast<char *>(std::malloc(m_len + 1))} {
        if (!m_p){
            std::cerr << "bellek yetersiz\n";
            std::exit(EXIT_FAILURE);
        }
        std::cout << this << " adresindeki nesne icin" << (void*)m_p << " adersindeki b. alani allocate edildi\n";
        std::strcpy(m_p,p );
    }

    // Shallow copy yerine deep copy yapmak icin copy ctor'umuzu kendimiz yaziyoruz.
    Sentence(const Sentence& other) : m_len{other.m_len},m_p{ static_cast<char *>(std::malloc(m_len + 1))}
    {   // malloc'la da goruldugu gibi kendisi yeni bir bellek alani tahsis etti. Bu sayede value semantic yapisina
        // uygun bir kod yazilmis oldu sorun simdilik ortadan kalkti.
        if (!m_p)
        {
            std::cerr << "bellek yetersiz\n";
            std::exit(EXIT_FAILURE);
        }
        strcpy(m_p, other.m_p);
    }

    Sentence& operator=(const Sentence& other){
        if( this == &other)
            return *this;
        // yukaridaki kontrolu yapmamin sebebi self assignment'tan kacinmak!!!
        // once kendi kaynagimi geri veriyorum.
        free(m_p);
        m_len = other.m_len;
        m_p = static_cast<char *>(std::malloc(m_len + 1));
        if (!m_p)
        {
            std::cerr << "bellek yetersiz\n";
            std::exit(EXIT_FAILURE);
        }

        std::strcpy(m_p, other.m_p);
        return *this;
        // neden kopyalama atama fonksiyonu kendisine atama yapılmış nesneyi
        //döndürüyor.

        // C++'ta atama operatörleriyle oluşturulan ifadelerin değer kategorisi
        // lValue expression'dur.

    }



    void print()const{
        std::cout << this << " adresindeki nesne icin" << (void*)m_p << " adersindeki b. alani geri verildi\n";
        std::cout << "["<< m_p << "]\n";
    }

    ~Sentence(){
        std::free(m_p);
    }

private:
    std:: size_t m_len; // dizinin boyutunu tutacak.
    char *m_p; //

};

void fcn_008(Sentence s)
{
    s.print();
}


// RAII idiomu :  Resource acquisition is initialization: Kaynak edinimi ilk deger vermeyle olur.
// Bircok sinifta kullanilan idiometrik bir yapi.


int main() {
    /*
    std:: cout << "Main Baslangici \n";
    Sentence s1 = "bugun hava cok guzeldi";
    fcn_008(s1); // Buraya s1 nesnesini koplayadik. fcn_008 fonksiyonuna girdi yazdirdi  ve cikarken destructor'a
    ugradi. Bunun sonucunda memory free edildi. Bunun yerine copy constructor'u kendim yazmam gerekir
    s1.print();
    std:: cout << "Main Bitisi \n";
     */

    std:: cout << "Main_002 Baslangici \n";
    Sentence sen_1{" kadirkidir"};

    {
        Sentence sen_2{" bmcotomotiv"};
        sen_2 = sen_1;  // bir sinif nesnesine atama operatoruyle ayni turden bir baska sinif nesnesi atandiginda
                        // bu atama islemini gerceklestiren sinifin bir baska ozel uye fonksiyonu var. Copy Assignment
                        // Copy yerine assignment olmasinin sebebi, atama sirasindaki iki sinifin da hayatta olmasi.
    }



    sen_1.print();
    //sen_2.print();
    std:: cout << "Main_002 Bitisi \n";

    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// assignment fonksiyonu su sekilde. Non static public inline fonksiyon

 class Myclass {
 public:
    Myclass& operator=(const Myclass&);
 };
/*
 * a = b; // for assignment
 * a.operator=(b);  // bununla yukarıdakinin bir farki yok. Operator overloading.
 */

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
class kdr_002{
public:
    kdr_002& operator=(const kdr_002& other)
    {
        ax = other.ax;
        ax = other.ax;
        ax = other.cx;
    }

private:
    A ax;
    B bx;
    C cx;
};
*/

// Bir nesneye kendisinin atanması. Self assingment.
// x = x; // y = y;

// eğer kopyalayan atama operator fonksiyonunu kendimiz yazacaksak (ve alternatif
// baska idiomatik bir yapi kullanilmayacaksa - copy swap) ilk yapmamiz gereken
// self-assignemnt kontrolü. Eger self assignment yoksa atama operatorunun  sol
// tarafi once kendi kaynagini geri veriyor. Sonra kendisi icin yeni bir kaynak
// edinip diger nesnenin kaynagini kendi nesnesinin kaynagina kopyaliyor.

// destructor
// copy constructor
// copy assignment

// Eger bir sinif icin destructor  yazma ihtiyaci duyuyorsak muhtemelen desctructor
// icin de bir kaynak geri verme islemi yapıyorsunuz.
// Memory leak, olsa olsa resource leak'in bir alt dalı olabilir.
// Eğer destructor'ın yazilmasi gerekiyorsa, copy constructor'ı da biz yazmaliyiz.
// Eğer copy constructor'ın yazilmasi gerekiyorsa, copy assingment'ı da biz yazmaliyiz.

///////////////////////////////////////////////////////////////////////////////////////////////

class Myclass_001{
public:
    Myclass_001();                                  // Def ctor
    ~Myclass_001();                                 // Def destructor
    Myclass_001(const Myclass&);                    // Copy ctor
    Myclass_001& operator=(const Myclass_001&);     // Copy Assignment
};
///////////////////////////////////////////////////////////////////////////////////////////////

/*
 * Destructor
 *          release resources
 *
 * Copy Ctor
 *          Deep copy
 *
 * Copy Assignment
 *          Release resources
 *          Deep copy
 */

///////////////////////////////////////////////////////////////////////////////////////////////

class Myclass_002{
public:
    void func();
};

int main_001(){
    Myclass_002 m1, m2;

    (m1 = m2).func();   // Operator atama ile assigment yaptiktan sonra yani m2 class'ini
                        // m1 class'ina assign ettikten sonra m2 class'inin func'i cagirilir. Bunu
                        // asagidaki gibi de yapabilirdim.

    m1.operator=(m2).func();

    Myclass k1,k2,k3,k4;

    k1 = k2 = k3 = k4;
    // ESITTIR
    k1.operator=(k2.operator=(k3.operator=(k4)));
}

///////////////////////////////////////////////////////////////////////////////////////////////

// MOVE SEMANTIC

// rValue&& move semantic icin dile eklenmistir.

void func(const int&);      // const lValue ref
void func(int &&);          //       rValue ref

int main_002(){

    int x = 5;

    func(x);        // lValue oldugundan ustteki cagirilir, alttaki viable degildir.
    func(10);       // ikisi de viable olmasina ragmen alttaki rValue oldugundan alttaki cagirilir.
}

// Eger bir class lValue ise bu class daha sonradan kullanilabilir, yasam omru devam ediyor.
// ama eger bir class rvalue ise bu class'in kaynagini calabiliriz.

class Myclass_003{
public:
    Myclass_003(const Myclass&);    //   Copy Ctor, lValue
    Myclass_003(Myclass &&);        //   Move constructor, rValue
};

// bir sinifin bir baska ozel uye fonksiyonu  8

 class Myclass_004{
 public:
     Myclass_004(const Myclass_004&);               // Copy Ctor
     Myclass_004(Myclass_004&&);                    // Move Ctor
     Myclass_004& operator=(const Myclass_004&);    // Copy Assigment
     Myclass_004& operator=(Myclass_004&&);         // Move Assigment

 };

//////////////////////////////////////////////////////////////////////////////////////////////

class Myclass_005{
    //
};

int main_004(){
    Myclass_005 m1;
    Myclass_005 m2 = m1; // Copy ctor cagirilacak. Cunku m1 lValue. AMAA

    Myclass_005 m3 = static_cast<Myclass_005&&>(m1);    // AMA bunun yerine bunu yapan bir
                                                        // fonksiyon mevcut. std::move fonksiyonu

    Myclass_005 m4 = std::move(m1);    // Bu fonksiyona bir lValue expression'u argüman olarak
                                          // verdiğimizde yukarıdakini çağırmış oluyoruz ve değer
                                          // rvalue expression oluyor. Artık move ctor cagirilir.
}

// Moved-from state - Yukarıdaki orneklerde m1.
// Moved-from state nesneler yani tasinmis nesneler bazı ozel kurallara tabii. Bunlara atama
// yapabilirsiniz ama bunların değerini kullanamazsınız. Ama birçok durumda bu Moved-from state'deki
// nesneleri genelde hiç kullanmayı düşünmüyoruz.

//////////////////////////////////////////////////////////////////////////////////////////////

class Myclass_006{
    // code
};

void foo(Myclass_006&& r){
    Myclass_006 m = r;  // burada fonksiyona r value expression gonderiyor olabilirsin.
                        // ama burada r degeri rvalue degil lValue'dur cunku yalniz basina lValue'dur.
                        // Yani bu sekilde calistirirsam yine copy islemi yapmis olurum.
                        // Copy yapmak istemiyorsam move fonksiyonunu kopyalamam lazım.
    Myclass_006 m2 = std::move(r); // bu sekilde yaparsam kaynagini calmis olurum.
}
 int main_005(){
    Myclass_006 x;
}

// oyle bir fonksiyon yazalim ki fonksiyon cagirildiginda fonksiyona gonderilen nesne eger
// lValue exp ise onun kaynagini koplayiycam cunku calarsam problem olur ama fonksiyona gelen
// nesne rValue exp ise onun kaynagini calmak istiyorum. Bunu nasıl yapacaksin? Template
// kullanmadan bunu yapmak istiyorsam bunun icin iki ayri fonksiyon yazmam gerekir.

void func(const Myclass_006& r) // lValue exp
{
    Myclass_006 m = r;  // kaynagi koplayamis oluyorum.
}
void func(Myclass_006&& r)      // rValue exp
{
    Myclass_006 m = std::move(r); // kaynagi calmis oldum.
}

// 1. Geri donus degeri class olan bir fonksiyonun geri donus degeri rValue expression'dur.
/**/
/*
Myclass_006 foo();
foo();  // bu fonksiyonun geri donus degeri rvalue expression'dur.
*/

// 2. Temporary Object : calisan kod tarafindan baktigimizda ortada bir nesne var ama ifadenin
// icinde bir isim yok. Ama bir gecici nesneyi fiilen olusturma sansim da var.
/*
 Myclass{};
 Myclass();
 foo(); Bu ucu temporary object oldugu icin rValue expression'dur.
 */

//////////////////////////////////////////////////////////////////////////////////////////////

class Myclass_007{
public:
    Myclass_007(const Myclass_007 &other ) : ax(other.ax), bx(other.bx) , cx(other.cx)
    {
        // derleyicinin yazdigi copy ctor
    }

    Myclass_007& operator=(const Myclass_007 &other ){
        ax = other.ax;
        bx = other.bx;
        bx = other.cx;

        return *this;
        // derleyicinin yazdigi copy assinment
    }

    Myclass_007(Myclass_007&& other) : bx(std::move(other.bx)) , ax(std::move(other.ax)) , cx(std::move(other.cx)){
        // derleyicinin yazdigi move Ctor
    }

    Myclass_007& operator=(Myclass_007&& other){
        ax = std::move(other.ax);
        bx = std::move(other.bx);
        cx = std::move(other.cx);

        return *this;
    }

private:
    int ax;
    int bx;
    int cx;
};

//////////////////////////////////////////////////////////////////////////////////////////////

// Sentence sinifi ornege donuyorum.

class  Sentence2 {
public:
    Sentence2(const char *p) : m_len{std::strlen(p)}, m_p{ static_cast<char *>(std::malloc(m_len + 1))} {
        if (!m_p){
            std::cerr << "bellek yetersiz\n";
            std::exit(EXIT_FAILURE);
        }
        std::strcpy(m_p,p );
    }

    // Shallow copy yerine deep copy yapmak icin copy ctor'umuzu kendimiz yaziyoruz.
    Sentence2(const Sentence2& other) : m_len{other.m_len},m_p{ static_cast<char *>(std::malloc(m_len + 1))}
    {   // malloc'la da goruldugu gibi kendisi yeni bir bellek alani tahsis etti. Bu sayede value semantic yapisina
        // uygun bir kod yazilmis oldu sorun simdilik ortadan kalkti.
        if (!m_p)
        {
            std::cerr << "bellek yetersiz\n";
            std::exit(EXIT_FAILURE);
        }
        strcpy(m_p, other.m_p);
    }

    // MOVE CONSTRUCTOR
    Sentence2(Sentence2&& other ) : mlen(other.m_len), m_p(other.m_p){
        other.m_p = nullptr; // Bunu yapmamin  amaci kaynagi kopyaladiktan sonra kaynak destructor'da
        // silinmemesi icin nullptr yapiyorum. Destructor'daki isleme de bakilabilir.
    }

    // MOVE ASSIGNMENT
    Sentence2& operator=(Sentence2&& other){
        if(this == &other)
            return *this;

        free(m_p); // kendi kaynagini geri veriyor.
        m_len = other.m_len;
        m_p = other.m_p;
        other.m_p = nullptr;
    }

    Sentence2& operator=(const Sentence2& other){
        if( this == &other)
            return *this;
        // yukaridaki kontrolu yapmamin sebebi self assignment'tan kacinmak!!!
        // once kendi kaynagimi geri veriyorum.
        free(m_p);
        m_len = other.m_len;
        m_p = static_cast<char *>(std::malloc(m_len + 1));
        if (!m_p)
        {
            std::cerr << "bellek yetersiz\n";
            std::exit(EXIT_FAILURE);
        }

        std::strcpy(m_p, other.m_p);
        return *this;
        // neden kopyalama atama fonksiyonu kendisine atama yapılmış nesneyi
        //döndürüyor.

        // C++'ta atama operatörleriyle oluşturulan ifadelerin değer kategorisi
        // lValue expression'dur.

    }



    void print()const{
        std::cout << "["<< m_p << "]\n";
    }

    // kaynak tasinacaksa kaynagi geri vermeyecek ama kaynak kopyalanacaksa kaynagi geri verecek.
    ~Sentence2(){
        if(m_p)
            std::free(m_p); // m_p'yi move ctor'da nulltpr yaptik. Kayngaini calmak icin.
    }

private:
    std:: size_t m_len; // dizinin boyutunu tutacak.
    char *m_p; //

};

void fcn_009(Sentence2 s)
{
    s.print();
}

// Derleyici hangi durumalrda sınıfın hangi özel üye fonksiyonlarını yazacak?
// Bir sinifin bir özel üye fonksiyonu asagidaki 3 durumdan birinde olabilir.

// 1. Fonksiyon hic olmayabilir. Not exist.
class asd{
    asd(int);   // Default ctor yok. Cunku parametreli ctor yazildi.
};

// 2. Sinifin ozel uye fonksiyonu user declared'tir. Programci tarafindan bildirilmis.
    asd1();    // bildirmis ama sonra tanimlanacak.
    asd2() = default; // bildirmistir ama derleyicinin default etmesini istemistir.
    asd3() = delete; // bunlarin ucu de user declared demek.

// 3. Implicitly declared.
    // derleyici bizim icin default edebilir ya da derleyici bizim icin delete edebilir.








