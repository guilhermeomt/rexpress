#ifndef PROPERTIES_H
#define PROPERTIES_H

#include <QWidget>

namespace Ui {
class Properties;
}

class Properties : public QWidget
{
    Q_OBJECT

public:
    explicit Properties(QWidget *parent = nullptr);
    ~Properties();
    Ui::Properties *ui;
};

#endif // PROPERTIES_H
