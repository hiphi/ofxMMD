/* ----------------------------------------------------------------- */
/*                                                                   */
/*  Copyright (c) 2009-2011  Nagoya Institute of Technology          */
/*                           Department of Computer Science          */
/*                2010-2012  hkrn                                    */
/*                                                                   */
/* All rights reserved.                                              */
/*                                                                   */
/* Redistribution and use in source and binary forms, with or        */
/* without modification, are permitted provided that the following   */
/* conditions are met:                                               */
/*                                                                   */
/* - Redistributions of source code must retain the above copyright  */
/*   notice, this list of conditions and the following disclaimer.   */
/* - Redistributions in binary form must reproduce the above         */
/*   copyright notice, this list of conditions and the following     */
/*   disclaimer in the documentation and/or other materials provided */
/*   with the distribution.                                          */
/* - Neither the name of the MMDAI project team nor the names of     */
/*   its contributors may be used to endorse or promote products     */
/*   derived from this software without specific prior written       */
/*   permission.                                                     */
/*                                                                   */
/* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND            */
/* CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,       */
/* INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF          */
/* MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE          */
/* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS */
/* BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,          */
/* EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED   */
/* TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,     */
/* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON */
/* ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,   */
/* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY    */
/* OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE           */
/* POSSIBILITY OF SUCH DAMAGE.                                       */
/* ----------------------------------------------------------------- */

#ifndef VPVL_VERTEX_H_
#define VPVL_VERTEX_H_

#include "Common.h"

namespace vpvl
{

class Bone;

/**
 * @file
 * @author Nagoya Institute of Technology Department of Computer Science
 * @author hkrn
 *
 * @section DESCRIPTION
 *
 * Vertex class represents a vertex of a Polygon Model Data object.
 */

class VPVL_API Vertex
{
public:
    Vertex();
    ~Vertex();

    static size_t stride();

    void read(const uint8_t *data);
    void write(uint8_t *data) const;

    const Vector3 &position() const {
        return m_position;
    }
    const Vector3 &normal() const {
        return m_normal;
    }
    float u() const {
        return m_u;
    }
    float v() const {
        return m_v;
    }
    int16_t bone1() const {
        return m_bone1;
    }
    int16_t bone2() const {
        return m_bone2;
    }
    float weight() const {
        return m_weight;
    }
    bool isEdgeEnabled() const {
        return m_edge;
    }

    void setPosition(const Vector3 &value);
    void setNormal(const Vector3 &value);
    void setTexCoord(float u, float v);
    void setBones(int16_t bone1ID, int16_t bone2ID);
    void setBones(Bone *bone1, Bone *bone2);
    void setWeight(float value);
    void setEdgeEnable(bool value);

private:
    Vector3 m_position;
    Vector3 m_normal;
    float m_u;
    float m_v;
    int16_t m_bone1;
    int16_t m_bone2;
    float m_weight;
    bool m_edge;

    VPVL_DISABLE_COPY_AND_ASSIGN(Vertex)
};

typedef Array<Vertex*> VertexList;
typedef Array<uint16_t> IndexList;

} /* namespace vpvl */

#endif
