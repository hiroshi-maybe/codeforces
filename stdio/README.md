
# Standard IO benchmark

## Standard Input

Read 1e6 64 bit integers.
```c++
    int n; scanf("%d", &n);
    vector<long long> a;
    a.reserve(n);
    for(int i=0; i<n; ++i) scanf("%lld", &a[i]);
```

|Program | Language | Result |
|--------|----------|--------|
wataxxreader.rs | Rust | 0.05s user 0.01s system 94% cpu 0.061 total
watareader.rs | Rust | 0.04s user 0.01s system 18% cpu 0.302 total
proconio.rs | Rust | 0.04s user 0.01s system 18% cpu 0.302 total
ebtechscanner.rs | Rust | 0.05s user 0.01s system 22% cpu 0.261 total
scanf.cpp | C++ |  0.17s user 0.01s system 47% cpu 0.384 total
tanakh.rs | Rust | 0.22s user 0.01s system 51% cpu 0.455 total
cin.cpp | C++ | 3.15s user 0.08s system 92% cpu 3.495 total

Reading line by line with Rust is fast.

## Standard Output

Print 1e6 integers with deliminators space and line break.

```c++
    for(int i=0; i<(int)1e6; ++i) {
        cout<<i<<" ";
    }
    for(int i=0; i<(int)1e6; ++i) {
        cout<<i<<endl;
    }
```

|Program | Language | Result |
|--------|----------|--------|
bufwriter-inlined-macro.rs | Rust | 0.12s user 0.00s system 97% cpu 0.124 total
bufwriter-inlined.rs | Rust | 0.11s user 0.00s system 43% cpu 0.257 total
printf.cpp | C++ | 0.27s user 0.01s system 48% cpu 0.557 total
print.rs | Rust |  0.59s user 0.27s system 71% cpu 1.184 total
bufwriter.rs | Rust |  0.74s user 0.31s system 82% cpu 1.266 total
cout.cpp | C++ | 0.93s user 0.30s system 97% cpu 1.265 total

If buffer is flushed (`cout`, `println`), it's slow.
