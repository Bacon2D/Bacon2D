#ifndef _QUASIGAMEPLUGINS_H_
#define _QUASIGAMEPLUGINS_H_

#include <QtDeclarative/QDeclarativeExtensionPlugin>

class QuasiGamePlugins : public  QDeclarativeExtensionPlugin
{
    Q_OBJECT

public:
    void registerTypes(const char *uri);
};

#endif /* _QUASIGAMEPLUGINS_H_ */

