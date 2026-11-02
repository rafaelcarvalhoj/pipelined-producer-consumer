# Concurrent Three-Stage Pipeline

A C/Pthreads project for a producer-transformer-consumer pipeline with two bounded buffers. The [project report](docs/relatorio.md) describes a temporary interruption of the first buffer. Remaining work is tracked in [TODO.md](TODO.md).

## Structure

```text
docs/relatorio.md                  Project description and requirements
src/main.c                         Program entry point
src/cli/                           Command-line argument parsing
src/structs/                       Argument, item, buffer, and pipeline types
src/application/repositories/      Thread-safe buffer operations
src/application/services/          Pipeline setup and lifecycle (in progress)
Makefile                           Build commands
```

## Run

Requires GCC, Make, and POSIX threads.

```sh
make build
./main 2 2 2 6 4
```

Arguments, in order: stage 1 threads, stage 2 threads, stage 3 threads, first buffer capacity, second buffer capacity. Use positive integers and different buffer capacities, as specified in the report.

To remove the executable:

```sh
make clean
```
