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

#ifndef VPVL_PMDMODEL_H_
#define VPVL_PMDMODEL_H_

#include "Bone.h"
#include "Constraint.h"
#include "Face.h"
#include "IK.h"
#include "Material.h"
#include "RigidBody.h"
#include "Vertex.h"

class btDiscreteDynamicsWorld;

namespace vpvl
{

class VMDMotion;

/**
 * @file
 * @author Nagoya Institute of Technology Department of Computer Science
 * @author hkrn
 *
 * @section DESCRIPTION
 *
 * PMDModel class represents a Polygon Model Data object, 3D model object.
 */

class VPVL_API PMDModel
{
public:
    class UserData {
    public:
        UserData() {}
        virtual ~UserData() {}
    };

    typedef struct SkinVertex SkinVertex;
    typedef struct State State;

    /**
      * Type of parsing errors.
      */
    enum Error
    {
        kNoError,
        kInvalidHeaderError,
        kInvalidSignatureError,
        kInvalidVersionError,
        kVerticesSizeError,
        kVerticesError,
        kIndicesSizeError,
        kIndicesError,
        kMaterialsSizeError,
        kMaterialsError,
        kBonesSizeError,
        kBonesError,
        kIKsSizeError,
        kIKsError,
        kFacesSizeError,
        kFacesError,
        kFacesForDisplaySizeError,
        kFacesForDisplayError,
        kBoneFrameNamesSizeError,
        kBoneFrameNamesError,
        kBoneDisplayNamesSizeError,
        kBoneDisplayNamesError,
        kEnglishNamesError,
        kExtraTextureNamesError,
        kRigidBodiesSizeError,
        kRigidBodiesError,
        kConstraintsSizeError,
        kConstraintsError,
        kNoBoneError,
        kMaxErrors
    };

    /**
      * Type of stride to get stride length.
      */
    enum StrideType
    {
        kVerticesStride,
        kEdgeVerticesStride,
        kNormalsStride,
        kTextureCoordsStride,
        kToonTextureStride,
        kIndicesStride,
        kEdgeIndicesStride,
        kBoneAttributesStride
    };

    struct DataInfo
    {
        const uint8_t *basePtr;
        const uint8_t *namePtr;
        const uint8_t *commentPtr;
        const uint8_t *verticesPtr;
        size_t verticesCount;
        const uint8_t *indicesPtr;
        size_t indicesCount;
        const uint8_t *materialsPtr;
        size_t materialsCount;
        const uint8_t *bonesPtr;
        size_t bonesCount;
        const uint8_t *IKsPtr;
        size_t IKsCount;
        const uint8_t *facesPtr;
        size_t facesCount;
        const uint8_t *facesForUIPtr;
        size_t facesForUICount;
        const uint8_t *boneCategoryNamesPtr;
        size_t boneCategoryNamesCount;
        const uint8_t *bonesForUIPtr;
        size_t bonesForUICount;
        const uint8_t *englishNamePtr;
        const uint8_t *englishCommentPtr;
        const uint8_t *englishBoneNamesPtr;
        const uint8_t *englishFaceNamesPtr;
        const uint8_t *englishBoneFramesPtr;
        const uint8_t *toonTextureNamesPtr;
        const uint8_t *rigidBodiesPtr;
        size_t rigidBodiesCount;
        const uint8_t *constraintsPtr;
        size_t constranitsCount;
    };

    PMDModel();
    ~PMDModel();

    static const int kCustomTextureMax = 11;
    static const int kCustomTextureNameMax = 100;
    static const int kNameSize = 20;
    static const int kCommentSize = 256;
    static const int kBoneCategoryNameSize = 50;
    static const float kMinBoneWeight;
    static const float kMinFaceWeight;

    /**
     * Add and attach a motion to the model.
     *
     * This method sort motions by priority automatically after adding the motion.
     * The motion is already attached, this method does nothing.
     *
     * @param motion A motion to attach
     */
    void addMotion(VMDMotion *motion);

    /**
     * Returns the motion is attached to the model.
     *
     * @param True if the motion is attached
     */
    bool containsMotion(VMDMotion *motion) const;

    /**
     * Set the physics world to join the model.
     *
     * After calling this method, isSimulationEnabled returns true.
     * If the model is already join to the world, this method nothing.
     * If VPVL_NO_BULLET is defined, this method does nothing.
     *
     * @param world The world to join the model
     */
    void joinWorld(btDiscreteDynamicsWorld *world);

    /**
     * Leave the model from world.
     *
     * After calling this method, isSimulationEnabled returns false.
     * If the model is already leaved from the world, this method nothing.
     * If VPVL_NO_BULLET is defined, this method does nothing.
     *
     * @param world The world to leave the model
     */
    void leaveWorld(btDiscreteDynamicsWorld *world);

    /**
     * Detach a motion from the model.
     *
     * @param motion A motion to detach
     */
    void removeMotion(VMDMotion *motion);

    /**
     * Detach all motions from the model.
     */
    void removeAllMotions();

    /**
     * Detach a motion and delete it from the model.
     *
     * First argument motion will be deleted and set to null.
     *
     * @param motion A motion to delete
     */
    void deleteMotion(VMDMotion *&motion);

    /**
     * Detach all motions and delete them from the model.
     */
    void deleteAllMotions();

    /**
     * Reset all motions of the model and seek to zero.
     */
    void resetMotion();

    /**
     * Returns the max frame index of all motions.
     *
     * @return max frame index
     */
    float maxFrameIndex() const;

    /**
     * Check whether all motions of the model are reached to the frame index.
     *
     * @param atEnd A frame index to check
     * @return True if all motions are reached to the frame index
     */
    bool isMotionReachedTo(float frameIndex) const;

    /**
     * Seek all motions of the model to the specified frame index.
     *
     * @param frameIndex A frame index to seek
     */
    void seekMotion(float frameIndex);

    void updateRootBone();

    /**
     * Advance all motions of the model relative with current frame index.
     *
     * @param deltaFrame A delta frame index to advance
     */
    void advanceMotion(float deltaFrame);

    /**
     * Update skin vertices, toon texture coordinates and edge vertices of the model.
     */
    void updateSkins();

    /**
     * Update skins and transforms all bones and faces of the model without seeking the motion.
     */
    void updateImmediate();

    /**
     * Calculate bounding sphere of the model.
     *
     * @param center The center origin of the model to be set
     * @param radius The raius value of the model to be set
     */
    void getBoundingSphere(Vector3 &center, Scalar &radius) const;

    /**
     * Reset all bones of the model to initial state.
     */
    void resetAllBones();

    /**
     * Reset all faces of the model to initial state.
     */
    void resetAllFaces();

    void smearAllBonesToDefault(float rate);
    void smearAllFacesToDefault(float rate);

    /**
     * Discard and release state of the model.
     *
     * This methods set 0 to first argument after discarding state.
     *
     * @param state State to discard
     * @see saveState
     * @see restoreState
     */
    void discardState(State *&state) const;

    /**
     * Allocate and save state of the model.
     *
     * You must release state with discardState.
     *
     * @return Current state of the model
     * @see discardState
     * @see restoreState
     */
    State *saveState() const;

    /**
     * Restore the model to current state.
     *
     * This methods return false if state is different from the model.
     * State will retain memory even if the model is restored,
     * You must release state with discardState.
     *
     * @param state Current state of the model
     * @return True if the model is restored
     * @see discardState
     * @see saveState
     */
    bool restoreState(State *state);

    /**
     * Returns the stride byte size of specified type.
     *
     * @return stride size of specified type
     */
    size_t strideSize(StrideType type) const;

    /**
     * Returns the stride offset size of specified type.
     *
     * @return stride size of specified type
     */
    size_t strideOffset(StrideType type) const;

    /**
     * Returns the base adderess of vertices pointer.
     *
     * @return Address of vertices
     */
    const void *verticesPointer() const;

    /**
     * Returns the base adderess of normal pointer.
     *
     * @return Address of normal pointer
     */
    const void *normalsPointer() const;

    /**
     * Returns the base adderess of texture coordinates pointer.
     *
     * @return Address of texture coordinates
     */
    const void *textureCoordsPointer() const;

    /**
     * Returns the base adderess of toon texture coordinates pointer.
     *
     * @return Address of texture coordinates
     */
    const void *toonTextureCoordsPointer() const;

    /**
     * Returns the base adderess of edge vertices pointer.
     *
     * @return Address of edge vertices
     */
    const void *edgeVerticesPointer() const;

    /**
     * Returns the base adderess of bone attributes pointer.
     *
     * @return Address of bone attributes
     */
    const void *boneAttributesPointer() const;

    /**
     * Returns the base adderess of bone matrices pointer.
     *
     * @return Address of bone matrices
     */
    const float *boneMatricesPointer() const;

    /**
     * Returns the texture name of the index.
     *
     * @param index Index of the texture
     * @return Texture name of the index
     */
    const uint8_t *toonTexture(int index) const;

    /**
     * Sets texture names of the model.
     *
     * setToonTextures() requires (PMDModel::kCustomTextureNameMax * 10) bytes buffer.
     *
     * @param texture names to set
     */
    void setToonTextures(const uint8_t *ptr);

    /**
     * Enable software (CPU not GPU) skinning.
     *
     * If this method is called with true, do CPU based skinning, updateSkinVertices() and
     * updateToon() will be called internally. As a result, verticesPointer(), normalsPointer(),
     * edgeVerticesPointer() and #toonTextureCoordsPointer() will be modified.
     *
     * If this method is called with false, doesn't do skinning, updatePosition() and
     * updateBoneMatrices() will be called internally. As a result, just setting vertex origin
     * position and bone matrices. Skinning must be done at the other.
     * (e.g. Shader skinning or GPGPU based skinning).
     *
     * Default behavior is CPU based skinning, isSoftwareSkinningEnabled() returns true.
     *
     * @param True if software skinning is enabled
     */
    void setSoftwareSkinningEnable(bool value);

    /**
     * Return the bone of the name.
     *
     * If the bone of the name is not found, returns 0.
     *
     * @param name Name to find the bone
     * @return Bone pointer of the name
     */
    Bone *findBone(const uint8_t *name) const;

    /**
     * Return the face of the name.
     *
     * If the face of the name is not found, returns 0.
     *
     * @param name Name to find the face
     * @return Face pointer of the name
     */
    Face *findFace(const uint8_t *name) const;

    /**
     * parse and validate if the buffer can load as a model from memory.
     *
     * @param data The buffer to load
     * @param size Size of the buffer
     * @param info Data of parsed information
     * @return True if the model is loaded successfully
     */
    bool preparse(const uint8_t *data, size_t size, DataInfo &info);

    /**
     * Load and build the model from memory.
     *
     * This method calls preparse internally so you don't need call preparse.
     *
     * @param data The buffer to load
     * @param size Size of the buffer
     * @return True if the model is loaded successfully
     */
    bool load(const uint8_t *data, size_t size);

    /**
     * Estimate buffer size to save.
     *
     * @return Allocate size to save
     */
    size_t estimateSize() const;

    /**
     * Save and write PMD data to the buffer.
     *
     * @param A buffer that is allocated size with PMDModel#estimateSize()
     */
    void save(uint8_t *data) const;

    /**
     * Returns the name of this model.
     *
     * @return the name of this model
     */
    const uint8_t *name() const {
        return m_name;
    }

    /**
     * Returns the comment of this model.
     *
     * @return the comment of this model
     */
    const uint8_t *comment() const {
        return m_comment;
    }

    /**
     * Returns the name of this model in English.
     *
     * @return the name of this model in English
     */
    const uint8_t *englishName() const {
        return m_englishName;
    }

    /**
     * Returns the comment of this model in English.
     *
     * @return the comment of this model in English
     */
    const uint8_t *englishComment() const {
        return m_englishComment;
    }

    const VertexList &vertices() const {
        return m_vertices;
    }
    const IndexList &indices() const {
        return m_indices;
    }
    const MaterialList &materials() const {
        return m_materials;
    }
    const BoneList &bones() const {
        return m_bones;
    }
    const IKList &IKs() const {
        return m_IKs;
    }
    const FaceList &faces() const {
        return m_faces;
    }
    const FaceList &facesForUI() const {
        return m_facesForUI;
    }
    const Array<uint8_t *> &boneCategoryNames() const {
        return m_boneCategoryNames;
    }
    const Array<BoneList *> &bonesForUI() const {
        return m_bonesForUI;
    }
    const RigidBodyList &rigidBodies() const {
        return m_rigidBodies;
    }
    const ConstraintList &constraints() const {
        return m_constraints;
    }
    const Array<VMDMotion *> &motions() const {
        return m_motions;
    }
    BoneList *mutableBones() {
        return &m_bones;
    }
    const Bone &rootBone() const {
        return m_rootBone;
    }
    Bone *mutableRootBone() {
        return &m_rootBone;
    }
    Bone *baseBone() const {
        return m_baseBone;
    }
    float edgeOffset() const {
        return m_edgeOffset / 0.03f;
    }
    bool isSimulationEnabled() const {
        return m_enableSimulation;
    }
    bool isToonEnabled() const {
        return m_enableToon;
    }
    bool isSoftwareSkinningEnabled() const {
        return m_enableSoftwareSkinning;
    }
    bool isVisible() const {
        return m_visible;
    }
    const Quaternion &rotationOffset() const {
        return m_rotationOffset;
    }
    const Color &edgeColor() const {
        return m_edgeColor;
    }
    const Vector3 &positionOffset() const {
        return m_positionOffset;
    }
    const Vector3 &lightPosition() const {
        return m_lightPosition;
    }
    UserData *userData() const {
        return m_userData;
    }
    Error error() const {
        return m_error;
    }

    const uint16_t *indicesPointer() const {
        return m_indicesPointer;
    }
    const uint16_t *edgeIndicesPointer() const {
        return m_edgeIndicesPointer;
    }
    uint32_t edgeIndicesCount() const {
        return m_edgeIndicesCount;
    }

    /**
     * Set the name of this model.
     *
     * @param value the name of this model
     */
    void setName(const uint8_t *value) {
        copyBytesSafe(m_name, value, sizeof(m_name));
    }

    /**
     * Set the name of this model in English.
     *
     * @param value the name of this model in English
     */
    void setComment(const uint8_t *value) {
        copyBytesSafe(m_comment, value, sizeof(m_comment));
    }

    /**
     * Set the comment of this model.
     *
     * @param value the name of this model
     */
    void setEnglishName(const uint8_t *value) {
        copyBytesSafe(m_englishName, value, sizeof(m_englishName));
    }

    /**
     * Set the comment of this model in English.
     *
     * @param value the comment of this model in English
     */
    void setEnglishComment(const uint8_t *value) {
        copyBytesSafe(m_englishComment, value, sizeof(m_englishComment));
    }

    void setBaseBone(Bone *value) {
        m_baseBone = value;
    }
    void setRotationOffset(const Quaternion &value) {
        m_rotationOffset = value;
    }
    void setEdgeColor(const Color &value) {
        m_edgeColor = value;
    }
    void setPositionOffset(const Vector3 &value) {
        m_positionOffset = value;
    }
    void setLightPosition(const Vector3 &value) {
        m_lightPosition = value.normalized();
    }
    void setEdgeOffset(float value) {
        m_edgeOffset = value * 0.03f;
    }
    void setToonEnable(bool value) {
        m_enableToon = value;
    }
    void setVisible(bool value) {
        m_visible = value;
    }
    void setUserData(UserData *value) {
        m_userData = value;
    }

    /* primitive operations of PMDModel to build and save PMD object */
    void setIndices(const IndexList &value);
    void addVertex(Vertex *value);
    void removeVertex(Vertex *value);
    void addMaterial(Material *value);
    void removeMaterial(Material *value);
    void addBone(Bone *value);
    void removeBone(Bone *value);
    void addIK(IK *value);
    void removeIK(IK *value);
    void addFace(Face *value);
    void removeFace(Face *value);
    void addRigidBody(RigidBody *value);
    void removeRigidBody(RigidBody *value);
    void addConstraint(Constraint *value);
    void removeConstraint(Constraint *value);

private:
    void parseHeader(const DataInfo &info);
    void parseVertices(const DataInfo &info);
    void parseIndices(const DataInfo &info);
    void parseMaterials(const DataInfo &info);
    void parseBones(const DataInfo &info);
    void parseIKs(const DataInfo &info);
    void parseFaces(const DataInfo &info);
    void parseFacesForUI(const DataInfo &info);
    void parseBoneCategoryNames(const DataInfo &info);
    void parseBonesForUI(const DataInfo &info);
    void parseEnglishDisplayNames(const DataInfo &info);
    void parseToonTextureNames(const DataInfo &info);
    void parseRigidBodies(const DataInfo &info);
    void parseConstraints(const DataInfo &info);
    void prepare();
    void release();
    void sortBones();
    void updateAllBones();
    void updateBoneFromSimulation();
    void updateAllFaces();
    void updateShadowTextureCoords(float coef);
    void updateSkinVertices();
    void updateToon(const Vector3 &lightPosition);
    void updateIndices();
    void updateBoneMatrices();
    void updatePosition();

    uint8_t m_name[kNameSize + 1];
    uint8_t m_comment[kCommentSize + 1];
    uint8_t m_englishName[kNameSize + 1];
    uint8_t m_englishComment[kCommentSize + 1];
    uint8_t m_textures[kCustomTextureMax][kCustomTextureNameMax + 1];
    VertexList m_vertices;
    IndexList m_indices;
    MaterialList m_materials;
    BoneList m_bones;
    IKList m_IKs;
    FaceList m_faces;
    FaceList m_facesForUI;
    RigidBodyList m_rigidBodies;
    ConstraintList m_constraints;
    Bone m_rootBone;
    Bone *m_baseBone;
    Face *m_baseFace;
    Hash<HashString, Bone *> m_name2bone;
    Hash<HashString, Face *> m_name2face;
    Array<VMDMotion *> m_motions;
    Array<uint8_t *> m_boneCategoryNames;
    Array<uint8_t *> m_boneCategoryEnglishNames;
    Array<Transform> m_skinningTransform;
    Array<Vector3> m_shadowTextureCoords;
    Array<BoneList *> m_bonesForUI;
    Array<uint16_t> m_facesForUIIndices;
    Array<float> m_boneMatrices;
    BoneList m_rotatedBones;
    Bone **m_orderedBones;
    Array<bool> m_isIKSimulated;
    SkinVertex *m_skinnedVertices;
    btDiscreteDynamicsWorld *m_world;
    UserData *m_userData;
    uint16_t *m_indicesPointer;
    uint16_t *m_edgeIndicesPointer;
    int m_edgeIndicesCount;
    Quaternion m_rotationOffset;
    Color m_edgeColor;
    Vector3 m_positionOffset;
    Vector3 m_lightPosition;
    Error m_error;
    float m_edgeOffset;
    float m_selfShadowDensityCoef;
    bool m_enableSimulation;
    bool m_enableSoftwareSkinning;
    bool m_enableToon;
    bool m_visible;

    VPVL_DISABLE_COPY_AND_ASSIGN(PMDModel)
};

}

#endif
