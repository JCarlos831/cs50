# Questions

## What is pneumonoultramicroscopicsilicovolcanoconiosis?

It is a term referring to a lung disease caused by silica dust. It is also cited as one of the longest words
in the English language.

## According to its man page, what does `getrusage` do?

It can return usage statistics on user CPU time used, system CPU time used, maximum resident set size, integral shared memory size,
integral unsahred data size, integral unshared stack size, page reclaims (soft page faults), page faults (hard page faults),
swaps, block input operations, block output operations, IPC messages ent, IPC messages received, signals received, voluntary context
switches, and involuntary context switches.

## Per that same man page, how many members are in a variable of type `struct rusage`?

16

## Why do you think we pass `before` and `after` by reference (instead of by value) to `calculate`, even though we're not changing their contents?

TODO

## Explain as precisely as possible, in a paragraph or more, how `main` goes about reading words from a file. In other words, convince us that you indeed understand how that function's `for` loop works.

TODO

## Why do you think we used `fgetc` to read each word's characters one at a time rather than use `fscanf` with a format string like `"%s"` to read whole words at a time? Put another way, what problems might arise by relying on `fscanf` alone?

TODO

## Why do you think we declared the parameters for `check` and `load` as `const` (which means "constant")?

TODO
