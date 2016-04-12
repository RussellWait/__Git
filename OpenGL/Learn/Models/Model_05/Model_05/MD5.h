#pragma once

enum
{
	X, Y, Z, W
};

// vector
typedef float Vec2_t[2];
typedef float Vec3_t[3];

// quaternion(x, y, z, w)
typedef float Quat4_t[4];

// joint
typedef struct
{
	char	name[64];
	int		parent;

	Vec3_t	pos;
	Quat4_t	orient;
} MD5_Joint_t;

// vertex
typedef struct
{
	Vec2_t st;

	int start;		// start weight
	int	count;		// weight conut
} MD5_Vertex_t;

// triangle
typedef struct
{
	int index[3];
} MD5_Triangle_t;

// weight
typedef struct
{
	int		joint;
	float	bias;

	Vec3_t	pos;
} MD5_Weight_t;

// bounding box
typedef struct
{
	Vec3_t	min;
	Vec3_t	max;
} MD5_BBox_t;

// MD5 mesh
typedef struct
{
	MD5_Vertex_t	*vertices;
	MD5_Triangle_t	*triangles;
	MD5_Weight_t	*weights;

	int				num_verts;
	int				num_tris;
	int				num_weights;

	char			shader[256];
} MD5_Mesh_t;

// MD5 model structure
typedef struct
{
	int	num_joints;
	int num_meshes;

	MD5_Joint_t	*baseSkel;
	MD5_Mesh_t	*meshes;
} MD5_Model_t;

// animation data
typedef struct
{
    int num_frames;
    int num_joints;
    int frameRate;

    MD5_Joint_t **skelFrames;   // ¹Ç÷À¿ò¼ÜÐÅÏ¢
    MD5_BBox_t  *bboxes;
} MD5_Anim_t;

// hierarchy (joint) info
typedef struct
{
    char    name[64];
    int     parent;
    int     flags;
    int     startIndex;
} Joint_Info_t;

// base frame joint
typedef struct
{
    Vec3_t  pos;
    Quat4_t orient;
} BaseFrame_Joint_t;

// animation info
typedef struct
{
    int curr_frame;
    int next_frame;

    double last_time;
    double max_time;
} Anim_Info_t;


// math
void Quat_computeW(Quat4_t q);
void Quat_normalize(Quat4_t q);
void Quat_multQuat(const Quat4_t q1, const Quat4_t q2, Quat4_t out);
void Quat_multVec(const Quat4_t q, const Vec3_t v, Quat4_t out);
void Quat_rotatePoint(const Quat4_t q, const Vec3_t in, Vec3_t out);

// handle static model
int ReadModel(const char *fileName, MD5_Model_t *mdl);
void DrawModel(const MD5_Model_t *mdl);
void FreeModel(MD5_Model_t *mdl);
void PrepareMesh(const MD5_Mesh_t *mesh, const MD5_Joint_t *joints);
void AllocVertexArrays(void);
void FreeVertexArrays(void);

// handle anim model
int ReadAnim(const char *fileName, MD5_Anim_t *anim);
void DrawAnim(MD5_Model_t *mdl, MD5_Anim_t *anim, int skelFrames_index);
void FreeAnim(MD5_Anim_t *anim);
