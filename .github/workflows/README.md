# Clang Format GitHub Workflow

This workflow is supported by the run-clang-format.py helper script.

## `run-clang-format.py`

A wrapper script around clang-format, suitable for linting multiple files and
to use for continuous integration.

This script has come from https://github.com/Sarcasm/run-clang-format.

This copy is from commit `de6e8ca07d171a7f378d379ff252a00f2905e81d`.

The script has been updated to also take a `--style` flag to be able to select
the clang-format coding style. The diff with the code change can be found in
the `run-clang-format.diff` file.

### `run-clang-format.py` license

MIT License

Copyright (c) 2017 Guillaume Papin

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
