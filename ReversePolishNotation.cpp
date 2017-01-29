#include <memory>
#include <vector>
#include <unordered_map>
#include <cassert>
#include <iostream>
#include <exception>
#include <stdexcept>

class Token;
typedef std::shared_ptr<Token> TokenPtr;


class Token {
public:
  Token(double val = 0) : m_value(val) {}
  virtual ~Token() {}
  virtual void Execute(std::vector<TokenPtr> & tokens) {
    tokens.push_back(std::make_shared<Token>(m_value));
  }
  void SetValue(double value) {
    m_value = value;
  }
  double GetValue() const  {
    return m_value;
  }
private:
  double m_value;
};

class Add : public Token {
public:
  Add() {}
  virtual ~Add() {}
  virtual void Execute(std::vector<TokenPtr> & tokens) {
    double right = tokens.back()->GetValue();
    tokens.pop_back();
    tokens.back()->SetValue(tokens.back()->GetValue() + right);
  }
};


class Sub : public Token {
public:
  Sub() {}
  virtual ~Sub() {}
  virtual void Execute(std::vector<TokenPtr> & tokens) {
    double right = tokens.back()->GetValue();
    tokens.pop_back();
    tokens.back()->SetValue(tokens.back()->GetValue() - right);
  }
};

class Mul : public Token {
public:
  Mul() {}
  virtual ~Mul() {}
  virtual void Execute(std::vector<TokenPtr> & tokens) {
    double right = tokens.back()->GetValue();
    tokens.pop_back();
    tokens.back()->SetValue(tokens.back()->GetValue() * right);
  }
};

class Div : public Token {
public:
  Div() {}
  virtual ~Div() {}
  virtual void Execute(std::vector<TokenPtr> & tokens) {
    double right = tokens.back()->GetValue();
    tokens.pop_back();
    tokens.back()->SetValue(tokens.back()->GetValue() / right);
  }
};

class OperatorCreator {
public:
  OperatorCreator(){}
  virtual ~OperatorCreator(){}
  virtual TokenPtr Create() = 0;
};
typedef std::shared_ptr<OperatorCreator> OperatorCreatorPtr;

class AddCreator : public OperatorCreator {
public:
  virtual TokenPtr Create() {
    TokenPtr reval =  std::make_shared<Add>();
    return reval;
  }
};

class SubCreator : public OperatorCreator {
public:
  virtual TokenPtr Create() {
    TokenPtr reval =  std::make_shared<Sub>();
    return reval;
  }
};

class MulCreator : public OperatorCreator {
public:
  virtual TokenPtr Create() {
    TokenPtr reval =  std::make_shared<Mul>();
    return reval;
  }
};

class DivCreator : public OperatorCreator {
public:
  virtual TokenPtr Create() {
    TokenPtr reval =  std::make_shared<Div>();
    return reval;
  }
};

class TokenFactory {
public:
  TokenFactory(){}
  TokenPtr GetToken(const std::string & str) {
    TokenPtr reval;
    if (m_mapper.count(str) != 0) {
      reval =  m_mapper[str]->Create();
    } else {
      reval = std::make_shared<Token>(std::stod(str));
    }
    return reval;
  }
  void RegisterOperator(const std::string & str, const OperatorCreatorPtr & op) {
    if (str.empty() || !op) return;
    m_mapper[str] = op;
  }
private:
  std::unordered_map<std::string, OperatorCreatorPtr> m_mapper;
};

double EvaluateRPN(std::vector<std::string> strs) {
  std::vector<TokenPtr> tokens;
  TokenFactory token_factory;
  OperatorCreatorPtr add_creator = std::make_shared<AddCreator>();
  OperatorCreatorPtr sub_creator = std::make_shared<SubCreator>();
  OperatorCreatorPtr mul_creator = std::make_shared<MulCreator>();
  OperatorCreatorPtr div_creator = std::make_shared<DivCreator>();
  token_factory.RegisterOperator("+",add_creator);
  token_factory.RegisterOperator("-",sub_creator);
  token_factory.RegisterOperator("*",mul_creator);
  token_factory.RegisterOperator("/",div_creator);
  for (const std::string & str : strs) {
      token_factory.GetToken(str)->Execute(tokens);
  }
  return tokens.back()->GetValue();
}

void UnitTest() {
  std::vector<std::string> strs = {"3","2","5","/","+","2","4","*","-"};
  std::cout << EvaluateRPN(strs) << std::endl;
}

int main() {
  UnitTest();
  return 0;
}
