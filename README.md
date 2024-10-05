# CStar
A C-like programming language.

#Docs

- func
func is a function and at the end of a function you put end
example:
```
func hello
asm mov, 0x0e
asm mov al, 'A'
asm int 0x10
end

```

- jmp
this jumps to a function or address
example:
```
jmp hello
```

- dw mostly used for boot loaders which means word
example:
```
dw 0x55aa
```

- asm this is just inline assembly
example:
```
asm mov al, bl
```

- // comments
example:
```
// This is very commentary
```