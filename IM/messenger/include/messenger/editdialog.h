#ifndef EDITDIALOG_H
#define EDITDIALOG_H

#include <QDialog>

class QLineEdit;

namespace IM
{

class EditDialog : public QDialog
{
    Q_OBJECT
public:
    EditDialog(QWidget* parent = 0);

    void setEditData(const QString& data);
    const QString getEditData();

private:
    QLineEdit* _lineEdit;
};

} // IM

#endif // EDITDIALOG_H

