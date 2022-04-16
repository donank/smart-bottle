# CONTRIBUTION GUIDELINES

## Before contributing

Welcome to [Oshun Development](https://github.com/donank/smart-bottle)! Before submitting pull requests, please make sure that you have **read the whole guidelines**. If you have any doubts about this contribution guide, please open [an issue](https://github.com/donank/smart-bottle/issues/new/choose) or create a [Discussion Thread](https://github.com/donank/smart-bottle/discussions/new), and clearly state your concerns.

## Contributing

### Maintainer/reviewer

**to do**

### Contributor

Being a contributor at Oshun, we request you to follow the points mentioned below:

- You did your own work.
  - No plagiarism allowed. Any plagiarized work will not be merged.
- Your work will be distributed under the [GPL V3.0 License](https://github.com/donank/smart-bottle/blob/main/LICENSE) once your pull request has been merged.
- Please follow the repository guidelines and standards mentioned below.

**New implementation** New implementations are welcome!

You can add new classes and functions which are **not present in the repository** or that can **improve** the old implementations (**integrating new hardware**, **documentation**, **improving test cases**, removing bugs or in any other reasonable sense)

### Making Changes

#### Code

- Please use the directory structure of the repository.
- Make sure the file extensions should be `*.hpp`, `*.h` or `*.cpp`.
- You can suggest reasonable changes to existing code.
- Strictly use snake_case in filenames.
- If you have added or modified code, please make sure the code compiles before submitting.
- Please conform to [Doxygen](https://www.doxygen.nl/manual/docblocks.html) standard and document the code as much as possible. This not only facilitates the readers but also generates the correct info on the website.
- **Be consistent in the use of these guidelines.**

#### Documentation

- Make sure you put useful comments in your code. Do not comment on obvious things.
- If you have modified/added documentation, please ensure that your language is concise and must not contain grammatical errors.
- Do not update [`README.md`](https://github.com/donank/smart-bottle/blob/main/README.md) along with other changes. First, create an issue and then link to that issue in your pull request to suggest specific changes required to [`README.md`](https://github.com/donank/smart-bottle/blob/main/README.md).
- The repository follows [Doxygen](https://www.doxygen.nl/manual/docblocks.html) standards and auto-generates the [repository website](https://github.com/donank/smart-bottle/). Please ensure the code is documented in this structure. A sample implementation is given below.



#### Commit Guidelines

- It is recommended to keep your changes grouped logically within individual commits. Maintainers find it easier to understand changes that are logically spilled across multiple commits. Try to modify just one or two files in the same directory. Pull requests that span multiple directories are often rejected.

```bash
git add file_xyz.cpp
git commit -m "your message"
```

Examples of commit messages with semantic prefixes:

```markdown
fix: xyz bug
feat: add xyx, class xyz
test: add test for xyz functionality
docs: add comments and explanation to xyz functionality
```

Common prefixes:

- fix: A bug fix
- feat: A new feature
- docs: Documentation changes
- test: Correct existing tests or add new ones

### Pull Requests


#### Building Locally

Before submitting a pull request,
 build the code locally

```bash

```


Most importantly,

- Happy coding!
