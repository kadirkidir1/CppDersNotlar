#include <iostream>
// 13 nisan 2022

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}

/*
 * Function overloading işlemi varsa hangi function'un şeçileceği olayına Function Overloading Resuliotion denir.
 * 2 farklı durumda hata olabilir, 1.si no match hatası. Hiçbiri viable olmayan durum.
 * 2. syntax hatası ise 2 ya da daha fazla uygun function varsa(viable) derleyicinin uygunları içerisinden en iyisi seçmesi
 * gerekiyor fakat dilin kuralları bir seçilebilrlik kriteri belirleyemediği için syntax hatası oluşur. Ambiguaty error.
 */


/*
  void func(const int&);        lValue bir değer çağırılırsa alttaki viable olmadığından bu çağırılacak.
  void func(int &&);            rValue bir değer çağırılırsa bu çalışacak.
 */

/*
void func(int&)
{
    std::cout << '0';
}

 void func(const int&)
{
    std::cout << '1';
}

void func(int&&)
{
    std::cout << '2';
}

 Yukarıda 3 adet FO vardır.

 1. durum
 int x = 20;
 func(x); --> 0 // sol değer referansı olduğundan 3.sü viable değil. Const overloading'e girdiğinden 0 yazdıracak.

 2. durum
 const int y = 20;
 func(y); --> 1 // sol değer referansı olduğundan 3.sü viable değil. Const overloading'e girdiğinden 1 yazdıracak.

 func(34); //rValue olduğundan 3.sü çağırılacak.

 */

/*
  void func(const double&);
  void func(double &&);

  int main(){
      int x{};
      func((double)x);      --> 2. f çağırılır. Tür değiştirme operatörüyle değiştirilen bir ifade hdef tür referans türü
                                değilse prValue türüdür. O yüzden 2. fonksiyon çağırılır.
  }
 */

/*
   endl bir ostream manipülatördür.
 */

/*
 windows harici farklı platformlarda aşağıdaki işlemi yaptığımızı düşünelim.

 int x{324};
 std::cout << x; // Bazen yazmayabilir. Çünkü biz bunu std output'un buffer'ına yazıyoruz. Bunun konsol ekranında çalışması
 için flush'lanması gerekir.
 */

 /* Type Cast Operators ( Tür değiştirme operatörleri
  * enum /enum classes
  */

 // implicit --> Örtülü, gizli. Açıkça kod yazmadan dilin kuralarına güvenerek derleyicinin kendisi yapması.
 // double bir değeri int'e atarsak otomatik bir değişim gerçekleşir. Bu implicit'e örnektir.
 // explicit --> Açıkça, belirterek.
 // C'de bir tane tür dönüştürme operatörü var.
 // C++ bu değişimi kapsamakla birlikte, temiz bir kodda C dönüştürme işlemi kullanılmamalıdır.
 /*
  * 1 Static Cast
  * 2 Const Cast
  * 3 reinterpret_cast
  * -----------------------
  * 4 dynamic cast --> Kalıtımla ilgili. İleride girilecek.
  */

 /*
 // Dikkat. Kendisi cost olan bir nesneyi const olmayan bir nesne gibi kullanmayın. UB'dir.
  *
  * const int x{324};
  * int* ip = (int*)&x;
  * *ip = 456;
  * Direkt olarak UB'dir. Syntax'ı aşar ama tanımsız davranış.
  */

 /*
 char * Strchr(const char* p,int c)
  {} --> Neden const. Çünkü aldığım adresteki verileri değiştirmeyeceğimi tahattüt ediyorum.
  */

  /*
   * Hangi türlerden olursa olsun onu char'dan oluşan bir dizi olarak kullanabilirsiniz bu UB değildir.
   *
   * int main(){
   * int x = 235455;
   * char *p = &x;
   * }
   * Yukarıdaki kod C++'ta error iken C'de legal ama warning verir.
   *
   */

  /*
   * int x = 0x1ac4d200;
   * void* vp = x; --> Cpp'de error ama C'de yine legal. Ama şu şekilde yazarsak
   * void* vp = (void *)x; --> Ben bunun tamsayı olduğunu biliyorum ama ben bunun bitlerini adres olarak kullanmak istiyorum.
   */

  // Temiz kodlamanın en temel ilkelerinden biri niyetinizi belli edeceksiniz. Niyetini belli etmeyen insanlardan da korkun. (Necati ergin joke)

  /*
   *  tür dönüşümleri potansiyel kodlama hatalarıdır. Tür dönüşümlerini 0'a düşürmekte fayda var. fakat ne niyetle yaptığımıza
   *  bağlı olarak risk değişebiliyor.
   */

  /* reinterpret_cast: Açıklama değil, ama bir hata arıyoruz. Tür döönüşümlerine bakalım dedim. Eğer reinterpret ise dönüşümleri
   * çok daha hızlı kontrol ederiz. Yok değil ise parantez operatörleriyle dönüşüm sağlanmışsa o zaman sıkıntı var demektir. Araki bulasın.
   */

  /* <> angular bracket
   * static_cast<int>(dval) --> parantezler syntax parantezi.
   * static_cast<int> dval --> böyle dediğimizde syntax hatası olmuş olur.
   * sizeof(x) // buradaki parantezler öncelik parantezi. Yani -- sizeof x olarak da kullanabiliriz.
   * sizeof(int) // burada öncelik parantezi değil, syntax parantezi
   *
   * C'de yazdığımız dönüşümler için ya da veri kaybına yol açan ama niyetli olarak yapılmış dönüşümlerde kesinlikle static cast kullanacağız.
   *
   * int main(){
   *    int x = 10;
   *    int y = 20;
   *
   *    double d1 = x/y; // bölme int türünde yapılacağından 0 olur.
   *    AMA
   *    double d2 = static_cast<double>(x)/y; // Burada dönüşüm işlem sırasında yapılıyor.
   *
   */

  /*
   double foo();
   int main(){
   double dval = foo();
   int ival = dval; // burada bir syntax hatası yok. Ama Double değer int sınırlarını aşıyorsa UB'dir. Aşmıyorsa ondalık kısım kaybedilir.
                    // Ancak yüzde yüz eminseniz bu şekilde bir dönüşüm yapılmalı.
   int kval = { dval }; // böyle yapılırsa syntax hatası.

   // C++'ta ise yapmam gereken işlem static cast işlemidir.
   int ival = static_cast<int>(dval);
   }
   */

  /*
    int main(){
        int x = 10;
        void* vp = &x;

        int *ip = vp; // C'de legal. C++'ta syntax hatası çünkü C++'ta int* türünden void* türüne dönüş yok!

        int* ip = static_cast<int*>(vp); // Bu şekilde yapılmalı. Cpp'de bu legal.
    }
   */


  /*
   enum color{red,blue,green};

   int main(){
   int ival = 2;
   ///
   color c = ival; // C++'ta syntax hatası.  Tersi durumda hata yok, enumdan inte otomatik dönüşüm var, Cpp'nin gençlik günahlarından bir tanesi.

   color c = static_cast<color>(ival);
   */

  /*
   // Enum türünden enum türüne dönüşürürken de static cast ile dönüştürme yapmalı. Otomatik dönüşüm yok!!!
   enum Color{red,blue,green};
   enum Kdr{alpha,beta,gamma};

   int main(){
   Color c = blue;
   ///
   Kdr asd = blue; // Bu syntax hatasıdır. Bu şekilde yapabilmek için!
   Kdr asd = static_cast<Color>(blue); // Bu şekilde yapmak gerekir.

   Color red;
   ++red; // bir arttırıyoruz. C'de, red iken blue oluyor.
   Ama Cpp'de enum türünden değişkenler ++, -- operatörlerine syntax hatası.
   Ayrıca Cpp'de bool türünden ifadeler de matematiksel ifadelere C++20 güncellemesiyle kaldırıldı
   */


  /*
   //Const cast = Ben senin const'luğunu tanımıyorum demektir açıkça.

   int main(){
   int x = 10;
   const int *p = &x;
   // İnt x const değil aslında.

   int* ptr = p; // C++'ta syntax hatası. Bunu gidermek için C'deki dönüşüm operatörü tercih edilebir ama tavsiye edilmez.
   int* ptr = (int*)p; // Hata vermez ama tavsiye edilmez. C++'ın kendine özgü türleriyle değişim yapmak daha mantıklıdır.

   int* ptr = const_cast<int*>(p); // eğer bu işlemi static_cast veya başka cast'le yapmaya kalksaydık sytnax hatası.

   // fiziksel olarak cost olması, değşkenin top level cost olması demek. Yani
   const int x = 20; --> top level const'tur.

   int y = 20;
   const int* p= &y; --> top level const değil.

   const int k = 30;
   int *ptr = const_cast<int*>(&k); // Buraya kadar hata yok.

   ++* p; // Ama set amaçlı kullanırsak UB olur.
   // const_cast const'luğu ve volatile'lığı kaldırıyor. Volatile için ayrı bir dönüştürme yok. Const_cast ile yapmamız gerekiyor.
   // Volatile'ı kaldırmak çok riskli bir işlemdir genelde.
   }

   */

  /*
  int main(){
      // Diyelim ki bir dosyamız var ve formatlı değil. Binary file.
      // C'nin standart kütüphanesinde formatsız veri yazmak için fwrite kullanılır.
      using namespace std;
      ifstream ifs{"enc.dat",ios::binary}
      if (!ifs)
      {
        cerr << "cannot open file\n";
        return 1;
        }

        // C'de olsaydı
        // double dval;
        // FILE *f = fopen("enc.dat",rb);
        // if(!f) {
        // fprintf(stderr,"dpsya acilamadi\n";


        ifs.read(&dval); // syntax hatası çünkü read fonksiyona char* bekliyor. Dönüşüm yapmamız gerekir.
        while(ifs.read(reinterpret_cast<char *>(&dval), sizeof(dval)));
        //reinterpret_cast

  }
   */

  /*
   int main(){
    using namespace std;
    int ival{};
    const int* iptr = &ival;
    char* cp = reinterpret_cast<char*>(iptr); // bu şekilde yapamayız çünkü burada const_cast de yapmak gerekir.
    char* cp = reinterpret_cast<char*>(const_cast<int*>(iptr)); // Bu şekilde olabilir. Legaldir. Ya da şöyle olabilir

    char* cp = const_cast<char*>(reinterprest_cast<const char *>(iptr)); // Bu şekilde de olabilir.
    // Bazen kod kalabılığı daha güvenli olabiliyor. C'de daha kolay olmasına rağmen burada daha güvenli.
   }
   */

  /*
   // Void türüne dönüşümde eski tip dönüşüm kullanılır.
   a) Derleyicinin uyarı mesajını kesiyor.
   b) okuyucuya da geri dönüş değerini kullanmadığımı gösteriyorum.
   // [[nodiscard]] attribute'dür. Fonksiyonun geri dönüş değerini kullanmak lojik bir zorunluluksa mutlaka fonksiyonun
   // geri dönüş değerinin öncesinde [[nodiscard]] attribute'ünü kulanın. Modern C++ ile eklendiler.

   int foo();

   int main()
   {
    foo(); // Bu şekilde çağırdığımızda geri dönüş değeri vermememize rağmen program bir hata vermez. Ama NoDiscard Attribute'ü
            // ile tanımlarsam fonksiyonu warning verecektir.
   }

   */

  /*
  [[nodiscard]]
  int foo();
  int main(){
      foo();        // Şimdi warning verecektir. Çünkü nodiscard ile tanımladık.
  }
   */

  /*
   // Modern C++ ile dile eklenen araçlardan biri bazı fonksiyonların
   // a) Default edilmesi
   // b) Bir fonksiyonun delete edilmesi. Sınıflarla ilgili. Dinamik ömürlü nesnelerle karşılaştırmayalım. Overload çünkü.

   void func(int) = delete;  // delete edilmiş fonksiyon.
   // bu fonksiyon var fakat eğer bu fonkfisyona çağrı yapılırsa durumu syntax hatası olarak değerlendir.
   // delete edilmiş fonksiyonlar var ve function Overload resolution'a katılır.

   void func(double);
   void func(int);
   void func(long) = delete;

   int main()
   {
    // func(1.2); Double kazanacak.
    // func(1.2f); float'tan double'a promotion olduğu için yine double kazanacaktı.
    // func(10L); Long parametre kazanacak ve delete edildiğinden derleyici syntax hatası verecek.
    // delete'in tek nedeni bu değil. Asıl olarak class'larda kullanılıyor.
   }
   */

  /*
   * öyle bir fonksiyon olsun ki sadece int ile çağırılabilsin.
   void func(int);
   template <typename T>
   void func(T) = delete; // Bu şekilde yapılırsa yalnızca int ile çağırılır. Ama işi kolaylaştırdılar. C++23 ile geldi. Really

   void func(really int); // Bu fonksiyonun parametresi sadece int parametre kabul eder başka bir şey kabul etmez ama C++23

   */

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////ENUMARATION////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   // C++'ta aritmetik türlerden enum türlerine dönüşüm yok. Yani implicit dönüşüm yok. Bilerek isteyerek yapılıyorsa static_Cast yapılmalı.

   /*
     enum Color { red, blue, green};
     int main()
     {
        Color mycolor{blue};
        mycolor = 1; // syntax hatası. İster sabit olsun ister değişken olsun.
        int ival{2};
        mycolor = static_cast<Color>(ival); // Doğru  kullanım bu şekilde olmalı.
     }
    */
   /*
    //C++'ın gençlik hatalarından bir tanesi ise, enum türlerinden int türüne dönüşüm olmaı.

    enum Color { red, blue, green};
    int main()
    {
        Color mycolor{blue};
        int ival;
        ival = mycolor; // Kesinlikle legal. Riskli olduğu için dile enum class eklendi.
    }
    */

   /*
   // Modern C++'tan önce de enumların _type'ı int olmak zorunda değil. Fakat C'de _type int olmak zorunda.
   // C'de sizeof(enum) == sizeof(int) iken fakat C++'ta int olma zorunluluğu yok.

   // enum Color{red, Blue = 987247823468723u, green}; // Burada int olmak zorunda değil, tipine kendini belirleyerek verir.
   // C++'ta ayrıca Color ile tanımlama yapabilirim. C'de yapamıyordum.
   //
    */

   /*
    enum Color {red, blue, green};

    int main(){
        auto x = red;
    */

   /*
    // Enumların ayrı bir scope'u yok. Türün scope'u neyse o.
    // Peki bu nerede hata olabiliyor. Birden fazla Enum parametrelerinin aynı kodda kullanılması ihtimali
    // çok yüksek. Bu durumda eğer aynı isim alanı içinde bu numaralandırma türleri bildiilirse, ve aynı
    // isimdelerse direkt olarak sytnax hatası olacak.

    #include screen.h
    enum ScreenColor{red, mag,brown}; --> Screen.h'dan geldi.

    #include traffic.h
    enum TrafficLight{red, yellow,green}; --> 2 tane red aynı scope'ta olduğu için isim çakışması oldu ve syntax hatası verecek.

    // C tarzı önlem. Daha fazla niteleyin.
    // C++'ta class scope içerisine almak.
    // Birde namescpace içerisine almak.
    // Modern C++'ta ne değişti.
    // 1) Artık geleneksel enum türleri yerine scoped enum kullanılıyor. Kapsamlandırılmış enum. Numaralandırma sabitlerinin
    // aynı scope var.
    // enum class not a class.
    // 2. Geleneksel enumlara, unscoped enum, traditional enum conversional enum deniyor. Bunlara da _type belirtme syntaxı
    // getirildi. Şöyle yazabiliriz.
    enum Color : unsigned int {red, blue, green}; // : atomundan sonra gelen tür _type seçeneğimiz. Ama tamsayı olmak zorunda.
    // Neden böyle kullanmak isteriz.
    // 1. Numalandırma türlerimiz küçükse, tasarruf etmek isteniyorsa küçük boyutla cast edilebilir.
    // Ama en önemli nedeni forward decleration'dur.
    enum Color : unsigned char; // Derleyici artık unsigned char olduğunu biliyor ve tanımlamaya kızmayacak.
    // Enum türlerinden diğer türlerine dönüşüm var mı? Var. Gelenekselde.

    */

   /*
    enum class Color {red, blue,green};// istersek _type da belirtebiliriz. : unsigned char gibi.
    enum class TF_Light {red, blue,green};
    enum class Other_Things {red, blue,green};
    // Ne değişti? Numaralandırma sabitlerinin ayrı scope'ları var.

    int main(){
        // auto c = red; // yazdığımızda derleyici red'i bulamayacak. Red ismi global scope'ta değil.
        auto c = Color::red; // Bu şekilde kullandığımda derleyici bunu tanıyacak.
        // Enum Class'ların bir diğer özelliği de aritmetik türlere artık otomatik dönüşüm yok.
    }
    */

   /*
    enum Color {red, blue, green};
    enum class Colorex {red, blue, green};

    int main()
    {
        Color mycolor{red};
        Colorex mycolorex{Colorox::red};
        int ival = mycolor; // Bunda bir error yok. Cpp'nin gençlik hatası.

        int ival2 = mycolorex; // Bu syntax hatası. Bunu çevirmek için static_cast yapmalıyız.
        int ival2 = static_cast<int>(mycolorex);


    }
    */

   /*
    enum class color{red, blue, green};

    int main(){
    const char* const pcolors[] = {"red","blue","green"}; // Enum değeriyle rengi string olarak görmek istiyorum diyelim.
    Color mycolor;

    // pcolors[mycolor]; // Syntax hatasıdır. Çünkü static cast gerekir.
    pcolors[static_cast<int>(mycolor)];
    }
    */

   // Using Enum bildirimi C++20 ile geldi.

   /*
    enum class color{red, blue, green};

    void func()
    {
     using enum Color; // böyle kullanılıyor. using enum class değil!!!
     auto c1 = red;
     auto c2 = blue;
    }
    */

    /*
     namespace neco {
        enum class color{red, blue, green}; }

     void func()
     {
      using enum neco::Color; // böyle kullanılıyor.
      auto c1 = red;
      auto c2 = blue;
     }
     */

/*
 * Eğer enum içerisinde her şeyi değil de belli başları kullanmak istersek aşağıdaki gibi yapmak gerekir.
 enum class color{red, blue, green};

 void func()
 {
  using Color::blue; // böyle kullanılıyor.
  auto c2 = blue;
  auto c1 = green; // syntax hatası
 }
 */

/*
 enum color{red, blue, green};
 int main(){
    auto c = Color::red; // bu şekilde kullanım, kapsamlandırdığımız anlamına gelmiyor. Daha çok template kodlarla ilgili.
 }
 */

// name lookup --> İsim arama demek.
// x = 55; --> burada x'in isim olduğunu biliyor. Hangi varlığa karşılık geldiğini bilmesi gerekiyor. Derleyicinin
// hangi ismi neyin yerine koyacağını ve bunu arama sürecine name lookup deniyor. Önce name lookup yapılır sonra contex kontrolü
// yapılır.
// C++'ta istisna olmadan bir ismin aranıp bulanamaması syntax hatasıdır.

///////
/*
 #include <cstdio>

 int main(){
    printf = 10; // Bu şekilde bir kullanım hatalıdır ama name lookup hatası değil. printf'in kullanım hatası. Ama!
 }

 ///////////////////////////////////
 int main(){
    int printf;
    printf = 10; // Bu şekilde bir kullanım hatalı değildir. Printf name lookup tarafından bulunmuştur.
    printf("KADIR"); // --> şimdi de bu syntax hatası oldu.
 }

 */

/*
 * 1 Name Lookup
 * 2 Context
 * 3 Access kontrolü.
 */

/*
 * bir isim eğer nitelenmişse, qualified name.
    :: --> scope resolution operator

    ::x --> bu ismin kullanıldığı namescope içerisinde aranacak.
 */

/*
 int foo();

 int main(){
 int foo = 6; // Syntax hatasıdır. Ama
 ::foo(); // syntax hatası değildir çünkü SRO ile globalde aranacağı bildirilmiş.
 }
 */

/*
 int x = 10;
 int main()
 {
    int x = 45;
    x += ::x; // tamamen legal.
 }

 */




































