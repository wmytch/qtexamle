#ifndef FORMDOC_H
#define FORMDOC_H

#include <QWidget>

namespace Ui {
class FormDoc;
}

class FormDoc : public QWidget
{
    Q_OBJECT
private:
    QString currentFile;
    bool fileOpened=false;
public:
    explicit FormDoc(QWidget *parent = nullptr);
    ~FormDoc();

    void loadFromFile(QString &fileName);
    QString currentFileName();
    bool isFileOpened();
    void setEditFont();
    void cutText();
    void copyText();
    void pasteText();
private:
    Ui::FormDoc *ui;
};

#endif // FORMDOC_H
