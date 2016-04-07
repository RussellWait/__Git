#pragma once

enum
{
	X, Y, Z, W
};

// vector
typedef float vec2_t[2];
typedef float vec3_t[3];

// quaternion(x, y, z, w)
typedef float quat4_t[4];

// joint
typedef struct
{
	char	name[64];
	int		parent;

	vec3_t	pos;
	quat4_t	orient;
} MD5_Joint_t;

// vertex
typedef struct
{
	vec2_t st;

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

	vec3_t	pos;
} MD5_Weight_t;

// bounding box
typedef struct
{
	vec3_t	min;
	vec3_t	max;
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


int ReadModel(const char *fileName, MD5_Model_t *mdl);
void DrawModel(const MD5_Model_t *mdl);
void FreeModel(MD5_Model_t *mdl);
void PremareMesh(const MD5_Mesh_t *mesh, const MD5_Joint_t *joints);
void AllocVertexArrays(void);
void FreeVertexArrays(void);
