# 项目名称 / 文档作者
项目名称：书店管理系统

文档作者：黄健浩


- ## 程序功能概述
对于不同用户（未登录用户、顾客、店员、店长）提供相应的功能，具体来说：
- ### 账户系统
> 0. 未登录用户：登录其他已注册的账户、注册顾客账户。
> 1. 顾客：未登录用户可以使用的所有功能、注销当前登录的账户、修改指定账户的密码（需要输入旧密码）、检索图书。
> 2. 店员：顾客可以使用的所有功能、创建权限低于自己的账户。
> 3. 店长：店员可以使用的所有功能、删除账户、修改指定账户的密码（无需输入旧密码）。
- ### 图书系统
> 1. 顾客：检索图书、购买图书。
> 2. 店员：顾客可以使用的所有功能、修改图书信息、图书进货。
> 3. 店长：店员可以使用的所有功能。

- ### 日志系统
> 2. 店员：生成员工自己的操作记录
> 3. 店长：店员可以使用的所有功能、查询财务记录、生成财务记录报告、生成全体员工工作情况报告、生成日志。


- 所需全部功能如下
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
  ```
  tokenscanner 解析 -> account / lib 完成指令 -> log 记录/ error 报错
  
  账户系统指令 ： 对 FileMap account_info(_file_name) 这一变量进行操作即可实现

  图书系统指令 ： 除 select 外对 FileMap book_info(_file_name) 这一变量进行操作即可实现

  关于 login 和 logout 的实现 ： 在 main 函数中使用 stack，存放 pair<Account,string> (string 表示被选中的书的 ISBN)
  ```

  
- 代码文件结构

  ```
  //含有 FileMemPool，FileMap
  //其中 FileMemPool 仅负责 new 和 delete
  //FileMap 为已封装的类， 其余的任何地方均不应出现 fstream 等
  BPTree.cpp
  BPTree.h
  
  TokenScanner.cpp
  TokenScanner.h
  
  AccountManager.cpp
  AccountManager.h
  
  BookManager.cpp
  BookManager.h
  
  LogSystem.cpp
  LogSystem.h
  
  Error.cpp
  Error.h
  ```  

- 各个类的接口及成员说明
  ```c++
  class FileMemPool {
   private:
    string file_name_;
  
   public:
    template <class T>
    class FilePtr {
     private:
      long pos_;
  
     public:
      FilePtr() : pos_(-1){}
      FilePtr(long _pos) : pos_(_pos){}
      long Get_Pos() const;
      operator bool();
    };
    FileMemPool(string _file_name) : file_name_(_file_name);
    template <class T>
    FilePtr<T> Fnew(const T& obj);
    template <class T>
    T Fread(const FilePtr<T>& ptr);
    template <class T>
    void Modify(const FilePtr<T>& ptr,const T& obj);
    ~FileMemPool() = default;
  };
  ```
  ```c++
  template <class T>
  class FileMap{
    private:
    FileMemPool ...

    public:
    FileMap(string file_name);
    ~FileMap();
    void Insert(...);
    void Delete(...);
    void Find(..., set<int>);
  };
  ```
  ```c++
  class TokenScanner {
   private:
    string buffer;
    void RemoveLeadingZero();

   public:
    enum TokenType;
    // tKeyValue means : -Key=Value
    // tKeyValueWithQuotation means : -Key="Value"
    TokenScanner(const string& str);
    TokenScanner(std::istream& os);
    bool HasMoreToken() const;
    string GetNextToken();
    pair<string, string> GetNextToken(const TokenType&);
  	TokenType JudgeToken();
  };
  ```

  ```c++
  class AccountManager {
   private:
    FileMap<UserID, Account, UserID, AccountHash> account_list;
    vector<pair<UserID, BookIndex>> LoginStack;
    void LoginNoExcept(const UserID& user_id);
    Account FindAccount(const UserID& user_id);
    bool AccountExist(const UserID& user_id);
    void ChangePasswordNoExcept(const UserID& user_id, const Password& new_password);
    void DeleteUserNoExcept(const UserID& user_id);

   public:
    AccountManager(const string& name);
    void LoginWithoutPassword(const UserID& user_id);
    void Login(const UserID& user_id, const Password& password);
    void Logout();
    void AddUser(const UserID& user_id, const Password& password,
                 const Priority& priority, const Username& username);
    void ChangePassword(const UserID& user_id, const Password& old_password,
                        const Password& new_password);
    void ChangePasswordWithoutPassword(const UserID& user_id, const Password& new_password);
    void DeleteUser(const UserID& user_id);
    int GetPriority();
  	void SelectBook(const BookIndex& book_index);
    BookIndex GetSelected();
  };
  ```

  ```c++
  class BookManager {
   private:
    const string name_;
    FileMemPool book_list;
    FileMap<ISBN, BookIndex, long, BookIndexHash> map_isbn;
    FileMap<BookName, BookIndex, long, BookIndexHash> map_book_name;
    FileMap<Author, BookIndex, long, BookIndexHash> map_author;
    FileMap<Keyword, BookIndex, long, BookIndexHash> map_keyword;
    BookIndex FindIndex(const ISBN& isbn);
    BookIndex CreatBookNoExcept(const ISBN& isbn);
    Book ReadBook(const BookIndex& book_index);
    set<Book> ReadBookList(const vector<BookIndex>& book_index_list);
    void ModifyBook(const BookIndex& book_index, const Book& book);

   public:
    BookManager(const string& name);
    set<Book> FindBook();
    set<Book> FindBook(const ISBN& isbn);
    set<Book> FindBook(const BookName& book_name);
    set<Book> FindBook(const Author& author);
    set<Book> FindBook(const Keyword& keyword);
    double BuyBook(const ISBN& isbn, const Quantity& quantity);
    BookIndex SelectBook(const ISBN& isbn);
    void Modify(const BookIndex& book_index, const ISBN& isbn);
    void Modify(const BookIndex& book_index, const BookName& book_name);
    void Modify(const BookIndex& book_index, const Author& author);
    void Modify(const BookIndex& book_index, const KeywordList& keyword_list);
    void Modify(const BookIndex& book_index, const MoneyQuantity& price);
    void Import(const BookIndex& book_index, const Quantity& quantity);
  };
  ```

  ```c++
  class LogSystem {
   private:
    FileMemPool index_file_;
    FileMemPool record_file_;
    int lst;

   public:
    LogSystem(const string& name_);
    void Record(const double& money);
    pair<double, double> Show();
    pair<double, double> Show(const Quantity& times);
    ~LogSystem();
  };
  ```

  ```c++
  class Error : public std::exception {
      public:
      Error() = default;
      const char* what() const noexcept override;
  };
  ```

  

- 具体算法说明

  b+tree
  
- 命名规范：google

  