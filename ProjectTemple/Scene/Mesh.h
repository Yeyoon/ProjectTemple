///////////////////////////////////////////////////////////////
// Filename:	Mesh.h
// Author:		Daniel Cossu
// Company:		Ripe Tomato Studios
///////////////////////////////////////////////////////////////
#ifndef __MESH_H_
#define __MESH_H_

struct ID3D11Buffer;
struct aiMesh;
struct aiScene;

namespace Engine
{
	class Texture;

	class Mesh
	{
	private:
		ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
		int m_vertexCount, m_numFaces;
		Texture *m_diffTexture, *m_specTexture, *m_bumpTexture, *m_alphaTexture;
		
		struct VERTEX
		{
			float px, py, pz; //Position
			float nx, ny, nz; //Normal
			float u, v;		  //Texture
			float tx, ty, tz; //Tangent
			float bx, by, bz; //Binormal
		};

		float m_centerX, m_centerY, m_centerZ;
		float m_sizeX, m_sizeY, m_sizeZ;
	public:
		Mesh(void);
		Mesh(const Mesh &other);
		virtual ~Mesh(void);

		bool Initialize(const aiMesh* mesh, aiScene* scene);
		void Shutdown(void);
		void Render(void);

		//ID3D11ShaderResourceView* GetTexture(void);
		//int GetIndexCount(void);
		int GetVertexCount(void);
		int GetFaceCount(void);
	};
};
#endif