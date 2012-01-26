#ifndef _ENUMS_H_
#define _ENUMS_H_

#include <QObject>

class Quasi : public QObject {
    Q_OBJECT

    Q_ENUMS (
        LayerType
        LayerDirection
        DrawType
        Ordering
    )

public:
    // Used on Layer
    enum LayerType {
        InfiniteType,
        MirroredType
    };

    // used on Layer
    enum LayerDirection {
        BackwardDirection = 0, // -1 returns undefined on QML :(
        ForwardDirection = 1
    };

    // Used on GameLayers
    enum DrawType {
        PlaneDrawType,
        TiledDrawType
    };

    // This is for the use of Layers and Items
    enum Ordering {
        // These enums defines the z order of the background layers
        BackgroundLayerOrdering_01 = 0,
        BackgroundLayerOrdering_02 = 1,
        BackgroundLayerOrdering_03 = 2,
        // These enums defines the z order of the interaction layers
        InteractionLayerOrdering_01 = 4,
        InteractionLayerOrdering_02 = 5,
        InteractionLayerOrdering_03 = 6,
        // These enums defines the z order of the game items
        ItemOrdering_01 = 4,
        ItemOrdering_02 = 5,
        ItemOrdering_03 = 6,
        // These enums defines the z order of the foreground layers
        ForegroundLayerOrdering_01 = 7,
        ForegroundLayerOrdering_02 = 8,
        ForegroundLayerOrdering_03 = 9
    };
};

#endif /* _ENUMS_H_ */
