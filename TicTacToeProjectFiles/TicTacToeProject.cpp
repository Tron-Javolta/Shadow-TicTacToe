#include "TicTacToeProject.h"
#include "AddNames.h"
#include "Rules.h"
#include "IconChoice.h"
#include "WinScreen.h"
#include "DrawScreen.h"
#include <ctime>
#include <cstdlib>
#include <array>
#include <algorithm>
#include <chrono>
#include <random>


bool gameRunning = false; // make this so start game can't be clicked again


// DEFINE METHODS IN HERE
TicTacToeProject::TicTacToeProject(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

// main button to run the game
void TicTacToeProject::on_startButton_clicked() {
	
	// pop up name box, take the name inputs and put them in player 1 and player 2 in the main ui
	QChar player1Icon, player2Icon;
	
	// check if game is already running, if it is then start button shouldn't be able to be clicked
	if (!gameRunning)
	{
		// Shuffle indices for shadow board to be random
		std::array<char, 9> numbers = { '1','2','3','4','5','6','7','8','9' };
		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

		shuffle(numbers.begin(), numbers.end(), std::default_random_engine(seed));
		//*************************************************************************
		
		// Label each shadow board square with randomized numbers 1-9
		QString text = "(";
		text += numbers[0];
		text += ")";
		
		ui.shadowBox1->setText(text);

		text = "(";
		text += numbers[1];
		text += ")";
		ui.shadowBox2->setText(text);

		text = "(";
		text += numbers[2];
		text += ")";
		ui.shadowBox3->setText(text);

		text = "(";
		text += numbers[3];
		text += ")";
		ui.shadowBox4->setText(text);

		text = "(";
		text += numbers[4];
		text += ")";
		ui.shadowBox5->setText(text);

		text = "(";
		text += numbers[5];
		text += ")";
		ui.shadowBox6->setText(text);

		text = "(";
		text += numbers[6];
		text += ")";
		ui.shadowBox7->setText(text);

		text = "(";
		text += numbers[7];
		text += ")";
		ui.shadowBox8->setText(text);

		text = "(";
		text += numbers[8];
		text += ")";
		ui.shadowBox9->setText(text);
		//***************************


		AddNames dialog(this); // spawns box

		// Execute if the game isn't started yet
		if (dialog.exec() && !gameRunning)
		{
			QString player1Name = dialog.player1Edit->text();
			QString player2Name = dialog.player2Edit->text();

			// start of game after receiving both player's names
			if (!player1Name.isEmpty() && !player2Name.isEmpty())
			{
				gameRunning = true;
				
				// Remove start button since game has started
				ui.startButton->setVisible(false);
				
				// Set player name labels to the names that were input
				ui.player1NameLabel->setText(player1Name);
				ui.player2NameLabel->setText(player2Name);


				// Determine who goes first
				srand(time(0));
				int firstPersonToPick = rand() % 2 + 1;

				QString turnString;

				if (firstPersonToPick == 1)
				{
					turnString = player1Name + "'s turn";
					ui.turnLabel->setText(player1Name);
				}

				else
				{
					turnString = player2Name + "'s turn";
					ui.turnLabel->setText(player2Name);
				}
				//*************************************


				// Display who's first and ask them to select their icon
				IconChoice iconDialog(this);

				QString firstPlayer = ui.turnLabel->text() + " goes first!";
				iconDialog.firstPersonLabel->setText(firstPlayer);

				bool iconsSelected = false;
				
				// Check for no or duplicate icons
				do
				{
					iconDialog.exec();

					// Save icon characters from each player
					QString player1IconString = iconDialog.player1IconEdit->text();
					QString player2IconString = iconDialog.player2IconEdit->text();

					if (!(player1IconString.at(0) == player2IconString.at(0)) && (!(player1IconString == "") || !(player2IconString == "")))
					{
						// Convert to a char for the icon
						player1Icon = player1IconString.at(0);
						player2Icon = player2IconString.at(0);
						iconsSelected = true;
					}
				} while (!iconsSelected);
				//***********************

				// Display the icons next to their respective name
				if (ui.turnLabel->text() == player1Name)
				{
					ui.player1Icon->setText(player1Icon);
					ui.player2Icon->setText(player2Icon);
				}
				else
				{
					ui.player1Icon->setText(player2Icon);
					ui.player2Icon->setText(player1Icon);
				}
				//*******************************************************
			}
		}
	}
}

// For rules button in-game
void TicTacToeProject::on_rulesButton_clicked() {
	
	Rules dialog(this);

	dialog.exec();
}

// For reset button in-game
void TicTacToeProject::on_resetButton_clicked() {

	if (gameRunning)
	{

		//Randomizes the shadow board
		std::array<char, 9> numbers = { '1','2','3','4','5','6','7','8','9' };
		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

		shuffle(numbers.begin(), numbers.end(), std::default_random_engine(seed));
		//**************************************************************************

		//Reassigns the numbers to each square of the shadow board
		QString text = "(";
		text += numbers[0];
		text += ")";

		ui.shadowBox1->setText(text);

		text = "(";
		text += numbers[1];
		text += ")";
		ui.shadowBox2->setText(text);

		text = "(";
		text += numbers[2];
		text += ")";
		ui.shadowBox3->setText(text);

		text = "(";
		text += numbers[3];
		text += ")";
		ui.shadowBox4->setText(text);

		text = "(";
		text += numbers[4];
		text += ")";
		ui.shadowBox5->setText(text);

		text = "(";
		text += numbers[5];
		text += ")";
		ui.shadowBox6->setText(text);

		text = "(";
		text += numbers[6];
		text += ")";
		ui.shadowBox7->setText(text);

		text = "(";
		text += numbers[7];
		text += ")";
		ui.shadowBox8->setText(text);

		text = "(";
		text += numbers[8];
		text += ")";
		ui.shadowBox9->setText(text);
		//***************************

		// unmark main board
		ui.TTTbutton1->setText("(1)");
		ui.TTTbutton2->setText("(2)");
		ui.TTTbutton3->setText("(3)");
		ui.TTTbutton4->setText("(4)");
		ui.TTTbutton5->setText("(5)");
		ui.TTTbutton6->setText("(6)");
		ui.TTTbutton7->setText("(7)");
		ui.TTTbutton8->setText("(8)");
		ui.TTTbutton9->setText("(9)");
		//****************************

		// Re-randomize player's turn
		// Set player name labels to names' input
		QString player1Name = ui.player1NameLabel->text();
		QString player2Name = ui.player2NameLabel->text();

		srand(time(0));
		int firstPersonToPick = rand() % 2 + 1;

		QString turnString; // Used for the turn label to display who's turn it is

		if (firstPersonToPick == 1)
		{
			turnString = player1Name + "'s turn";
			ui.turnLabel->setText(player1Name);
		}

		else
		{
			turnString = player2Name + "'s turn";
			ui.turnLabel->setText(player2Name);
		}
		//*************************************

	}
}

// Main board button 1
void TicTacToeProject::on_TTTbutton1_clicked() {
	
	// Check if game is not running or button has already been marked
	if (!gameRunning && (ui.TTTbutton1->text() == "(1)"))
		return;

	else if (!(ui.TTTbutton1->text() == "(1)"))
		return;

	// Name the button
	else
	{
		QString player = ui.turnLabel->text();

		QString iconForButton;
		
		// Get player's icon for who's turn it is
		if (player == ui.player1NameLabel->text())
			iconForButton = ui.player1Icon->text();

		else
			iconForButton = ui.player2Icon->text();

		// Set the button to new text to display who has the spot
		QString newButtonLabel = iconForButton + "(1)";
		ui.TTTbutton1->setText(newButtonLabel);

		// Check main board for win
		if (ui.TTTbutton2->text().at(0) == ui.TTTbutton1->text().at(0) && ui.TTTbutton3->text().at(0) == ui.TTTbutton1->text().at(0))
			displayWinScreen();

		else if (ui.TTTbutton1->text().at(0) == ui.TTTbutton5->text().at(0) && ui.TTTbutton1->text().at(0) == ui.TTTbutton9->text().at(0))
			displayWinScreen();

		else if (ui.TTTbutton1->text().at(0) == ui.TTTbutton4->text().at(0) && ui.TTTbutton1->text().at(0) == ui.TTTbutton7->text().at(0))
			displayWinScreen();

		//*******************************

		// Check each shadow board box for matches
		if (ui.shadowBox1->text() == "(1)")
		{
			ui.shadowBox1->setText(newButtonLabel);
			if (ui.shadowBox1->text().at(0) == ui.shadowBox2->text().at(0) && ui.shadowBox1->text().at(0) == ui.shadowBox3->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox1->text().at(0) == ui.shadowBox5->text().at(0) && ui.shadowBox1->text().at(0) == ui.shadowBox9->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox1->text().at(0) == ui.shadowBox4->text().at(0) && ui.shadowBox1->text().at(0) == ui.shadowBox7->text().at(0))
				displayWinScreen();
		}


		else if (ui.shadowBox2->text() == "(1)")
		{
			ui.shadowBox2->setText(newButtonLabel);
			if (ui.shadowBox2->text().at(0) == ui.shadowBox1->text().at(0) && ui.shadowBox2->text().at(0) == ui.shadowBox3->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox2->text().at(0) == ui.shadowBox5->text().at(0) && ui.shadowBox2->text().at(0) == ui.shadowBox8->text().at(0))
				displayWinScreen();
		}

		else if (ui.shadowBox3->text() == "(1)")
		{
			ui.shadowBox3->setText(newButtonLabel);

			if (ui.shadowBox3->text().at(0) == ui.shadowBox1->text().at(0) && ui.shadowBox3->text().at(0) == ui.shadowBox2->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox3->text().at(0) == ui.shadowBox6->text().at(0) && ui.shadowBox3->text().at(0) == ui.shadowBox9->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox3->text().at(0) == ui.shadowBox5->text().at(0) && ui.shadowBox3->text().at(0) == ui.shadowBox7->text().at(0))
				displayWinScreen();
		}

		else if (ui.shadowBox4->text() == "(1)")
		{
			ui.shadowBox4->setText(newButtonLabel);
			if (ui.shadowBox4->text().at(0) == ui.shadowBox5->text().at(0) && ui.shadowBox4->text().at(0) == ui.shadowBox6->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox4->text().at(0) == ui.shadowBox1->text().at(0) && ui.shadowBox4->text().at(0) == ui.shadowBox7->text().at(0))
				displayWinScreen();
		}

		else if (ui.shadowBox5->text() == "(1)")
		{
			ui.shadowBox5->setText(newButtonLabel);
			
			if (ui.shadowBox5->text().at(0) == ui.shadowBox2->text().at(0) && ui.shadowBox5->text().at(0) == ui.shadowBox8->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox5->text().at(0) == ui.shadowBox4->text().at(0) && ui.shadowBox5->text().at(0) == ui.shadowBox6->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox5->text().at(0) == ui.shadowBox1->text().at(0) && ui.shadowBox5->text().at(0) == ui.shadowBox9->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox5->text().at(0) == ui.shadowBox3->text().at(0) && ui.shadowBox5->text().at(0) == ui.shadowBox7->text().at(0))
				displayWinScreen();
		}

		else if (ui.shadowBox6->text() == "(1)")
		{
			ui.shadowBox6->setText(newButtonLabel);

			if (ui.shadowBox6->text().at(0) == ui.shadowBox4->text().at(0) && ui.shadowBox6->text().at(0) == ui.shadowBox5->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox6->text().at(0) == ui.shadowBox3->text().at(0) && ui.shadowBox6->text().at(0) == ui.shadowBox9->text().at(0))
				displayWinScreen();
		}

		else if (ui.shadowBox7->text() == "(1)")
		{
			ui.shadowBox7->setText(newButtonLabel);

			if (ui.shadowBox7->text().at(0) == ui.shadowBox1->text().at(0) && ui.shadowBox7->text().at(0) == ui.shadowBox4->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox7->text().at(0) == ui.shadowBox5->text().at(0) && ui.shadowBox7->text().at(0) == ui.shadowBox3->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox7->text().at(0) == ui.shadowBox8->text().at(0) && ui.shadowBox7->text().at(0) == ui.shadowBox9->text().at(0))
				displayWinScreen();
		}
		
		else if (ui.shadowBox8->text() == "(1)")
		{
			ui.shadowBox8->setText(newButtonLabel);

			if (ui.shadowBox8->text().at(0) == ui.shadowBox7->text().at(0) && ui.shadowBox8->text().at(0) == ui.shadowBox9->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox8->text().at(0) == ui.shadowBox2->text().at(0) && ui.shadowBox8->text().at(0) == ui.shadowBox5->text().at(0))
				displayWinScreen();
		}

		else if (ui.shadowBox9->text() == "(1)")
		{
			ui.shadowBox9->setText(newButtonLabel);

			if (ui.shadowBox9->text().at(0) == ui.shadowBox3->text().at(0) && ui.shadowBox9->text().at(0) == ui.shadowBox6->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox9->text().at(0) == ui.shadowBox1->text().at(0) && ui.shadowBox9->text().at(0) == ui.shadowBox5->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox9->text().at(0) == ui.shadowBox7->text().at(0) && ui.shadowBox9->text().at(0) == ui.shadowBox8->text().at(0))
				displayWinScreen();
		}
		//*****************************************

		// If no more moves to make
		if (allMarked())
			displayDrawScreen();

		// Set next player to go
		if (ui.turnLabel->text() == ui.player1NameLabel->text())
			ui.turnLabel->setText(ui.player2NameLabel->text());

		else
			ui.turnLabel->setText(ui.player1NameLabel->text());
	}
}

// Main board button 2
void TicTacToeProject::on_TTTbutton2_clicked() {
	
	// Check if game is not running and if button is already marked
	if (!gameRunning && (ui.TTTbutton2->text() == "(2)"))
		return;

	else if (!(ui.TTTbutton2->text() == "(2)"))
		return;

	// Name the button
	else
	{
		QString player = ui.turnLabel->text();

		QString iconForButton;

		// Get icon of the player who's turn it is
		if (player == ui.player1NameLabel->text())
			iconForButton = ui.player1Icon->text();

		else
			iconForButton = ui.player2Icon->text();

		// Set the button to new text to display who has the spot
		QString newButtonLabel = iconForButton + "(2)";
		ui.TTTbutton2->setText(newButtonLabel);

		// Check main board for win
		if (ui.TTTbutton2->text().at(0) == ui.TTTbutton1->text().at(0) && ui.TTTbutton3->text().at(0) == ui.TTTbutton1->text().at(0))
			displayWinScreen();

		else if (ui.TTTbutton2->text().at(0) == ui.TTTbutton5->text().at(0) && ui.TTTbutton2->text().at(0) == ui.TTTbutton7->text().at(0))
			displayWinScreen();

	//*******************************

		// Check for shadow board box matches
		if (ui.shadowBox1->text() == "(2)")
		{
			ui.shadowBox1->setText(newButtonLabel);
			if (ui.shadowBox1->text().at(0) == ui.shadowBox2->text().at(0) && ui.shadowBox1->text().at(0) == ui.shadowBox3->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox1->text().at(0) == ui.shadowBox5->text().at(0) && ui.shadowBox1->text().at(0) == ui.shadowBox9->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox1->text().at(0) == ui.shadowBox4->text().at(0) && ui.shadowBox1->text().at(0) == ui.shadowBox7->text().at(0))
				displayWinScreen();
		}


		else if (ui.shadowBox2->text() == "(2)")
		{
			ui.shadowBox2->setText(newButtonLabel);
			if (ui.shadowBox2->text().at(0) == ui.shadowBox1->text().at(0) && ui.shadowBox2->text().at(0) == ui.shadowBox3->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox2->text().at(0) == ui.shadowBox5->text().at(0) && ui.shadowBox2->text().at(0) == ui.shadowBox8->text().at(0))
				displayWinScreen();
		}

		else if (ui.shadowBox3->text() == "(2)")
		{
			ui.shadowBox3->setText(newButtonLabel);

			if (ui.shadowBox3->text().at(0) == ui.shadowBox1->text().at(0) && ui.shadowBox3->text().at(0) == ui.shadowBox2->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox3->text().at(0) == ui.shadowBox6->text().at(0) && ui.shadowBox3->text().at(0) == ui.shadowBox9->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox3->text().at(0) == ui.shadowBox5->text().at(0) && ui.shadowBox3->text().at(0) == ui.shadowBox7->text().at(0))
				displayWinScreen();
		}

		else if (ui.shadowBox4->text() == "(2)")
		{
			ui.shadowBox4->setText(newButtonLabel);
			if (ui.shadowBox4->text().at(0) == ui.shadowBox5->text().at(0) && ui.shadowBox4->text().at(0) == ui.shadowBox6->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox4->text().at(0) == ui.shadowBox1->text().at(0) && ui.shadowBox4->text().at(0) == ui.shadowBox7->text().at(0))
				displayWinScreen();
		}

		else if (ui.shadowBox5->text() == "(2)")
		{
			ui.shadowBox5->setText(newButtonLabel);

			if (ui.shadowBox5->text().at(0) == ui.shadowBox2->text().at(0) && ui.shadowBox5->text().at(0) == ui.shadowBox8->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox5->text().at(0) == ui.shadowBox4->text().at(0) && ui.shadowBox5->text().at(0) == ui.shadowBox6->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox5->text().at(0) == ui.shadowBox1->text().at(0) && ui.shadowBox5->text().at(0) == ui.shadowBox9->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox5->text().at(0) == ui.shadowBox3->text().at(0) && ui.shadowBox5->text().at(0) == ui.shadowBox7->text().at(0))
				displayWinScreen();
		}

		else if (ui.shadowBox6->text() == "(2)")
		{
			ui.shadowBox6->setText(newButtonLabel);

			if (ui.shadowBox6->text().at(0) == ui.shadowBox4->text().at(0) && ui.shadowBox6->text().at(0) == ui.shadowBox5->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox6->text().at(0) == ui.shadowBox3->text().at(0) && ui.shadowBox6->text().at(0) == ui.shadowBox9->text().at(0))
				displayWinScreen();
		}

		else if (ui.shadowBox7->text() == "(2)")
		{
			ui.shadowBox7->setText(newButtonLabel);

			if (ui.shadowBox7->text().at(0) == ui.shadowBox1->text().at(0) && ui.shadowBox7->text().at(0) == ui.shadowBox4->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox7->text().at(0) == ui.shadowBox5->text().at(0) && ui.shadowBox7->text().at(0) == ui.shadowBox3->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox7->text().at(0) == ui.shadowBox8->text().at(0) && ui.shadowBox7->text().at(0) == ui.shadowBox9->text().at(0))
				displayWinScreen();
		}

		else if (ui.shadowBox8->text() == "(2)")
		{
			ui.shadowBox8->setText(newButtonLabel);

			if (ui.shadowBox8->text().at(0) == ui.shadowBox7->text().at(0) && ui.shadowBox8->text().at(0) == ui.shadowBox9->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox8->text().at(0) == ui.shadowBox2->text().at(0) && ui.shadowBox8->text().at(0) == ui.shadowBox5->text().at(0))
				displayWinScreen();
		}

		else if (ui.shadowBox9->text() == "(2)")
		{
			ui.shadowBox9->setText(newButtonLabel);

			if (ui.shadowBox9->text().at(0) == ui.shadowBox3->text().at(0) && ui.shadowBox9->text().at(0) == ui.shadowBox6->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox9->text().at(0) == ui.shadowBox1->text().at(0) && ui.shadowBox9->text().at(0) == ui.shadowBox5->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox9->text().at(0) == ui.shadowBox7->text().at(0) && ui.shadowBox9->text().at(0) == ui.shadowBox8->text().at(0))
				displayWinScreen();
		}
		//*****************************************

		// Check for full board
		if (allMarked())
			displayDrawScreen();

		// Set next player to go
		if (ui.turnLabel->text() == ui.player1NameLabel->text())
			ui.turnLabel->setText(ui.player2NameLabel->text());

		else
			ui.turnLabel->setText(ui.player1NameLabel->text());
	}
}

// Main board button 3
void TicTacToeProject::on_TTTbutton3_clicked() {

	// Check if game is not running and if button is marked
	if (!gameRunning && (ui.TTTbutton3->text() == "(3)"))
		return;

	else if (!(ui.TTTbutton3->text() == "(3)"))
		return;

	// Name the button
	else
	{
		QString player = ui.turnLabel->text();

		QString iconForButton;

		// Get player who's turn it is's icon
		if (player == ui.player1NameLabel->text())
			iconForButton = ui.player1Icon->text();

		else
			iconForButton = ui.player2Icon->text();

		// Set the button to new text to display who has the spot
		QString newButtonLabel = iconForButton + "(3)";
		ui.TTTbutton3->setText(newButtonLabel);

		// Check main board for win
		if (ui.TTTbutton2->text().at(0) == ui.TTTbutton1->text().at(0) && ui.TTTbutton3->text().at(0) == ui.TTTbutton1->text().at(0))
			displayWinScreen();

		else if (ui.TTTbutton3->text().at(0) == ui.TTTbutton5->text().at(0) && ui.TTTbutton3->text().at(0) == ui.TTTbutton7->text().at(0))
			displayWinScreen();

		else if (ui.TTTbutton3->text().at(0) == ui.TTTbutton6->text().at(0) && ui.TTTbutton3->text().at(0) == ui.TTTbutton9->text().at(0))
			displayWinScreen();
		//*******************************

		// Find shadow board box matches
		if (ui.shadowBox1->text() == "(3)")
		{
			ui.shadowBox1->setText(newButtonLabel);
			if (ui.shadowBox1->text().at(0) == ui.shadowBox2->text().at(0) && ui.shadowBox1->text().at(0) == ui.shadowBox3->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox1->text().at(0) == ui.shadowBox5->text().at(0) && ui.shadowBox1->text().at(0) == ui.shadowBox9->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox1->text().at(0) == ui.shadowBox4->text().at(0) && ui.shadowBox1->text().at(0) == ui.shadowBox7->text().at(0))
				displayWinScreen();
		}


		else if (ui.shadowBox2->text() == "(3)")
		{
			ui.shadowBox2->setText(newButtonLabel);
			if (ui.shadowBox2->text().at(0) == ui.shadowBox1->text().at(0) && ui.shadowBox2->text().at(0) == ui.shadowBox3->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox2->text().at(0) == ui.shadowBox5->text().at(0) && ui.shadowBox2->text().at(0) == ui.shadowBox8->text().at(0))
				displayWinScreen();
		}

		else if (ui.shadowBox3->text() == "(3)")
		{
			ui.shadowBox3->setText(newButtonLabel);

			if (ui.shadowBox3->text().at(0) == ui.shadowBox1->text().at(0) && ui.shadowBox3->text().at(0) == ui.shadowBox2->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox3->text().at(0) == ui.shadowBox6->text().at(0) && ui.shadowBox3->text().at(0) == ui.shadowBox9->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox3->text().at(0) == ui.shadowBox5->text().at(0) && ui.shadowBox3->text().at(0) == ui.shadowBox7->text().at(0))
				displayWinScreen();
		}

		else if (ui.shadowBox4->text() == "(3)")
		{
			ui.shadowBox4->setText(newButtonLabel);
			if (ui.shadowBox4->text().at(0) == ui.shadowBox5->text().at(0) && ui.shadowBox4->text().at(0) == ui.shadowBox6->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox4->text().at(0) == ui.shadowBox1->text().at(0) && ui.shadowBox4->text().at(0) == ui.shadowBox7->text().at(0))
				displayWinScreen();
		}

		else if (ui.shadowBox5->text() == "(3)")
		{
			ui.shadowBox5->setText(newButtonLabel);

			if (ui.shadowBox5->text().at(0) == ui.shadowBox2->text().at(0) && ui.shadowBox5->text().at(0) == ui.shadowBox8->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox5->text().at(0) == ui.shadowBox4->text().at(0) && ui.shadowBox5->text().at(0) == ui.shadowBox6->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox5->text().at(0) == ui.shadowBox1->text().at(0) && ui.shadowBox5->text().at(0) == ui.shadowBox9->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox5->text().at(0) == ui.shadowBox3->text().at(0) && ui.shadowBox5->text().at(0) == ui.shadowBox7->text().at(0))
				displayWinScreen();
		}

		else if (ui.shadowBox6->text() == "(3)")
		{
			ui.shadowBox6->setText(newButtonLabel);

			if (ui.shadowBox6->text().at(0) == ui.shadowBox4->text().at(0) && ui.shadowBox6->text().at(0) == ui.shadowBox5->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox6->text().at(0) == ui.shadowBox3->text().at(0) && ui.shadowBox6->text().at(0) == ui.shadowBox9->text().at(0))
				displayWinScreen();
		}

		else if (ui.shadowBox7->text() == "(3)")
		{
			ui.shadowBox7->setText(newButtonLabel);

			if (ui.shadowBox7->text().at(0) == ui.shadowBox1->text().at(0) && ui.shadowBox7->text().at(0) == ui.shadowBox4->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox7->text().at(0) == ui.shadowBox5->text().at(0) && ui.shadowBox7->text().at(0) == ui.shadowBox3->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox7->text().at(0) == ui.shadowBox8->text().at(0) && ui.shadowBox7->text().at(0) == ui.shadowBox9->text().at(0))
				displayWinScreen();
		}

		else if (ui.shadowBox8->text() == "(3)")
		{
			ui.shadowBox8->setText(newButtonLabel);

			if (ui.shadowBox8->text().at(0) == ui.shadowBox7->text().at(0) && ui.shadowBox8->text().at(0) == ui.shadowBox9->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox8->text().at(0) == ui.shadowBox2->text().at(0) && ui.shadowBox8->text().at(0) == ui.shadowBox5->text().at(0))
				displayWinScreen();
		}

		else if (ui.shadowBox9->text() == "(3)")
		{
			ui.shadowBox9->setText(newButtonLabel);

			if (ui.shadowBox9->text().at(0) == ui.shadowBox3->text().at(0) && ui.shadowBox9->text().at(0) == ui.shadowBox6->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox9->text().at(0) == ui.shadowBox1->text().at(0) && ui.shadowBox9->text().at(0) == ui.shadowBox5->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox9->text().at(0) == ui.shadowBox7->text().at(0) && ui.shadowBox9->text().at(0) == ui.shadowBox8->text().at(0))
				displayWinScreen();
		}
		//*****************************************

		// Check if board is full
		if (allMarked())
			displayDrawScreen();

		// Set next player to go
		if (ui.turnLabel->text() == ui.player1NameLabel->text())
			ui.turnLabel->setText(ui.player2NameLabel->text());

		else
			ui.turnLabel->setText(ui.player1NameLabel->text());
	}
}

// Main board button 4
void TicTacToeProject::on_TTTbutton4_clicked() {

	// Check if game is not running and if button is already marked
	if (!gameRunning && (ui.TTTbutton4->text() == "(4)"))
		return;

	else if (!(ui.TTTbutton4->text() == "(4)"))
		return;

	// Name the button
	else
	{
		QString player = ui.turnLabel->text();

		QString iconForButton;

		// Get player who's turn it is's icon
		if (player == ui.player1NameLabel->text())
			iconForButton = ui.player1Icon->text();

		else
			iconForButton = ui.player2Icon->text();

		// Set the button to new text to display who has the spot
		QString newButtonLabel = iconForButton + "(4)";
		ui.TTTbutton4->setText(newButtonLabel);

		// Check main board for win
		if (ui.TTTbutton4->text().at(0) == ui.TTTbutton5->text().at(0) && ui.TTTbutton4->text().at(0) == ui.TTTbutton6->text().at(0))
			displayWinScreen();

		else if (ui.TTTbutton4->text().at(0) == ui.TTTbutton1->text().at(0) && ui.TTTbutton4->text().at(0) == ui.TTTbutton7->text().at(0))
			displayWinScreen();
	//*******************************


		// Find shadow board box matches
		if (ui.shadowBox1->text() == "(4)")
		{
			ui.shadowBox1->setText(newButtonLabel);
			if (ui.shadowBox1->text().at(0) == ui.shadowBox2->text().at(0) && ui.shadowBox1->text().at(0) == ui.shadowBox3->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox1->text().at(0) == ui.shadowBox5->text().at(0) && ui.shadowBox1->text().at(0) == ui.shadowBox9->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox1->text().at(0) == ui.shadowBox4->text().at(0) && ui.shadowBox1->text().at(0) == ui.shadowBox7->text().at(0))
				displayWinScreen();
		}


		else if (ui.shadowBox2->text() == "(4)")
		{
			ui.shadowBox2->setText(newButtonLabel);
			if (ui.shadowBox2->text().at(0) == ui.shadowBox1->text().at(0) && ui.shadowBox2->text().at(0) == ui.shadowBox3->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox2->text().at(0) == ui.shadowBox5->text().at(0) && ui.shadowBox2->text().at(0) == ui.shadowBox8->text().at(0))
				displayWinScreen();

		}

		else if (ui.shadowBox3->text() == "(4)")
		{
			ui.shadowBox3->setText(newButtonLabel);

			if (ui.shadowBox3->text().at(0) == ui.shadowBox1->text().at(0) && ui.shadowBox3->text().at(0) == ui.shadowBox2->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox3->text().at(0) == ui.shadowBox6->text().at(0) && ui.shadowBox3->text().at(0) == ui.shadowBox9->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox3->text().at(0) == ui.shadowBox5->text().at(0) && ui.shadowBox3->text().at(0) == ui.shadowBox7->text().at(0))
				displayWinScreen();
		}

		else if (ui.shadowBox4->text() == "(4)")
		{
			ui.shadowBox4->setText(newButtonLabel);
			if (ui.shadowBox4->text().at(0) == ui.shadowBox5->text().at(0) && ui.shadowBox4->text().at(0) == ui.shadowBox6->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox4->text().at(0) == ui.shadowBox1->text().at(0) && ui.shadowBox4->text().at(0) == ui.shadowBox7->text().at(0))
				displayWinScreen();
		}

		else if (ui.shadowBox5->text() == "(4)")
		{
			ui.shadowBox5->setText(newButtonLabel);

			if (ui.shadowBox5->text().at(0) == ui.shadowBox2->text().at(0) && ui.shadowBox5->text().at(0) == ui.shadowBox8->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox5->text().at(0) == ui.shadowBox4->text().at(0) && ui.shadowBox5->text().at(0) == ui.shadowBox6->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox5->text().at(0) == ui.shadowBox1->text().at(0) && ui.shadowBox5->text().at(0) == ui.shadowBox9->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox5->text().at(0) == ui.shadowBox3->text().at(0) && ui.shadowBox5->text().at(0) == ui.shadowBox7->text().at(0))
				displayWinScreen();
		}

		else if (ui.shadowBox6->text() == "(4)")
		{
			ui.shadowBox6->setText(newButtonLabel);

			if (ui.shadowBox6->text().at(0) == ui.shadowBox4->text().at(0) && ui.shadowBox6->text().at(0) == ui.shadowBox5->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox6->text().at(0) == ui.shadowBox3->text().at(0) && ui.shadowBox6->text().at(0) == ui.shadowBox9->text().at(0))
				displayWinScreen();
		}

		else if (ui.shadowBox7->text() == "(4)")
		{
			ui.shadowBox7->setText(newButtonLabel);

			if (ui.shadowBox7->text().at(0) == ui.shadowBox1->text().at(0) && ui.shadowBox7->text().at(0) == ui.shadowBox4->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox7->text().at(0) == ui.shadowBox5->text().at(0) && ui.shadowBox7->text().at(0) == ui.shadowBox3->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox7->text().at(0) == ui.shadowBox8->text().at(0) && ui.shadowBox7->text().at(0) == ui.shadowBox9->text().at(0))
				displayWinScreen();

		}

		else if (ui.shadowBox8->text() == "(4)")
		{
			ui.shadowBox8->setText(newButtonLabel);

			if (ui.shadowBox8->text().at(0) == ui.shadowBox7->text().at(0) && ui.shadowBox8->text().at(0) == ui.shadowBox9->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox8->text().at(0) == ui.shadowBox2->text().at(0) && ui.shadowBox8->text().at(0) == ui.shadowBox5->text().at(0))
				displayWinScreen();
		}

		else if (ui.shadowBox9->text() == "(4)")
		{
			ui.shadowBox9->setText(newButtonLabel);

			if (ui.shadowBox9->text().at(0) == ui.shadowBox3->text().at(0) && ui.shadowBox9->text().at(0) == ui.shadowBox6->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox9->text().at(0) == ui.shadowBox1->text().at(0) && ui.shadowBox9->text().at(0) == ui.shadowBox5->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox9->text().at(0) == ui.shadowBox7->text().at(0) && ui.shadowBox9->text().at(0) == ui.shadowBox8->text().at(0))
				displayWinScreen();
		}
		//*****************************************

		// Check for full board
		if (allMarked())
			displayDrawScreen();

		// SET NEXT PLAYER TO GO
		if (ui.turnLabel->text() == ui.player1NameLabel->text())
			ui.turnLabel->setText(ui.player2NameLabel->text());

		else
			ui.turnLabel->setText(ui.player1NameLabel->text());
	}
}

// Main board button 5
void TicTacToeProject::on_TTTbutton5_clicked() {

	// Check if game is not running/icon marked
	if (!gameRunning && (ui.TTTbutton5->text() == "(5)"))
		return;

	else if (!(ui.TTTbutton5->text() == "(5)"))
		return;

	// Name the button
	else
	{
		QString player = ui.turnLabel->text();

		QString iconForButton;

		// Get icon of player who's turn it is
		if (player == ui.player1NameLabel->text())
			iconForButton = ui.player1Icon->text();

		else
			iconForButton = ui.player2Icon->text();

		// Set the button to new text to display who has the spot
		QString newButtonLabel = iconForButton + "(5)";
		ui.TTTbutton5->setText(newButtonLabel);

		// Check main board for win
		if (ui.TTTbutton5->text().at(0) == ui.TTTbutton2->text().at(0) && ui.TTTbutton5->text().at(0) == ui.TTTbutton8->text().at(0))
			displayWinScreen();

		else if (ui.TTTbutton5->text().at(0) == ui.TTTbutton1->text().at(0) && ui.TTTbutton5->text().at(0) == ui.TTTbutton9->text().at(0))
			displayWinScreen();

		else if (ui.TTTbutton5->text().at(0) == ui.TTTbutton4->text().at(0) && ui.TTTbutton5->text().at(0) == ui.TTTbutton6->text().at(0))
			displayWinScreen();

		else if (ui.TTTbutton5->text().at(0) == ui.TTTbutton3->text().at(0) && ui.TTTbutton5->text().at(0) == ui.TTTbutton7->text().at(0))
			displayWinScreen();
	//*******************************

	// Check shadow board boxes for matches
		if (ui.shadowBox1->text() == "(5)")
		{
			ui.shadowBox1->setText(newButtonLabel);
			if (ui.shadowBox1->text().at(0) == ui.shadowBox2->text().at(0) && ui.shadowBox1->text().at(0) == ui.shadowBox3->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox1->text().at(0) == ui.shadowBox5->text().at(0) && ui.shadowBox1->text().at(0) == ui.shadowBox9->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox1->text().at(0) == ui.shadowBox4->text().at(0) && ui.shadowBox1->text().at(0) == ui.shadowBox7->text().at(0))
				displayWinScreen();
		}


		else if (ui.shadowBox2->text() == "(5)")
		{
			ui.shadowBox2->setText(newButtonLabel);
			if (ui.shadowBox2->text().at(0) == ui.shadowBox1->text().at(0) && ui.shadowBox2->text().at(0) == ui.shadowBox3->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox2->text().at(0) == ui.shadowBox5->text().at(0) && ui.shadowBox2->text().at(0) == ui.shadowBox8->text().at(0))
				displayWinScreen();
		}

		else if (ui.shadowBox3->text() == "(5)")
		{
			ui.shadowBox3->setText(newButtonLabel);

			if (ui.shadowBox3->text().at(0) == ui.shadowBox1->text().at(0) && ui.shadowBox3->text().at(0) == ui.shadowBox2->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox3->text().at(0) == ui.shadowBox6->text().at(0) && ui.shadowBox3->text().at(0) == ui.shadowBox9->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox3->text().at(0) == ui.shadowBox5->text().at(0) && ui.shadowBox3->text().at(0) == ui.shadowBox7->text().at(0))
				displayWinScreen();
		}

		else if (ui.shadowBox4->text() == "(5)")
		{
			ui.shadowBox4->setText(newButtonLabel);
			if (ui.shadowBox4->text().at(0) == ui.shadowBox5->text().at(0) && ui.shadowBox4->text().at(0) == ui.shadowBox6->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox4->text().at(0) == ui.shadowBox1->text().at(0) && ui.shadowBox4->text().at(0) == ui.shadowBox7->text().at(0))
				displayWinScreen();
		}

		else if (ui.shadowBox5->text() == "(5)")
		{
			ui.shadowBox5->setText(newButtonLabel);

			if (ui.shadowBox5->text().at(0) == ui.shadowBox2->text().at(0) && ui.shadowBox5->text().at(0) == ui.shadowBox8->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox5->text().at(0) == ui.shadowBox4->text().at(0) && ui.shadowBox5->text().at(0) == ui.shadowBox6->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox5->text().at(0) == ui.shadowBox1->text().at(0) && ui.shadowBox5->text().at(0) == ui.shadowBox9->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox5->text().at(0) == ui.shadowBox3->text().at(0) && ui.shadowBox5->text().at(0) == ui.shadowBox7->text().at(0))
				displayWinScreen();
		}

		else if (ui.shadowBox6->text() == "(5)")
		{
			ui.shadowBox6->setText(newButtonLabel);

			if (ui.shadowBox6->text().at(0) == ui.shadowBox4->text().at(0) && ui.shadowBox6->text().at(0) == ui.shadowBox5->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox6->text().at(0) == ui.shadowBox3->text().at(0) && ui.shadowBox6->text().at(0) == ui.shadowBox9->text().at(0))
				displayWinScreen();
		}

		else if (ui.shadowBox7->text() == "(1)")
		{
			ui.shadowBox7->setText(newButtonLabel);

			if (ui.shadowBox7->text().at(0) == ui.shadowBox1->text().at(0) && ui.shadowBox7->text().at(0) == ui.shadowBox4->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox7->text().at(0) == ui.shadowBox5->text().at(0) && ui.shadowBox7->text().at(0) == ui.shadowBox3->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox7->text().at(0) == ui.shadowBox8->text().at(0) && ui.shadowBox7->text().at(0) == ui.shadowBox9->text().at(0))
				displayWinScreen();
		}

		else if (ui.shadowBox8->text() == "(5)")
		{
			ui.shadowBox8->setText(newButtonLabel);

			if (ui.shadowBox8->text().at(0) == ui.shadowBox7->text().at(0) && ui.shadowBox8->text().at(0) == ui.shadowBox9->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox8->text().at(0) == ui.shadowBox2->text().at(0) && ui.shadowBox8->text().at(0) == ui.shadowBox5->text().at(0))
				displayWinScreen();
		}

		else if (ui.shadowBox9->text() == "(5)")
		{
			ui.shadowBox9->setText(newButtonLabel);

			if (ui.shadowBox9->text().at(0) == ui.shadowBox3->text().at(0) && ui.shadowBox9->text().at(0) == ui.shadowBox6->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox9->text().at(0) == ui.shadowBox1->text().at(0) && ui.shadowBox9->text().at(0) == ui.shadowBox5->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox9->text().at(0) == ui.shadowBox7->text().at(0) && ui.shadowBox9->text().at(0) == ui.shadowBox8->text().at(0))
				displayWinScreen();
		}
		//*****************************************

		// Check if board is full
		if (allMarked())
			displayDrawScreen();

		// Set next player to go
		if (ui.turnLabel->text() == ui.player1NameLabel->text())
			ui.turnLabel->setText(ui.player2NameLabel->text());

		else
			ui.turnLabel->setText(ui.player1NameLabel->text());
	}
}

// Main board button 6
void TicTacToeProject::on_TTTbutton6_clicked() {

	// Check if game is not running/icon marked
	if (!gameRunning && (ui.TTTbutton6->text() == "(6)"))
		return;

	else if (!(ui.TTTbutton6->text() == "(6)"))
		return;

	// Name the button
	else
	{
		QString player = ui.turnLabel->text();

		QString iconForButton;

		// Get icon of player who's turn it is
		if (player == ui.player1NameLabel->text())
			iconForButton = ui.player1Icon->text();

		else
			iconForButton = ui.player2Icon->text();

		// Set the button to new text to display who has the spot
		QString newButtonLabel = iconForButton + "(6)";
		ui.TTTbutton6->setText(newButtonLabel);

		// Check main board for win
		if (ui.TTTbutton6->text().at(0) == ui.TTTbutton3->text().at(0) && ui.TTTbutton6->text().at(0) == ui.TTTbutton9->text().at(0))
			displayWinScreen();

		else if (ui.TTTbutton6->text().at(0) == ui.TTTbutton5->text().at(0) && ui.TTTbutton6->text().at(0) == ui.TTTbutton4->text().at(0))
			displayWinScreen();
	//*******************************

	// Check shadow board for matches
		if (ui.shadowBox1->text() == "(6)")
		{
			ui.shadowBox1->setText(newButtonLabel);
			if (ui.shadowBox1->text().at(0) == ui.shadowBox2->text().at(0) && ui.shadowBox1->text().at(0) == ui.shadowBox3->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox1->text().at(0) == ui.shadowBox5->text().at(0) && ui.shadowBox1->text().at(0) == ui.shadowBox9->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox1->text().at(0) == ui.shadowBox4->text().at(0) && ui.shadowBox1->text().at(0) == ui.shadowBox7->text().at(0))
				displayWinScreen();
		}

		else if (ui.shadowBox2->text() == "(6)")
		{
			ui.shadowBox2->setText(newButtonLabel);
			if (ui.shadowBox2->text().at(0) == ui.shadowBox1->text().at(0) && ui.shadowBox2->text().at(0) == ui.shadowBox3->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox2->text().at(0) == ui.shadowBox5->text().at(0) && ui.shadowBox2->text().at(0) == ui.shadowBox8->text().at(0))
				displayWinScreen();
		}

		else if (ui.shadowBox3->text() == "(6)")
		{
			ui.shadowBox3->setText(newButtonLabel);

			if (ui.shadowBox3->text().at(0) == ui.shadowBox1->text().at(0) && ui.shadowBox3->text().at(0) == ui.shadowBox2->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox3->text().at(0) == ui.shadowBox6->text().at(0) && ui.shadowBox3->text().at(0) == ui.shadowBox9->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox3->text().at(0) == ui.shadowBox5->text().at(0) && ui.shadowBox3->text().at(0) == ui.shadowBox7->text().at(0))
				displayWinScreen();
		}

		else if (ui.shadowBox4->text() == "(6)")
		{
			ui.shadowBox4->setText(newButtonLabel);
			if (ui.shadowBox4->text().at(0) == ui.shadowBox5->text().at(0) && ui.shadowBox4->text().at(0) == ui.shadowBox6->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox4->text().at(0) == ui.shadowBox1->text().at(0) && ui.shadowBox4->text().at(0) == ui.shadowBox7->text().at(0))
				displayWinScreen();
		}

		else if (ui.shadowBox5->text() == "(6)")
		{
			ui.shadowBox5->setText(newButtonLabel);

			if (ui.shadowBox5->text().at(0) == ui.shadowBox2->text().at(0) && ui.shadowBox5->text().at(0) == ui.shadowBox8->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox5->text().at(0) == ui.shadowBox4->text().at(0) && ui.shadowBox5->text().at(0) == ui.shadowBox6->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox5->text().at(0) == ui.shadowBox1->text().at(0) && ui.shadowBox5->text().at(0) == ui.shadowBox9->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox5->text().at(0) == ui.shadowBox3->text().at(0) && ui.shadowBox5->text().at(0) == ui.shadowBox7->text().at(0))
				displayWinScreen();
		}

		else if (ui.shadowBox6->text() == "(6)")
		{
			ui.shadowBox6->setText(newButtonLabel);

			if (ui.shadowBox6->text().at(0) == ui.shadowBox4->text().at(0) && ui.shadowBox6->text().at(0) == ui.shadowBox5->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox6->text().at(0) == ui.shadowBox3->text().at(0) && ui.shadowBox6->text().at(0) == ui.shadowBox9->text().at(0))
				displayWinScreen();
		}

		else if (ui.shadowBox7->text() == "(6)")
		{
			ui.shadowBox7->setText(newButtonLabel);

			if (ui.shadowBox7->text().at(0) == ui.shadowBox1->text().at(0) && ui.shadowBox7->text().at(0) == ui.shadowBox4->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox7->text().at(0) == ui.shadowBox5->text().at(0) && ui.shadowBox7->text().at(0) == ui.shadowBox3->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox7->text().at(0) == ui.shadowBox8->text().at(0) && ui.shadowBox7->text().at(0) == ui.shadowBox9->text().at(0))
				displayWinScreen();
		}

		else if (ui.shadowBox8->text() == "(6)")
		{
			ui.shadowBox8->setText(newButtonLabel);

			if (ui.shadowBox8->text().at(0) == ui.shadowBox7->text().at(0) && ui.shadowBox8->text().at(0) == ui.shadowBox9->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox8->text().at(0) == ui.shadowBox2->text().at(0) && ui.shadowBox8->text().at(0) == ui.shadowBox5->text().at(0))
				displayWinScreen();
		}

		else if (ui.shadowBox9->text() == "(6)")
		{
			ui.shadowBox9->setText(newButtonLabel);

			if (ui.shadowBox9->text().at(0) == ui.shadowBox3->text().at(0) && ui.shadowBox9->text().at(0) == ui.shadowBox6->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox9->text().at(0) == ui.shadowBox1->text().at(0) && ui.shadowBox9->text().at(0) == ui.shadowBox5->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox9->text().at(0) == ui.shadowBox7->text().at(0) && ui.shadowBox9->text().at(0) == ui.shadowBox8->text().at(0))
				displayWinScreen();
		}
		//*****************************************

		// Check if board is full
		if (allMarked())
			displayDrawScreen();

		// Set next player to go
		if (ui.turnLabel->text() == ui.player1NameLabel->text())
			ui.turnLabel->setText(ui.player2NameLabel->text());

		else
			ui.turnLabel->setText(ui.player1NameLabel->text());
	}
}

// Main board button 7
void TicTacToeProject::on_TTTbutton7_clicked() {

	// Check if game is not running/icon marked
	if (!gameRunning && (ui.TTTbutton7->text() == "(7)"))
		return;

	else if (!(ui.TTTbutton7->text() == "(7)"))
		return;

	// Name the button
	else
	{
		QString player = ui.turnLabel->text();

		QString iconForButton;

		// Get player who's turn it is's icon
		if (player == ui.player1NameLabel->text())
			iconForButton = ui.player1Icon->text();

		else
			iconForButton = ui.player2Icon->text();

		// Set the button to new text to display who has the spot
		QString newButtonLabel = iconForButton + "(7)";
		ui.TTTbutton7->setText(newButtonLabel);

		// Check main board for win
		if (ui.TTTbutton7->text().at(0) == ui.TTTbutton8->text().at(0) && ui.TTTbutton7->text().at(0) == ui.TTTbutton9->text().at(0))
			displayWinScreen();

		else if (ui.TTTbutton7->text().at(0) == ui.TTTbutton1->text().at(0) && ui.TTTbutton7->text().at(0) == ui.TTTbutton4->text().at(0))
			displayWinScreen();

		else if (ui.TTTbutton7->text().at(0) == ui.TTTbutton5->text().at(0) && ui.TTTbutton7->text().at(0) == ui.TTTbutton3->text().at(0))
			displayWinScreen();
	//*******************************

	// Check shadow board for matches
		QString shadowMarker;
		if (ui.shadowBox1->text() == "(7)")
		{
			ui.shadowBox1->setText(newButtonLabel);
			if (ui.shadowBox1->text().at(0) == ui.shadowBox2->text().at(0) && ui.shadowBox1->text().at(0) == ui.shadowBox3->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox1->text().at(0) == ui.shadowBox5->text().at(0) && ui.shadowBox1->text().at(0) == ui.shadowBox9->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox1->text().at(0) == ui.shadowBox4->text().at(0) && ui.shadowBox1->text().at(0) == ui.shadowBox7->text().at(0))
				displayWinScreen();
		}

		else if (ui.shadowBox2->text() == "(7)")
		{
			ui.shadowBox2->setText(newButtonLabel);
			if (ui.shadowBox2->text().at(0) == ui.shadowBox1->text().at(0) && ui.shadowBox2->text().at(0) == ui.shadowBox3->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox2->text().at(0) == ui.shadowBox5->text().at(0) && ui.shadowBox2->text().at(0) == ui.shadowBox8->text().at(0))
				displayWinScreen();
		}

		else if (ui.shadowBox3->text() == "(7)")
		{
			ui.shadowBox3->setText(newButtonLabel);

			if (ui.shadowBox3->text().at(0) == ui.shadowBox1->text().at(0) && ui.shadowBox3->text().at(0) == ui.shadowBox2->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox3->text().at(0) == ui.shadowBox6->text().at(0) && ui.shadowBox3->text().at(0) == ui.shadowBox9->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox3->text().at(0) == ui.shadowBox5->text().at(0) && ui.shadowBox3->text().at(0) == ui.shadowBox7->text().at(0))
				displayWinScreen();
		}

		else if (ui.shadowBox4->text() == "(7)")
		{
			ui.shadowBox4->setText(newButtonLabel);
			if (ui.shadowBox4->text().at(0) == ui.shadowBox5->text().at(0) && ui.shadowBox4->text().at(0) == ui.shadowBox6->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox4->text().at(0) == ui.shadowBox1->text().at(0) && ui.shadowBox4->text().at(0) == ui.shadowBox7->text().at(0))
				displayWinScreen();
		}

		else if (ui.shadowBox5->text() == "(7)")
		{
			ui.shadowBox5->setText(newButtonLabel);

			if (ui.shadowBox5->text().at(0) == ui.shadowBox2->text().at(0) && ui.shadowBox5->text().at(0) == ui.shadowBox8->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox5->text().at(0) == ui.shadowBox4->text().at(0) && ui.shadowBox5->text().at(0) == ui.shadowBox6->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox5->text().at(0) == ui.shadowBox1->text().at(0) && ui.shadowBox5->text().at(0) == ui.shadowBox9->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox5->text().at(0) == ui.shadowBox3->text().at(0) && ui.shadowBox5->text().at(0) == ui.shadowBox7->text().at(0))
				displayWinScreen();
		}

		else if (ui.shadowBox6->text() == "(7)")
		{
			ui.shadowBox6->setText(newButtonLabel);

			if (ui.shadowBox6->text().at(0) == ui.shadowBox4->text().at(0) && ui.shadowBox6->text().at(0) == ui.shadowBox5->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox6->text().at(0) == ui.shadowBox3->text().at(0) && ui.shadowBox6->text().at(0) == ui.shadowBox9->text().at(0))
				displayWinScreen();
		}

		else if (ui.shadowBox7->text() == "(7)")
		{
			ui.shadowBox7->setText(newButtonLabel);

			if (ui.shadowBox7->text().at(0) == ui.shadowBox1->text().at(0) && ui.shadowBox7->text().at(0) == ui.shadowBox4->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox7->text().at(0) == ui.shadowBox5->text().at(0) && ui.shadowBox7->text().at(0) == ui.shadowBox3->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox7->text().at(0) == ui.shadowBox8->text().at(0) && ui.shadowBox7->text().at(0) == ui.shadowBox9->text().at(0))
				displayWinScreen();
		}

		else if (ui.shadowBox8->text() == "(7)")
		{
			ui.shadowBox8->setText(newButtonLabel);

			if (ui.shadowBox8->text().at(0) == ui.shadowBox7->text().at(0) && ui.shadowBox8->text().at(0) == ui.shadowBox9->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox8->text().at(0) == ui.shadowBox2->text().at(0) && ui.shadowBox8->text().at(0) == ui.shadowBox5->text().at(0))
				displayWinScreen();
		}

		else if (ui.shadowBox9->text() == "(7)")
		{
			ui.shadowBox9->setText(newButtonLabel);

			if (ui.shadowBox9->text().at(0) == ui.shadowBox3->text().at(0) && ui.shadowBox9->text().at(0) == ui.shadowBox6->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox9->text().at(0) == ui.shadowBox1->text().at(0) && ui.shadowBox9->text().at(0) == ui.shadowBox5->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox9->text().at(0) == ui.shadowBox7->text().at(0) && ui.shadowBox9->text().at(0) == ui.shadowBox8->text().at(0))
				displayWinScreen();
		}
		//*****************************************

		// Check if board is full
		if (allMarked())
			displayDrawScreen();

		// Set next player to go
		if (ui.turnLabel->text() == ui.player1NameLabel->text())
			ui.turnLabel->setText(ui.player2NameLabel->text());

		else
			ui.turnLabel->setText(ui.player1NameLabel->text());
	}
}

// Main board button 8
void TicTacToeProject::on_TTTbutton8_clicked() {

	// Check if game is not running/icon marked
	if (!gameRunning && (ui.TTTbutton8->text() == "(8)"))
		return;

	else if (!(ui.TTTbutton8->text() == "(8)"))
		return;

	// Name the button
	else
	{
		QString player = ui.turnLabel->text();

		QString iconForButton;

		// Get player who's turn it is's icon
		if (player == ui.player1NameLabel->text())
			iconForButton = ui.player1Icon->text();

		else
			iconForButton = ui.player2Icon->text();

		// Set the button to new text to display who has the spot
		QString newButtonLabel = iconForButton + "(8)";
		ui.TTTbutton8->setText(newButtonLabel);

		// Check main board for win
		if (ui.TTTbutton8->text().at(0) == ui.TTTbutton9->text().at(0) && ui.TTTbutton8->text().at(0) == ui.TTTbutton7->text().at(0))
			displayWinScreen();

		else if (ui.TTTbutton8->text().at(0) == ui.TTTbutton5->text().at(0) && ui.TTTbutton8->text().at(0) == ui.TTTbutton2->text().at(0))
			displayWinScreen();
	//*******************************

	// Check shadow board for matches
		if (ui.shadowBox1->text() == "(8)")
		{
			ui.shadowBox1->setText(newButtonLabel);
			if (ui.shadowBox1->text().at(0) == ui.shadowBox2->text().at(0) && ui.shadowBox1->text().at(0) == ui.shadowBox3->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox1->text().at(0) == ui.shadowBox5->text().at(0) && ui.shadowBox1->text().at(0) == ui.shadowBox9->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox1->text().at(0) == ui.shadowBox4->text().at(0) && ui.shadowBox1->text().at(0) == ui.shadowBox7->text().at(0))
				displayWinScreen();
		}

		else if (ui.shadowBox2->text() == "(8)")
		{
			ui.shadowBox2->setText(newButtonLabel);
			if (ui.shadowBox2->text().at(0) == ui.shadowBox1->text().at(0) && ui.shadowBox2->text().at(0) == ui.shadowBox3->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox2->text().at(0) == ui.shadowBox5->text().at(0) && ui.shadowBox2->text().at(0) == ui.shadowBox8->text().at(0))
				displayWinScreen();
		}

		else if (ui.shadowBox3->text() == "(8)")
		{
			ui.shadowBox3->setText(newButtonLabel);

			if (ui.shadowBox3->text().at(0) == ui.shadowBox1->text().at(0) && ui.shadowBox3->text().at(0) == ui.shadowBox2->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox3->text().at(0) == ui.shadowBox6->text().at(0) && ui.shadowBox3->text().at(0) == ui.shadowBox9->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox3->text().at(0) == ui.shadowBox5->text().at(0) && ui.shadowBox3->text().at(0) == ui.shadowBox7->text().at(0))
				displayWinScreen();
		}

		else if (ui.shadowBox4->text() == "(8)")
		{
			ui.shadowBox4->setText(newButtonLabel);
			if (ui.shadowBox4->text().at(0) == ui.shadowBox5->text().at(0) && ui.shadowBox4->text().at(0) == ui.shadowBox6->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox4->text().at(0) == ui.shadowBox1->text().at(0) && ui.shadowBox4->text().at(0) == ui.shadowBox7->text().at(0))
				displayWinScreen();
		}

		else if (ui.shadowBox5->text() == "(8)")
		{
			ui.shadowBox5->setText(newButtonLabel);

			if (ui.shadowBox5->text().at(0) == ui.shadowBox2->text().at(0) && ui.shadowBox5->text().at(0) == ui.shadowBox8->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox5->text().at(0) == ui.shadowBox4->text().at(0) && ui.shadowBox5->text().at(0) == ui.shadowBox6->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox5->text().at(0) == ui.shadowBox1->text().at(0) && ui.shadowBox5->text().at(0) == ui.shadowBox9->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox5->text().at(0) == ui.shadowBox3->text().at(0) && ui.shadowBox5->text().at(0) == ui.shadowBox7->text().at(0))
				displayWinScreen();
		}

		else if (ui.shadowBox6->text() == "(8)")
		{
			ui.shadowBox6->setText(newButtonLabel);

			if (ui.shadowBox6->text().at(0) == ui.shadowBox4->text().at(0) && ui.shadowBox6->text().at(0) == ui.shadowBox5->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox6->text().at(0) == ui.shadowBox3->text().at(0) && ui.shadowBox6->text().at(0) == ui.shadowBox9->text().at(0))
				displayWinScreen();
		}

		else if (ui.shadowBox7->text() == "(8)")
		{
			ui.shadowBox7->setText(newButtonLabel);

			if (ui.shadowBox7->text().at(0) == ui.shadowBox1->text().at(0) && ui.shadowBox7->text().at(0) == ui.shadowBox4->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox7->text().at(0) == ui.shadowBox5->text().at(0) && ui.shadowBox7->text().at(0) == ui.shadowBox3->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox7->text().at(0) == ui.shadowBox8->text().at(0) && ui.shadowBox7->text().at(0) == ui.shadowBox9->text().at(0))
				displayWinScreen();
		}

		else if (ui.shadowBox8->text() == "(8)")
		{
			ui.shadowBox8->setText(newButtonLabel);

			if (ui.shadowBox8->text().at(0) == ui.shadowBox7->text().at(0) && ui.shadowBox8->text().at(0) == ui.shadowBox9->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox8->text().at(0) == ui.shadowBox2->text().at(0) && ui.shadowBox8->text().at(0) == ui.shadowBox5->text().at(0))
				displayWinScreen();
		}

		else if (ui.shadowBox9->text() == "(8)")
		{
			ui.shadowBox9->setText(newButtonLabel);

			if (ui.shadowBox9->text().at(0) == ui.shadowBox3->text().at(0) && ui.shadowBox9->text().at(0) == ui.shadowBox6->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox9->text().at(0) == ui.shadowBox1->text().at(0) && ui.shadowBox9->text().at(0) == ui.shadowBox5->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox9->text().at(0) == ui.shadowBox7->text().at(0) && ui.shadowBox9->text().at(0) == ui.shadowBox8->text().at(0))
				displayWinScreen();
		}
		//*****************************************

		// Check if board is full
		if (allMarked())
			displayDrawScreen();

		// Set next player to go
		if (ui.turnLabel->text() == ui.player1NameLabel->text())
			ui.turnLabel->setText(ui.player2NameLabel->text());

		else
			ui.turnLabel->setText(ui.player1NameLabel->text());
	}
}

// Main board button 9
void TicTacToeProject::on_TTTbutton9_clicked() {

	// Check if game is not running/icon marked
	if (!gameRunning && (ui.TTTbutton9->text() == "(9)"))
		return;

	else if (!(ui.TTTbutton9->text() == "(9)"))
		return;

	// Name the button
	else
	{
		QString player = ui.turnLabel->text();

		QString iconForButton;

		// Get icon of player who's turn it is
		if (player == ui.player1NameLabel->text())
			iconForButton = ui.player1Icon->text();

		else
			iconForButton = ui.player2Icon->text();

		// Set the button to new text to display who has the spot
		QString newButtonLabel = iconForButton + "(9)";
		ui.TTTbutton9->setText(newButtonLabel);

		// Check main board for win
		if (ui.TTTbutton9->text().at(0) == ui.TTTbutton7->text().at(0) && ui.TTTbutton9->text().at(0) == ui.TTTbutton8->text().at(0))
			displayWinScreen();

		else if (ui.TTTbutton9->text().at(0) == ui.TTTbutton6->text().at(0) && ui.TTTbutton9->text().at(0) == ui.TTTbutton3->text().at(0))
			displayWinScreen();

		else if (ui.TTTbutton9->text().at(0) == ui.TTTbutton5->text().at(0) && ui.TTTbutton9->text().at(0) == ui.TTTbutton1->text().at(0))
			displayWinScreen();
	//*******************************

	// Check shadow board for matches
		if (ui.shadowBox1->text() == "(9)")
		{
			ui.shadowBox1->setText(newButtonLabel);
			if (ui.shadowBox1->text().at(0) == ui.shadowBox2->text().at(0) && ui.shadowBox1->text().at(0) == ui.shadowBox3->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox1->text().at(0) == ui.shadowBox5->text().at(0) && ui.shadowBox1->text().at(0) == ui.shadowBox9->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox1->text().at(0) == ui.shadowBox4->text().at(0) && ui.shadowBox1->text().at(0) == ui.shadowBox7->text().at(0))
				displayWinScreen();
		}

		else if (ui.shadowBox2->text() == "(9)")
		{
			ui.shadowBox2->setText(newButtonLabel);
			if (ui.shadowBox2->text().at(0) == ui.shadowBox1->text().at(0) && ui.shadowBox2->text().at(0) == ui.shadowBox3->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox2->text().at(0) == ui.shadowBox5->text().at(0) && ui.shadowBox2->text().at(0) == ui.shadowBox8->text().at(0))
				displayWinScreen();
		}

		else if (ui.shadowBox3->text() == "(9)")
		{
			ui.shadowBox3->setText(newButtonLabel);

			if (ui.shadowBox3->text().at(0) == ui.shadowBox1->text().at(0) && ui.shadowBox3->text().at(0) == ui.shadowBox2->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox3->text().at(0) == ui.shadowBox6->text().at(0) && ui.shadowBox3->text().at(0) == ui.shadowBox9->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox3->text().at(0) == ui.shadowBox5->text().at(0) && ui.shadowBox3->text().at(0) == ui.shadowBox7->text().at(0))
				displayWinScreen();
		}

		else if (ui.shadowBox4->text() == "(9)")
		{
			ui.shadowBox4->setText(newButtonLabel);
			if (ui.shadowBox4->text().at(0) == ui.shadowBox5->text().at(0) && ui.shadowBox4->text().at(0) == ui.shadowBox6->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox4->text().at(0) == ui.shadowBox1->text().at(0) && ui.shadowBox4->text().at(0) == ui.shadowBox7->text().at(0))
				displayWinScreen();
		}

		else if (ui.shadowBox5->text() == "(9)")
		{
			ui.shadowBox5->setText(newButtonLabel);

			if (ui.shadowBox5->text().at(0) == ui.shadowBox2->text().at(0) && ui.shadowBox5->text().at(0) == ui.shadowBox8->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox5->text().at(0) == ui.shadowBox4->text().at(0) && ui.shadowBox5->text().at(0) == ui.shadowBox6->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox5->text().at(0) == ui.shadowBox1->text().at(0) && ui.shadowBox5->text().at(0) == ui.shadowBox9->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox5->text().at(0) == ui.shadowBox3->text().at(0) && ui.shadowBox5->text().at(0) == ui.shadowBox7->text().at(0))
				displayWinScreen();
		}

		else if (ui.shadowBox6->text() == "(9)")
		{
			ui.shadowBox6->setText(newButtonLabel);

			if (ui.shadowBox6->text().at(0) == ui.shadowBox4->text().at(0) && ui.shadowBox6->text().at(0) == ui.shadowBox5->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox6->text().at(0) == ui.shadowBox3->text().at(0) && ui.shadowBox6->text().at(0) == ui.shadowBox9->text().at(0))
				displayWinScreen();
		}

		else if (ui.shadowBox7->text() == "(9)")
		{
			ui.shadowBox7->setText(newButtonLabel);

			if (ui.shadowBox7->text().at(0) == ui.shadowBox1->text().at(0) && ui.shadowBox7->text().at(0) == ui.shadowBox4->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox7->text().at(0) == ui.shadowBox5->text().at(0) && ui.shadowBox7->text().at(0) == ui.shadowBox3->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox7->text().at(0) == ui.shadowBox8->text().at(0) && ui.shadowBox7->text().at(0) == ui.shadowBox9->text().at(0))
				displayWinScreen();
		}

		else if (ui.shadowBox8->text() == "(9)")
		{
			ui.shadowBox8->setText(newButtonLabel);

			if (ui.shadowBox8->text().at(0) == ui.shadowBox7->text().at(0) && ui.shadowBox8->text().at(0) == ui.shadowBox9->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox8->text().at(0) == ui.shadowBox2->text().at(0) && ui.shadowBox8->text().at(0) == ui.shadowBox5->text().at(0))
				displayWinScreen();

		}

		else if (ui.shadowBox9->text() == "(9)")
		{
			ui.shadowBox9->setText(newButtonLabel);

			if (ui.shadowBox9->text().at(0) == ui.shadowBox3->text().at(0) && ui.shadowBox9->text().at(0) == ui.shadowBox6->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox9->text().at(0) == ui.shadowBox1->text().at(0) && ui.shadowBox9->text().at(0) == ui.shadowBox5->text().at(0))
				displayWinScreen();

			else if (ui.shadowBox9->text().at(0) == ui.shadowBox7->text().at(0) && ui.shadowBox9->text().at(0) == ui.shadowBox8->text().at(0))
				displayWinScreen();
		}
		//*****************************************

		// Check if board is full
		if (allMarked())
			displayDrawScreen();

		// Set next player to go
		if (ui.turnLabel->text() == ui.player1NameLabel->text())
			ui.turnLabel->setText(ui.player2NameLabel->text());

		else
			ui.turnLabel->setText(ui.player1NameLabel->text());
	}
}

void TicTacToeProject::displayWinScreen() {
	{
		WinScreen winScreen(this);

		QString player = ui.turnLabel->text();

		winScreen.winnerLabel->setText(player + " won the game!");

		winScreen.exec();

		gameRunning = false;

		ui.startButton->setVisible(true); // Set start button visible again to do a new game

		// RESET BOARD

		// unmark main board
		ui.TTTbutton1->setText("(1)");
		ui.TTTbutton2->setText("(2)");
		ui.TTTbutton3->setText("(3)");
		ui.TTTbutton4->setText("(4)");
		ui.TTTbutton5->setText("(5)");
		ui.TTTbutton6->setText("(6)");
		ui.TTTbutton7->setText("(7)");
		ui.TTTbutton8->setText("(8)");
		ui.TTTbutton9->setText("(9)");
		//****************************

		// reset shadow board
		ui.shadowBox1->setText("");
		ui.shadowBox2->setText("");
		ui.shadowBox3->setText("");
		ui.shadowBox4->setText("");
		ui.shadowBox5->setText("");
		ui.shadowBox6->setText("");
		ui.shadowBox7->setText("");
		ui.shadowBox8->setText("");
		ui.shadowBox9->setText("");

		ui.turnLabel->setText("");

		ui.player1NameLabel->setText("");
		ui.player2NameLabel->setText("");

		ui.player1Icon->setText("");
		ui.player2Icon->setText("");
	}
}

void TicTacToeProject::displayDrawScreen() {
	DrawScreen draw(this);

	draw.exec();

	// RESET BOARD

	// unmark main board
	ui.TTTbutton1->setText("(1)");
	ui.TTTbutton2->setText("(2)");
	ui.TTTbutton3->setText("(3)");
	ui.TTTbutton4->setText("(4)");
	ui.TTTbutton5->setText("(5)");
	ui.TTTbutton6->setText("(6)");
	ui.TTTbutton7->setText("(7)");
	ui.TTTbutton8->setText("(8)");
	ui.TTTbutton9->setText("(9)");
	//****************************

	//Randomizes the shadow board
	std::array<char, 9> numbers = { '1','2','3','4','5','6','7','8','9' };
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

	shuffle(numbers.begin(), numbers.end(), std::default_random_engine(seed));
	//**************************************************************************

	//Reassigns the numbers to each square of the shadow board
	QString text = "(";
	text += numbers[0];
	text += ")";

	ui.shadowBox1->setText(text);

	text = "(";
	text += numbers[1];
	text += ")";
	ui.shadowBox2->setText(text);

	text = "(";
	text += numbers[2];
	text += ")";
	ui.shadowBox3->setText(text);

	text = "(";
	text += numbers[3];
	text += ")";
	ui.shadowBox4->setText(text);

	text = "(";
	text += numbers[4];
	text += ")";
	ui.shadowBox5->setText(text);

	text = "(";
	text += numbers[5];
	text += ")";
	ui.shadowBox6->setText(text);

	text = "(";
	text += numbers[6];
	text += ")";
	ui.shadowBox7->setText(text);

	text = "(";
	text += numbers[7];
	text += ")";
	ui.shadowBox8->setText(text);

	text = "(";
	text += numbers[8];
	text += ")";
	ui.shadowBox9->setText(text);
	//***************************
}

// Function for checking if the board is full
bool TicTacToeProject::allMarked() {

	if (ui.TTTbutton1->text() != "(1)" && ui.TTTbutton2->text() != "(2)" && ui.TTTbutton3->text() != "(3)"
		&& ui.TTTbutton4->text() != "(4)" && ui.TTTbutton5->text() != "(5)" && ui.TTTbutton6->text() != "(6)"
		&& ui.TTTbutton7->text() != "(7)" && ui.TTTbutton8->text() != "(8)" && ui.TTTbutton9->text() != "(9)")
		return true;

	else
		return false;
}