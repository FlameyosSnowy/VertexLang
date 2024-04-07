mod compiler;
use compiler::lexer;

use std::env;

use std::rc::Rc;

fn main() {
    let args = env::args();
    let tokenizer = lexer::Lexer::new();

    let string = String::from("1 + 1");
    let borrowed: Rc<str> = Rc::from(&*string);

    tokenizer.tokenize(&'static borrowed);
}


