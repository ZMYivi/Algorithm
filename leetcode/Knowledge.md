# C++一些知识点

## const关键字

1. const修饰普通变量，则该变量不可以在后续被修改值，如果强行修改该变量，通过获取内存地址然后再修改该变量的值，最后输出的还是之前的值，但是在程序运行过程中变量的值会发生变化，因此不要通过这种方式去修改const修饰的变量，会产生奇怪的错误。

2. const修饰指针变量，这类修饰有三种，第一种是修饰指针指向的数值，第二种是修饰指针的内存地址，第三种是即修饰指针指向的内容也修饰指针的地址，下面给出代码。

   ```c++
   // 第一种
   const int *p = 8;
   // 第二种
   int a = 8;
   int* const p = &a;
   *p = 9; // 正确
   int  b = 7;
   p = &b; // 错误
   // 第三种
   int a = 8;
   const int * const  p = &a;
   ```

   可以看出，const放在变量类型前就是修饰的是指向的值，如果放在变量前就是修饰的地址。

3. const参数传递和函数返回值，在参数传递中使用方式有三种，第一种是修饰普通类型的参数，因为传参本来就会产生一个临时变量，这种使用没有什么意义，第二种是修饰指针，这种情况是防止指针被意外的篡改，第三种是修饰自定义类型参数，因为这类传参的时候，会进行一个临时对象的构造，比较浪费时间，因此如果要传递自定义类型的数据的时候，可以使用const修饰引用传递的方法，下面给出代码。

   ```c++
   // 第一种
   #include<iostream>
    
   using namespace std;
    
   void Cpf(const int a)
   {
       cout<<a;
       // ++a;  是错误的，a 不能被改变
   }
    
   int main(void)
    
   {
       Cpf(8);
       system("pause");
       return 0;
   }
   
   // 第二种
   #include<iostream>
    
   using namespace std;
    
   void Cpf(int *const a)
   {
       cout<<*a<<" ";
       *a = 9;
   }
    
   int main(void)
   {
       int a = 8;
       Cpf(&a);
       cout<<a; // a 为 9
       system("pause");
       return 0;
   }
   
   // 第三种
   #include<iostream>
    
   using namespace std;
    
   class Test
   {
   public:
       Test(){}
       Test(int _m):_cm(_m){}
       int get_cm()const
       {
          return _cm;
       }
    
   private:
       int _cm;
   };
    
    
    
   void Cmf(const Test& _tt)
   {
       cout<<_tt.get_cm();
   }
    
   int main(void)
   {
       Test t(8);
       Cmf(t);
       system("pause");
       return 0;
   }
   ```

   

