#ifndef _UTIL_H_
#define _UTIL_H_

struct b2Vec2;

namespace b2Util
{
    float b2Angle(b2Vec2 v1, b2Vec2 v2);
    float b2Length(b2Vec2 v1, b2Vec2 v2);
    b2Vec2 b2Center(b2Vec2 v1, b2Vec2 v2);
}

#endif /* _UTIL_H_ */
