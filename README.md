# Math Quiz Game (C++)

A console-based arithmetic quiz game with configurable difficulty, operation type, and question count — built using enums and structs to keep the game state clean and readable.

## Features

- Choose the number of questions per game (1–10)
- Three difficulty levels, each scaling the number range used in questions:
  - **Easy** → numbers 1–10
  - **Medium** → numbers 1–100
  - **Hard** → numbers 1–1000
- Five operation modes: Addition, Subtraction, Multiplication, Division, or **Mixed** (a random operation is picked each question)
- Instant per-question feedback (correct/wrong, with the right answer shown on a miss)
- Console color + terminal bell cue on wrong answers for extra feedback
- End-of-game summary with total questions, difficulty, operation type, correct/wrong counts, and a performance message
- "Play again?" loop to replay without restarting the program

## How It Works

The game is built around two structs:

- `stGame` — holds the session configuration (question count, difficulty, operation type)
- `stQuestion` — holds a single question's numbers, operation, correct answer, and the user's answer

`QuestionLevelRange()` generates numbers scaled to the chosen difficulty, and `CalculateAnswer()` / `OperationSymbol()` handle the arithmetic and display for each operation — including resolving "Mixed" mode down to a concrete random operation per question.

## Requirements

- A C++ compiler (uses `system("color ..")` for feedback coloring, so it runs best on Windows or a Windows-compatible terminal)

## Build & Run

```bash
g++ main.cpp -o math_quiz
./math_quiz
```

## Sample Flow

```
Please choose the number of questions (1-10): 5
Please choose the difficulty level (1-Easy, 2-Medium, 3-Hard): 1
Please choose the operation type (1-Addition, 2-Subtraction, 3-Multiplication, 4-Division, 5-Mixed): 1

Question [1/5]
7
+ 3
-----------
Your answer: 10
Correct!
```

## Bug Fixes Along the Way

- Fixed a division bug where remainders weren't displaying correctly by adjusting the data type used for answers
- Rebalanced difficulty scaling after finding that Hard mode's original number range made questions too difficult

## Testing

Manually tested 20+ times across difficulty levels and operation types to confirm scoring and edge cases behave correctly.

## Possible Improvements

- Cross-platform terminal color handling (currently relies on Windows `system("color ..")`)
- Guard against division producing non-integer results in Division mode
- Add a running score/history across multiple play sessions
