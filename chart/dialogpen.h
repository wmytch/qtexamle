#ifndef DIALOGPEN_H
#define DIALOGPEN_H

#include <QDialog>
#include <QPen>
namespace Ui {
class DialogPen;
}

class DialogPen : public QDialog
{
    Q_OBJECT

public:
    explicit DialogPen(QWidget *parent = nullptr);
    ~DialogPen();

    void setPen(QPen pen);
    QPen getPen();
    static QPen getPen(QPen initPen,bool &ok);

private:
    Ui::DialogPen *ui;

    QPen pen;

};

#endif // DIALOGPEN_H
