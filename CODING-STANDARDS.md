Coding Standards for Gibanica
=============================

C++
---

### Naming conventions

- Variables will be named in `camelCase`
- Ditto functions
- Types should be in `UpperCamelCase`

### Layout

- Indentation is 4 spaces

- Braces follow K&R style:
```c++
if (foo) {
  // do something
} else {
  // do something else
}
```

### Namespacing

- `using namespace bla;` should be avoided
- Code should be namespaced, and directory structure should follow namespace
  structure

### Testing

- All new code should have tests in gtest
