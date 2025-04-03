# mruby-cute

MRuby bindings for the [Cutest Framework](https://randygaul.github.io/cute_framework/) available for making 2D games in C/C++.

## Running tests

```bash
$ rake test
```

## Build release type

```bash
$ env RELEASE=true rake
```

## Compilation Commands

Prerequisite: [Bear](https://github.com/rizsotto/Bear)

To generate `compilation_commands.json` file, prepend `bear --` to the compilation command. For example:

```bash
bear -- rake
```
