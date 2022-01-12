# 项目名称 / 文档作者
项目名称：书店管理系统

文档作者：黄健浩


- # 程序功能概述
对于不同用户（未登录用户、顾客、店员、店长）提供相应的功能，具体来说：
- ## 账户系统
> 0. 未登录用户：登录其他已注册的账户、注册顾客账户。
> 1. 顾客：未登录用户可以使用的所有功能、注销当前登录的账户、修改指定账户的密码（需要输入旧密码）、检索图书。
> 2. 店员：顾客可以使用的所有功能、创建权限低于自己的账户。
> 3. 店长：店员可以使用的所有功能、删除账户、修改指定账户的密码（无需输入旧密码）。
- ## 图书系统
> 1. 顾客：检索图书、购买图书。
> 2. 店员：顾客可以使用的所有功能、修改图书信息、图书进货。
> 3. 店长：店员可以使用的所有功能。

- ## 日志系统
> 2. 店员：生成员工自己的操作记录
> 3. 店长：店员可以使用的所有功能、查询财务记录、生成财务记录报告、生成全体员工工作情况报告、生成日志。

具体来说如下所示
```css
    # 基础指令
    quit
    exit
    
    # 账户系统指令
    su [User-ID] ([Password])?
    logout
    register [User-ID] [Password] [User-Name]
    passwd [User-ID] ([Old-Password])? [New-Password]
    useradd [User-ID] [Password] [Priority] [User-Name]
    delete [User-ID]
    
    # 图书系统指令
    show (-ISBN=[ISBN] | -name="[Book-Name]" | -author="[Author]" | -keyword="[Keyword]")?
    buy [ISBN] [Quantity]
    select [ISBN]
    modify (-ISBN=[ISBN] | -name="[Book-Name]" | -author="[Author]" | -keyword="[Keyword]" | -price=[Price])+
    import [Quantity] [Total-Cost]
    
    # 日志系统指令
    report myself
    show finance ([Time])?
    report finance
    report employee
    log
```


- 主体逻辑说明
tokenscanner 解析$\rightarrow$ account/lib 完成指令 $\rightarrow$ log记录/error报错
  
- 代码文件结构

  ```
  tokenscanner.cpp
  tokenscanner.hpp
  
  account.cpp
  account.hpp
  account
  
  lib.cpp
  lib.hpp
  lib
  
  log.cpp
  log.hpp
  log
  
  error.cpp
  error.hpp
  ```

  

- 各个类的接口及成员说明

  ```c++
  enum TokenType {};//your code
  class tokenscanner{
      private:
      std::string buffer;/* The original argument string */
      
      public:
      TokenScanner();
      TokenScanner(std::string str);
      virtual ~TokenScanner();
      
      void setInput(std::string str);
      bool hasMoreTokens();
      std::string nextToken();
      TokenType getTokenType(std::string token) const;//
  };
  ```

  ```c++
  class account{
      private:
      char user_id[30],passward[30];
      char user_name[30];
      int priority;//0,1,3,7
      
      public:
      account();
      ~account();
      //static void init(string _filename);
      static void login();//TODO
      static void logout();//TODO
      void register(string,string,string);
      void passwd(string,string,string);
      void useradd(string,string,int,string);
      //void delete(int);
      //bool
      
  };
  
  queue<account> curr_login;
  ```

  ```c++
  class lib{
      private:
      char isbn[20];
      char book_name[60],author[60],keyword[60],quantity[10];
      double price,total_cost;
      
      public:
      void show(const char *);
      void buy(const char *);
      void select(const char *);
      void modify(const char *);
      void import(const char *);
  };
  ```

  ```c++
  #include account.hpp
  class log{
      private:
      int time;
      
      public:
      void report_myself();
      void show_finance(const char *="");
      void report_finance();
      void report_employee();
      void create_log();
  };
  //report_myself : input_string
  //report_finance : +/-[int] + bookname + user_name
  //report_employee : employee_name + input_string
  //create_log : user_name + priority + input_string
  ```

  ```c++
  class error{
      private:
      const char *msg;
      
      public:
      error():msg("Invalid"){}
      const char *what(){return msg;}
  };
  ```

  

- 具体算法说明

  b+tree