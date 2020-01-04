#include "std_lib_facilities.h"
#include <cstdlib>

class Token {
public:
  char kind;
  double value;
  string name;
  Token(char ch)
    :kind(ch), value(0) {}
  Token(char ch, double val)
    :kind(ch), value(val) {}
  Token(char ch, string n)
    :kind(ch), name(n) {}
};

class Token_stream {
public:
  Token get();      // get a Token (get() is defined elsewhere)
  void putback(Token t);    // put a Token back
  void ignore(char c);
  Token_stream()
    :full(false), buffer(0) {}
private:
  bool full;        // is there a Token in the buffer?
  Token buffer;     // here is where we keep a Token put back using putback()
};

void Token_stream::putback(Token t) {
  if(full) error("putback() into a full buffer");
  buffer = t;
  full = true;
}

void Token_stream::ignore(char c) {
  if(full && c == buffer.kind) {
    full = false;
    return;
  }
  full = false;
  char ch = 0;
  while(cin>>ch)
    if(ch == c) return;
}

class Variable {
public:
  string name;
  double value;
  Variable(string n, double v) :name(n), value(v) { }
};

vector<Variable> var_table;

class DivisionError {
public:
  string what;
  DivisionError(string str)
    :what(str) {}
};

const char LET = 'L';
const char NUMBER_TYPE = 8;
const char QUIT = 'q';
const char PRINT = ';';

Token_stream ts;
void calculate();
void clean_up_mass();
double expression();
double term();
double primary();
double get_value(string s);
void set_value(string s, double d);
double statement();
void calculate();
bool is_declared(string var);
double define_name(string var, double val);
double declaration();

int main() {
  double val = 0.0;
  try {
    define_name("pi", 3.14);
    calculate();
    keep_window_open();
    return 0;
  } catch (...) {
    cerr << "Oops: unknown exception!" << endl;
    keep_window_open("~~");
    return 2;
  }
}

void clean_up_mass() {
  ts.ignore(PRINT);
}

double expression() {
  double left = term();
  Token t = ts.get();
  while(true) {
    switch(t.kind) {
      case '+':
        left += term();
        t = ts.get();
        break;
      case '-':
        left -= term();
        t = ts.get();
        break;
      default:
        ts.putback(t);
        return left;
    }
  }
}

double term() {
  double left = primary();
  Token t = ts.get();

  while(true) {
    switch(t.kind) {
      case '*':
        left *= primary();
        t = ts.get();
        break;
      case '/': {
        double d = primary();
        try {
          if (d == 0) throw DivisionError("divide by zero");
          left /= d;
          t = ts.get();
        } catch (DivisionError &e) {
          cerr << e.what << endl;
          keep_window_open("-1");
          return 1;
        }
        break;
      }
      case '%': {
        double d = primary();
        try {
          if (d == 0) throw DivisionError("divide by zero");
          int i1 = narrow_cast<int>(left);
          int i2 = narrow_cast<int>(term());
          left = i1 %i2;
          t = ts.get();
        } catch (DivisionError &e) {
          cerr << e.what << endl;
          keep_window_open("-1");
          return 1;
        }
        break;
      }
      default:
        ts.putback(t);
        return left;
    }
  }
}

double primary() {
  Token t = ts.get();
  switch(t.kind) {
    case '(': {
      double d = expression();
      t = ts.get();
      if (t.kind != ')') error("')' expected");
      return d;
    }
    case NUMBER_TYPE:
      return t.value;
    case '-':
      return - primary();
    case '+':
      return primary();
    default:
      error("primary expected");
  }
}

Token Token_stream::get(){

  if (full) {       // do we already have a Token ready?
    // remove token from buffer
    full=false;
    return buffer;
  }

  char ch;
  cin >> ch;    // note that >> skips whitespace (space, newline, tab, etc.)

  switch (ch) {
    case ';':    // for "print"
    case 'q':    // for "quit"
    case '(': case ')': case '+': case '-': case '*': case '/':
      return Token(ch);        // let each character represent itself
    case '.':
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '9':
    {
      cin.putback(ch);         // put digit back into the input stream
      double val;
      cin >> val;              // read a floating-point number
      return Token(NUMBER_TYPE,val);   // let '8' represent "a number"
    }
    default:
      if(isalpha(ch)) {
        string s;
        s += ch;
        while(cin.get(ch) && (isalpha(ch) || isdigit(ch))) s += ch;
        cin.putback(ch);
        if(s == "let") return Token(LET);
        return Token('a', s);
      }
      error("Bad token");
  }
}

double get_value(string s) {
  for(int i = 0; i < var_table.size(); ++i)
    if(var_table[i].name == s) return var_table[i].value;
  error("get: undefined variable ", s);
}

void set_value(string s, double d) {
  for(int i = 0; i < var_table.size(); ++i)
    if(var_table[i].name == s) {
      var_table[i].value = d;
      return;
    }
  error("set: undefined method ", s);
}

double statement() {
  Token t = ts.get();
  switch(t.kind) {
    case LET:
      return declaration();
    default:
      ts.putback(t);
      return expression();
  }
}


void calculate()
{
  while(cin)
  try {
    cout << "> ";
    Token t = ts.get();
    while (t.kind == PRINT) t = ts.get();
    if (t.kind == QUIT) return;
    ts.putback(t);
    cout << "= " << statement() << endl;
  } catch(runtime_error& e) {
    cerr << e.what() << endl;
    clean_up_mass();
  }
}

bool is_declared(string var) {
  for(int i = 0; i < var_table.size(); ++i)
    if(var_table[i].name == var) return true;
  return false;
}

double define_name(string var, double val) {
  if(is_declared(var)) error(var, " declared twice");
  var_table.push_back(Variable(var, val));
  return val;
}

double declaration() {
  Token t = ts.get();
  if(t.kind != 'a') error("name expected in declaration");
  string var_name = t.name;
  Token t2 = ts.get();
  if(t2.kind != '=') error("= missing in declaration of ", var_name);

  double d = expression();
  define_name(var_name, d);
  return d;
}