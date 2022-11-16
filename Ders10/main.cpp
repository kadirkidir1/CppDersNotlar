#include <iostream>
#include <cstring>
#include <cstdlib>

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}

// Eğer sınıfa herhangi bir constructor bildirilmemişse derleyici implicitly olarak bir defauly ctor ataması yapar.
// Ama bir ctor tanımlanmışsa, örneğin kdr(int); şeklinde, bu sefer derleyici default ctor atamaz. Parametresiz olarak
// çağırılan bir işlemde hata yapılmış olur.

// Ctor nokta, ok veya çözünürlük operatörüyle çağırılamaz.
// Ancak sınıfın destructor'u nokta, ok veya çözünürlük operatörüyle çağırılabilir. Syntax hatası olarak bir hata vermez
// ama asla yazmayın. Sadece tek bir yerde çağırılması gerektiği için izin verilmiş. Böyle bir çağrının gerektiği
// çok ender senaryolardan biri placement new operatörü ile hayata getirilen nesneler için.

// Constructor initializer list, modern cpp
// member initializer list (MIL) modern cpp'den önce.
// CIL, MIL başka, birde ismi Initializer list olan sınıf var bu da başka.

class Myclass{
public:
    Myclass();
private:
    int mx, my;
};

Myclass::Myclass() : mx(10), my(20) // Modern cpp'ye kadar burada parantezlerin kullanılması zorunluydu.
                                    // Ancak modern cpp ile küme parantezi de dahil oldu. Aşağıdaki örnekte görülebilir.
{

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Myclass2{
public:
    Myclass2();
private:
    int mx, my;
};

Myclass2::Myclass2() : mx{10}, my{20}// Modern Cpp ile uniform init eklendi.
{

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Myclass3{
public:
    Myclass3();
private:
    int mx, my;
};

Myclass3::Myclass3() : my{2*mx}, mx{20}// Değişkenler tanımanırken sınıf içindeki tanım sıralarınca tanımlanır derleyici
                                       // tarafından. Yani mx önce tanımlanır. my = 2*mx ifadesinde ise syntax hatası
                                       // oluşmaz lakin UB'dir. mx garbage bir değer alır. Bu kural önemlidir.
{

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Myclass4{
public:
    Myclass4() : mx{10} // mx nesnesi const olduğundan ve sonradan değer verilemeyeceği için CIL ile init etmek zorunlu-
    {                   // dur. Aksi halde syntax hatası olur.

    }
private:
    const int mx;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Myclass5{
public:
    Myclass5() // buradaki hatanın sebebi, referans nesnelere ilk değer verilmesi zorunludur. Bu yüzden hata alındı.
    {
    }
private:
    int &mr;
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Bazı durumlarda MIL oluşturmak zorunlu. Örneğin sınıfın veri elamanını bir referans olması ya da const olması.

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class date{
public:
    Date(int d, int m, int y) : m_day{d} , m_mon{m} ,m_year{y} {}

private:
    int m_day;
    int m_mon;
    int m_year;
};

// Bu şekilde kullanım çok yaygın olan bir kullanımdır.

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class khk{
private:
    int mx = 10;
    int my = 20;    // Bu şekilde değer verme modern C++ ile dile eklendi.
    int mz{39};     // Bu şekilde de değer verebiliyorum. Buna default member init ya da in-class init deniyor.
                    // Ama tam anlamıyla ilk değer vermiyor. Eğer constructor ile ilk değer verilmiyorsa bunun eklenmesi
                    // talimatını vermiş oluyoruz. Aşağıdaki örnekte bunu daha detaylı görebiliriz.
    int mh(19);     // Bu şekilde değer veremiyoruz. Syntax hatası.
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Myclass6{
public:
    Myclass6();

private:
    int mx{20};
};

Myclass6::Myclass6() // Bu şekilde çağırırsam derleyici otomatik olarak aşağıdaki gibi çağırıyor.
// Myclass6::Myclass6() : mx{20}
{

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// CIL her zaman birinci tercihiniz olsun.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Person{
public:
    Person(const char *p){
        m_name = p;
    }
private:
    std::string m_name;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// bir sınıfın default ctor'u olmak zorunda değil.

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class khk2{
public:
    khk2() = delete; // Sınıfın default ctor'u var fakat delete edilmiş. Yani ona yapılan çağrı syntax hatası olur.
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Makul bir sebebi olmadıkça sınıfınınza muhakkak default ctor yazın!!!

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * Delegating constructor: C++'a biraz geç eklendi. Normalde ctor ismiyle çağırılamaz, fakat bu delegating ctor
 * ile bir sınıfın ctor'u veri elemanlarının init edilmesi için sınıfın başka bir ctor'ını çağırabilir. Özellikle
 * ctor'ların ortak bir kodunun olması durumunda sıkça tercih edilen bir yapıdır.
 */

class khk3{
public:
    khk3(int x, int y, int z) : m_a{x}, m_b{y}, m_c{z} { }
    khk3(int x) : khk3(x,0,0) {}
    // khk3(int x) : khk3(x,0,0)  , m_c{43} {} --> Bu syntax hatası. böyle kullanıyorsak başka türlü değer veremeyiz.
private:
    int m_a, m_b, m_c;
};

// Default member init eski c++'ta yoktu. Modern C++ ile geldi.
// Brace init ve delegating ctor Modern C++ ile dile eklenen ögeler arasında.

// Special Member Function //
// Özel üye fonksiyonların sayısı modern C++ ile 6'ya yükseldi. Çok önemli
/*
 * 1 Default ctor
 * 2 desctructor
 * 3 copy ctor
 * 4 move ctor          ( C++11 )
 * 5 copy assignment
 * 6 move assignment    ( C++11 )
 * Bunları özel yapan belirli koşullar oluştuğunda derleyicinin bu üye fonksiyonları bizim için yazması. Buna
 *  derleyicinin generate etmesi deniyor. Yeni syntax'ta derleyicinin bu kodunu default etmesi deniyor.
 *
 *  Bu fonksiyonların programcı tarafından bildirilerek ama tanımının derleyici tarafından yapılmasının istenebilmesi.
 */

class khk4{
public:
    // khk4();          // noktalı virgül koysaydım kendim bildirmiş olacaktım. User declared (defined)
    //khk4() = default; // default Overload edilmiş durumda. Bunu ben bildiriyorum ama tanımlamasını derleyiciye
                        // bırakıyorum demek bu şekilde tanımlamak. User-declared - Defaulted
    khk4() = delete;    // user-declared. Bu ve üstteki 2sinin ortak özelliği user declared olması.
                        // default etme yalnızca special member functionlar için geçerli.
                        // delete etme ise special fonksiyonlara özel değil. Herhangi bir fonksiyon için söz konusu.
};

// Eğer derleyici sınıfın bir özel üye fonksiyonunu default edecek ise fakat derleyicinin özel üye fonksiyonu
// dilin kurallarına uygun bir şekilde oluşturması sürecinde bir syntax hatası oluşursa derleyici default edeceği
// özel üye fonksiyonu delete eder. Modern C++ ile gelen bir kural.

// Const bir nesnenin default init edilmesi legal değil.
class khk5{     // Bu sınıfın default ctor'u derleyici tarafından delete edilmiş durumda. Derleyici default init edemez.
private:        // Çünkü const'tan dolayı bir sıkıntı mevcut. Bu sebepten dolayı derleyici syntax hatası vermez, default
                // ctor'u siler.
    const int x;
};

int fcn_001(){
    khk5 x;     // --> Call to implicitly-deleted default constructor of 'khk5'
}               //     Hata vermesinin sebebi const'tan dolayı default ctor'un silinmiş olması. Default init edilemez.

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class khk6{
public:
    khk6(int);
};

class khk7{
private:
    khk6 m_a; // Şu an için bir hata vermez.
};

int fcn_002(){
    khk7 m;  // Call to implicitly-deleted default constructor of 'khk7'
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class khk8{
    khk8();
public:

};

class khk9{
private:
    khk8 a; // Şu aşamada yine bir hata vermez lakin, khk8 class'ının default ctor'u private olduğu için yani default
            // ctor init edemediği için khk9'un default ctor'u delete edilmiştir.
    khk9() = default; // Yazsak bile, derleyici default ctor'u delete ederdi.
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*  COPY CONSTRUCTOR
 *
 */

class khk10{
    //....
};

void fcn_004(khk10);        // doğrudan class değer alıyor.

khk10 fcn_005();

int fcn_003(){
    khk10 m1;
    khk10 m2(m1);           // Copy ctor çağırılacak
    khk10 m3{m1};           // Copy ctor çağırılacak
    khk10 m4 = m1;          // Copy ctor çağırılacak

    fcn_004(m1);            // Copy ctor çağırılacak

    khk10 m5 = fcn_005();   // Copy ctor çağırılacak
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// rule of zero: Eger derleyicinin yazacagi yani default edecegi ozel uye fonksiyonlar sizin icin bir engel
// olusturmuyorsa ideali her zaman sınıfın özel üye fonksiyonlarının derleyici tarafindan yazilmasi.

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Derleyicinin yazdigi copy constructor.

class A1{};
class B1{};
class C1{};

class khk11{
    // derleyicinin yazdigi copy constructor
    khk11(const khk11& other) : ax{other.ax}, bx{other.bx}, cx{other.cx}
    {
        // derleyicinin yazdigi copy ctor.
    }

private:
    A1 ax;
    B1 bx;
    C1 cx;

};

// derleyicinin yazdigi default ctor sinifin non-static (constructor zaten static olamaz) public ve inline üye
// fonksiyonudur.

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Date_002 {
public:
    Date_002(int d, int m, int y) : m_day{d}, m_mon{m}, m_year{y}{}
    void print()const
    {
        std::cout << m_day << '.' << m_mon << '.' << m_year << '\n';
    }
private:
    int m_day, m_mon, m_year;
};

int fcn_006(){
    Date_002 today{11,05,2022};
    today.print();

    Date_002 x{today};      // Copy constructor
    x.print();

    // oyle durumlar varki derleyicinin yazacagi ctor bana sorun yaratabiliyr. Boyle durumlarda
    // derleyicinin degil benim yazdigim copy ctor cagirilsin istiyorum.

}

/*
 * Sınıfın veri elemanı bir pointersa ve bu class kopyalanırsa, asıl pointer ve kopyalanan pointer da aynı adrese
 * işaret edip aynı bellek alanını kullanır.
 *
 * 1) Value semantics:
 * 2) Value type: Asagidaki kodda:
 *
 *      int x = 34;
 *      int y = x;
 *      x++; // Bu durumda y'nin degeri degismez. Value semantic bu demek.
 *
 * Class'imizda eger pointer varsa ana class ve copy class da ayni yere isaret etmis olacak. Bu sekilde value semantic
 * saglanmamis olacak. Bundan daha kotusu, dikkat dikkat !! pointerin gosterdigi nesnesin hayati biterse ve copy class
 * kalirsa bu sefer dangling denilen hadise meydana gelir. Gecersiz pointer!!!
 * Oyle bir copy constructor yazmaliyim ki benim yazdigim copy ctor pointer'i kopyalamak yerine pointerin gosterdigi
 * alani kopyalar. Boylece nesnenin ayri bir kaynagi olur.
 *
 * Deep copy : kaynagin kendisini kopyala.
 * shallow copy --> Sığ copy : Kaynagi degil kaynagi gosteren pointeri kopyala.
 */

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class  Sentence {
public:
    Sentence(const char *p) : m_len{std::strlen(p)}, m_p{ static_cast<char *>(std::malloc(m_len + 1))} {
        if (!m_p){
            std::cerr << "bellek yetersiz\n";
            std::exit(EXIT_FAILURE);
        }
        std::strcpy(m_p,p );
    }

    void print()const{
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

int fcn_007(){
    Sentence s1 = "bugun hava cok guzeldi";
    fcn_008(s1); // Buraya s1 nesnesini koplayadik. fcn_008 fonksiyonuna girdi yazdirdi  ve cikarken destructor'a
                    // ugradi. Bunun sonucunda memory free edildi. Bunun yerine copy constructor'u kendim yazmam gerekir
    s1.print();
}

// RAII idiomu :  Resource acquisition is initialization: Kaynak edinimi ilk deger vermeyle olur.
// Bircok sinifta kullanilan idiometrik bir yapi.






























