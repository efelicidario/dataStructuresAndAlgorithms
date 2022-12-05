/**
 * Implementation of the functions to evaluate arithmetic expressions
 * The implementation should use the Stack data structure
 */
//You should always comments to each function to describe its PURPOSE and PARAMETERS
#include "stack.h"
#include "eval_expr.h"


/**
 * @brief Helper function to check if the string is an operand.
 * @param num The element to be checking.
 * @return true if is a valid ASCII value (0-9).
 * @return false if is a valid ASCII value (0-9).
 */
bool is_operand(char num) {
    int x;
    x = int(num);   // converts the int to a char

    if (x >= 48 && x <= 57) {   // checks the valid bounds in ASCII
        return true;            // returns true if is in bounds
    }
    else
        return false;
}

/**
 * @brief Helper function to check if the string is an operator.
 * @param op The element to be checking.
 * @return true if is a +, -, *, or / sign.
 * @return false if is anything else.
 */
bool is_operator(char op) {
    switch(op) {                // checks for valid operators
        case '+' : return true;
        case '-' : return true;
        case '*' : return true;
        case '/' : return true;
        default  :              // returns false if symbol is undefined
        cout << "Error: unknown symbol" << endl;
        return false;
    }
}

/**
 * @brief Helper function to perform the operation on the expression.
 * @param a .
 * @param b .
 * @param op .
 * @return the result of the performed operation.
 * @return -1 if the symbol is unknown.
 */
float operation(float a, float b, char op) {
    if (op == '+') {        // performs the appropriate
        return a + b;       // operation
    }
    else if (op == '-') {
        return b - a;
    }
    else if (op == '*') {
        return a * b;
    }
    else if (op == '/') {
        return b / a;
    }
    else                    // return -1 if symbol is unknown
        return -1;
}

/**
 * @brief Evaluate a postfix expression
 * @param postfix_expr The input expression in the postfix format.
 * @param result gets the evaluated value of the expression (by reference).
 * @return true if expression is a valid postfix expression and evaluation is done without error, otherwise false.
 */
bool evalPostfixExpr(string postfix_expr, float& result) {
    Stack <float> stk;
    int strCount = 0;
    float a, b;

    while (strCount != postfix_expr.length()) {     // while there's still items left in the expression
        postfix_expr[strCount];                     // AND no error
        if (is_operand(postfix_expr[strCount])) {   // if an operand (number), push onto stack
            stk.push(int(postfix_expr[strCount]) - 48);
        }
        else if (is_operator(postfix_expr[strCount])) { // if an operator,
            if (stk.isEmpty()) {
                cout << "Error: invalid expression!" << endl;
                return false;
            }
            stk.pop(a);                                 // pop operand
            if (stk.isEmpty()) {
                cout << "Error: invalid expression!" << endl;
                return false;
            }
            stk.pop(b);                                 // pop operand
            if (a == 0 && postfix_expr[strCount] == '/') {
                cout << "Error: division by zero" << endl;
                return false;
            }
            result = operation(a, b, postfix_expr[strCount]);   // apply operator the two operands,
            stk.push(result);                                   // push result
        }
        else {
            return false;
        }
        strCount++;
    }
    return true;
}


/**
 * @brief Convert an infix expression to an equivalent postfix expression
 * @param infix_expr The input expression in the infix format.
 * @return the converted postfix expression. If the input infix expression is invalid, return an empty string "";
 */
string convertInfixToPostfix(string infix_expr) {
    return "";
}

/**
 * @brief Evaluate an infix expression. It's converted to a postfix expression first and then evaluated
 * @param infix_expr The input expression in the infix format.
 * @param result gets the evaluated value of the expression (by reference).
 * @return true if expression is valid and evaluation is done without error, otherwise false.
 */
bool evalInfixExpr(string infix_expr, float& result) {
    return true;
}
