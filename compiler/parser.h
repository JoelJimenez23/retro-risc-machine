#include<stdlib.h>

typedef struct {
    Token *tokens;   
    Token *current;  
    Token *previous; 
} Parser;

void parser_init(Parser *p, Token *list) {
    p->tokens = list;
    p->current = list;
    p->previous = list;
}

int parser_isAtEnd(Parser *p) {
    return p->current->type == END;
}

int parser_check(Parser *p, TokenType type) {
    if (parser_isAtEnd(p)) return 0;
    return p->current->type == type;
}

int parser_advance(Parser *p) {
    if (p->current->type != END) {
        p->previous = p->current;
        p->current++; 
        return 1;
    }
    return 0;
}

int parser_match(Parser *p, TokenType type) {
    if (p->current->type == type) {
        parser_advance(p);
        return 1;
    }
    return 0;
}
