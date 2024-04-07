use std::fs::File;
use std::io::{BufReader, BufRead};
use std::str::Chars;

use super::tokens::{Token, TokenType};

pub struct Lexer {
}

impl Lexer {
    pub fn new() -> Self {
        return Self{};
    }

    fn tokenize_general(&self, index: usize, character: char, chars: &mut Chars<'static>) -> Token {
        if character.is_digit(10) {
            return self.tokenize_number(index, chars);
        } else {
            panic!("Unknown letter/symbol found: {}", character);
        }

    }

    fn find_token_type_of_number(string: &String, is_float: bool, is_double: bool, is_long: bool) -> TokenType {
        if let Ok(number) = string.parse::<f32>()  {
            if !is_float { panic!("Could not know number type."); }
            return TokenType::Float(number);
        } else if let Ok(number) = string.parse::<f64>()  {
            if !is_double { panic!("Could not know number type."); }
            return TokenType::Double(number);
        } else if let Ok(number) = string.parse::<i64>() {
            if !is_long { panic!("Could not know number type."); }
            return TokenType::Long(number);
        } else if let Ok(number) = string.parse::<i32>() {
            return TokenType::Integer(number);
        } else {
            panic!("Could not know number type.");
        }
    }

    fn tokenize_number(&self, index: usize, chars: &mut Chars<'static>) -> Token {
        let mut number = String::new();
        let mut is_float: bool = false;
        let mut is_double: bool = false;
        let mut is_long: bool = false;
        while let Some(character) = chars.nth(index) {
            if character.is_digit(10) { 
                number.push(character);
            } else {
                match character {
                    'f' => {
                        is_double = false;
                        is_float = true;
                        break;
                    },
                    'L' => {
                        is_long = true;
                        break;
                    },
                    '.' => {
                        is_double = true;
                    },
                    _ => break
                }
            }
        }
        let type_of_token = Lexer::find_token_type_of_number(&number, is_float, is_double, is_long);
        return Token { name: number, token_type: type_of_token };
    }

    pub fn tokenize(&self, line: &'static str) -> Vec<Token> {
        let mut tokens = Vec::new();
        let mut chars = line.chars();
        for i in 0..line.len() {
            let character = chars.nth(i);
            match character {
                Some(c) => {
                    if c.is_whitespace() { continue; }
                    tokens.push(self.tokenize_general(i, c, &mut chars));
                },
                None => break
            }
        }
        return tokens;
    }

    pub fn tokenize_file(&self, file: File) -> Vec<Vec<Token>> {
        let mut tokens = Vec::new();
        let reader = BufReader::new(file);

        for string in reader.lines() {
            match string {
                Ok(line) => {
                    let borrowed: &'static str = line.as_str().as_ref();
                    tokens.push(self.tokenize(borrowed));
                },
                Err(_) => break,
            }
        }

        tokens
    }
}