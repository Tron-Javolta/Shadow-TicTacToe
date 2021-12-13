#pragma once

#include <QDialog>
#include "ui_AddNames.h"

class AddNames : public QDialog, public Ui::AddNames
{
	Q_OBJECT

public:
	AddNames(QWidget *parent = Q_NULLPTR);
	~AddNames();
};
