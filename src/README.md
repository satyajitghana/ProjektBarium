## How the AST classes are defined

```
node
  └─ expression
        ├─ decimal: value
        ├─ fraction: value
        ├─ string lit: value
        ├─ binary_operator: lhs, op, rhs
        ├─ identifier: name
        ├─ block : vector<statement>
        ├─ assignment: lhs, rhs
        └─ function_call: ident, args_list
  └─ statement
        └─ expr_statement: expr
```