#ifndef SALARIO_H
#define SALARIO_H

#include <QObject>
#include <QWidget>

class Salario : public QObject
{
    Q_OBJECT
public:
    explicit Salario(QObject *parent = nullptr);

signals:

};

#endif // SALARIO_H
