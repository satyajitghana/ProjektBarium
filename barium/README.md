## How the AST classes are defined

`class_name: data_members`

```
node
  ├─ expression
  │     ├─ decimal: value
  │     ├─ fraction: value
  │     ├─ string lit: value
  │     ├─ binary_operator: lhs, op, rhs
  │     ├─ identifier: name
  │     ├─ block: vector<statement>
  │     ├─ assignment: lhs, rhs
  │     ├─ function_call: ident, args_list
  │     ├─ comp_operator: lhs, op, rhs
  │     └─ array_access: var_name, index, next_dimension
  │
  └─ statement
        ├─ expr_statement: expr
        ├─ variable_declaration: type, ident, assign_expr
        ├─ conditional: comp_expr, then_expr, else_expr
        ├─ for_loop: init_expr, cond_expr, update_expr, then_expr
        └─ for_range: ident, range_lim, then_expr
```