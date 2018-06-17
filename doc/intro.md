# Introduction \[intro]

This document specifies the public API of the _MiA library_.

## References \[intro.refs]

The following documents are referred to in the text
in such a way that some or all of their content
constitutes requirements of this document.

- https://github.com/johelegp/jegp/blob/devel/doc/intro.md
- JCGM 200:2012, _International Vocabulary of Metrology --
    Basic and General Concepts and Associated Terms_

https://github.com/johelegp/jegp/blob/devel/doc/intro.md
is herein called the _JEGP library_.
JCGM 200:2012 is herein called the _VIM_.

## Terms and definitions \[intro.defs]

For the purposes of this document,
the terms and definitions
given in the VIM, Clause 1,
apply.

Terms that are used
only in a small portion of this document
are defined where they are used
and italicized where they are defined.

## General \[intro.general]

The library specification
subsumes the JEGP library's \[intro.general],
assumingly amended to the context of this library.

[GSL] is used
to follow the [C++ Core Guidelines].
[units] is used
to describe domain-specific units.

[GSL]: https://github.com/Microsoft/GSL
[C++ Core Guidelines]: https://github.com/isocpp/CppCoreGuidelines
[units]: https://github.com/nholthaus/units

Table \[intro.general] -- Library categories

| Clause      | Category           |
| ----------- | ------------------ |
| \[ext]      | Extensions headers |
| \[concepts] | Concepts library   |
| \[units]    | Units library      |
