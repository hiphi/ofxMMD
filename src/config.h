/* ----------------------------------------------------------------- */
/*                                                                   */
/*  Copyright (c) 2010-2011  hkrn                                    */
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

#ifndef VPVL_CONFIG_H_
#define VPVL_CONFIG_H_

/* use OpenGL coordinate system */
#define VPVL_COORDINATE_OPENGL

/* use Allegro5 OpenGL extensions instead of GLEW */
/* #undef VPVL_USE_ALLEGRO5 */

/* Build libvpvl without BulletPhysics except LinearMath */
/* #undef VPVL_NO_BULLET */

/* Build libvpvl with Open Asset Import Library */
#define VPVL_LINK_ASSIMP

/* Build libvpvl's renderer with GLSL shader */
#define VPVL_USE_GLSL

/* Build libvpvl's renderer with NVIDIA Cg (based on vpvl::gl::Renderer) */
/* #undef VPVL_USE_NVIDIA_CG */

/* Build libvpvl for iOS */
/* #undef VPVL_BUILD_IOS */

/* Build libvpvl linking with GLEW (no longer be used) */
/* #undef VPVL_LINK_GLEW */

/* Build libvpvl with project file support */
/* #undef VPVL_ENABLE_PROJECT */

/* Build libvpvl linking with Qt */
/* #undef VPVL_LINK_QT */

/* version */
#define VPVL_VERSION_MAJOR 0
#define VPVL_VERSION_COMPAT 12
#define VPVL_VERSION_MINOR 0

#define VPVL_MAKE_VERSION(major, compat, minor) \
    (((major) << 16) | ((compat) << 8) | (minor))
#define VPVL_VERSION VPVL_MAKE_VERSION(VPVL_VERSION_MAJOR, \
                                       VPVL_VERSION_COMPAT, \
                                       VPVL_VERSION_MINOR)

#define VPVL_VERSION_STRING "0.12.0"

#endif
