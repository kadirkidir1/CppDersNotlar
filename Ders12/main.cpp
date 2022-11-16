#include <iostream>

/*
 Bir class'ı default etmemizin nedeni var. Şu an için girmiyoruz ama Default yerine içi boş bırakmakla,
 aşağıdaki gibi default etmek arasında, bazı özellikleri kullanmak bakımından farklılıklar var.
 Myclass()= default;
 */

/*
    struct x{
        x() {}          // user-declared
        x();            // user-declared
        x() = default;  // user-declared
        x() = delete;   // user-declared
    };
 */

///////////////////////////////////////////////////////////////////////////////////////////////////////

void func0(double);
void func0(int) = delete;

int main0() {
    //func0(12); // bunu cagirmam hatadir cunku FOR sürecinde(function overloading Resolution) int parametreli
    // deger secilir ama delete edildigi icin syntax hatasi verir.
    return 0;
}



///////////////////////////////////////////////////////////////////////////////////////////////////////

class kdr0{
public:
    kdr0();                 //
    kdr0(const kdr0&);      //copy ctor
    kdr0(kdr0&&);
};
void func10(kdr0);

int main1() {
    kdr0 kx;

    func10(kx);   // copy ctor cagirilacak cunku sol taraf degeri.

    func10(kdr0{});   // bu durumda rvalue oldugundan move ctor cagirilacak.

    // eger move ctor yazilmasaydi ama yukaridaki fonksiyon tekrar cagirilsaydi rValue olan, copy
    // ctor cagirilirdi cunku (cont t&) sol tarafa da baglanabilir bir sag taraf degerine de baglanabilir.
    // Yani bir sinifin hem copy ctor'u hem move ctor'u varsa bir sinif nesnesine ilk deger vermek icin
    // rValue kullanirsam move ctor, lValue kullanirsam copy ctor. Ayni sey atama durumu icin de gecerli.
    //
}

///////////////////////////////////////////////////////////////////////////////////////////////////////

class kdr1{
public:
    kdr1(int); // bu sinifin default ctor'unun drumu not declared. Yani yok. Ama sinifin diger 5 ozel
                // uye fonksiyonu implicitly declared.
};

////////////////////////////////////////////////////////////////////////////////////////////////////

// eger siz sinif icin bir destructor bildirirseniz ama diger hicbir ozel uye fonksiyonu bildirmezseniz
// ctor'u derleyici default ediyor. Sinifin copy ctor'u da implicitly declared.

class kdr2{
public:
    // kdr2();     // implicitly declared.
    ~kdr2();
    // kdr2(const kdr2&); // implicitly declared
    kdr2(const kdr2&&);
    //eger sinifa dtor bildirirseniz derleyici default, copy constructor ve copy assignment'i implicitly declared ediyor.
    // ama move member'lar not declared. Ama burada default copy constructor ve copy assignment'i bu sekilde
    // yani default olarak kullanma, basina is acabilir tehlikeli.

};

/*
 eger siz k-copy ctor bildirirseniz yani gittiniz bir sinifa copy ctor yazdiniz.

 */
    // copy ctor bildirsem dahi default ctor olmayacak. Cunku bir ctor yazdigimde derleyici
    //default ctor yazmiyor.ama destructor derleyici tarafindan bildirilecek. Implicitly declared.
    // copy assignment'i yine implicitly declared ama move member'ları yine not declared.
    // Ama copy ctor bildiriyorsanız mutlaka mutlaka mutlaka copy assignment'ı bildirmelisiniz.
class kdr3{
    kdr3(const kdr3&);
};

// Copy assignment user declared ise derleyici default ctor'u yazar, destructor'u yazar,
// copy ctor'u declared eder yani kullanmamalıyız.

// eger destructor ,copy ctor ya da copy assingment bildirseniz dahi sinifin move member'lari default
// edilmemis olur

// eger move ctor bilgirirseniz, move member'lardan herhangi birini bildirirseniz derleyici copy
// member'ları delete ediyor. Default ctor'u bildirmeyecek, desructor'u ve move assign'ı not declared
// edecek.

// eger sinifiniz icin move member'lardan birini bildirirseniz derleyici copy member'lari delete eder.
// bu su anlama geliyor move member'ların olmasini ama copy member'ların da olmasını derleyici tarafından
// yazılmasını istiyorsanız move memberları bildirdiginiz anda copy member'ların default edilmesini
// ayrica ozellikle kendiniz bildirmeniz gerekiyor.

class kdr4{
public:
    kdr4();

    kdr4(kdr4&&);   //  move ctor yazdigim anda copy memberlar deleted. yani copy member'lari bildir
                    // mezsem derleyici bunlari deleted biliyor.
                    // kdr4(const kdr4&) = delete; gibi davraniyor.


};

// bazi siniflar hem copyable hem moveable
// bazi siniflar non-copyable ama moveable -- kopyayalanamaz syntax hatası olur ama taşınabilir.
// bazi siniflar non copyable ve non moveable -- ne kopyalaniyor ne de tasinabiliyor.

//

#include <memory>
#include <mutex>

int main3(){
    using namespace std;
    unique_ptr<int> uptr1{new int};
    unique_ptr<int> uptr2{uptr1};       // syntax hatasi cunku bu sinif non-copyable
    unique_ptr<int> uptr2{std::move(uptr1)}; // move ctor cagirildi ama copy ctor cagirilamadi.

    mutex mx;
    mutex my = mx;  // mutex nesneleri kopyalanamaz.
    mutex mz = move(mx); // tasinmasi da syntax hatasi.
    // mutexler non copyable and non moveable.

}

////////////////////////////////////////////////////////////////////////////////////////////////////

class myc{
public:
    myc();
    myc(myc&&);     //move ctor
    myc& operator=(myc&&); // move assgnm
};

int f_myc(){
    myc m1,m2;

    m1 = m2; // syntax hatasi cunku move member'lardan herhangi birisi taninirsa copy member'lar
             // derleyici tarafindan delete edilir.

    m1 = std::move(m2);   // legal
    // yine de yazilimcilar burada deleted olmasini gormek icin, derleyici delete etse bile
    // user-declared delete ediyor. Asagidaki  gibi.
}

class myc1{
public:
    myc1();
    myc1(const myc1&) = delete; // copy ctor
    myc1& operator=(const myc1&) = delete; // copy assng
    myc1(myc1&&);     //move ctor
    myc1& operator=(myc1&&); // move assgnm
};

// Eger bir fonksiyonun geri dönüş değeri bir sinif turundense  ve bu fonksiyon icerisinde otomatik omurlu
// bir sinif olusturursaniz bu fonksiyonunuzun geri donus degeri bu otomatik omurlu nesne olursa bu durumda
// tasima semantigi yine devreye giriyor. Yani normalde soyle dusunebilirsiniz "return edilen deger bir lValue
// expression olduguna gore" kopyalama yapilacak.

myc1 func()
{
    myc1 m;
    /// code here

    return m;
}

int asd1(){
    myc1 m1;
    m1 = func();    // burada geri donus degerinin copy ctor oldugunu dusunebilirsiniz ama dilin kurallarina gore
                    // otomatik omurlu bir nesne return edildiginde burada yine tasima semantigi devreye giriyo.
                    // fonksiyonun return ettigi deger lValue exp olmasina ragmen lValue exp, xValue exp'e donus-
                    // turuluyor. Bu, dilin ozel bir kuralı. Ve tasima semantigi devreye giriyor.
                    // eger class Moveable degilse copy ctor ile islem gerceklestirilir.
}

////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 Dinamik omurlu nesneler biz istedigimiz zaman hayara baslatabildigimiz biz istedigimiz zaman da hayatlarını
 bitirebildigimiz nesneler. Dinamik nesnelerin storage'ları tipik olarak programın calisma zamanında elde ediliyor.

 Dinamik omurlu nesneler programcının diledigi noktada hayatlarını baslatabilecegi, diledigi noktada hayatlarını
 bitirebilecegi nesneler. Ve bu nesneler olarak tipik oalrak programın calisma zamanında bir bellek alani
 tahsis ediliyor.

 a) maliyetleri tipik olarak çok daha fazla. Bu nesnelerin storage'ları programın calisma zamanında elde ediliyor.
    default kullanacagimiz bir sey degil, lazim degilsen mecbur olmadikca kullanma.
 b) kodlama hatasi riski otomatik omurlu nesnelere gore 50-100 kat daha fazladir.
 c) kodun okunmasi ve yazilmasi daha zor.


 hayata gelecek nesne sayisi programin calisma zamaninda belli olacaksa burada dinamik omurlu nesne mecburen
 kullanilir. Ya da hayata gelecek nesnenin turunun programin calisma zamaninda belli olmasi.

 Dinamik omurlu nesneler (New) operatorleriyle hayata gelir.
    "     "       "     delete operatorleriyle hayatı sonlandirilir.

 Birden fazla new ve delete operatoru var.

 new myc1;          // default init
 new int
 new std::string

 new myc1();        // Value init
 new myc1{};        // Value init
 new myc1(x,y,z)
 new myc1{x,y,z}
 */

// Dikkat new ifadesi bir adres uretir. Uretilen adres hayata gelen nesnenin adresidir.
// Yani new Myclass yazdigimizda bu ifadenin turu Myclass *'dır. Burada pointer semantigi kullaniliyor.

int asd2(){
    myc1* p{new myc1};
    // Dinamik olarak olusturdugum myc1 class'inin adresini myc1* turunden p pointeri tutacak.
    // Burada referans kullanamaz miyim? Tabiki kullanabilirim ortada bir sol taraf degeri varsa bir referans
    // kullanbilirim amaaaa bu durumda refransinizin Myclass& olmasi icin ona dinamik omurlu degerin kendisiyle
    // referans verebilirisniiz. Yani asagidaki gibi.

    myc1 &r = *new myc1;    // bu da cok yaygin bir kullanim bicim degil.
    // genelde raw pointer'larla isliyoruz.

    auto y = new myc1;      // burada y'nin turu myc1*'dir.
    auto *p2 = new myc1;    // bu da yaygin bir kullanim. Syntax hatasi yok tabiki.

    delete p;               // bu sekilde hayatini sonlandiriyoruz ama bu kadar basit degil!!!
    delete &r;
    delete y;

}

// pointer like class // kendisi pointer degil ama pointer gibi davraniyor???
// mmesela iterator siniflari boyle
// pointer-like class'larin interface'lerinin olusturulmasinda agirlikli olarak operator overloading kullanilir.
// gercek pointerlara C++'ta "raw pointer" deniyor. Bazene de "naked pointer"

////////////////////////////////////////////////////////////////////////////////////////////////////

// void* operator new(std::size_t)
// new cagirdigimizda aslinda yukaridaki fonksiyon cagiriliyor. Yani C'deki malloc ile tamamen ayni.
// neden malloc yerine derleyici bu fonksiyonu cagiriyor??
// Malloc'la aradaki buyuk fark su malloc basarisiz olursa nullptr donduruyor ama operator new fonksiyonu
// basarisiz olursa exception throw ediyor.
// exception konusunu yakin zamanda detayli olarak gorecegiz.
// derleyici new ifadesi karsiligi once standart kutuphanesinin operator new fonksiyonunu cagirir.
// void* operator new(std::size_t)
// derleyici cagirdigi operator new fonksiyonuna sinif turunun sizeof degerini gonderir.
// cagirilan bu fonksiyon parametresine katarilan buyuklukte bir bellek alanini allocate edemezse
// bu durumda exception throw ediyor.
int asd3(){
    auto p1 = new myc1;

    /*
        auto p = (Myc1 *)(operator new(sizeof(myc1))
        p->myc1
     */
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

class Myclass1{
public:
    Myclass1(){
        std::cout << "Myclass () this : "<< this << "\n";

    }

    ~Myclass1(){
        std::cout << "Myclass () this : "<< this << "\n";
    // normalde program bitisinde destructor cagirilirdi ama dinamik omurlu nesnelerde destructpr
    // cagirabilmesi icin delete operatoruyle cagirilmasi gerekir.
    }
};

int main_3(){
    auto p1 = new Myclass1;
    std::cout << "p1 = " << p1 << "\n";
    // Burada goruyoruzki p1, nesnenin this pointer'i
}

// dikkat eger hayata getirdiginiz dinamik omurlu nesneyi delete etmezseniz su iki sonucu olusturmus olursunuz.
// 1) dinamik omurlu sinif nesnesinin destructor'u cagirilmaz.
// 2) operator new fonksiyonu ile elde edilmis sizeof(Myclass) buyuklugundeki bellek blogu deaollocate edilmez.

/*
 Mulakatta soruyorlar. Ben new operatoruyle bir nesne olusturdum ama bunu delete etmedim ne olıur.
 ilk verilen cevap memory leak cevabıdır. Bu cevap yarım dogru. yani tam dogru degil. Dolayisiyla
 yanlis. Neden???
 arkadaslar. memory leak olusmasi sadece sonuclardan bir tanesi cunlu dilin kurallari diyorki operator new ile
 elde edilen bu bellek blogunun geri veirlmesi icin delete edilmesi gerekiyor dolayısıyla siz delete operatorunu
 kullanmadiginiz zaman bu bellek alani geri verilmemis oluyor. Bu problemin yalnızca bir kismi. Asil problem olan ise
 delete etmediginizde nesneyi destructor da cagirilmiyor. peki bu onemli mi? ya bu kaynak kullanan bir sinif
 nesnesiyse? Constructor'i ile kaynak edinip destructor'i ile geri veriyorsa??? Bu bir RAII nesnesiyle destructor'in
 geri cagirilmamasi demek, kaynaklarin geri verilmemesi demek. o yuzden sorumuzun cevabi su olmali.

 a) destructor'i cagirilmadigi icin resource leak olur ya da olabilir. ( eger resource kullaniliyorsa / kaynak sizintisi )
 b) mutlaka memory leak olur.

 */

int main_4(){
    auto p1 = new Myclass1;
    std::cout << "p1 = " << p1 << "\n";
    // Burada goruyoruzki p1, nesnenin this pointer'i

    delete p1;
    // derleyici delete operatoru karsiligi nasil bir kod uretiyor?

    p->~Myclass1;
    void operator delete(void *vp);   //
}

// new ile operator new birbirine karistirilmamali.
// new bir operator ama operator new bir fonksiyon.

// new operatoru ve delete operatoru karsiligi ne yaptigini degistiremezsiniz.
// operator new ve operator delete overload edilebilir.
#include <cstdlib>
void *operator new(std::size_t n)
{
    // bu fonksiyon operator new fonksiyonunun overload'udur. Genel itibariyle operator new ile
    // benzer islemleri yapsa da profesyonel manada aynı degildir ve bilinmesi gereken baska seyler de vardir.
    std::cout << "operator new called! n = " << n << "\n";
    void* vp = std::malloc(n);
    if (vp == nullptr){
        throw std::bad_alloc{};
    }
    std::cout << "the address of allocated block is : " << vp << "\n";

    return vp;
}

void operator delete(void* vptr){
    std::cout << "operator delete called!! vptr = " << vptr << "\n";
    std::cout << "the memory block at the address of " << vptr << "is deallocated \n";
    free(vptr);
}

class myc2{
public:
    myc2() {
        std::cout << "Myc2 default ctor this : " << this << "\n";
    }
    ~myc2() {
        std::cout << "Myc2 destructor this : " << this << "\n";
    }
private:
    unsigned char m_buf[1024]{};
};

int main14()
{
    std::cout << "sizeof(myc2) = " << sizeof(myc2) << "\n";

    auto p = new myc2;  // bu fonksiyonu cagirdigim an yukarida kendi yazmis oldugum operator new fonksiyonu
                        // cagirilacak.
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// birden fazla new ve delete operatoru var.
// birde array new isimli new operatoru var.


int asd33(){
    std::cout << " kac elemanli bir dizi";
    int n;

    std::cin >> n;
    myc2* p = new myc2[n];
    // burada yalin delete operatorunu kullanirsam tanimsiz davranis. Yani yalniz basina
    // delete p; deyip gecemem.

    delete[]p;  // koseli parantez icerisine herhangi bir sey yazmiyoruz. dinamik array'ler bu sekilde silinir.

}



















