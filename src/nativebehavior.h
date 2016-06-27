#ifndef NATIVEBEHAVIOR_H
#define NATIVEBEHAVIOR_H

#include <QObject>
#include <behavior.h>
#include <functional>

class NativeBehavior : public Behavior
{
    Q_OBJECT
public:
    NativeBehavior(QObject* parent = nullptr);
    virtual void update(const int& delta) override;
    std::function<void(const int&)> update_func;
};

#endif // NATIVEBEHAVIOR_H
