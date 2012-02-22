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

#include "vpvl.h"
#include "util.h"

namespace vpvl
{

#pragma pack(push, 1)

/* based on BDEF */
struct VertexChunk
{
    float position[3];
    float normal[3];
    float u;
    float v;
    int16_t parentBoneID;
    int16_t childBoneID;
    uint8_t weight;
    uint8_t edge;
};

#pragma pack(pop)

size_t Vertex::stride()
{
    return sizeof(VertexChunk);
}

Vertex::Vertex()
    : m_position(0.0f, 0.0f, 0.0f),
      m_normal(0.0f, 0.0f, 0.0f),
      m_u(0.0f),
      m_v(0.0f),
      m_bone1(0),
      m_bone2(0),
      m_weight(0.0f),
      m_edge(false)
{
}

Vertex::~Vertex()
{
    m_position.setZero();
    m_normal.setZero();
    m_u = 0.0f;
    m_v = 0.0f;
    m_bone1 = 0;
    m_bone2 = 0;
    m_weight = 0.0f;
    m_edge = false;
}

void Vertex::read(const uint8_t *data)
{
    VertexChunk chunk;
    internal::copyBytes(reinterpret_cast<uint8_t *>(&chunk), data, sizeof(chunk));

#ifdef VPVL_BUILD_IOS
    float *pos = chunk.position;
    float *normal = chunk.normal;
    float u = chunk.u;
    float v = chunk.v;
#else
    float pos[3], normal[3], u, v;
    memcpy(pos, &chunk.position, sizeof(pos));
    memcpy(normal, &chunk.normal, sizeof(normal));
    memcpy(&u, &chunk.u, sizeof(u));
    memcpy(&v, &chunk.v, sizeof(v));
#endif

    int16_t bone1 = chunk.parentBoneID;
    int16_t bone2 = chunk.childBoneID;
    uint8_t weight = chunk.weight;
    uint8_t edge = chunk.edge;

#ifdef VPVL_COORDINATE_OPENGL
    setPosition(Vector3(pos[0], pos[1], -pos[2]));
#else
    setPosition(Vector3(pos[0], pos[1], pos[2]));
#endif
#ifdef VPVL_COORDINATE_OPENGL
    setNormal(Vector3(normal[0], normal[1], -normal[2]));
#else
    setNormal(Vector3(normal[0], normal[1], normal[2]));
#endif
    setTexCoord(u, v);
    setBones(bone1, bone2);
    setWeight(weight);
    setEdgeEnable(edge == 0);
}

void Vertex::write(uint8_t *data) const
{
    VertexChunk chunk;
#ifdef VPVL_COORDINATE_OPENGL
    chunk.position[2] = -m_position.z();
    chunk.normal[2] = -m_normal.z();
#else
    chunk.position[2] = m_position.z();
    chunk.normal[2] = m_normal.z();
#endif
    chunk.position[0] = m_position.x();
    chunk.position[1] = m_position.y();
    chunk.normal[0] = m_normal.x();
    chunk.normal[1] = m_normal.y();
    chunk.u = m_u;
    chunk.v = m_v;
    chunk.parentBoneID = m_bone1;
    chunk.childBoneID = m_bone2;
    chunk.weight = static_cast<uint8_t>(m_weight * 100.0f);
    chunk.edge = m_edge ? 0 : 1;
    internal::copyBytes(data, reinterpret_cast<const uint8_t *>(&chunk), sizeof(chunk));
}

void Vertex::setPosition(const Vector3 &value)
{
    m_position = value;
}

void Vertex::setNormal(const Vector3 &value)
{
    m_normal = value;
}

void Vertex::setTexCoord(float u, float v)
{
    m_u = u;
    m_v = v;
}

void Vertex::setBones(Bone *bone1, Bone *bone2)
{
    setBones(bone1->id(), bone2->id());
}

void Vertex::setBones(int16_t bone1ID, int16_t bone2ID)
{
    m_bone1 = bone1ID;
    m_bone2 = bone2ID;
}

void Vertex::setWeight(float value)
{
    m_weight = value * 0.01f;
}

void Vertex::setEdgeEnable(bool value)
{
    m_edge = value;
}

}
