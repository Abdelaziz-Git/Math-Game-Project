

#include <iostream>
using namespace std;

short ReadHowManyQuestions()
{
	short NumberOfQuestions = 1;
	do
	{
		cout << "How many questions do you want? From 1 To 10 ?";
		cin >> NumberOfQuestions;

		while (cin.fail())
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			cout << "How many questions do you want? From 1 To 10 ?";
			cin >> NumberOfQuestions;
		}

	} while (NumberOfQuestions < 1 || NumberOfQuestions>10);


	return NumberOfQuestions;
}

enum enQuestionsLevel
{
	EasyLevel = 1, MedLevel = 2, HardLevel = 3, MixLevel = 4
};
enQuestionsLevel ReadQuestionsLevel()
{
	short QuestionsLevel = 1;
	do
	{
		cout << "Enter questions level: [1] Easy, [2] Med, [3] Hard, [4] Mix?";
		cin >> QuestionsLevel;

		while (cin.fail())
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "Enter questions level: [1] Easy, [2] Med, [3] Hard, [4] Mix?";
			cin >> QuestionsLevel;
		}

	} while (QuestionsLevel < 1 || QuestionsLevel>4);
	return enQuestionsLevel(QuestionsLevel);
}

enum enOperationsType
{
	Add = 1, Sub = 2, Mul = 3, Div = 4, MixOp = 5

};

enOperationsType ReadOperationType()
{
	short Op = 1;
	do
	{
		cout << "Enter operation type: [1] Add(+), [2] Sub(-), [3] Mul(x), [4] Div(/), [5] Mix(+ - x /) ?";
		cin >> Op;

		while (cin.fail())
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			cout << "Enter operation type: [1] Add(+), [2] Sub(-), [3] Mul(x), [4] Div(/), [5] Mix(+ - x /) ?";
			cin >> Op;
		}


	} while (Op < 1 || Op>5);
	return enOperationsType(Op);
}

struct stQuestion
{
	int Number1 = 0, Number2 = 0;
	enOperationsType OpType;
	enQuestionsLevel QuestionLevel;
	int CorrectAswer = 0;
	int PlayerAnswer = 0;
	bool AswerResult = false;
};
struct stQuizz
{
	stQuestion QuestionListe[100];
	short NumberOfQuestions = 1;
	short NumberOfRightAswers = 0;
	short NumberOfWrongAswer = 0;
	enQuestionsLevel QuestionsLevel;
	enOperationsType OperationsType;
	bool IsPass = false;

};

int RandomNumber(int From, int To)
{
	int RandNum = rand() % (To - From + 1) + From;
	return RandNum;
}

enQuestionsLevel GetRandomQuestionsLevel()
{
	return enQuestionsLevel(RandomNumber(1, 3));
}

enOperationsType GetRandomOperationsType()
{
	return enOperationsType(RandomNumber(1, 4));
}

int SimpleCalculator(int Number1, int Number2, enOperationsType OperationType)
{
	switch (OperationType)
	{
	case Add:
		return Number1 + Number2;
	case Sub:
		return Number1 - Number2;
	case Mul:
		return Number1 * Number2;
	case Div:
		return Number1 / Number2;
	default:
		return Number1 + Number2;
	}
}

stQuestion GenerateQuestion(enQuestionsLevel QuestionsLevel, enOperationsType OperationsType)
{
	stQuestion Question;


	if (QuestionsLevel == enQuestionsLevel::MixLevel)
	{
		QuestionsLevel = GetRandomQuestionsLevel();
	}

	if (OperationsType == enOperationsType::MixOp)
	{
		OperationsType = GetRandomOperationsType();
	}

	Question.OpType = OperationsType;

	switch (QuestionsLevel)
	{
	case EasyLevel:
		Question.Number1 = RandomNumber(1, 10);
		Question.Number2 = RandomNumber(1, 10);
		Question.CorrectAswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OpType);
		Question.QuestionLevel = QuestionsLevel;
		return Question;
	case MedLevel:
		Question.Number1 = RandomNumber(20, 50);
		Question.Number2 = RandomNumber(20, 50);
		Question.CorrectAswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OpType);
		Question.QuestionLevel = QuestionsLevel;
		return Question;
	case HardLevel:
		Question.Number1 = RandomNumber(50, 100);
		Question.Number2 = RandomNumber(50, 100);
		Question.CorrectAswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OpType);
		Question.QuestionLevel = QuestionsLevel;
		return Question;
	}
	return Question;
}
void GenerateQuizzQuestions(stQuizz& Quizz)
{
	for (short QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQuestions; QuestionNumber++)
	{
		Quizz.QuestionListe[QuestionNumber] = GenerateQuestion(Quizz.QuestionsLevel, Quizz.OperationsType);
	}
}

string Tabs1(short NumberOfTabs)
{
	string t = "";
	for (short i = 0; i < NumberOfTabs; i++)
	{
		t += "\t";
	}
	return t;
}
string GetOpTypeSymbol(enOperationsType OpType)
{
	switch (OpType)
	{
	case Add:
		return "+";
	case Sub:
		return "-";
	case Mul:
		return "x";
	case Div:
		return "/";
	case MixOp:
		return "Mix";
	default:
		return "+";
	}
}

void PrintTheQuestion(stQuizz Quizz, short QuestionNumber)
{
	cout << "\n" << Tabs1(1) << "Question [" << QuestionNumber + 1 << "/" << Quizz.NumberOfQuestions << "]\n";
	cout << Tabs1(1) << Quizz.QuestionListe[QuestionNumber].Number1 << endl;
	cout << Tabs1(1) << Quizz.QuestionListe[QuestionNumber].Number2 << " ";
	cout << GetOpTypeSymbol(Quizz.QuestionListe[QuestionNumber].OpType) << endl;
	cout << Tabs1(1) << "_______\n";

}
int ReadPlayerAnswer()
{
	int Answer = 0;
	cout << Tabs1(1);
	cin >> Answer;

	while (cin.fail())
	{
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << Tabs1(1);
		cin >> Answer;
	}

	return Answer;
}
void SetSecrenColor(bool AnswerResult)
{
	if (AnswerResult)
	{
		system("color 2F");
	}
	else
	{
		system("color 4F");
		cout << "\a";
	}
}
void CorrectQuestionListAnswer(stQuizz& Quizz, short QuestionNumber)
{
	if (Quizz.QuestionListe[QuestionNumber].CorrectAswer != Quizz.QuestionListe[QuestionNumber].PlayerAnswer)
	{
		cout << Tabs1(1) << "Wrong answer: -(\n";
		cout << Tabs1(1) << "The right answer is: " << Quizz.QuestionListe[QuestionNumber].CorrectAswer << endl;

		Quizz.NumberOfWrongAswer++;
		Quizz.QuestionListe[QuestionNumber].AswerResult = false;
	}
	else
	{
		cout << Tabs1(1) << "Right answer: -)\n";
		Quizz.NumberOfRightAswers++;
		Quizz.QuestionListe[QuestionNumber].AswerResult = true;
	}
	SetSecrenColor(Quizz.QuestionListe[QuestionNumber].AswerResult);
}

void AskAndCorrectQuestionListAnswer(stQuizz& Quizz)
{
	for (short QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQuestions; QuestionNumber++)
	{
		PrintTheQuestion(Quizz, QuestionNumber);
		Quizz.QuestionListe[QuestionNumber].PlayerAnswer = ReadPlayerAnswer();
		CorrectQuestionListAnswer(Quizz, QuestionNumber);
	}
	Quizz.IsPass = (Quizz.NumberOfRightAswers >= Quizz.NumberOfWrongAswer);

}

string IsPass(bool Right)
{
	if (Right)
		return"Pass: -)";
	else
		return"Fail: -(";
}
string GetQuestionsLevelText(enQuestionsLevel QuestionsLevel)
{
	string arrQuestionsLevelText[4] = { "Easy","Med","Hard","Mix" };
	return arrQuestionsLevelText[QuestionsLevel - 1];
}

void PrintQuizzResult(stQuizz Quizz)
{
	cout << endl << Tabs1(3) << "__________________________________\n";
	cout << Tabs1(3) << "Final results is " << IsPass(Quizz.IsPass);
	cout << endl << Tabs1(3) << "__________________________________";

	cout << "\n" << Tabs1(3) << "Number of questions     : " << Quizz.NumberOfQuestions;
	cout << "\n" << Tabs1(3) << "Questions Level         : " << GetQuestionsLevelText(Quizz.QuestionsLevel);
	cout << "\n" << Tabs1(3) << "OpType                  : " << GetOpTypeSymbol(Quizz.OperationsType);
	cout << "\n" << Tabs1(3) << "Number of right answers : " << Quizz.NumberOfRightAswers;
	cout << "\n" << Tabs1(3) << "Number of wrong answers : " << Quizz.NumberOfWrongAswer;


	cout << endl << Tabs1(3) << "__________________________________\n";


	SetSecrenColor(Quizz.IsPass);
}

void PlayMathGame(stQuizz& Quizz)
{
	Quizz.NumberOfQuestions = ReadHowManyQuestions();
	Quizz.QuestionsLevel = ReadQuestionsLevel();
	Quizz.OperationsType = ReadOperationType();

	GenerateQuizzQuestions(Quizz);
	AskAndCorrectQuestionListAnswer(Quizz);
	PrintQuizzResult(Quizz);

}
void ResetSecren()
{
	system("cls");
	system("color 0F");
}
void StarGame()
{
	stQuizz Quizz;
	char PlayAgain = 'y';
	do
	{
		ResetSecren();
		PlayMathGame(Quizz);
		cout << endl << Tabs1(3) << "Do you want to play again ? Y or N ?";
		cin >> PlayAgain;

	} while (PlayAgain == 'y' || PlayAgain == 'Y');
}



int main()
{
	srand((unsigned)time(NULL));

	StarGame();

	return 0;
}


int RandomNumber(int, int);