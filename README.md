<div align="center">
    <img src="icon.png" width="156px"/>
    <p style="font-size: 32px; font-weight: 500; margin: 0;">Lotus</p>
    <p style="font-size: 20px; font-weight: 500; margin-top: 5px;">Lightweight and easy-to-understand programming language, developed by two developers as a practice project to gain a deeper understanding of language design and implementation.</p>
</div>

## Features
- Easy to understand [documentation](Documentation.md)
- [VS Code extension](https://marketplace.visualstudio.com/items?itemName=scrumboard-company.lotus-lang)
- Simple and readable syntax
- Written in C++ for performance
- Designed for learning and experimentation

## Why Lotus?
We created Lotus to practice building a programming language and to explore how compilers and interpreters work. Our goal is to make a language that is both lightweight and beginner-friendly.

## Installation & Usage
After installing the language, we recommend you to restart your PC to ensure PATH variable works correctly

(Currently, the project is in development. Installation instructions will be provided soon)

Lotus files have .lts extension.

## CLI

CLI command to compile lotus files

```Lotus ./main.lts```

Flags
```
--help, -h - outputs all CLI flags
--version, -v - outputs lotus version
--flag [name] [value] - set flag value before interpretation
--flag-config [cfgFilePath] - specify flags config
--include, -i [path] - adds additional include path
```


## Example Code
Here is a simple "Hello, World!" program in Lotus:
```lotus
print("Hello, World!")
```

## Upcoming features
We are actively working on improving Lotus. Some planned features include:
- More standard libraries
- Bug fixes
- Unicode support
