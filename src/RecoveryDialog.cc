#include "RecoveryDialog.h"
#include "MainWindow.h"

#include <QAbstractItemView>
#include <QFile>
#include <QMessageBox>
#include <QPushButton>
#include <QString>

RecoveryDialog::RecoveryDialog(QWidget * parent) : QDialog(parent)
{
	setupUi(this);

	this->listWidget->setSelectionMode(QAbstractItemView::SingleSelection);
	connect(this->listWidget, SIGNAL(itemSelectionChanged()), this, SLOT(onSelectionChanges()));

	this->closeButton = this->buttonBox->button(QDialogButtonBox::Close);
	this->discardButton = this->buttonBox->button(QDialogButtonBox::Discard);
	this->openButton = this->buttonBox->button(QDialogButtonBox::Open);

	this->discardButton->setDisabled(true);
	this->openButton->setDisabled(true);
	
	connect(this->closeButton, SIGNAL(clicked()), this, SLOT(onCloseClicked()));
	connect(this->discardButton, SIGNAL(clicked()), this, SLOT(onDiscardClicked()));
	connect(this->openButton, SIGNAL(clicked()), this, SLOT(onOpenClicked()));
}


RecoveryDialog::~RecoveryDialog()
{
	for (unsigned int i = 0; i < items.size(); i++) {
		delete items.at(i);
	}
}


void RecoveryDialog::addFile(fs::path path)
{
	QListWidgetItem * item = new QListWidgetItem(this->listWidget);
	item->setText(QString::fromStdString(path.string()));
	items.push_back(item);
	this->listWidget->addItem(item);
}


void RecoveryDialog::onCloseClicked()
{
    done(0);
}


void RecoveryDialog::onDiscardClicked()
{
    QListWidgetItem * item = this->listWidget->currentItem();
    
    if (item) {
	bool ok = QFile::remove(item->text());

	if (!ok) {
	    QMessageBox::warning(this, tr("Warning"), tr("Failed to remove file:\n %1").arg(item->text()));
	    return;
	}
	
	this->listWidget->takeItem(this->listWidget->currentRow());

	if (this->listWidget->count() == 0) {
	    done(1);
	}
    }
}


void RecoveryDialog::onOpenClicked()
{
}


void RecoveryDialog::onSelectionChanges()
{
	QListWidgetItem * item = this->listWidget->currentItem();
	if (item) {
		this->discardButton->setDisabled(false);
		this->openButton->setDisabled(false);
	}
}