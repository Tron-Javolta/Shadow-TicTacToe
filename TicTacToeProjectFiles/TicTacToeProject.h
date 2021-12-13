#pragma once

#include <QtWidgets/QWidget>
#include "ui_TicTacToeProject.h"

class TicTacToeProject : public QWidget
{
	Q_OBJECT

public:
	TicTacToeProject(QWidget *parent = Q_NULLPTR);


private:
	Ui::TicTacToeProjectClass ui;

	void displayWinScreen();
	void displayDrawScreen();

	bool allMarked();

private slots:
	void on_startButton_clicked();

	void on_rulesButton_clicked();

	void on_resetButton_clicked();

	void on_TTTbutton1_clicked();
	void on_TTTbutton2_clicked();
	void on_TTTbutton3_clicked();
	void on_TTTbutton4_clicked();
	void on_TTTbutton5_clicked();
	void on_TTTbutton6_clicked();
	void on_TTTbutton7_clicked();
	void on_TTTbutton8_clicked();
	void on_TTTbutton9_clicked();
};
