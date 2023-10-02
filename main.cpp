//Om Namah Shiva
#include <bits/stdc++.h>
using namespace std;

/**
 * Grammer: 
 * 
 * E  --> TE'
 * E' --> +TE' | epsilon
 * T  --> FT'
 * T' --> *FT' | epsilon
 * F  --> (E) | id
 * 
 * **/

enum Token {
	PLUS,		 // +
	STAR,		 // *
	LEFT_PAREN,  // (
	RIGHT_PAREN, // )
	ID 			 // id
};

class Parser {
public:
	Parser(vector<Token> expr) : current(0) {
		this->expr = expr;
	}
	void parse(){
		eval_E();
		if(current != expr.size())
			throw invalid_argument(error_message("expected expression"));

	}
	void printAST(){
		cout << parseTree;
	}

private:
	int current;
	vector<Token> expr;
	string parseTree;

	void eval_E(){
		parseTree += "[ E: ";
		eval_T();
		while(current != expr.size()){
			if(match(PLUS)){
				parseTree += " + ";
				eval_T();
			} else
				break;
		}
		parseTree += " ]";
	}

	void eval_T(){
		parseTree += "[ T: ";
		eval_F();
		while(current != expr.size()){
			if(match(STAR)){
				parseTree += " * ";
				eval_F();
			} else
				break;
		}
		parseTree += " ]";
	}

	void eval_F(){
		parseTree += "[ F: ";
		// while(current != expr.size()){
			if(match(LEFT_PAREN)){
				parseTree += " ( ";
				eval_E();
				if(!match(RIGHT_PAREN)){
					throw invalid_argument(error_message("expected right parenthesis ')'"));
				}
			} else if(match(ID)){
				parseTree += " id ";
			}
		// }
		parseTree += " ]";
	}

	bool match(Token token){
		if(current == expr.size())
			return 0;
		if(expr[current] == token){
			current++;
			return 1;
		}
		return 0;
	}
	string error_message(string msg) {
        return "Syntax error: " + msg;
    }
};

signed main()
{
	vector<Token> expr = {LEFT_PAREN, ID, PLUS, ID, RIGHT_PAREN, STAR, ID};
	// vector<Token> expr = {ID, ID};
	Parser parser(expr);
	parser.parse();
	parser.printAST();
    
    return 0;
  	
}