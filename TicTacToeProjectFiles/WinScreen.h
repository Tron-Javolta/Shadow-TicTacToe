#pragma once

#include <QDialog>
#include "ui_WinScreen.h"

class WinScreen : public QDialog, public Ui::WinScreen
{
	Q_OBJECT

public:
	WinScreen(QWidget *parent = Q_NULLPTR);
	~WinScreen();
};
