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

#ifndef VPVL_CAMERAANIMATION_H_
#define VPVL_CAMERAANIMATION_H_

#include "BaseAnimation.h"

namespace vpvl
{

class CameraKeyframe;
typedef Array<CameraKeyframe *> CameraKeyFrameList;

/**
 * @file
 * @author Nagoya Institute of Technology Department of Computer Science
 * @author hkrn
 *
 * @section DESCRIPTION
 *
 * CameraAnimation class represents a camera Animation that includes many camera key frames
 * of a Vocaloid Motion Data object inherits BaseAnimation.
 */

class VPVL_API CameraAnimation : public BaseAnimation
{
public:
    CameraAnimation();
    ~CameraAnimation();

    void read(const uint8_t *data, int size);
    void seek(float frameAt);
    void takeSnap(const Vector3 &center);
    void reset();
    void refresh();

    /**
     * Get a camera key frame associated with index.
     *
     * @param i A frame index to get key frame
     * @return A camera key frame associated with index
     */
    CameraKeyframe *frameAt(int i) const {
        return static_cast<CameraKeyframe *>(m_frames[i]);
    }

    /**
     * Get a position of camera work.
     *
     * @return A position (X, Y, Z)
     */
    const Vector3 &position() const {
        return m_position;
    }

    /**
     * Get an angle of camera work.
     *
     * @return An angle (X, Y, Z) in degree
     */
    const Vector3 &angle() const {
        return m_angle;
    }

    /**
     * Get distance of camera work.
     *
     * @return A value of distance
     */
    float distance() const {
        return m_distance;
    }

    /**
     * Get fovy of camera work.
     *
     * @return A value of fovy
     */
    float fovy() const {
        return m_fovy;
    }

private:
    static float weightValue(const CameraKeyframe *keyFrame,
                             float w,
                             int at);
    static void lerpVector3(const CameraKeyframe *keyFrame,
                            const Vector3 &from,
                            const Vector3 &to,
                            float w,
                            int at,
                            float &value);

    Vector3 m_position;
    Vector3 m_angle;
    float m_distance;
    float m_fovy;

    VPVL_DISABLE_COPY_AND_ASSIGN(CameraAnimation)
};

}

#endif

