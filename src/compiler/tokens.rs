use std::fmt::Display;

pub struct Token {
    pub name: String, 
    pub token_type: TokenType
}

impl Display for Token {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(f, "Name: {}, Type: {:?}", self.name, self.token_type);
        Ok(())
    }
}

#[derive(std::fmt::Debug)]
pub enum TokenType {
    Char(char),
    Float(f32),
    Double(f64),
    Integer(i32),
    Long(i64),
    Plus,
    Minus,
    Multiply,
    Divide,
    Modulus,
    LParen,
    RParen
}