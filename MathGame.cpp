#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;

enum enOperation { ADDITION = 1, SUBTRACTION, MULTIPLICATION, DIVISION, Mixed };
enum enDifficulty { EASY = 1, MEDIUM, HARD };

struct stGame {
	short NumberOfQuestions;
	enDifficulty QuestionLevel;
	enOperation OperationType;
};

struct stQuestion {
	short Number1 = 0;
	short Number2 = 0;
	enOperation Operation = ADDITION;
	int CorrectAnswer = 0;
	int UserAnswer = 0;
};

short GiveMessageInputNumber(string Message, short Min, short Max) {
	short Number;
	do {
		cout << Message;
		cin >> Number;
	} while (Number < Min || Number > Max);
	return Number;
}

short RandomNumber(short Min, short Max)
{
	return rand() % (Max - Min + 1) + Min;
}

void ValidateAnswer(int UserAnswer, int CorrectAnswer) {
	if (UserAnswer == CorrectAnswer) {
		cout << "Correct!" << endl;
		system("color 2F");
	}
	else {
		cout << "Wrong! The correct answer is: " << CorrectAnswer << endl;
		system("color 4F");
		cout << "\a";
	}
}

int CalculateAnswer(int Number1, int Number2, enOperation Operation) {
	switch (Operation) {
	case ADDITION:
		return Number1 + Number2;
	case SUBTRACTION:
		return Number1 - Number2;
	case MULTIPLICATION:
		return Number1 * Number2;
	case DIVISION:
		return Number1 / Number2;
	default:
		return 0;
	}
}
enOperation GetRandomOperation() {
	return (enOperation)RandomNumber(1, 4);
}


char OperationSymbol(enOperation Operation) {
	switch (Operation) {
	case ADDITION:
		return '+';
	case SUBTRACTION:
		return '-';
	case MULTIPLICATION:
		return '*';
	case DIVISION:
		return '/';
	case Mixed:
		return OperationSymbol(GetRandomOperation());
	default:
		return ' ';
	}
}
int QuestionLevelRange(enDifficulty Difficulty) {
	switch (Difficulty) {
	case EASY:
		return RandomNumber(1, 10);
	case MEDIUM:
		return RandomNumber(1, 100);
	case HARD:
		return RandomNumber(1, 1000);
	default:
		return 10;
	}
}
void QustionSet(stGame game, stQuestion& question)
{
	question.Number1 = QuestionLevelRange(game.QuestionLevel);
	question.Number2 = QuestionLevelRange(game.QuestionLevel);

	if (game.OperationType == Mixed)
		question.Operation = GetRandomOperation();
	else
		question.Operation = game.OperationType;

	cout << question.Number1 << endl << OperationSymbol(question.Operation) << " " << question.Number2 << endl << "-----------" << endl;
}
void DoMath(stQuestion& question) {
	question.CorrectAnswer = CalculateAnswer(question.Number1, question.Number2, question.Operation);
	cout << "Your answer: ";
	cin >> question.UserAnswer;
	ValidateAnswer(question.UserAnswer, question.CorrectAnswer);
}
string QuestionLevelName(enDifficulty Difficulty) {
	switch (Difficulty) {
	case EASY:
		return "Easy";
	case MEDIUM:
		return "Medium";
	case HARD:
		return "Hard";
	default:
		return "Unknown";
	}
}
string OperationTypeName(enOperation Operation) {
	switch (Operation) {
	case ADDITION:
		return "Addition";
	case SUBTRACTION:
		return "Subtraction";
	case MULTIPLICATION:
		return "Multiplication";
	case DIVISION:
		return "Division";
	case Mixed:
		return "Mixed";
	default:
		return "Unknown";
	}
}

void EndScreen(stGame Game, stQuestion question, int numberOfRightQuestions) {
	cout << "--------------------------------------------------" << endl;
	cout << "                  Game Over!" << endl;
	cout << "--------------------------------------------------" << endl;
	cout << "Number of Questions: " << Game.NumberOfQuestions << endl;
	cout << "Difficulty Level: " << QuestionLevelName(Game.QuestionLevel) << endl;
	cout << "Operation Type: " << OperationTypeName(Game.OperationType) << endl;
	cout << "Number of Correct Answers: " << numberOfRightQuestions << endl;
	cout << "Number of Wrong Answers: " << Game.NumberOfQuestions - numberOfRightQuestions << endl;
	if (numberOfRightQuestions == Game.NumberOfQuestions)
	{
		cout << "Congratulations! You answered all questions correctly!" << endl;
	}
	else if (numberOfRightQuestions * 2 >= Game.NumberOfQuestions)
	{
		cout << "Good job! You answered " << numberOfRightQuestions << " out of " << Game.NumberOfQuestions << " questions correctly." << endl;
	}
	else
	{
		cout << "You answered " << numberOfRightQuestions << " out of " << Game.NumberOfQuestions << " questions correctly. Better luck next time!" << endl;
	}

}
void theGame()
{
	int numberOfRightQuestions = 0;
	int NumberOfQuestions = GiveMessageInputNumber("Please choose the number of questions (1-10): ", 1, 10);
	int DifficultyLevel = GiveMessageInputNumber("Please choose the difficulty level (1-Easy, 2-Medium, 3-Hard): ", 1, 3);
	int OperationType = GiveMessageInputNumber("Please choose the operation type (1-Addition, 2-Subtraction, 3-Multiplication, 4-Division, 5-Mixed): ", 1, 5);
	stGame Game;
	stQuestion question;
	Game.NumberOfQuestions = NumberOfQuestions;
	Game.QuestionLevel = (enDifficulty)DifficultyLevel;
	Game.OperationType = (enOperation)OperationType;
	for (int i = 1; i <= Game.NumberOfQuestions; i++)
	{
		cout << "Question [" << i << "/" << Game.NumberOfQuestions << "]" << endl;
		QustionSet(Game, question);
		DoMath(question);
		if (question.UserAnswer == question.CorrectAnswer) {
			numberOfRightQuestions++;
		}
	}

	EndScreen(Game, question, numberOfRightQuestions);
}

void TheWholeGame() {
	char PlayAgain;
	do {
		system("cls");
		theGame();
		cout << "Do you want to play again? (Y/N): ";
		cin >> PlayAgain;
	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main() {
	srand(time(NULL));
	TheWholeGame();
	return 0;
}