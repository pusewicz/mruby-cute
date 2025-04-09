# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Build Commands
- Build: `rake compile`
- Test all: `rake test`
- Run example: `rake example`

## Code Style Guidelines
- C: Use C23 standard with consistent indentation (spaces)
- Ruby: Follow mruby idioms for tests, use assert() for test cases
- Variable naming: snake_case for Ruby and for C functions
- Error handling: Check return values, validate function parameters
- C struct wrappers follow consistent pattern with initialization, accessors, and factory methods
- Tests should verify initialization, accessors, and factory methods
- Comments: Keep functions documented inline while focusing on non-obvious behavior

## Common Patterns
- Always check to start from a fresh main branch and create feature branches
- MRuby C API used throughout for MRuby integration
- Consistent memory management with allocation and freeing in wrappers
- Run tests to verify modifications work properly
- Focus on performance as it is a key aspect of this gamedev project
- MRuby-Cute documentation should be added using YARD stub files in `docstub/`
- Cute Framework structs are mapped to MRuby classes such as `CF_V2` => `Cute::V2`
- Pay attention to return values for structs. If they are not pointers and they need to be wrapped, use the `mrb_*_wrap_nested` functions

## Source locations

- MRuby code is located in `deps/mruby/`
- CuteFramework code is located in `deps/cute_framework/`

## Links

  * [Cute Framework GitHub](https://github.com/RandyGaul/cute_framework)
  * [mruby-cute GitHub](https://github.com/pusewicz/mruby-cute)
  * [Progress Issue](https://github.com/pusewicz/mruby-cute/issues/5)
