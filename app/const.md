| Return Type      | Function Qualifiers | Valid | Meaning / Notes                                                                             |
| ---------------- | ------------------- | ----- | ------------------------------------------------------------------------------------------- |
| `Object`         | *(none)*            | ✅     | Returns a copy, function may modify `this`                                                  |
| `Object`         | `const`             | ✅     | Returns a copy, cannot modify `this`                                                        |
| `const Object`   | *(none)*            | ✅     | Returns a const copy (discouraged)                                                          |
| `const Object`   | `const`             | ✅     | Returns a const copy from a const method (discouraged)                                      |
| `Object&`        | *(none)*            | ✅     | Returns a mutable reference, function may modify `this`                                     |
| `Object&`        | `const`             | ✅     | Returns a mutable reference from a const object — **⚠️ only valid if `Object` is mutable!** |
| `const Object&`  | *(none)*            | ✅     | Returns a const reference to `Object`, mutable function                                     |
| `const Object&`  | `const`             | ✅     | Returns const reference from const object — **common for getters**                          |
| `Object&&`       | *(none)*            | ✅     | Returns an rvalue reference (e.g., in move semantics)                                       |
| `Object&&`       | `const`             | ✅     | Valid, but usually not meaningful — rvalue references from const objects rarely make sense  |
| `const Object&&` | *(none)*            | ✅     | Returns const rvalue ref (rare)                                                             |
| `const Object&&` | `const`             | ✅     | Valid; rare and usually not needed                                                          |
| `Object`         | `&`                 | ✅     | Can be called only on lvalues                                                               |
| `Object`         | `const &`           | ✅     | Lvalue-qualified const method                                                               |
| `Object`         | `&&`                | ✅     | Can be called only on rvalues                                                               |
| `Object`         | `const &&`          | ✅     | Const rvalue-qualified member function                                                      |
| `Object&`        | `&`                 | ✅     | Return ref, only callable on lvalues                                                        |
| `Object&`        | `const &`           | ✅     | Return ref, callable on const lvalues                                                       |
| `Object&&`       | `&&`                | ✅     | Return rvalue ref, callable on rvalues only                                                 |
| `Object&&`       | `const &&`          | ✅     | Valid but rarely useful                                                                     |
| `const Object&`  | `&` / `const &`     | ✅     | Const ref return, callable on lvalue `this`                                                 |
| `const Object&&` | `&&` / `const &&`   | ✅     | Const rvalue ref return, rare use cases                                                     |
