Here's a breakdown of the assignment split among four people:

---

## **Person 1: `code` class**
**Responsibility:** The foundational class that stores and manipulates digit sequences.

| Task | Description |
|------|-------------|
| Private members | `vector<int> content`, `int n` (length), `int m` (range) |
| Constructor | `code(int length, int range)` |
| `initializeRandom()` | Fill code with random digits 0 to m-1 |
| `readGuess()` | Read n digits from keyboard into content |
| `print()` | Output the code to screen |
| `length()` | Return n |
| `digitAt(int i)` | Return digit at position i |
| `checkCorrect(const code&)` | Count exact position matches |
| `checkIncorrect(const code&)` | Count correct digits in wrong positions |

---

## **Person 2: `response` class**
**Responsibility:** Store and handle guess feedback (correct/incorrect counts).

| Task | Description |
|------|-------------|
| Private members | `int numCorrect`, `int numIncorrect` |
| Constructor | Initialize both values (with defaults) |
| Getters | `getCorrect()`, `getIncorrect()` |
| Setters | `setCorrect(int)`, `setIncorrect(int)` |
| `operator==` | Global function comparing two responses |
| `operator<<` | Global function to print a response |

---

## **Person 3: `mastermind` class**
**Responsibility:** Game controller that ties everything together.

| Task | Description |
|------|-------------|
| Private member | `code secretCode`, `int n`, `int m` |
| Constructor 1 | `mastermind(int n, int m)` - user-provided values |
| Constructor 2 | `mastermind()` - default n=5, m=10 |
| `printSecretCode()` | Print the secret code |
| `humanGuess()` | Read guess from keyboard, return `code` object |
| `getResponse(const code&)` | Return `response` object for a guess |
| `isSolved(const response&)` | Return true if game is won |
| `playGame()` | Main game loop (10 rounds, win/lose logic) |

---

## **Person 4: `main()` and Input Validation**
**Responsibility:** Program entry point, user interaction, and validation.

| Task | Description |
|------|-------------|
| `validateInput(int n, int m)` | Check n and m are within valid bounds (1-10) |
| `main()` | Seed random, prompt for n and m, create `mastermind`, call `playGame()` |
| Error handling | Display errors for invalid input, use defaults if needed |
| `srand(time(0))` | Initialize random number generator |
| Testing | Ensure secret code prints for grading purposes |

---

## **Integration Notes**

| Step | Who Leads | Dependencies |
|------|-----------|--------------|
| 1 | Person 1 & 2 | Can work independently in parallel |
| 2 | Person 3 | Needs Person 1 & 2's classes |
| 3 | Person 4 | Needs Person 3's class |

**Suggested workflow:**
1. Persons 1 & 2 complete their classes first (can work simultaneously)
2. Person 3 integrates both classes into `mastermind`
3. Person 4 writes `main()` and tests the full program

Each person should include comments explaining their code and test their portion individually before integration.
