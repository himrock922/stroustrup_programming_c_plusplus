#include "std_lib_facilities.h"
#include <cstdlib>

class Token {
public:
  char kind;
  double value;
  Token(char ch)
    :kind(ch), value(0) {}
  Token(char ch, double val)
    :kind(ch), value(val) {}
};

class Token_stream {
public:
  Token get();      // get a Token (get() is defined elsewhere)
  void putback(Token t);    // put a Token back
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

class DivisionError {
public:
  string what;
  DivisionError(string str)
    :what(str) {}
};

Token_stream ts;
double expression();
double term();
double primary();

int main() {
  double val = 0.0;
  try {
    while (cin) {
      cout << "> ";
      Token t = ts.get();

      if (t.kind == 'q') break; // 'q' for quit
      if (t.kind == ';')        // ';' for "print now"
        cout << "=" << val << endl;
      else
        ts.putback(t);
      val = expression();
    }
    keep_window_open();
  }
  catch (exception &e) {
    cerr << "error: " << e.what() << '\n';
    keep_window_open();
    return 1;
  }
  catch (...) {
    cerr << "Oops: unknown exception!\n";
    keep_window_open();
    return 2;
  }
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
    case '8':
      return t.value;
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
      return Token('8',val);   // let '8' represent "a number"
    }
    default:
      error("Bad token");
  }
}
