#include "strings.h"
#include "calc.h"
int parse_number(const char **expr){
	int result = 0;
	while(**expr >= '0' && **expr <= '9'){
		result = result * 10 + (**expr - '0');
		(*expr)++;
	}
	return result;
}
int parse_factor(const char **expr){
	if(**expr == '('){
		(*expr)++;
		int result = parse_expression(expr);
		if(**expr == ')'){
			(*expr)++;
		}
		return result;
	}else{
		return parse_number(expr);
	}
}
		
		
int parse_term(const char **expr){
	int result = parse_factor(expr);
	while(**expr == '*' || **expr == '/'){
		char op = **expr;
		(*expr)++;
		int right = parse_factor(expr);
		if(op == '*'){
			result *= right;
		}else if(op == '/'){
			result /= right;
		}
	}
	return result;
}
int parse_expression(const char **expr){
	int result = parse_term(expr);
	while(**expr == '+' || **expr == '-'){
		char op = **expr;
		(*expr)++;
		int right = parse_term(expr);
		if(op == '+'){
			result += right;
		}else if(op == '-'){
			result -= right;
		}
	}
	return result;
}
int eval(const char *expr){
	return parse_expression(&expr);
}