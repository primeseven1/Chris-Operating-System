System calls
============

- System calls are passed via registers, and must always be 4 bytes.
- Writing system calls also has a LOT of generalization and it kind of has to be that way.
  For example, there is a typedef called anyType_t (void), and what you would do is move the return value manually in a register
- Avoid using anyType_t when possible :D