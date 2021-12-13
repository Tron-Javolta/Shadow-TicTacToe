#pragma once

#include <QDialog>
#include "ui_IconChoice.h"

class IconChoice : public QDialog, public Ui::IconChoice
{
	Q_OBJECT

public:
	IconChoice(QWidget *parent = Q_NULLPTR);
	~IconChoice();
};
