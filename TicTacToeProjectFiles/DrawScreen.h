#pragma once

#include <QDialog>
#include "ui_DrawScreen.h"

class DrawScreen : public QDialog, public Ui::DrawScreen
{
	Q_OBJECT

public:
	DrawScreen(QWidget *parent = Q_NULLPTR);
	~DrawScreen();
};
