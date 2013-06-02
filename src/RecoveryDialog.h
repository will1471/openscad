#ifndef _RECOVERYDIALOG_H_
#define _RECOVERYDIALOG_H_

#include "ui_RecoveryDialog.h"

#include <QDialog>
#include <QListWidgetItem>

#include <boost/filesystem.hpp>
#include <vector>

namespace fs = boost::filesystem;

class RecoveryDialog : public QDialog, public Ui::RecoveryDialog
{
	Q_OBJECT;

public:
	RecoveryDialog(QWidget *parent = NULL);
	~RecoveryDialog();
        
	void addFile(fs::path path);

private slots:
        void onCloseClicked();
        void onDiscardClicked();
        void onOpenClicked();
        void onSelectionChanges();

private:
	std::vector<QListWidgetItem *> items;
        QPushButton * closeButton;
        QPushButton * discardButton;
        QPushButton * openButton;
        
};

#endif