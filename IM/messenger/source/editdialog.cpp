#include "messenger/editdialog.h"

#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>

namespace IM
{

EditDialog::EditDialog(QWidget *parent) :
    QDialog(parent),
    _lineEdit(0)
{
    QVBoxLayout* layout = new QVBoxLayout();
    setLayout(layout);

    _lineEdit = new QLineEdit();
    layout->addWidget(_lineEdit);
    QHBoxLayout* horiz = new QHBoxLayout();
    layout->addLayout(horiz);

    QPushButton* btnOk = new QPushButton(tr("Ok"));
    horiz->addWidget(btnOk);

    QPushButton* btnCancel = new QPushButton(tr("Cancel"));
    horiz->addWidget(btnCancel);

    connect(btnOk, SIGNAL(clicked()), SLOT(accept()));
    connect(btnCancel, SIGNAL(clicked()), SLOT(reject()));
}

void EditDialog::setEditData(const QString& data)
{
    _lineEdit->setText(data);
}

const QString EditDialog::getEditData()
{
    return _lineEdit->text();
}

}

