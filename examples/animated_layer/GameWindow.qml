/**
 * Copyright (C) 2012 by INdT
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * @author Rodrigo Goncalves de Oliveira <rodrigo.goncalves@openbossa.org>
 * @author Roger Felipe Zanoni da Silva <roger.zanoni@openbossa.org>
 */

QuasiGame {
    id: game

    width: 800
    height: 385

    currentScene: scene

    QuasiScene {
        id: scene

        width: parent.width
        height: parent.height

        QuasiLayers {
            anchors.fill: parent
            drawType: Quasi.TiledDrawType // draiwing type; PlaneDrawType or TiledDrawType (default)
            tileWidth: 32 // width of each tile when using 'TiledDrawType' as drawing type; default: 32
            tileHeight: 32 // height of each tile when using 'TiledDrawType' as drawing type; default: 32
            //drawGrid: true // nice for debug; default: false
            //gridColor: "green" // nice for debug; default: red

            layers: [
                QuasiAnimatedLayer {
                    source: ":/large_enough.png" // image source
                    //factor: 1.0 // updating factor of this layer, useful when using multiple layers; default: 1.0
                    /* layer ordering, set how the layers will be presented when rendering
                    * possible values, splited in three main areas:
                    * - These enums defines the ordering of the background layers
                    *    BackgroundLayerOrdering_01, BackgroundLayerOrdering_02 and BackgroundLayerOrdering_03
                    * - These enums defines the ordering of the interaction layers (where the characters, enemies, objects, etc, live)
                    *    InteractionLayerOrdering_01 (default for every layer), InteractionLayerOrdering_02 and InteractionLayerOrdering_03
                    * - These enums defines the orderin of the foreground layers
                    *    ForegroundLayerOrdering_01, ForegroundLayerOrdering_02 and ForegroundLayerOrdering_03
                    * Please, bear in mind that you can use as many layers you want to (and that your system can support), but they will ordered according these values
                    */
                    order: Quasi.BackgroundLayerOrdering_01

                    horizontalStep: 5 // base horizontal offset, aka 'step'. There are no need of a signed value as it will always get the positive value; default: 0, i.e., no movement at all
                    direction: Quasi.BackwardDirection // direction of the background animation; ForwardDirection or BackwardDirection (default)
                    layerType: Quasi.InfiniteType // type of animation; MirroredType or InfiniteType (default)
                }
            ]
        }

        QuasiSprite {
            id: spriteItem

            y: 175

            animation: "sliding"

            animations: QuasiSpriteAnimation {
                name: "sliding"

                source: ":/sliding.png"
                frames: 4
                duration: 450
                loops: Animation.Infinite
            }
        }
    }
}
