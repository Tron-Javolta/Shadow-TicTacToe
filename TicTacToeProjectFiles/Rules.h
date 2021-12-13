#pragma once

#include <QDialog>
#include "ui_Rules.h"

class Rules : public QDialog, public Ui::Rules
{
	Q_OBJECT

public:
	Rules(QWidget *parent = Q_NULLPTR);
	~Rules();
};
