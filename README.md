# Badiff

Is it possible to make diff algorithms on the web faster by compiling a C implementation to WebAssembly?

Who knows? Certainly not me. Badiff is a way for me to learn C - it's a C implementation of the very smart Myers' diff algorithm[1] compiled to WASM. I challenged myself to use no resources other than the original paper, including AI. In hindsight, I learned a lot more about the algorithm than C, namely that it is much slower and produces much uglier diffs than bleeding edge diffing tools like [diffchecker.com](https://www.diffchecker.com/). Seeing how Badiff will perform with some modern optimizations will be interesting, but as of right now I am happy. It may be a bad diffing algorithm, but it is a good learning experience.

[Try it out here!](https://fyang151.github.io/badiff/)

[1] Myers, E. W. (1986). An O(ND) Difference Algorithm and Its Variations. *Algorithmica*, 1(1), 251-266. [PDF](https://neil.fraser.name/software/diff_match_patch/myers.pdf)