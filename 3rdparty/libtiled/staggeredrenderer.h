/*
 * staggeredrenderer.h
 * Copyright 2011-2014, Thorbjørn Lindeijer <thorbjorn@lindeijer.nl>
 *
 * This file is part of libtiled.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *    1. Redistributions of source code must retain the above copyright notice,
 *       this list of conditions and the following disclaimer.
 *
 *    2. Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE CONTRIBUTORS ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 * EVENT SHALL THE CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef STAGGEREDRENDERER_H
#define STAGGEREDRENDERER_H

#include "hexagonalrenderer.h"

namespace Tiled {

/**
 * A staggered isometric renderer.
 *
 * This renderer is meant to be used with isometric tiles, but rather than
 * doing a true isometric projection the tiles are shifted in order to fit
 * together. This has the advantage that the map has a rectangular shape.
 *
 * Only one variation of staggered map rendering is supported at the moment,
 * namely shifting the uneven rows to the right.
 *
 * Objects are handled the same way as the OrthogonalRenderer, though they
 * snap at half the tile width and height.
 *
 * At the moment, several Tiled features will not work correctly with this
 * renderer. This is due to the way the shifting messes with the coordinate
 * system. List of known issues:
 *
 *   Fill tool:
 *
 *     Doesn't work properly cause its assumptions about neighboring are
 *     broken by this renderer.
 *
 *   Stamp tool:
 *
 *     A stamp only makes sense if it's placed at an even y offset from
 *     where it was created. When moved by an uneven y offset, the rows
 *     that are shifted swap, messing up the stamp.
 *
 *     The circle and line drawing modes of the stamp tool won't work
 *     properly due to the irregular coordinate system.
 *
 *   Rectangular select tool:
 *
 *     This one will appear to behave somewhat erratic.
 *
 *   Map resize and offset actions:
 *
 *     Similar problem as with stamps when offsetting at an uneven y offset.
 *
 */
class TILEDSHARED_EXPORT StaggeredRenderer : public HexagonalRenderer
{
public:
    StaggeredRenderer(const Map *map) : HexagonalRenderer(map) {}

    using HexagonalRenderer::screenToTileCoords;
    QPointF screenToTileCoords(qreal x, qreal y) const override;
};

} // namespace Tiled

#endif // STAGGEREDRENDERER_H
