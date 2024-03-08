#include "QuizAdminManager.h"
#include "Category.h"
#include "DatabaseConnection.h"

void QuizAdminManager::insertCategory(const string& category_name) {
	DatabaseConnection().callInsertCategory(category_name);
}

void QuizAdminManager::insertQuiz(const string& category_id, const string& quiz_title, const string& quiz_description) {
	DatabaseConnection().callInsertQuiz(category_id, quiz_title, quiz_description);
}

void QuizAdminManager::insertQuestion(const string& quiz_id, const string& question_text, const string& question_type) {
	DatabaseConnection().callInsertQuestion(quiz_id, question_text, question_type);
}

void QuizAdminManager::insertOption(const string& question_id, const string& option_text, const bool& isCorrect) {
	DatabaseConnection().callInsertOption(question_id, option_text, isCorrect);
}

void QuizAdminManager::updateCategory(const string& category_id, const string& category_name) {
	DatabaseConnection().callUpdateCategory(category_id, category_name);
}

void QuizAdminManager::updateQuiz(const string& quiz_id, const string& category_id, const string& quiz_title, const string& quiz_description) {
	DatabaseConnection().callUpdateQuiz(quiz_id, category_id, quiz_title, quiz_description);
}

void QuizAdminManager::updateQuestion(const string& question_id, const string& quiz_id, const string& question_text, const string& question_type) {
	DatabaseConnection().callUpdateQuestion(question_id, quiz_id, question_text, question_type);
}

void QuizAdminManager::updateOption(const string& option_id, const string& question_id, const string& option_text, const bool& isCorrect) {
	DatabaseConnection().callUpdateOption(option_id, question_id, option_text, isCorrect);
}

void QuizAdminManager::deleteCategory(const string& category_id) {
	DatabaseConnection().callDeleteCategory(category_id);
}

void QuizAdminManager::deleteQuiz(const string& quiz_id) {
	DatabaseConnection().callDeleteQuiz(quiz_id);
}

void QuizAdminManager::deleteQuestion(const string& question_id) {
	DatabaseConnection().callDeleteQuestion(question_id);
}

void QuizAdminManager::deleteOption(const string& option_id) {
	DatabaseConnection().callDeleteOption(option_id);
}

void QuizAdminManager::startAdminOperation() {
	int choice1;
	cout << "-----------------------------------------------------------------------------" << endl;
	cout << "Welcome ADMIN!" << endl;
	cout << "Do you wish to play quiz (1) " << endl << "OR " << endl << "Modify Our Quiz DB? (2)" << endl;
	cin >> choice1;

	if (choice1 == 1) {
		QuizUserManager::startUserOperation();
	}
	else if(choice1 == 2) {
		cout << "------------------------------------ADMIN CONTROLS------------------------------------------" << endl;
		cout << "What do you want to do CUD Opeations on?" << endl;
		cout << "NOTE: YOU CANT TOUCH ANY OF THE PRIMARY KEYS, we wont provide you anyway to do that too :)" << endl;
		cout << "1: Category" << endl;
		cout << "2: Quiz" << endl;
		cout << "3: Question" << endl;
		cout << "4: Option" << endl;

		cin >> choice1;
		cout << "----------------------------------------------------------------------------------" << endl;
		if (choice1 == 1) {
			int choice2 = 0;
			cout << "Do you want to insert new Category?" << endl << "Yes(1) or No(0) ?" << endl;
			cin >> choice2;
			if (choice2 == 0) {
				int choice3 = 0;
				//Update, Delete
				getAllCategories();
				int catCount = 0;
				cout << "These are the categories we have: " << endl;
				for (auto& c : currentCategories) {
					catCount++;
					cout << catCount << ") " << c << endl;
				}
				cout << "Which category? " << endl;
				cin >> choice3;
				Category temp = currentCategories[choice3 - 1];
				cout << "Do you want to update(1) OR delete(0) ?" << endl;
				cin >> choice3;
				if (choice3 == 0) {
					//delete
					deleteCategory(temp.category_id);
					cout << "Deleted your category! And thus all its Quizzes are also deleted! " << endl;
					cout << "If you want to make more changes, Please Re-Login! Thankyou!" << endl;
				}
				else if (choice3 == 1) {
					//update
					cout << "You can only change the Category Name for Categories..." << endl << "Enter new Category Name: " << endl;
					string tempCategoryName;
					cin >> tempCategoryName;
					updateCategory(temp.category_id, tempCategoryName);
					cout << "Updated!" << endl;
					cout << "If you want to make more changes, Please Re-Login! Thankyou!" << endl;
				}
				else {
					cout << "CMON! Give proper Input!!!" << endl;
					cout << "Restart Now, as your punishment  >_<   " << endl;
					exit(0);
				}

			}
			else if (choice2 == 1) {
				//Insert
				cout << "You are about to insert a new Category." << endl;
				cout << "Enter your category name: " << endl << endl;
				string tempCatName;
				cin >> tempCatName;
				cout << "Inserting Data!" << endl;
				insertCategory(tempCatName);
				cout << "Inserted! If you want to do more changes, Log Back In!" << endl;
			}
			else {
				cout << "CMON! Give proper Input!!!" << endl;
				cout << "Restart Now, as your punishment  >_<   " << endl;
				exit(0);
			}

			getAllCategories();
			cout << "------------------------------CHANGED CATEGORIES--------------------------------------------" << endl;
			for (auto& c : currentCategories) {
				cout << c << endl;
			}
			cout << endl;
			exit(0);
		}
		else if (choice1 == 2) {

		}
		else if (choice1 == 3) {

		}
		else if (choice1 == 4) {

		}
		else {
			cout << "CMON! Give proper Input!!!" << endl;
			cout << "Restart Now, as your punishment  >_<   " << endl;
			exit(0);
		}
	}
	else {
		cout << "CMON! Give proper Input!!!" << endl;
		cout << "Restart Now, as your punishment  >_<   " << endl;
		exit(0);
	}
}
