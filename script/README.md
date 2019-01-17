# Preparation

Add script to environment variable
```bash
$ chmod -R 755 ${CODEFORCES_HOME}/script/bin
$ export PATH="${PATH}:${CODEFORCES_HOME}/script/bin"
```

# Usage

Generate problem files
```bash
$ cp-gen my new problem
```

Add test cases to `MyNewProblem.in` and `MyNewProblem.out`.
Run batch test
```bash
$ cp-batch MyNewProblem | diff OneCardPoker.out - 
```
